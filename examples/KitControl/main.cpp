#include <rpgui.hpp>
#include "Page1.hpp"
#include "Page2.hpp"

using namespace rpgui;

void switchPages();

uint8_t buttons;

type::ID page1Id; 
type::ID page2Id; 

int main()
{

    rpgui::core::MainApp::Init();
    stdio_init_all();

    page1Id = page1::view::CreatePage();
    page2Id = page2::view::CreatePage();

    page1::controller::Init();
    core::MainApp::SelectPageAt(0);

    page2::controller::Init();
    core::MainApp::SelectPageAt(1);

    while (1)
    {
        switchPages();
        if (core::MainApp::GetSelectedPageId() == page1Id)
        {
            page1::controller::Update();
        }
        if (core::MainApp::GetSelectedPageId() == page2Id)
        {
            page2::controller::Update();
        }
        rpgui::core::MainApp::Update();
    }
}

void switchPages()
{

    switch (HID::kbd::pressedKeys[0])
    {
    case 'a':
        page1::controller::Init();
        core::MainApp::SelectPage(page1Id);
        break;
    case 's':
        page2::controller::Init();
        core::MainApp::SelectPage(page2Id);
        break;

    default:
        break;
    }
}
