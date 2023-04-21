
#include <rpgui.hpp>
#include <rp_logger.hpp>

#include "settings.hpp"
#include "blue.bmp.h"

using namespace rpgui::type;
using namespace rpgui::common;

int main()
{
    rpgui::core::init();
    printf("RP DEV\r\n");

    auto baloon = Sprite(Blue8Img.image, sizeof(Blue8Img.image), Blue8Img.width, Blue8Img.height, Blue8Img.pitch);
    auto peter = Sprite("peter8.bmp");
    

    while (1)
    {
        // IVGA::IDrawRectangle(Point(0,0),Width(WIDTH), Height(HEIGHT), rpgui::colors::Red);
        IVGA::IDrawImage(baloon, Point(20, 20));
        IVGA::IDrawImage(peter, Point(60,20));
        IVGA::IWaitVSync();
    }
}
