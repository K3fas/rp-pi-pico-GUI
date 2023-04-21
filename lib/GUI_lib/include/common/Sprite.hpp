#pragma once
#include "Types.hpp"

#ifdef PICOVGA
#include "global.h"
#endif

namespace rpgui::common
{
    class Sprite
    {
    private:
#ifdef PICOVGA
        sCanvas _image;
#endif

    public:
        Sprite() = delete;
        Sprite(const Sprite &) = delete;
        ~Sprite();

        Sprite(const uint8_t *image, const uint16_t imageSize, int width, int height, int pitch);

#ifdef PICOVGA
        sCanvas *GetCanvas();
        void SetFormat(const sCanvas &toMatch);
#endif

        int GetWidth() const;
        int GetHeight() const;
        int GetPitch() const;
    };

} // namespace rpgui::common
