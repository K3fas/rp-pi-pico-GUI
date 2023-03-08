//
// Created by kefas on 26.2.23.
//

#ifndef PICO_KIT_FRAMEWORK_CORE_HPP
#define PICO_KIT_FRAMEWORK_CORE_HPP

#include "include.hpp"
#include "pages/Page.hpp"
#include "events/MouseEvent.hpp"
#include "events/Dispatcher.hpp"

#include "tusb.h"
#include "tusb_data.hpp"

#include <vector>

using namespace rpgui::page;
using namespace rpgui::event;

extern HID::MOUSE_t MOUSE;

namespace rpgui::core
{

    class MainApp
    {
    private:
        static constexpr float sensitivity = 2.0f;

        inline static std::vector<Page *> _pages;
        inline static Dispatcher<MouseEventType> _mouseHandler;
        inline static struct events_s
        {
            inline static MouseEvent pressed = MouseEvent(MouseEventType::Pressed, "onPressedEvent");
            inline static MouseEvent released = MouseEvent(MouseEventType::Released, "onReleasedEvent");
            inline static MouseEvent clicked = MouseEvent(MouseEventType::Clicked, "onClickedEvent");
        } _events;

        inline static struct cursor_pos_t
        {
            float x, y;
            cursor_pos_t()
                : x(0), y(0) {}
        } cursorPos;

    private:
        static void DrawPages()
        {
            for (auto &&page : _pages)
            {
                page->Draw();
            }
        }

        static void ProcessMouseInput()
        {
            if (MOUSE.clicked)
            {
                _mouseHandler.Post(_events.clicked);
            }
        }

        static void ProcessMouseMovement()
        {
            if (!MOUSE.moved)
                return;

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

    public:
        MainApp() = delete;
        ~MainApp() = delete;

        static void AddPage(Page *page)
        {
            _pages.emplace_back(page);
        }

        static void Update()
        {
            ProcessMouseInput();
            ProcessMouseMovement();
            DrawPages();
        }

        template <typename T>
        static void AddListener(T type, const rpgui::event::SlotType<T> &function)
        {
            _mouseHandler.Subscribe(type, function);
        }
    };

} // namespace rpgui::core

#endif // PICO_KIT_FRAMEWORK_CORE_HPP