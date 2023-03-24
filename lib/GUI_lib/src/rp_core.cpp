//
// Created by kefas on 26.2.23.
//

#include "rp_core.hpp"

#include "IVGA.hpp"
#include "Page.hpp"
#include "MouseDispatcher.hpp"
#include "Cursor.hpp"
#include "Types.hpp"


using namespace rpgui::core;

MouseDispatcher MainApp::_mouseHandler;
Cursor MainApp::_cursor;
MainApp::clickState MainApp::_clickState;


void rpgui::core::MainApp::drawPage()
{
    _selectedPage->Draw();
}

void rpgui::core::MainApp::AddPage(Page *page)
{
    if(page == nullptr)
        return;
    
    if (_selectedPage == nullptr)
    {
        _selectedPage = page;
    }

    _pages.push_back(page);
}

void rpgui::core::MainApp::Update()
{
    IVGA::ICore1Exec(updateOnCore1);
}

void rpgui::core::MainApp::AddListener(MouseEventType type, const Handler &handler)
{
    MainApp::_mouseHandler.Subscribe(type, handler);
}

void rpgui::core::MainApp::updateOnCore1()
{
    //IVGA::IDrawClear();
    //MainApp::timers.core1.start = time_us_32();
    processMouseInput();
    processMouseMovement();
    drawCursor();
    //MainApp::timers.core1.tusb = time_us_32() -MainApp::timers.core1.start;
    drawPage();
    drawCursor();
    
    //MainApp::timers.core1.draw = time_us_32() -MainApp::timers.core1.start;
    if (rpgui::core::MainApp::waitVSync)
    {
        IVGA::IWaitVSync();
    }
    //MainApp::timers.core1.VSync = time_us_32() -MainApp::timers.core1.start;
    //MainApp::timers.Print();
}

void rpgui::core::MainApp::drawCursor()
{
    MainApp::_cursor.Draw();
}

void rpgui::core::MainApp::processMouseInput()
{
    // lmb only
    // handle new pressed key
    if (MOUSE.mouseKeys[0] == true && MainApp::_clickState == MainApp::clickState::none)
    {
        MainApp::_clickState = MainApp::clickState::pressed;

        auto pos = _cursor.GetBounds();
        auto event = MouseEvent<MouseEventType>(MouseEventType::Pressed, pos.x,pos.y);
        MainApp::_mouseHandler.Post(event);
    }

    // handle released key
    if (MOUSE.mouseKeys[0] == false && MainApp::_clickState == MainApp::clickState::pressed)
    {
        MainApp::_clickState = MainApp::clickState::none;

        auto pos = _cursor.GetBounds();
        auto eReleased = MouseEvent<MouseEventType>(MouseEventType::Released, pos.x, pos.y);
        auto eClicked = MouseEvent<MouseEventType>(MouseEventType::Clicked, pos.x, pos.y);
        MainApp::_mouseHandler.Post(eReleased);
        MainApp::_mouseHandler.Post(eClicked);
    }
}

void rpgui::core::MainApp::processMouseMovement()
{
    if (!MOUSE.moved)
        return;
    MainApp::_cursor.pos.x += MOUSE.mousePos[0] * sensitivity * 0.020;
    MainApp::_cursor.pos.y += MOUSE.mousePos[1] * sensitivity * 0.020;

    if (MainApp::_cursor.pos.x > WIDTH)
        MainApp::_cursor.pos.x = WIDTH;
    if (MainApp::_cursor.pos.y > HEIGHT)
        MainApp::_cursor.pos.y = HEIGHT;
    if (MainApp::_cursor.pos.x < 0)
        MainApp::_cursor.pos.x = 0;
    if (MainApp::_cursor.pos.y < 0)
        MainApp::_cursor.pos.y = 0;

    MainApp::_cursor.SetBounds(Bounds(MainApp::_cursor.pos.x, MainApp::_cursor.pos.y, _cursor.size*2+1, _cursor.size*2+1));

    MOUSE.mousePos[0] = 0;
    MOUSE.mousePos[1] = 0;

    MOUSE.moved = false;
}
