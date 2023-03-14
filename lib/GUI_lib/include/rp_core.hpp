//
// Created by kefas on 26.2.23.
//

#ifndef PICO_KIT_FRAMEWORK_CORE_HPP
#define PICO_KIT_FRAMEWORK_CORE_HPP

#include "include.hpp"
#include "Page.hpp"
#include "MouseEvent.hpp"
#include "MouseDispatcher.hpp"

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
        static constexpr bool waitVSync = true;

        inline static std::vector<Page *> _pages;
        inline static MouseDispatcher _mouseHandler;
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
                MOUSE.clicked = !MOUSE.clicked;
            }
        }

        static void ProcessMouseMovement()
        {
            if (!MOUSE.moved)
                return;

            cursorPos.x += MOUSE.mousePos[0] * sensitivity * 0.020;
            cursorPos.y += MOUSE.mousePos[1] * sensitivity * 0.020;
            // TODO CHANGE THIS !
            if (cursorPos.x > 512)
                cursorPos.x = 512;
            if (cursorPos.y > 400)
                cursorPos.y = 512;
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
            _pages.push_back(page);
        }

        static void Update();

        static void AddListener(MouseEventType type, const Handler& handler)
        {
            _mouseHandler.Subscribe(type, handler);
        }

    private:
        static void updateOnCore1();
    };

} // namespace rpgui::core

#endif // PICO_KIT_FRAMEWORK_CORE_HPP