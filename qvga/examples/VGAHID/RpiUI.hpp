#pragma once

#include "IVGA.hpp"
#include "tusb_data.hpp"
#include <vector>

extern HID::KBD_t KBD;
extern HID::MOUSE_t MOUSE;

namespace UI
{
	using namespace VColors;
	using namespace IVGA;

	constexpr float sensitivity = 2;

	class Cursor;

	class Drawable
	{
		struct Boundaries
		{
			Point start, end;

			Boundaries() = default;
			Boundaries(const Boundaries &b) = default;
			Boundaries(Point &start, Point &end)
				: start(start), end(end) {}
		} boundaries;

	public:
		Drawable() = default;
		Drawable(const Drawable &) = default;
		Drawable(Point &start, Point &end)
			: boundaries(start, end) {}

		virtual void DrawElement() const {}
		const Boundaries &GetBounds() const { return boundaries; };
		void SetBounds(const Point &start, const Point &end)
		{
			boundaries.start = start;
			boundaries.end = end;
		}
	};

	class Clickable : public Drawable
	{
	public:
		bool isClickable = false;
		void (*handler)() = NULL;

		void HandleCLicked() { handler(); }
	};

	class Label : public Drawable
	{
	public:
		Point position;
		std::string text;
		VColors::Color textColor;
		VColors::Color backgroundColor;

		Label() = default;
		Label(std::string text, Point position, VColors::Color textColor = VColors::Color::White, VColors::Color backgroundColor = VColors::Color::Black)
			: position(position), text(text), textColor(textColor), backgroundColor(backgroundColor)
		{
			// TODO: Calculate end bound of text
			SetBounds(position, position);
		}

		void DrawElement() const
		{
			IVGA::IDrawText(text.c_str(), position, textColor);
		}
	};

	class Rectangle : public Clickable
	{
	public:
		IVGA::Rectangle coords;
		Color color;

		Rectangle() = default;

		Rectangle(IVGA::Rectangle coords, Color color)
			: coords(coords), color(color)
		{
			auto end = Point{coords.start.x + coords.width.v, coords.start.y + coords.height.v};
			SetBounds(coords.start, end);
		}

		void DrawElement() const
		{
			IVGA::IDrawRectangle(coords, color);
		}

		void HandleClicked()
		{
			if (isClickable)
			{
				if (handler != NULL)
					handler();
			}
		}
	};

	class View
	{
		std::vector<Drawable *> children;
		std::vector<Clickable *> listeners;
		inline static std::vector<Drawable *> *toDraw;
		uint8_t numChildren;

	public:
		View()
		{
		}
		View(std::vector<Drawable *> &children)
			: children(children) {}

		void DrawAll() const
		{
			for (auto &drawable : this->children)
			{
				drawable->DrawElement();
			}
		}

		void DrawOnCore1()
		{
			toDraw = &children;
			ICore1Exec(DrawFunc);
		}

		void AddElement(Drawable *element)
		{
			children.emplace_back(element);
			++numChildren;
		}
		void AddElement(Clickable *element)
		{
			children.emplace_back(element);
			++numChildren;

			listeners.emplace_back(element);
		}

		std::vector<Clickable *> &GetListeners() { return listeners; }

	private:
		static void DrawFunc()
		{
			for (auto &drawable : *toDraw)
			{
				drawable->DrawElement();
			}
		}
	};

	class MainView
	{
		class Cursor : public Drawable
		{
			MainView &mainView;
			struct cursor_pos_t
			{
				float x = WIDTH / 2, y = HEIGHT / 2;
			} cursorPos;

		public:
			Cursor(MainView &view)
				: mainView(view) {}

			void DrawElement() const
			{
				IDrawLine(Point(cursorPos.x - 2, cursorPos.y), Point(cursorPos.x - 2, cursorPos.y), Color::White);
				IDrawLine(Point(cursorPos.x, cursorPos.y - 2), Point(cursorPos.x, cursorPos.y + 2), Color::White);
			}

			void HandleCursor()
			{
				CheckMoved();
				CheckClicked();
			}

		private:
			void HandleCursorPos()
			{
				cursorPos.x += MOUSE.mousePos[0] * sensitivity * 0.020;
				cursorPos.y += MOUSE.mousePos[1] * sensitivity * 0.020;
				if (cursorPos.x > WIDTH)
					cursorPos.x = WIDTH;
				if (cursorPos.y > HEIGHT)
					cursorPos.y = HEIGHT;
				if (cursorPos.x < 0)
					cursorPos.x = 0;
				if (cursorPos.y < 0)
					cursorPos.y = 0;
			}

			void ProcessLeftClick()
			{
				auto &listeners = mainView.GetCurrentView().GetListeners();
				for (auto &listener : listeners)
				{
					if (IsInBounds(*listener))
						listener->HandleCLicked();
				}
			}

			void ProcessMiddleClick()
			{
			}

			void ProcessRightClick()
			{
			}

			void HandleClicked()
			{
				if (MOUSE.mouseKeys[0] == 1)
				{
					ProcessLeftClick();
					MOUSE.mouseKeys[0] = 0;
				}
				if (MOUSE.mouseKeys[1] == 1)
				{
					ProcessMiddleClick();
					MOUSE.mouseKeys[0] = 0;
				}
				if (MOUSE.mouseKeys[2] == 1)
				{
					ProcessRightClick();
					MOUSE.mouseKeys[0] = 0;
				}
			}

			void CheckMoved()
			{
				if (MOUSE.moved == true)
				{
					HandleCursorPos();
					MOUSE.moved = false;
				}
			}

			void CheckClicked()
			{
				if (MOUSE.clicked == true)
				{
					HandleClicked();
					MOUSE.clicked = false;
				}
			}

			bool IsInBounds(const Clickable &item)
			{
				auto bounds = item.GetBounds();

				if (!(cursorPos.x > bounds.start.x && cursorPos.x < bounds.end.x))
					return false;
				if (!(cursorPos.y > bounds.start.y && cursorPos.y < bounds.end.y))
					return false;
				return true;
			}
		};

		std::vector<View> views;
		Cursor cursor;
		View *currentView;
		const bool drawOnCore1;

	public:
		MainView(bool drawOnCore1)
			: drawOnCore1(drawOnCore1), cursor(Cursor(*this))
		{
		}

		void SetCurrentView(View &view) { currentView = &view; }
		View &GetCurrentView() const { return *currentView; }
		void Update()
		{
			DrawClear();
			cursor.HandleCursor();
			if (drawOnCore1)
				RenderOnCore1();
			else
				Render();
			cursor.DrawElement();
		}

	private:
		void Render() { currentView->DrawAll(); }
		void RenderOnCore1() { currentView->DrawOnCore1(); }
	};
} // namespace UI
