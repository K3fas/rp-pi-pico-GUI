#include "Sprite.hpp"
#include "SDWrapper.hpp"
#include "VisualElement.hpp"
#include "IVGA.hpp"
#include <cstdlib>

#define bmpBI_RGB 0
#define bmpBI_RLE8 1
#define bmpBI_RLE4 2

using namespace rpgui::common;
using namespace rpgui::type;


rpgui::ui::Sprite::~Sprite()
{
}

rpgui::ui::Sprite::Sprite(const uint8_t *image, const uint16_t imageSize, int width, int height, int pitch)
    : VisualElement(Bounds(0, 0, width, height), Color::Transparent), _sprite(const_cast<uint8_t *>(image), imageSize, width, height, pitch)
{
}

rpgui::ui::Sprite::Sprite(const std::string &name, const std::string &path)
{
    if (_sprites.find(name) != _sprites.end())
    {
        // Load sprite from RAM
        auto inmem = _sprites.find(name)->second;
        _sprite = inmem;
    }
    else
    {
        // Load sprite from SD
        auto [result, file] = rpgui::util::SDWrapper::OpenFile(name, path);
        if (FR_OK != result)
        {
            return;
        }
        _sprite = loadData(file);
        rpgui::util::SDWrapper::CloseFile(file);
        _sprites.insert(std::make_pair(name,_sprite));
    }
        this->SetBounds(Bounds(0, 0, _sprite.width, _sprite.height));
}

void rpgui::ui::Sprite::Draw() const
{
    auto b = GetBounds();
    IVGA::IDrawImage(*this, Point(b.x, b.y));
}

#ifdef PICOVGA
sCanvas rpgui::ui::Sprite::GetCanvas(const sCanvas &toMatch) const
{
    auto canvas = sCanvas();
    canvas.format = toMatch.format;
    canvas.img = _sprite.image;
    canvas.h = _sprite.height;
    canvas.w = _sprite.width;
    canvas.wb = _sprite.pitch;

    return canvas;
}

#endif

const uint8_t *rpgui::ui::Sprite::GetImage() const
{
    return _sprite.image;
}

int rpgui::ui::Sprite::GetWidth() const
{
    return _sprite.width;
}

int rpgui::ui::Sprite::GetHeight() const
{
    return _sprite.height;
}

int rpgui::ui::Sprite::GetPitch() const
{
    return _sprite.pitch;
}

SpriteData rpgui::ui::Sprite::loadData(FIL *file)
{

#pragma pack(push, 1)
    struct bmpBITMAPFILEHEADER
    {
        uint16_t bfType;
        uint32_t bfSize;
        uint16_t bfReserved1;
        uint16_t bfReserved2;
        uint32_t bfOffBits;
    };

    struct bmpBITMAPINFOHEADER
    {
        uint32_t biSize;
        int32_t biWidth;
        int32_t biHeight;
        uint16_t biPlanes;
        uint16_t biBitCount;
        uint32_t biCompression;
        uint32_t biSizeImage;
        int32_t biXPelsPerMeter;
        int32_t biYPelsPerMeter;
        uint32_t biClrUsed;
        uint32_t biClrImportant;
    };
#pragma pack(pop)

    uint16_t fileSize = f_size(file);
    if (fileSize < 40)
    {
        // Handle error
        return SpriteData();
    }

    // create buffer
    uint8_t *Img = (uint8_t *)std::malloc(fileSize);
    if (Img == NULL)
    {
        // Handle error
        return SpriteData();
    }

    unsigned int num_read = 0;
    f_rewind(file);
    FRESULT res = f_read(file, Img, fileSize, &num_read);
    if (res != FR_OK || num_read != fileSize)
    {
        // Handle error
        printf("Error reading");
        return SpriteData();
    }

    // check BMP header
    bmpBITMAPFILEHEADER *bmf = (bmpBITMAPFILEHEADER *)Img;
    bmpBITMAPINFOHEADER *bmi = (bmpBITMAPINFOHEADER *)&bmf[1];

    uint16_t width, height, pitch, size;

    // Set image parameters
    if (bmi->biHeight < 0)
    {
        height = -bmi->biHeight;
    }
    else
    {
        height = bmi->biHeight;
    }
    width = bmi->biWidth;
    size = width * height;
    pitch = width;
    auto bitCount = bmi->biBitCount;

    if (bitCount == 4)
    {
        size /= 2;
        pitch /= 2;
    }
    if (bitCount == 2)
    {
        size /= 4;
        pitch /= 4;
    }
    if (bitCount == 1)
    {
        size /= 8;
        pitch /= 8;
    }

    if ((bmf->bfType != 0x4d42) ||
        (bmf->bfOffBits < 0x30) || (bmf->bfOffBits > 0x440) ||
        (bmi->biCompression != bmpBI_RGB) ||
        (width < 4) || (width > 10000) || (height < 4) || (height > 10000) ||
        ((bitCount != 8) && (bitCount != 4) && (bitCount != 1)))
    {
        printf("Incorrect format of input file\n");
        printf("  must be 8-bit, 4-bit or 1-bit pallette uncompressed.\n");
        return SpriteData();
    }

    // free bmp headers
    // get only image part

    uint8_t *image = (uint8_t *)std::malloc(size);
    for (int i = size - 1; i >= 0; i--)
    {
        // TODO: add conversion to 2 bits
        image[i] = Img[bmf->bfOffBits + i];
    }

    std::free(Img);

    return SpriteData(image, size, width, height, pitch);

    // are we done ?
}
