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
    auto pos = MainApp::_cursor.GetBounds();
    pos.x += MOUSE.mousePos[0] * sensitivity * 0.020;
    pos.y += MOUSE.mousePos[1] * sensitivity * 0.020;

    if (pos.x > WIDTH)
        pos.x = WIDTH;
    if (pos.y > HEIGHT)
        pos.y = HEIGHT;
    if (pos.x < 0)
        pos.x = 0;
    if (pos.y < 0)
        pos.y = 0;

    MainApp::_cursor.SetBounds(pos);

    MOUSE.mousePos[0] = 0;
    MOUSE.mousePos[1] = 0;

    MOUSE.moved = false;
}
