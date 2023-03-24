//
// Created by kefas on 26.2.23.
//

#ifndef PICO_KIT_FRAMEWORK_CORE_HPP
#define PICO_KIT_FRAMEWORK_CORE_HPP

#include "tusb.h"
#include "tusb_data.hpp"

#include "timers.hpp"

#include <vector>

namespace rpgui::core
{
    class Cursor;
}

namespace rpgui::event
{
    class MouseDispatcher;
    class Handler;
}

namespace rpgui::page
{
    class Page;
}

namespace rpgui::type
{
    enum class MouseEventType;
}

using namespace rpgui::page;
using namespace rpgui::event;
using namespace rpgui::type;

extern HID::MOUSE_t MOUSE;

namespace rpgui::core
{
    class MainApp
    {
    private:
        static constexpr float sensitivity = 2.0f;
        static constexpr bool waitVSync = true;

        inline static std::vector<Page *> _pages;
        inline static Page *_selectedPage;

        static enum class clickState {
            none,
            pressed,
        } _clickState;

        static MouseDispatcher _mouseHandler;
        static Cursor _cursor;

        inline static timers_t timers;

    public:
        MainApp() = delete;
        ~MainApp() = delete;

        static void AddPage(Page *page);

        static void Update();

        static void AddListener(MouseEventType type, const Handler &handler);

    private:
        static void drawPage();

        static void processMouseInput();

        static void processMouseMovement();

        static void updateOnCore1();

        static void drawCursor();
    };

} // namespace rpgui::core

#endif // PICO_KIT_FRAMEWORK_CORE_HPP