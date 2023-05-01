#include <rpgui.hpp>
#include "speedtest.hpp"
#include "IVGA.hpp"

using namespace rpgui;

static constexpr uint16_t elementCount = 50;
static constexpr uint16_t runs = 100;

void cleanup(common::View **array)
{
    rplog::Logger::logTrace(std::cout, "Cleaning up ");
    for (size_t i = 0; i < elementCount; i++)
    {
        delete array[i];
    }

    IVGA::IDrawClear();
    rpgui::core::MainApp::ClearHandlers();
}

int main(){

    rpgui::core::init();
    stdio_init_all();

    SpeedTester tester("speed_tests.txt");
    common::View *elements[elementCount];

    for (size_t i = 0; i < elementCount; i++)
    {
        elements[i] = new ui::Button(common::Bounds(0, 0, 128, 128), Color::Red, "TEST");
    }
    tester.PerformTest(elements, elementCount, runs, "Button");
    cleanup(elements);

    for (size_t i = 0; i < elementCount; i++)
    {
        elements[i] = new ui::CheckBox(common::Bounds(0, 0, 128, 128), Color::Red, false);
    }

    tester.PerformTest(elements, elementCount, runs, "CheckBox");
    cleanup(elements);

    for (size_t i = 0; i < elementCount; i++)
    {
        elements[i] = new ui::Label("TEST TEXT TEST TEXT TEST TEXT TEST TEXT", Color::Red);
    }

    tester.PerformTest(elements, elementCount, runs, "Label");
    cleanup(elements);

    for (size_t i = 0; i < elementCount; i++)
    {
        elements[i] = new ui::Line(Point(0, 0), Point(WIDTH, HEIGHT), Color::Red);
    }

    tester.PerformTest(elements, elementCount, runs, "Line");
    cleanup(elements);

    for (size_t i = 0; i < elementCount; i++)
    {
        elements[i] = new ui::Polyline({Point(0, 0), Point(WIDTH, HEIGHT)}, Color::Red);
    }

    tester.PerformTest(elements, elementCount, runs, "Polyline");
    cleanup(elements);

    for (size_t i = 0; i < elementCount; i++)
    {
        auto btn =  new ui::RadioButton(Width(128), Height(32), Color::Red);
        btn->AddItem("TEST");
        btn->AddItem("TEST");
        btn->AddItem("TEST");
        btn->AddItem("TEST");
        elements[i] = btn;
    }

    tester.PerformTest(elements, elementCount, runs, "RadioButton, 4 options");
    cleanup(elements);

    

    for (size_t i = 0; i < elementCount; i++)
    {
        elements[i] = new ui::Stepper<int>(Width(128), Height(32), Color::Red);
    }

    tester.PerformTest(elements, elementCount, runs, "Stepper");
    cleanup(elements);

    for (size_t i = 0; i < elementCount; i++)
    {
        elements[i] = new ui::Switch(Width(128), Height(32), false, Color::Red);
    }

    tester.PerformTest(elements, elementCount, runs, "Switch");
    cleanup(elements);

    for (size_t i = 0; i < elementCount; i++)
    {
        elements[i] = new ui::ProgressBar(common::Bounds(0, 0, 128, 128), 50, 0, 100);
    }

    tester.PerformTest(elements, elementCount, runs, "ProgressBar");
    cleanup(elements);

    for (size_t i = 0; i < elementCount; i++)
    {
        elements[i] = new ui::Sprite("peter8.bmp");
    }

    tester.PerformTest(elements, elementCount, runs, "Sprite");
    cleanup(elements);

    auto lbl = new ui::Label("TESTS DONE");

    while (1)
    {
        lbl->Draw();
    }
}