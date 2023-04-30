#include "Sprite.hpp"
#include "SDWrapper.hpp"
#include "Base.hpp"
#include "IVGA.hpp"
#include <cstdlib>

#define bmpBI_RGB 0
#define bmpBI_RLE8 1
#define bmpBI_RLE4 2
rpgui::ui::Sprite::~Sprite()
{
    if (_image)
        delete _image;
}

rpgui::ui::Sprite::Sprite(const uint8_t *image, const uint16_t imageSize, int width, int height, int pitch)
    : View(Bounds(0, 0, width, height), Color::Transparent), _image(const_cast<uint8_t *>(image)), _size(imageSize), _width(width), _height(height), _pitch(pitch)
{
}

rpgui::ui::Sprite::Sprite(const std::string &name, const std::string &path)
{
    auto [result, file] = rpgui::util::SDWrapper::OpenFile(name, path);
    if (FR_OK != result)
    {
        return;
    }

    loadData(file);
    this->SetBounds(Bounds(0, 0, _width, _height));
    rpgui::util::SDWrapper::CloseFile(file);
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
    canvas.img = _image;
    canvas.h = _height;
    canvas.w = _width;
    canvas.wb = _pitch;

    return canvas;
}

#endif

const uint8_t *rpgui::ui::Sprite::GetImage() const
{
    return _image;
}

int rpgui::ui::Sprite::GetWidth() const
{
    return _width;
}

int rpgui::ui::Sprite::GetHeight() const
{
    return _height;
}

int rpgui::ui::Sprite::GetPitch() const
{
    return _pitch;
}

void rpgui::ui::Sprite::loadData(FIL *file)
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

    uint16_t size = f_size(file);
    if (size < 40)
    {
        // Handler error
        return;
    }

    // create buffer
    uint8_t *Img = (uint8_t *)std::malloc(size);
    if (Img == NULL)
    {
        // Handler error
        return;
    }

    unsigned int num_read = 0;
    f_rewind(file);
    FRESULT res = f_read(file, Img, size, &num_read);
    if (res != FR_OK || num_read != size)
    {
        // Handle error
        printf("Error reading");
        return;
    }

    // check BMP header
    bmpBITMAPFILEHEADER *bmf = (bmpBITMAPFILEHEADER *)Img;
    bmpBITMAPINFOHEADER *bmi = (bmpBITMAPINFOHEADER *)&bmf[1];

    // Set image parameters
    if (bmi->biHeight < 0)
    {
        _height = -bmi->biHeight;
    }
    else
    {
        _height = bmi->biHeight;
    }
    _width = bmi->biWidth;
    _size = _width * _height;
    _pitch = _width;
    auto bitCount = bmi->biBitCount;

    if (bitCount == 4)
    {
        _size /= 2;
        _pitch /= 2;
    }
    if (bitCount == 2)
    {
        _size /= 4;
        _pitch /= 4;
    }
    if (bitCount == 1)
    {
        _size /= 8;
        _pitch /= 8;
    }

    if ((bmf->bfType != 0x4d42) ||
        (bmf->bfOffBits < 0x30) || (bmf->bfOffBits > 0x440) ||
        (bmi->biCompression != bmpBI_RGB) ||
        (_width < 4) || (_width > 10000) || (_height < 4) || (_height > 10000) ||
        ((bitCount != 8) && (bitCount != 4) && (bitCount != 1)))
    {
        printf("Incorrect format of input file\n");
        printf("  must be 8-bit, 4-bit or 1-bit pallette uncompressed.\n");
        return;
    }

    // free bmp headers
    // get only image part

    _image = (uint8_t *)std::malloc(_size);
    for (int i = _size - 1; i >= 0; i--)
    {
        // TODO: add conversion to 2 bits
        _image[i] = Img[bmf->bfOffBits + i];
    }

    std::free(Img);

    // are we done ?
}
