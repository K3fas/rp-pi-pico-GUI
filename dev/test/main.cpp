
#include <rpgui.hpp>
#include <rp_logger.hpp>

#include "settings.hpp"
#include "blue.bmp.h"

using namespace rpgui::type;
using namespace rpgui::common;
using namespace rpgui::ui;

int main()
{
    stdio_init_all();
    rpgui::core::init();
    printf("RP DEV\r\n");

    auto baloon = Sprite(Blue8Img.image, sizeof(Blue8Img.image), Blue8Img.width, Blue8Img.height, Blue8Img.pitch);
    auto peter = Sprite("peter8.bmp");

    baloon.SetBounds(Bounds(20,20,0,0));
    peter.SetBounds(Bounds(60,20,0,0));
    

    while (1)
    {
        // IVGA::IDrawRectangle(Point(0,0),Width(WIDTH), Height(HEIGHT), rpgui::colors::Red);
        baloon.Draw();
        peter.Draw();
        IVGA::IWaitVSync();
    }
}
