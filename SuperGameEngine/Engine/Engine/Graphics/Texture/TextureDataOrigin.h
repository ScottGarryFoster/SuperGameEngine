#pragma once
#include "../../../FatedQuestReferences.h"
#include <vector>
#include <string>


// +------------------------------+
// Generated by SuperGenerator as an
// SuperEnum. See Tools for details.
// Date: 2024/12/22 20:34:47
// +------------------------------+
namespace FatedQuestLibraries
{
    /// <summary>
    /// How the texture was loaded in last.
    /// This is used to understand how to recreate the texture
    /// if the renderer was ever torn down.
    /// </summary>
    enum class TextureDataOrigin
    {
        /// <summary>
        /// Only used for unsuccessful parsing.
        /// </summary>
        Unknown = -1,

        /// <summary>
        /// Created from a file on disk.
        /// </summary>
        FromFile,

        /// <summary>
        /// Created from data within memory.
        /// </summary>
        FromData,
    };

    /// <summary>
    /// Accompanies enums to provide extra functionality.
    /// </summary>
    class ETextureDataOrigin
    {
    public:
        static TextureDataOrigin Min() { return TextureDataOrigin::FromFile; }
        static TextureDataOrigin Max() { return TextureDataOrigin::FromData; }

        static TextureDataOrigin* ToArray()
        {
            static TextureDataOrigin returnArray[] =
            {
                TextureDataOrigin::FromFile,
                TextureDataOrigin::FromData,
            };
            
            return returnArray;
        }

        static std::vector<TextureDataOrigin> ToVector()
        {
            static std::vector<TextureDataOrigin> returnVector =
            {
                TextureDataOrigin::FromFile,
                TextureDataOrigin::FromData,
            };
            
            return returnVector;
        }

        static std::string ToString(TextureDataOrigin value)
        {
            switch (value)
            {
                case TextureDataOrigin::Unknown: return "Unknown";
                case TextureDataOrigin::FromFile: return "FromFile";
                case TextureDataOrigin::FromData: return "FromData";
            }
            
            return "Unknown";
        }

        static TextureDataOrigin FromString(std::string value, bool checkCase = true)
        {
            if (checkCase)
            {
                if (value == "Unknown") return TextureDataOrigin::Unknown;
                if (value == "FromFile") return TextureDataOrigin::FromFile;
                if (value == "FromData") return TextureDataOrigin::FromData;
            }
            else
            {
                std::string valueLower = FatedQuestLibraries::StringHelpers::ToLower(value); 
                if (valueLower == "unknown") return TextureDataOrigin::Unknown;
                if (valueLower == "fromfile") return TextureDataOrigin::FromFile;
                if (valueLower == "fromdata") return TextureDataOrigin::FromData;
            }
            
            return TextureDataOrigin::Unknown;
        }
    };
}
