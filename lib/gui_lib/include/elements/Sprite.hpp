#pragma once
#include "include.hpp"
#include "SpriteData.hpp"
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

    class Sprite : public VisualElement
    {
    private:
        inline static std::map<const std::string, SpriteData> _sprites;
        SpriteData _sprite;

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
        SpriteData loadData(FIL *file);
    };

} // namespace rpgui::common
