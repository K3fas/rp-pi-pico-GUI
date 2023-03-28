#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#include "bsp/board.h"
#include "tusb.h"

#include <rpgui.hpp>

using namespace rpgui::ui;
using namespace rpgui::common;
using namespace rpgui::type;
using namespace rpgui::colors;

Page *InitPage();

void AddPages();

#define LED1 6
#define LED2 7
#define LED3 8
#define LED4 9

struct
{
    bool led1 = false;
    bool led2 = false;
    bool led3 = false;
    bool led4 = false;

} page;

int main()
{

    board_init();
    tusb_init();

    gpio_init(LED1);
    gpio_init(LED2);
    gpio_init(LED3);
    gpio_init(LED4);

    gpio_set_dir(LED1, GPIO_OUT);
    gpio_set_dir(LED2, GPIO_OUT);
    gpio_set_dir(LED3, GPIO_OUT);
    gpio_set_dir(LED4, GPIO_OUT);

    AddPages();

    while (1)
    {
        gpio_put(LED1, page.led1);
        gpio_put(LED2, page.led2);
        gpio_put(LED3, page.led3);
        gpio_put(LED4, page.led4);

        rpgui::core::MainApp::Update();
    }
}

Page *InitPage()
{
    auto ret = new rpgui::page::Page();
    auto lay1 = new rpgui::layout::StackLayout(Point(10, 10), Width(40), Height(200));
    lay1->AddElement(new Label("LEDs:"));
    lay1->AddElement(new Switch(Width(0), Height(10), page.led1));
    lay1->AddElement(new Switch(Width(0), Height(10), page.led2));
    lay1->AddElement(new Switch(Width(0), Height(10), page.led3));
    lay1->AddElement(new Switch(Width(0), Height(10), page.led4));

    ret->AddLayout(lay1);
    return ret;
}

void AddPages()
{
    rpgui::core::MainApp::AddPage(InitPage());
}
