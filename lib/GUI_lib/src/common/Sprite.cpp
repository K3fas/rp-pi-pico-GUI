#include "Sprite.hpp"
#ifdef PICOVGA

rpgui::common::Sprite::~Sprite()
{
    if(_image.img)
        delete _image.img;
}

rpgui::common::Sprite::Sprite(const uint8_t *image, const uint16_t imageSize, int width, int height, int pitch)
{
    auto imageptr = new ALIGNED u8[imageSize];
    memcpy(imageptr, image, imageSize);
    _image.img = imageptr;
    _image.w = width;
    _image.h = height;
    _image.wb = pitch;
}

void rpgui::common::Sprite::SetFormat(const sCanvas &toMatch)
{
    _image.format = toMatch.format;
}

sCanvas *rpgui::common::Sprite::GetCanvas()
{
    return &_image;
}

#else
rpgui::common::Sprite::Sprite(uint8_t *image, int width, int height, int pitch)
{
}

rpgui::common::Sprite::~Sprite()
{
}

#endif

int rpgui::common::Sprite::GetWidth() const
{
    return _image.w;
}

int rpgui::common::Sprite::GetHeight() const
{
    return _image.h;
}

int rpgui::common::Sprite::GetPitch() const
{
    return _image.wb;
}