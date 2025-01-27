#pragma once
#include <vector>
#include <string>
#include "../Text/StringHelpers.h"

#ifdef _DEBUG
#include <iostream>
#endif

namespace FatedQuestLibraries
{
    /// <summary>
    /// Describes how to package products.
    /// </summary>
    enum class CopyFileOptions : uint32_t
    {
        /// <summary>
        /// Used only when entry could not be parsed.
        /// </summary>
        Unknown = 0,

        /// <summary>
        /// File: Report an error if an existing found
        /// Directory: Skip-subdirectories. Copy the file contents.
        /// Symbolic Links: Follow symlinks
        /// </summary>
        None = 1 << 0,

        /// <summary>
        /// In a file copy skip existing files.
        /// </summary>
        SkipExistingFile = 1 << 1,

        /// <summary>
        /// Overwrite existing files.
        /// </summary>
        OverwriteExistingFile = 1 << 2,

        /// <summary>
        /// If copy is newer, override with source.
        /// </summary>
        UpdateExistingFile = 1 << 3,

        /// <summary>
        /// When copying directories, copy sub-directories as well.
        /// </summary>
        RecursiveDirectories = 1 << 4,

        /// <summary>
        /// Copy symlinks as symlinks, not as the files they point to.
        /// </summary>
        CopySymlinks = 1 << 5,

        /// <summary>
        /// Ignore symlinks.
        /// </summary>
        SkipSymlinks = 1 << 6,

        /// <summary>
        /// Only copy the directory structure not the files.
        /// </summary>
        DirectoriesOnly = 1 << 7,

        /// <summary>
        /// Instead of creating copies of files, create symlinks pointing to the originals. 
        /// Note: the source path must be an absolute path unless the destination path is in the current directory.
        /// </summary>
        CreateSymlinks = 1 << 8,

        /// <summary>
        /// Instead of creating copies of files, create hardlinks that resolve to the same files as the originals.
        /// </summary>
        CreateHardLinks = 1 << 9,
    };

    inline CopyFileOptions operator|(CopyFileOptions a, CopyFileOptions b)
    {
        return static_cast<CopyFileOptions>(static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
    }

    inline CopyFileOptions operator&(CopyFileOptions a, CopyFileOptions b)
    {
        return static_cast<CopyFileOptions>(static_cast<uint32_t>(a) & static_cast<uint32_t>(b));
    }

    inline CopyFileOptions& operator|=(CopyFileOptions& a, CopyFileOptions b)
    {
        a = a | b;
        return a;
    }

    inline CopyFileOptions& operator&=(CopyFileOptions& a, CopyFileOptions b)
    {
        a = a & b;
        return a;
    }

    /// <summary>
    /// Accompanies enums to provide extra functionality.
    /// </summary>
    class ECopyOptions
    {
    public:
        static CopyFileOptions Min() { return CopyFileOptions::None; }
        static CopyFileOptions Max() { return CopyFileOptions::CreateHardLinks; }
        static CopyFileOptions* ToArray()
        {
            static CopyFileOptions arr[] =
            {
                CopyFileOptions::None,
                CopyFileOptions::SkipExistingFile,
                CopyFileOptions::OverwriteExistingFile,
                CopyFileOptions::UpdateExistingFile,
                CopyFileOptions::RecursiveDirectories,
                CopyFileOptions::CopySymlinks,
                CopyFileOptions::SkipSymlinks,
                CopyFileOptions::DirectoriesOnly,
                CopyFileOptions::CreateSymlinks,
                CopyFileOptions::CreateHardLinks,
            };
            return arr;
        }

        static std::vector<CopyFileOptions> ToVector()
        {
            static std::vector<CopyFileOptions> returnVector =
            {
                CopyFileOptions::None,
                CopyFileOptions::SkipExistingFile,
                CopyFileOptions::OverwriteExistingFile,
                CopyFileOptions::UpdateExistingFile,
                CopyFileOptions::RecursiveDirectories,
                CopyFileOptions::CopySymlinks,
                CopyFileOptions::SkipSymlinks,
                CopyFileOptions::DirectoriesOnly,
                CopyFileOptions::CreateSymlinks,
                CopyFileOptions::CreateHardLinks,
            };
            return returnVector;
        }

        static std::string ToString(CopyFileOptions value)
        {
            switch (value)
            {
            case CopyFileOptions::None: return "None";
            case CopyFileOptions::SkipExistingFile: return "SkipExistingFile";
            case CopyFileOptions::OverwriteExistingFile: return "OverwriteExistingFile";
            case CopyFileOptions::UpdateExistingFile: return "UpdateExistingFile";
            case CopyFileOptions::RecursiveDirectories: return "RecursiveDirectories";
            case CopyFileOptions::CopySymlinks: return "CopySymlinks";
            case CopyFileOptions::SkipSymlinks: return "SkipSymlinks";
            case CopyFileOptions::DirectoriesOnly: return "DirectoriesOnly";
            case CopyFileOptions::CreateSymlinks: return "CreateSymlinks";
            case CopyFileOptions::CreateHardLinks: return "CreateHardLinks";
            }

#ifdef _DEBUG
            std::cout << "NotImplementedException: ECopyOptions::ToString, No string value for enum requested." << std::endl;
#endif // _DEBUG

            return "Unknown";
        }

        static CopyFileOptions FromString(std::string value, bool checkCase = true)
        {
            if (checkCase)
            {
                if (value == "Unknown") return CopyFileOptions::Unknown;
                if (value == "None") return CopyFileOptions::None;
                if (value == "SkipExistingFile") return CopyFileOptions::SkipExistingFile;
                if (value == "OverwriteExistingFile") return CopyFileOptions::OverwriteExistingFile;
                if (value == "UpdateExistingFile") return CopyFileOptions::UpdateExistingFile;
                if (value == "RecursiveDirectories") return CopyFileOptions::RecursiveDirectories;
                if (value == "CopySymlinks") return CopyFileOptions::CopySymlinks;
                if (value == "SkipSymlinks") return CopyFileOptions::SkipSymlinks;
                if (value == "DirectoriesOnly") return CopyFileOptions::DirectoriesOnly;
                if (value == "CreateSymlinks") return CopyFileOptions::CreateSymlinks;
                if (value == "CreateHardLinks") return CopyFileOptions::CreateHardLinks;
            }
            else
            {
                std::string toLower = StringHelpers::ToLower(value);
                if (toLower == "unknown") return CopyFileOptions::Unknown;
                if (toLower == "none") return CopyFileOptions::None;
                if (toLower == "skipexistingfile") return CopyFileOptions::SkipExistingFile;
                if (toLower == "overwriteexistingfile") return CopyFileOptions::OverwriteExistingFile;
                if (toLower == "updateExistingfile") return CopyFileOptions::UpdateExistingFile;
                if (toLower == "recursivedirectories") return CopyFileOptions::RecursiveDirectories;
                if (toLower == "copysymlinks") return CopyFileOptions::CopySymlinks;
                if (toLower == "skipsymlinks") return CopyFileOptions::SkipSymlinks;
                if (toLower == "directoriesonly") return CopyFileOptions::DirectoriesOnly;
                if (toLower == "createsymlinks") return CopyFileOptions::CreateSymlinks;
                if (toLower == "createhardlinks") return CopyFileOptions::CreateHardLinks;
            }

#ifdef _DEBUG
            std::cout << "NotImplementedException: ECopyOptions::FromString, No enum value for given string: " << value << std::endl;
#endif // _DEBUG

            return CopyFileOptions::Unknown;
        }

        static bool HasOption(CopyFileOptions options, CopyFileOptions option)
        {
            return (static_cast<uint32_t>(options) & static_cast<uint32_t>(option)) == static_cast<uint32_t>(option);
        }
    };
}