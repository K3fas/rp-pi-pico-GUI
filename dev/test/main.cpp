
#include <rpgui.hpp>
#include <rp_logger.hpp>
#include "stdio.h"
#include "pico/stdlib.h"
#include "Timers.hpp"

#include "settings.hpp"
#include "blue.bmp.h"

using namespace rpgui::type;
using namespace rpgui::common;
using namespace rpgui::ui;

int main()
{
    rpgui::core::init();
    stdio_init_all();
    // Send some data over USB
    const char* message = "Hello, world!";
    uart_write_blocking(uart0, (uint8_t*)message, strlen(message));
    printf("RP DEV\r\n");

    auto baloon = Sprite(Blue8Img.image, sizeof(Blue8Img.image), Blue8Img.width, Blue8Img.height, Blue8Img.pitch);
    auto peter = Sprite("peter8.bmp");

    baloon.SetBounds(Bounds(20,20,0,0));
    peter.SetBounds(Bounds(60,20,0,0));
    auto timer = rpgui::util::Timers();
    timer.AddStamp("Start");
    timer.AddStamp("End");

    while (1)
    {
        // IVGA::IDrawRectangle(Point(0,0),Width(WIDTH), Height(HEIGHT), rpgui::colors::Red);
        timer.Stamp(0);
        baloon.Draw();
        peter.Draw();
        IVGA::IWaitVSync();
        timer.Stamp(1);
        timer.PrintStamps();
    }
}
