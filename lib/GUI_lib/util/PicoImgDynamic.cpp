#include "PicoImgDynamic.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "ff.h"

#define bmpBI_RGB	0
#define bmpBI_RLE8	1
#define bmpBI_RLE4	2


rpgui::util::ImageData::~ImageData()
{
    delete(Image);
}

rpgui::util::ImageData::ImageData(const std::string& fileName, const std::string& path)
{
    auto fs = prepareSD();
    auto file = openFile(fs);
    loadData(file, fileName, path);
    f_close(file);
}

void rpgui::util::ImageData::prepareSD()
{
    //TODO: Add SD wrapper class ? 
}

void rpgui::util::ImageData::openFile(const FATFS& fs, const std::string& fileName, const std::string& path)
{
    FRESULT res;      
    FIL fil;

    // Open the root directory
    res = f_opendir(&dir, "/");
    if (res != FR_OK) {
        // Handle error
    }

    if(!path.empty())
    {
        // Navigate to the path subdirectory
        res = f_chdir(path);
        if (res != FR_OK) {
            // Handle error
        }
    }

    if(!fileName.empty())
    {
        // Open the file for reading
        res = f_open(&fil, fileName, FA_READ);
        if (res != FR_OK) {
            // Handle error
        }

        return fil;
    }
}

void rpgui::util::ImageData::loadData(const FIL& file)
{
    struct _bmpBITMAPFILEHEADER {
            uint16_t		bfType;
            uint32_t		bfSize;
            uint16_t		bfReserved1;
            uint16_t		bfReserved2;
            uint32_t		bfOffBits;
    } bmpBITMAPFILEHEADER;

    struct _bmpBITMAPINFOHEADER{
            uint32_t		biSize;
            int32_t		biWidth;
            int32_t		biHeight;
            uint16_t		biPlanes;
            uint16_t		biBitCount;
            uint32_t		biCompression;
            uint32_t		biSizeImage;
            int32_t		biXPelsPerMeter;
            int32_t		biYPelsPerMeter;
            uint32_t		biClrUsed;
            uint32_t		biClrImportant;
    } bmpBITMAPINFOHEADER;

    uint16_t size = f_size(file);
    if(size < 40)
    {
        // Handler error
        return;
    }

    unsigned int num_read;
    // create buffer
	uint8_t* Img = (unsigned char*)malloc(size);
	if (Img == NULL)
	{
		// Handler error
		return;
	}

    uint8_t num_read;
    FRESULT res = f_read(&file, Img, sizeof(Img), &num_read);
    if (res != FR_OK) {
        // Handle error
    }

    // check BMP header
	bmpBITMAPFILEHEADER *bmf = (bmpBITMAPFILEHEADER*)Img;
	bmpBITMAPINFOHEADER *bmi = (bmpBITMAPINFOHEADER*)&bmf[1];

    width = bmi->biWidth;
	heigth = bmi->biHeight;
	auto bitCount = bmi->biBitCount;

    if (heigth < 0) heigth = -heigth;
	if ((bmf->bfType != 0x4d42) ||
		(bmf->bfOffBits < 0x30) || (bmf->bfOffBits > 0x440) ||
		(bmi->biCompression != bmpBI_RGB) ||
		(width < 4) || (width > 10000) || (heigth < 4) || (heigth > 10000) ||
		((bitCount != 8) && (bitCount != 4) && (bitCount != 1)))
	{
		printf("Incorrect format of input file %s,\n", argv[1]);
		printf("  must be 8-bit, 4-bit or 1-bit pallette uncompressed.\n");
		return ;
	}

    // free bmp headers
    // get only image part
    uint16_t imageSize = width * heigth;
    Image = realloc(Img[bmf->bfOffBits], imageSize * sizeof(uint8_t));
    free(Img);

    // are we done ?

}
