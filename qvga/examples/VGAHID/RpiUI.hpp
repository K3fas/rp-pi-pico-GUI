#pragma once

#include "IVGA.hpp"
#include "tusb_data.hpp"
#include <vector>

extern int8_t mousePos[];
extern uint8_t mouseKeys[];

namespace UI
{
    using namespace VColors;
    using namespace IVGA;

    constexpr float sensitivity = 2;

    class Drawable
    {
    public:
        virtual void DrawElement() const {}
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
            : position(position), text(text), textColor(textColor), backgroundColor(backgroundColor) {}

        void DrawElement() const
        {
            IVGA::IDrawText(text.c_str(), position, textColor);
        }
    };

    class Cursor : public Drawable
    {
        struct cursor_pos_s
        {
            float x = WIDTH / 2, y = HEIGHT / 2;
        } cursorPos;

    public:
        void DrawElement() const
        {
            IVGA::IDrawLine(Point(cursorPos.x - 2, cursorPos.y), Point(cursorPos.x - 2, cursorPos.y), Color::White);
            IVGA::IDrawLine(Point(cursorPos.x, cursorPos.y - 2), Point(cursorPos.x, cursorPos.y + 2), Color::White);
        }

        // void SetCursor()
        // {
        //     cursorPos.x += mousePos[0] * sensitivity * 0.020;
        //     cursorPos.y += mousePos[1] * sensitivity * 0.020;
        //     if (cursorPos.x > WIDTH)
        //         cursorPos.x = WIDTH;
        //     if (cursorPos.y > HEIGHT)
        //         cursorPos.y = HEIGHT;
        //     if (cursorPos.x < 0)
        //         cursorPos.x = 0;
        //     if (cursorPos.y < 0)
        //         cursorPos.y = 0;
        // }

        // void UpdateCursor()
        // {
        //     if (mousePos[2] == 1)
        //     {
        //         SetCursor();
        //         mousePos[2] = 0;
        //     }
        // }

        // void ProcessLeftClick()
        // {
        //     // Invoke event based on item clicked ?
        // }

        // void ProcessMiddleClick()
        // {
        // }

        // void ProcessRightClick()
        // {
        // }

        // void Clicked()
        //     {
        //         if (mouseKeys[0] == 1)
        //         {
        //             ProcessLeftClick();
        //             mouseKeys[0] = 0;
        //         }
        //         if (mouseKeys[1] == 1)
        //         {
        //             ProcessMiddleClick();
        //             mouseKeys[0] = 0;
        //         }
        //         if (mouseKeys[2] == 1)
        //         {
        //             ProcessRightClick();
        //             mouseKeys[0] = 0;
        //         }
        //     }
    };

    class Rectangle : public Drawable
    {
    public:
        IVGA::Rectangle coords;
        Color color;

        Rectangle() = default;
        Rectangle(IVGA::Rectangle coords, Color color)
            : coords(coords), color(color) {}

        void DrawElement() const
        {
            IVGA::IDrawRectangle(coords, color);
        }
    };

    class View
    {
        std::vector<Drawable *> children;
        inline static std::vector<Drawable *> *toDraw;
        uint8_t numChildren;

    public:
        View()
        {
            children.emplace_back(new Cursor());
        }
        View(std::vector<Drawable *> &children)
            : children(children) {}

        void DrawAll() const
        {
            DrawClear();
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

    private:
        static void DrawFunc()
        {
            DrawClear();
            for (auto &drawable : *toDraw)
            {
                drawable->DrawElement();
            }
        }
    };

} // namespace UI
