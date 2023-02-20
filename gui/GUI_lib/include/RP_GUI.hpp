#pragma once

#include "IVGA.hpp"
#include "tusb_data.hpp"
#include <vector>
#include <map>

extern HID::KBD_t KBD;
extern HID::MOUSE_t MOUSE;

namespace UI
{
	using namespace VColors;
	using namespace IVGA;

	constexpr float sensitivity = 2;

	enum UpdateSettings
	{
		Core0,
		Core1,
	};

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
		bool isClickable = true;
		void (*handler)() = NULL;

		void HandleCLicked()
		{
			if (handler)
				handler();
		}
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
			SetBounds(position, Point{position.x + text.length() * 8, position.y + 8});
		}

		void DrawElement() const
		{
			if (backgroundColor == Color::Tranparent)
			{
				IDrawText(text.c_str(), position, textColor);
			}
			else
			{
				IDrawText(text.c_str(), position, textColor, backgroundColor);
			}
		}
	};

	class Rectangle : public Drawable
	{
	public:
		IVGA::Rectangle coords;
		Color color;

		Rectangle() = default;
		Rectangle(const Rectangle &) = default;
		Rectangle(IVGA::Rectangle coords, Color color)
			: coords(coords), color(color)
		{
			auto end = Point{coords.start.x + coords.width.v, coords.start.y + coords.height.v};
			SetBounds(coords.start, end);
		}

		void DrawElement() const
		{
			IDrawRectangle(coords, color);
		}
	};

	class Circle : public Drawable
	{
	public:
		Radius radius;
		Point center;
		Color color;
		bool isFilled = true;

		Circle() = default;
		Circle(const Circle &) = default;
		Circle(Radius radius, Point center, Color color = Color::White, bool isFilled = true)
			: radius(radius), center(center), color(color), isFilled(isFilled)
		{
			auto start = Point{center.x - radius.v, center.y - radius.v};
			auto end = Point{center.x + radius.v, center.y + radius.v};
			SetBounds(start, end);
		}

		void DrawElement() const
		{
			IDrawCircle(center, radius, color, isFilled);
		}
	};

	class Frame : public Drawable
	{
	public:
		IVGA::Rectangle coords;
		Color color;
		uint8_t borderSize = 2;

		Frame() = default;
		Frame(const Frame &) = default;
		Frame(IVGA::Rectangle coords, Color color, uint8_t borderSize = 2)
			: coords(coords), color(color), borderSize(borderSize)
		{
			auto end = Point{coords.start.x + coords.width.v, coords.start.y + coords.height.v};
			SetBounds(coords.start, end);
		}

		void DrawElement() const
		{
			for (uint8_t i = 0; i < borderSize; i++)
			{
				IDrawFrame(coords - i, color);
			}
		}
	};

	class Indicator : public Circle
	{
	public:
		bool *value;
		Color colorOff = Color::Red;

		Indicator() = default;
		Indicator(Radius radius, Point center, bool *value, Color colorOn = Color::Green, Color colorOff = Color::Red)
			: Circle(radius, center, colorOn, true), value(value), colorOff(colorOff) {}

		void DrawElement() const
		{
			if (value)
			{
				if (*value == true)
					IDrawCircle(center, radius, color, true);

				else
					IDrawCircle(center, radius, colorOff, true);
			}
		}
	};

	class Button : public Clickable
	{
	public:
		IVGA::Rectangle coords;
		Color color;

		Button() = default;
		Button(const Button &) = default;
		Button(IVGA::Rectangle coords, Color color)
			: coords(coords), color(color)
		{
			auto end = Point{coords.start.x + coords.width.v, coords.start.y + coords.height.v};
			SetBounds(coords.start, end);
		}

		Button(IVGA::Rectangle coords, Color color, void (*handler)())
			: Button(coords, color)
		{
			this->handler = handler;
		}

		void DrawElement() const
		{
			IDrawRectangle(coords, color);
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
		inline static uint8_t viewCount = 0;
		const uint8_t id;
		uint8_t childrenCount;
		std::vector<Drawable *> children;
		std::vector<Clickable *> listeners;
		inline static std::vector<Drawable *> *toDraw;

	public:
		View() : id(viewCount++) {}
		View(std::vector<Drawable *> &children)
			: children(children), id(viewCount++) {}

		void DrawAll() const
		{
			for (auto &drawable : this->children)
			{
				drawable->DrawElement();
			}
		}

		void PrepareDraw()
		{
			toDraw = &children;
		}

		static void DrawToDraw()
		{
			for (auto &drawable : *toDraw)
			{
				drawable->DrawElement();
			}
		}

		void AddElement(Drawable *element)
		{
			children.emplace_back(element);
			++childrenCount;
		}
		void AddElement(Clickable *element)
		{
			children.emplace_back(element);
			++childrenCount;

			listeners.emplace_back(element);
		}

		std::vector<Clickable *> &GetListeners() { return listeners; }

	private:
	};

	class MainView
	{
		class Cursor : public Drawable
		{
			struct cursor_pos_t
			{
				float x, y;
				cursor_pos_t()
					: x(WIDTH / 2), y(HEIGHT / 2) {}
			} cursorPos;

		public:
			Cursor() = default;

			void DrawElement() const
			{
				IDrawLine(Point(cursorPos.x - 2, cursorPos.y), Point(cursorPos.x + 2, cursorPos.y), Color::White);
				IDrawLine(Point(cursorPos.x, cursorPos.y - 2), Point(cursorPos.x, cursorPos.y + 2), Color::White);
			}

			void HandleCursor()
			{
				CheckMoved();
				CheckClicked();
			}

		private:
			void ProcessLeftClick()
			{
				auto &listeners = MainView::GetListeners();
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

				MOUSE.mousePos[0] = 0;
				MOUSE.mousePos[1] = 0;
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

		const UpdateSettings settings;
		std::vector<View> views;
		static inline Cursor cursor;
		static inline View *currentView;

	public:
		MainView(UpdateSettings settings)
			: settings(settings)
		{
		}

		void SetCurrentView(View &view)
		{
			currentView = &view;
			Update();
		}
		void InsertView(View view)
		{
			views.emplace_back(view);
		}

		View &GetCurrentView() const { return *currentView; }
		std::vector<View> &GetViews() { return views; }
		static std::vector<Clickable *> &GetListeners() { return currentView->GetListeners(); }

		void Update()
		{

			if (settings == UpdateSettings::Core0)
			{
				cursor.HandleCursor();
				DrawClear();
				Render();
				cursor.DrawElement();
			}
			else
			{
				currentView->PrepareDraw();
				ICore1Exec(RenderOnCore1);
			}
		}

	private:
		void Render() { currentView->DrawAll(); }
		static void RenderOnCore1()
		{
			cursor.DrawElement();
			cursor.HandleCursor();
			DrawClear();
			currentView->DrawToDraw();
			cursor.DrawElement();
		}
	};
} // namespace UI
