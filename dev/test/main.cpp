
#include <rpgui.hpp>
#include <rp_logger.hpp>
#include "stdio.h"
#include "pico/stdlib.h"
#include "Timers.hpp"

#include "settings.hpp"
#include "blue.bmp.h"

#define LED1 6
#define LED2 7
#define LED3 8
#define LED4 9

using namespace rpgui::type;
using namespace rpgui::common;
using namespace rpgui::ui;
using namespace rpgui::event;
using namespace rpgui::core;

void LED_init()
{
    gpio_init(LED1);
    gpio_init(LED2);
    gpio_init(LED3);
    gpio_init(LED4);

    gpio_set_dir(LED1, GPIO_OUT);
    gpio_set_dir(LED2, GPIO_OUT);
    gpio_set_dir(LED3, GPIO_OUT);
    gpio_set_dir(LED4, GPIO_OUT);
}

void onClicked(MouseEvent<MouseEventType> &event, Clickable *sender)
{
    auto btn = (Button *)sender;
    if (event.Type() == MouseEventType::Clicked)
    {
        printf("Clicked MouseEvent function called");
    }
    if (btn)
    {
        btn->color = Color::DarkRed;
    }
    event.SetHandled();
}

// int main()
// {
//     rpgui::core::init();
//     stdio_init_all();

//     // Send some data over USB
//     const char *message = "Hello, world!";
//     uart_write_blocking(uart0, (uint8_t *)message, strlen(message));
//     printf("RP DEV\r\n");

//     auto baloon = Sprite(Blue8Img.image, sizeof(Blue8Img.image), Blue8Img.width, Blue8Img.height, Blue8Img.pitch);
//     auto peter = Sprite("peter8.bmp");

//     baloon.SetBounds(Bounds(20, 20, 0, 0));
//     peter.SetBounds(Bounds(60, 20, 0, 0));
//     auto timer = rpgui::util::Timers();
//     timer.AddStamp("Start");
//     timer.AddStamp("End");

//     MouseDispatcher dispatcher;

//     // auto btn = new Button(Width(64), Height(8), Color::Blue);
//     // dispatcher.Subscribe(MouseEventType::Clicked, Handler(onClicked, btn));

//     // auto event1 = MouseEvent<MouseEventType>(MouseEventType::Clicked, Point(30,4));
//     // auto event2 = MouseEvent<MouseEventType>(MouseEventType::Pressed, Point(30,4));
//     // dispatcher.Post(event1);
//     // dispatcher.Post(event2);

//     // struct example_data_t
//     // {
//     //     bool led1, led2;
//     // } data;

//     // auto layout = new StackLayout(Point(10, 10), Width(64), Height(100));

//     // auto switch1 = new Switch(Width(64), Height(8), false, Color::Blue);
//     // layout->AddElement(switch1);
//     // layout->AddElement(new Switch(Width(64), Height(8), data.led2, Color::Blue));

//     // data.led1 = switch1->isSwitched.GetValue();

//     // gpio_put(LED1, data.led1);
//     // gpio_put(LED2, data.led2);

//     while (1)
//     {
//         // IVGA::IDrawRectangle(Point(0,0),Width(WIDTH), Height(HEIGHT), rpgui::colors::Red);
//         timer.Stamp(0);
//         baloon.Draw();
//         peter.Draw();
//         IVGA::IWaitVSync();
//         timer.Stamp(1);
//         timer.PrintStamps();
//     }
// }

int main()
{
    rpgui::core::MainApp::Init();
    stdio_init_all();
    LED_init();

    struct
    {
        bool led[4] {false};
    }leds;

    auto layout = new StackLayout(Point(WIDTH/2-32, HEIGHT/2),Width(64), Height(128));
    layout->AddElement(new Switch(Width(0), Height(16),leds.led[0]));
    layout->AddElement(new Switch(Width(0), Height(16),leds.led[1]));
    layout->AddElement(new Switch(Width(0), Height(16),leds.led[2]));
    layout->AddElement(new Switch(Width(0), Height(16),leds.led[3]));

    MainApp::AddPage(new Page(layout));

    while (1)
    {
        MainApp::Update();
        gpio_put(LED1, leds.led[0]);
        gpio_put(LED2, leds.led[1]);
        gpio_put(LED3, leds.led[2]);
        gpio_put(LED4, leds.led[3]);
    }
}
