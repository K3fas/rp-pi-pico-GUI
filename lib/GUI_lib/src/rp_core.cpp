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

void rpgui::core::MainApp::drawPages()
{
    for (auto &&page : _pages)
    {
        page->Draw();
    }
}

void rpgui::core::MainApp::Update()
{
    updateOnCore1();
}

void rpgui::core::MainApp::AddListener(MouseEventType type, const Handler &handler)
{
    MainApp::_mouseHandler.Subscribe(type, handler);
}

void rpgui::core::MainApp::updateOnCore1()
{
    processMouseInput();
    processMouseMovement();
    if (rpgui::core::MainApp::waitVSync)
    {
        IVGA::IWaitVSync();
    }
    IVGA::IDrawClear();
    drawPages();
    drawCursor();
}

void rpgui::core::MainApp::drawCursor()
{
    MainApp::_cursor.Draw();
}

void rpgui::core::MainApp::processMouseInput()
{
    if (MOUSE.clicked)
    {
        auto event = Event<MouseEventType>(MouseEventType::Clicked, "onClicked");
        auto pos = MainApp::_cursor.GetBounds();
        MainApp::_mouseHandler.Post(event, pos.x, pos.y);
        MOUSE.clicked = !MOUSE.clicked;
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

    MainApp::_cursor.SetBounds(Bounds(MainApp::_cursor.pos.x, MainApp::_cursor.pos.y, 0, 0));

    MOUSE.mousePos[0] = 0;
    MOUSE.mousePos[1] = 0;

    MOUSE.moved = false;
}
