#pragma once

#include "Types.hpp"
#include "Sprite.hpp"
#include <string>

using namespace rpgui::common;

namespace rpgui::util
{
}
    
    Sprite* GenerateSprite(Sprite* sprite, const std::string &fileName, const std::string &path);

} // namespace rpgui::util
