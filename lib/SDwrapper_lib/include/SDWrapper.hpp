#pragma once
#include "ff.h"
#include "f_util.h"

#include <vector>
#include <string>
#include <tuple>

namespace rpgui::util
{
    class SDWrapper
    {
    private:
        inline static bool _sdInit = false;
        inline static std::vector<FIL *> _openedFiles;

    public:
        SDWrapper() = delete;
        SDWrapper(const SDWrapper &) = delete;
        ~SDWrapper() = delete;

        static FRESULT Init();
        static void Dispose();

        static std::tuple<FRESULT, FIL *> OpenFile(const std::string &name, const std::string &path,
                                                   const unsigned char mode = FA_READ | FA_WRITE | FA_OPEN_APPEND);
        static FRESULT CloseAllFiles();
        static FRESULT CloseFile(FIL *file);

        static FRESULT SyncFile(FIL *file);
    };

} // namespace rpgui::util
