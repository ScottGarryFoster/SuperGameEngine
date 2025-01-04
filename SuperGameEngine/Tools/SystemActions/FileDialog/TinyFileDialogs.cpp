#include "TinyFileDialogs.h"
#include "../../../Engine/External/TinyFileDialog/tinyfiledialogs.h"


using namespace SuperGameTools;

std::string TinyFileDialogs::OpenFile() const
{
    const char* dialogTitle = "Select a file";
    const char* defaultPath = "";
    constexpr int numberOfFilterPatternsInArray = 0;
    const char** filters = nullptr;
    const char* filterDescription = nullptr;
    int allowMultipleSelects = 0;

    const char* filePath = tinyfd_openFileDialog(
        dialogTitle, 
        defaultPath, 
        numberOfFilterPatternsInArray, 
        filters, 
        filterDescription, 
        allowMultipleSelects);

    return filePath;
}