#include "SDWrapper.hpp"

#include "hw_config.h"
#include "pico/stdlib.h"

#include <algorithm>

FRESULT rpgui::util::SDWrapper::Init()
{
    if(_sdInit)
        return FRESULT::FR_OK;
    
    sd_card_t *pSD = sd_get_by_num(0);
    FRESULT fr = f_mount(&pSD->fatfs, pSD->pcName, 1);
    if (FR_OK != fr)
    {
        _sdInit = false;
        return fr;
    }

    _sdInit = true;
    return fr;
}

void rpgui::util::SDWrapper::Dispose()
{
    CloseAllFiles();

    if (_sdInit)
    {
        sd_card_t *pSD = sd_get_by_num(0);
        f_unmount(pSD->pcName);
    }
}

std::tuple<FRESULT, FIL *> rpgui::util::SDWrapper::OpenFile(const std::string &name, const std::string &path)
{
    FIL *fil = new FIL();
    FRESULT res;
    if (!_sdInit)
    {
        res = Init();
        if(FR_OK != res)
        {
            return std::make_tuple(FRESULT::FR_NO_FILESYSTEM, nullptr);
        }
    }

    if(!path.empty())
    {
        res = f_chdir(path.c_str());
        if(FR_OK != res)
        {
            return std::make_tuple(res, nullptr); 
        }
    }

    res = f_open(fil, name.c_str(), FA_WRITE | FA_READ | FA_OPEN_APPEND);
    if(FR_OK == res)
    {
        _openedFiles.push_back(fil);
    }
    return std::make_tuple(res, fil);
}

FRESULT rpgui::util::SDWrapper::CloseAllFiles()
{
    FRESULT ret;
    for (auto file : _openedFiles)
    {
        auto result = f_close(file);
        if (FR_OK != result)
        {
            ret = result;
        }
    }

    return ret;
}

FRESULT rpgui::util::SDWrapper::CloseFile(FIL *file)
{
    auto it = std::find(_openedFiles.begin(), _openedFiles.end(), file);
    if (it == _openedFiles.end())
    {
        return FRESULT::FR_NO_FILE;
    }

    auto result = f_close(it.operator*());
    _openedFiles.erase(it);
    return result;
}
