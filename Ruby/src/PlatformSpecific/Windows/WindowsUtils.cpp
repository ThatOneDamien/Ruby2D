#include "ruby_pch.h"

#include "Ruby/Utility/PlatformFileUtils.h"
#include "Ruby/Main/App.h"

#include <commdlg.h>

namespace Ruby
{
    namespace FileUtils
    {
        constexpr size_t MAX_PATH_SIZE = 256ull;

        std::string loadFile(const char* filters)
        {
            OPENFILENAMEA ofn;
            CHAR pathBuf[MAX_PATH_SIZE] = { '\0' };
            CHAR currentDir[MAX_PATH_SIZE] = { '\0' };

            ZeroMemory(&ofn, sizeof(OPENFILENAME));

            ofn.lStructSize = sizeof(OPENFILENAME);
            ofn.hwndOwner = (HWND)App::getInstance().getWindow().getNativeWindowPtr();
            ofn.lpstrFile = pathBuf;
            ofn.nMaxFile = sizeof(CHAR) * MAX_PATH_SIZE;
            ofn.lpstrInitialDir = GetCurrentDirectoryA(MAX_PATH_SIZE, currentDir) ? currentDir : nullptr;
            ofn.lpstrFilter = filters;
            ofn.nFilterIndex = 1;
            ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

            if (GetOpenFileNameA(&ofn))
                return ofn.lpstrFile;

            return std::string();
        }

        std::string saveFile(const char* filters)
        {
            OPENFILENAMEA ofn;
            CHAR pathBuf[MAX_PATH_SIZE] = { '\0' };
            CHAR currentDir[MAX_PATH_SIZE] = { '\0' };

            ZeroMemory(&ofn, sizeof(OPENFILENAME));
            
            ofn.lStructSize = sizeof(OPENFILENAME);
            ofn.hwndOwner = (HWND)App::getInstance().getWindow().getNativeWindowPtr();
            ofn.lpstrFile = pathBuf;
            ofn.nMaxFile = sizeof(CHAR) * MAX_PATH_SIZE;
            ofn.lpstrInitialDir = GetCurrentDirectoryA(MAX_PATH_SIZE, currentDir) ? currentDir : nullptr;
            ofn.lpstrFilter = filters;
            ofn.nFilterIndex = 1;
            ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR;

            // Sets the default extension by extracting it from the filter
            ofn.lpstrDefExt = strchr(filters, '\0') + 1;

            return GetSaveFileNameA(&ofn) == TRUE ? std::string(ofn.lpstrFile) : std::string();
        }
    }
}
