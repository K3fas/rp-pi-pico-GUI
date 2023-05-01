#pragma once
#include "include.hpp"
#include <string>
#include <map>
#include "ff.h"

#ifdef PICOVGA
#include "global.h"
#endif

using namespace rpgui::common;
using namespace rpgui::type;

namespace rpgui::ui
{

    class Sprite : public View
    {
    private:
        inline static std::map<const std::string, sprite_data> _sprites;
        sprite_data _sprite;

    public:
        Sprite() = delete;
        Sprite(const Sprite &) = delete;
        ~Sprite();

        Sprite(const uint8_t *image, const uint16_t imageSize, int width, int height, int pitch);
        Sprite(const std::string &name, const std::string &path = "");

        void Draw() const final;

#ifdef PICOVGA
        sCanvas GetCanvas(const sCanvas &toMatch) const;
#endif

        const uint8_t *GetImage() const;
        int GetWidth() const;
        int GetHeight() const;
        int GetPitch() const;

    private:
        sprite_data loadData(FIL *file);
    };

} // namespace rpgui::common
