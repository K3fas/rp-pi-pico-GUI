
#include <rpgui.hpp>
#include <rp_logger.hpp>

#include "settings.hpp"
#include "blue.bmp.h"

using namespace rpgui::type;
using namespace rpgui::common;

int main()
{
    rpgui::core::init();

    auto baloon = Sprite(Blue8Img.image, sizeof(Blue8Img.image), Blue8Img.width, Blue8Img.height, Blue8Img.pitch);
    {
        auto logger = rplog::Logger();
        logger.AddFile("wrapperTest.txt");
        // logger.AddSink(std::cout);
        logger.Log("Wrapper testing", rplog::Level::CRITICAL);
        logger.DisposeSD();
    }

    printf("RP DEV\r\n");
    sleep_ms(2000);

    while (1)
    {
        IVGA::IDrawRectangle(Point(0,0),Width(WIDTH), Height(HEIGHT), rpgui::colors::Red);
        //IVGA::IDrawImage(baloon, Point(20, 20));
        IVGA::IWaitVSync();
    }
}
