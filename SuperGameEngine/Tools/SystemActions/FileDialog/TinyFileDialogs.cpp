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

    // Null does not equal empty so need to clean this up.
    if (filePath == nullptr)
    {
        return {};
    }

    return filePath;
}

std::string TinyFileDialogs::OpenFile(
    const std::string& title, 
    const std::string& defaultPath,
    const std::vector<std::string>& filters, 
    const std::string& fileDisplayName) const
{
    const char* dialogTitle = title.c_str();
    const char* defaultPathAsChar = defaultPath.c_str();

    std::string filterDescription = fileDisplayName + " (";
    const char** justExtensions = new const char* [filters.size()];
    for (size_t i = 0; i < filters.size(); ++i)
    {
        justExtensions[i] = filters.at(i).c_str();

        if (i == 0)
        {
            filterDescription += filters.at(i);
        }
        else
        {
            filterDescription += ", " + filters.at(i);
        }
    }
    filterDescription += ")";

    int allowMultipleSelects = 0;
    const char* filePath = tinyfd_openFileDialog(
        dialogTitle,
        defaultPathAsChar,
        static_cast<int>(filters.size()),
        filters.empty() ? nullptr : justExtensions,
        filterDescription.c_str(),
        allowMultipleSelects);

    delete[] justExtensions;

    // Null does not equal empty so need to clean this up.
    if (filePath == nullptr)
    {
        return {};
    }

    return filePath;
}

std::string TinyFileDialogs::SaveFile() const
{
    const char* dialogTitle = "Save your file";
    const char* defaultPath = "";
    constexpr int numberOfFilterPatternsInArray = 1;
    const char** filters = nullptr;
    const char* filterDescription = nullptr;
    int allowMultipleSelects = 0;

    const char* filePath = tinyfd_saveFileDialog(
        dialogTitle,
        defaultPath,
        numberOfFilterPatternsInArray,
        filters,
        filterDescription);

    // Null does not equal empty so need to clean this up.
    if (filePath == nullptr)
    {
        return {};
    }

    return filePath;
}

std::string TinyFileDialogs::SaveFile(
    const std::string& title, 
    const std::string& defaultPath,
    const std::vector<std::string>& filters, 
    const std::string& fileDisplayName) const
{
    const char* dialogTitle = title.c_str();
    const char* defaultPathAsChar = defaultPath.c_str();

    std::string filterDescription = fileDisplayName + " (";
    const char** justExtensions = new const char* [filters.size()];
    for (size_t i = 0; i < filters.size(); ++i)
    {
        justExtensions[i] = filters.at(i).c_str();

        if (i == 0)
        {
            filterDescription += filters.at(i);
        }
        else
        {
            filterDescription += ", " + filters.at(i);
        }
    }
    filterDescription += ")";

    const char* filePath = tinyfd_saveFileDialog(
        dialogTitle,
        defaultPathAsChar,
        static_cast<int>(filters.size()),
        filters.empty() ? nullptr : justExtensions,
        filterDescription.c_str());

    delete[] justExtensions;

    // Null does not equal empty so need to clean this up.
    if (filePath == nullptr)
    {
        return {};
    }

    return filePath;
}
