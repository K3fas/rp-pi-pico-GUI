//
// Created by kefas on 26.2.23.
//

#include "rp_core.hpp"

#include "IVGA.hpp"
#include "settings.hpp"
#include "Page.hpp"
#include "MouseDispatcher.hpp"
#include "Cursor.hpp"

using namespace rpgui::core;

MouseDispatcher MainApp::_mouseHandler;
Cursor MainApp::_cursor;
MainApp::clickState MainApp::_clickState;

extern void hid_app_task(void);

void rpgui::core::init()
{
    IVGA::init();
}

void rpgui::core::MainApp::drawPage()
{
    _selectedPage->Draw();
}

ID rpgui::core::MainApp::AddPage(Page *page)
{
    if (page == nullptr)
        return 0;

    if (_selectedPage == nullptr)
    {
        _selectedPage = page;
    }

    _pages.push_back(page);
    return page->GetId();
}

void rpgui::core::MainApp::SelectPage(ID id)
{
    for (auto &&page : _pages)
    {
        if(page->GetId() == id)
        {
            _selectedPage = page;
            return ;
        }
    }
}

void rpgui::core::MainApp::Update()
{
    tuh_task();
    hid_app_task();
    if (drawOnCore1)
    {
        IVGA::ICore1Exec(updateOnCoreX);
    }
    else
    {
        updateOnCoreX();
    }
}

void rpgui::core::MainApp::AddListener(MouseEventType type, const Handler &handler, const uint8_t priority)
{
    MainApp::_mouseHandler.Subscribe(type, handler, priority);
}

void rpgui::core::MainApp::updateOnCoreX()
{
    // IVGA::IDrawClear();
    // MainApp::timers.core1.start = time_us_32();
    processMouseInput();
    processMouseMovement();
    drawCursor();
    // MainApp::timers.core1.tusb = time_us_32() -MainApp::timers.core1.start;
    drawPage();
    drawCursor();

    // MainApp::timers.core1.draw = time_us_32() -MainApp::timers.core1.start;
    if (waitVSync)
    {
        IVGA::IWaitVSync();
    }
    // MainApp::timers.core1.VSync = time_us_32() -MainApp::timers.core1.start;
    // MainApp::timers.Print();
}

void rpgui::core::MainApp::drawCursor()
{
    MainApp::_cursor.Draw();
}

void rpgui::core::MainApp::processMouseInput()
{
    // lmb only
    // handle new pressed key
    if (HID::mouse.mouseKeys[0] == true && MainApp::_clickState == MainApp::clickState::none)
    {
        MainApp::_clickState = MainApp::clickState::pressed;

        auto pos = _cursor.GetBounds();
        auto event = MouseEvent<MouseEventType>(MouseEventType::Pressed, Point(pos.x, pos.y));
        MainApp::_mouseHandler.Post(event);
    }

    // handle released key
    if (HID::mouse.mouseKeys[0] == false && MainApp::_clickState == MainApp::clickState::pressed)
    {
        MainApp::_clickState = MainApp::clickState::none;

        auto pos = _cursor.GetBounds();
        auto eReleased = MouseEvent<MouseEventType>(MouseEventType::Released, Point(pos.x, pos.y));
        auto eClicked = MouseEvent<MouseEventType>(MouseEventType::Clicked, Point(pos.x, pos.y)); 
        MainApp::_mouseHandler.Post(eReleased);
        MainApp::_mouseHandler.Post(eClicked);
    }
}

void rpgui::core::MainApp::processMouseMovement()
{
    if (!HID::mouse.moved)
        return;
    MainApp::_cursor.pos.x += HID::mouse.mousePos[0] * sensitivity * 0.020;
    MainApp::_cursor.pos.y += HID::mouse.mousePos[1] * sensitivity * 0.020;

    if (MainApp::_cursor.pos.x > WIDTH)
        MainApp::_cursor.pos.x = WIDTH;
    if (MainApp::_cursor.pos.y > HEIGHT)
        MainApp::_cursor.pos.y = HEIGHT;
    if (MainApp::_cursor.pos.x < 0)
        MainApp::_cursor.pos.x = 0;
    if (MainApp::_cursor.pos.y < 0)
        MainApp::_cursor.pos.y = 0;

    MainApp::_cursor.SetBounds(Bounds(MainApp::_cursor.pos.x, MainApp::_cursor.pos.y, cursorSize * 2 + 1, cursorSize * 2 + 1));

    HID::mouse.mousePos[0] = 0;
    HID::mouse.mousePos[1] = 0;

    HID::mouse.moved = false;
}
