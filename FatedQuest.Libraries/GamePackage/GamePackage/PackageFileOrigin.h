#pragma once
#include <vector>
#include <string>


// +------------------------------+
// Generated by SuperGenerator as an
// SuperEnum. See Tools for details.
// +------------------------------+
namespace FatedQuestLibraries
{
    /// <summary>
    /// The type and priority the package file needs to take within a game package.
    /// </summary>
    enum class PackageFileOrigin : int8_t
    {
        /// <summary>
        /// Only used for unsuccessful parsing.
        /// </summary>
        Unknown = -1,

        /// <summary>
        /// The file is unarchived and sits as a standalone file on disk.
        /// </summary>
        Unarchived,

        /// <summary>
        /// The file is archived within a package and must be accessed via the archive file.
        /// </summary>
        Archived,
    };

    /// <summary>
    /// Accompanies enums to provide extra functionality.
    /// </summary>
    class EPackageFileOrigin
    {
    public:
        static PackageFileOrigin Min() { return PackageFileOrigin::Unarchived; }
        static PackageFileOrigin Max() { return PackageFileOrigin::Archived; }

        static PackageFileOrigin* ToArray()
        {
            static PackageFileOrigin returnArray[] =
            {
                PackageFileOrigin::Unarchived,
                PackageFileOrigin::Archived,
            };
            
            return returnArray;
        }

        static std::vector<PackageFileOrigin> ToVector()
        {
            static std::vector<PackageFileOrigin> returnVector =
            {
                PackageFileOrigin::Unarchived,
                PackageFileOrigin::Archived,
            };
            
            return returnVector;
        }

        static std::string ToString(PackageFileOrigin value)
        {
            switch (value)
            {
                case PackageFileOrigin::Unknown: return "Unknown";
                case PackageFileOrigin::Unarchived: return "Unarchived";
                case PackageFileOrigin::Archived: return "Archived";
            }
            
            return "Unknown";
        }

        static PackageFileOrigin FromString(std::string value, bool checkCase = true)
        {
            if (checkCase)
            {
                if (value == "Unknown") return PackageFileOrigin::Unknown;
                if (value == "Unarchived") return PackageFileOrigin::Unarchived;
                if (value == "Archived") return PackageFileOrigin::Archived;
            }
            else
            {
                std::string valueLower = ToLower(value); 
                if (valueLower == "unknown") return PackageFileOrigin::Unknown;
                if (valueLower == "unarchived") return PackageFileOrigin::Unarchived;
                if (valueLower == "archived") return PackageFileOrigin::Archived;
            }
            
            return PackageFileOrigin::Unknown;
        }

        /// <summary>
        /// Converts to lower. Copy from StringHelpers to ensure Enum does not require
        /// any outside dependency. Although we could include a header, doing so restricts
        /// the project which holds StringHelpers.
        /// </summary>
        static std::string ToLower(const std::string & input)
        {
            std::string output = input;
            for (char& c : output)
            {
                if (c >= 'A' && c <= 'Z')
                {
                    c = c - 'A' + 'a';
                }
            }
            return output;
        }
    };
}
