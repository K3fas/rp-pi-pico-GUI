//
// Created by kefas on 26.2.23.
//

#ifndef PICO_KIT_FRAMEWORK_CORE_HPP
#define PICO_KIT_FRAMEWORK_CORE_HPP

#include "tusb.h"
#include "tusb_data.hpp"
#include "Types.hpp"

#include "Timers.hpp"

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

namespace rpgui::core
{

    class MainApp
    {
    private:
        inline static std::vector<Page *> _pages;
        inline static Page *_selectedPage;

        static enum class clickState {
            none,
            pressed,
        } _clickState;

        static MouseDispatcher _mouseHandler;
        static Cursor _cursor;

    public:
        MainApp() = delete;
        MainApp(const MainApp&) = delete;
        ~MainApp() = delete;

        static void Init();

        static ID AddPage(Page *page);

        static void SelectPage(ID id);

        static void SelectPageAt(uint8_t at);

        static ID GetSelectedPageId();

        static ID GetSelectedPageAt();

        static void Update();

        static void AddListener(MouseEventType type, const Handler &handler, const uint8_t priority = 0);

        // Used for testing
        static void ClearHandlers();

    private:
        static void drawPage();

        static void processMouseInput();

        static void processMouseMovement();

        static void updateOnCoreX();

        static void drawCursor();
    };

} // namespace rpgui::core

#endif // PICO_KIT_FRAMEWORK_CORE_HPP