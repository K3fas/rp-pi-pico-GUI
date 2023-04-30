
#include <rpgui.hpp>
#include <rp_logger.hpp>
#include "stdio.h"
#include "pico/stdlib.h"
#include "Timers.hpp"

#include "settings.hpp"

#include "tusb_data.hpp"

using namespace rpgui::type;
using namespace rpgui::common;
using namespace rpgui::ui;
using namespace rpgui::event;
using namespace rpgui::core;

void switchScreens()
{
    switch (HID::kbd::pressedKeys[0])
    {
    case 'a':
        MainApp::SelectPageAt(0);
        break;
    case 's':
        MainApp::SelectPageAt(1);
        break;
    case 'd':
        MainApp::SelectPageAt(2);

        break;
    case 'f':
        MainApp::SelectPageAt(3);

        break;
    case 'g':
        MainApp::SelectPageAt(4);

        break;
    case 'h':
        MainApp::SelectPageAt(5);

        break;
    case 'j':
        MainApp::SelectPageAt(6);

        break;
    case 'k':
        MainApp::SelectPageAt(7);

        break;

    default:
        break;
    }
}

Page *seedPage(View *el)
{
    auto page = new Page();
    auto lay = new StackLayout(Point(WIDTH / 2 - 64, HEIGHT / 2 - 8), Width(128), Height(120));
    lay->AddElement(el);
    page->AddLayout(lay);
    return page;
}

int main()
{
    rpgui::core::init();
    stdio_init_all();

    MainApp::AddPage(seedPage(new Button(Width(64), Height(16), Color::Magenta, "Click me !")));
    MainApp::AddPage(seedPage(new CheckBox(Width(64), Height(16), false, Color::Magenta)));
    MainApp::AddPage(seedPage(new Label("Im a Label", Color::White, Color::Transparent, nullptr, 16)));
    MainApp::AddPage(seedPage(new Line(Point(10, 10), Point(WIDTH - 10, HEIGHT / 2))));
    MainApp::AddPage(seedPage(new Line(Point(10, 10), Point(WIDTH - 10, HEIGHT / 2))));
    MainApp::AddPage(seedPage(new ProgressBar(Width(64), Height(16),58.0,0,100, Color::SemiGray, Color::Magenta)));

    
    

    while (1)
    {
        MainApp::Update();
        switchScreens();
    }
}
