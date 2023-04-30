
#include <rpgui.hpp>
#include <vector>
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

    case 'l':
        MainApp::SelectPageAt(8);

        break;

    default:
        break;
    }
}

Page *seedPage(View *el[], uint8_t count, const std::string &name)
{
    auto page = new Page();
    auto lay = new StackLayout(Point(WIDTH / 2 - 64, HEIGHT / 2 - 8), Width(128), Height(120));
    lay->AddElement(new Label("This is a " + name));
    for (size_t i = 0; i < count; i++)
    {
        lay->AddElement(el[i]);
    }

    page->AddLayout(lay);
    return page;
}

Page *seedPage(View *el, const std::string &name)
{
    auto page = new Page();
    auto lay = new StackLayout(Point(WIDTH / 2 - 64, HEIGHT / 2 - 8), Width(128), Height(120));
    lay->AddElement(new Label("This is a " + name));
    lay->AddElement(el);

    page->AddLayout(lay);
    return page;
}

int main()
{
    rpgui::core::init();
    stdio_init_all();

    MainApp::AddPage(seedPage(new Button(Width(64), Height(32), Color::DarkBlue, "Click me !"), "Button"));
    View *box[] = {new CheckBox(Width(64), Height(64), false, Color::DarkBlue), new CheckBox(Width(64), Height(64), true, Color::DarkBlue)};
    auto pline = new Polyline(std::vector<Point>{Point(0, 0), Point(15, 20), Point(35, 10), Point(180, 55), Point(WIDTH / 2, HEIGHT / 2)}, Color::Red);
    View *lines[] = {new Line(Point(10, 10), Point(WIDTH - 10, HEIGHT / 2)), pline};

    MainApp::AddPage(seedPage(box, 2, "CheckBox"));
    MainApp::AddPage(seedPage(new Label("Label", Color::White, Color::Transparent, nullptr, 16), ""));
    MainApp::AddPage(seedPage(lines, 2, "Line and PolyLine"));
    MainApp::AddPage(seedPage(new ProgressBar(Width(64), Height(32), 58.0, 0, 100, Color::SemiGray, Color::DarkBlue), "ProgressBar"));

    auto rbtn = new RadioButton(Width(1), Height(16), Color::DarkBlue);
    rbtn->AddItem("Item 1");
    rbtn->AddItem("Item 2");
    rbtn->AddItem("Item 3");
    MainApp::AddPage(seedPage(rbtn, "RadioButton"));
    MainApp::AddPage(seedPage(new Stepper<int>(Width(64), Height(16), Color::DarkBlue), "Stepper"));
    View *swtchs[] = {new Switch(Width(64), Height(16), false, Color::SemiGray), new Switch(Width(64), Height(16), true, Color::SemiGray)};
    MainApp::AddPage(seedPage(swtchs, 2, "Switch"));
    auto peter = new Sprite("peter8.bmp");
    MainApp::AddPage(seedPage((View *)peter, "Sprite"));

    while (1)
    {
        MainApp::Update();
        switchScreens();
    }
}
