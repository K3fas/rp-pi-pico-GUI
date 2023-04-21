#pragma once

#include "Types.hpp"
#include <string>

namespace rpgui::util
{
    struct ImageData
    {
    public:    
        uint8_t* Image;
        uint16_t width, heigth, pitch;;
    

    public:
        ImageData() = delete;
        ImageData(const ImageData&) = delete;
        ~ImageData();

        ImageData(const std::string& fileName, const std::string& path);

    private:
        FATFS prepareSD();
        void openFile();
        void loadData();
    };
    
    
} // namespace rpgui::util
