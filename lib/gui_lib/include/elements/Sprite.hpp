#pragma once
#include "include.hpp"
#include <string>
#include "ff.h"

#ifdef PICOVGA
#include "global.h"
#endif
 


using namespace rpgui::common;

namespace rpgui::ui
{
    class Sprite : public VisualElement
    {
    private:
        uint8_t* _image;
        uint16_t _size;
        uint16_t _width;
        uint16_t _height;
        uint16_t _pitch;

    public:
        Sprite() = delete;
        Sprite(const Sprite &) = delete;
        ~Sprite();

        Sprite(const uint8_t *image, const uint16_t imageSize, int width, int height, int pitch);
        Sprite(const std::string& name, const std::string& path = "");

        void Draw() const final;

#ifdef PICOVGA
        sCanvas GetCanvas(const sCanvas& toMatch) const;
#endif

        const uint8_t* GetImage() const;
        int GetWidth() const;
        int GetHeight() const;
        int GetPitch() const;

        private:
        void loadData(FIL* file);
    };

} // namespace rpgui::common
