#pragma once
#include <vector>
#include <string>


// +------------------------------+
// Generated by SuperGenerator as an
// SuperEnum. See Tools for details.
// +------------------------------+
namespace SuperGameTools
{
    /// <summary>
    /// How the document suggests being openned.
    /// </summary>
    enum class DocumentEventOpenLevel
    {
        /// <summary>
        /// Only used for unsuccessful parsing.
        /// </summary>
        Unknown = -1,

        /// <summary>
        /// Upto the system taking the document.
        /// </summary>
        EitherOr,

        /// <summary>
        /// Openned from a place which demand exclusivity.
        /// </summary>
        Exclusive,

        /// <summary>
        /// Can be added to existing documents of the same type.
        /// </summary>
        Additive,
    };

    /// <summary>
    /// Accompanies enums to provide extra functionality.
    /// </summary>
    class EDocumentEventOpenLevel
    {
    public:
        static DocumentEventOpenLevel Min() { return DocumentEventOpenLevel::EitherOr; }
        static DocumentEventOpenLevel Max() { return DocumentEventOpenLevel::Additive; }

        static DocumentEventOpenLevel* ToArray()
        {
            static DocumentEventOpenLevel returnArray[] =
            {
                DocumentEventOpenLevel::EitherOr,
                DocumentEventOpenLevel::Exclusive,
                DocumentEventOpenLevel::Additive,
            };
            
            return returnArray;
        }

        static std::vector<DocumentEventOpenLevel> ToVector()
        {
            static std::vector<DocumentEventOpenLevel> returnVector =
            {
                DocumentEventOpenLevel::EitherOr,
                DocumentEventOpenLevel::Exclusive,
                DocumentEventOpenLevel::Additive,
            };
            
            return returnVector;
        }

        static std::string ToString(DocumentEventOpenLevel value)
        {
            switch (value)
            {
                case DocumentEventOpenLevel::Unknown: return "Unknown";
                case DocumentEventOpenLevel::EitherOr: return "EitherOr";
                case DocumentEventOpenLevel::Exclusive: return "Exclusive";
                case DocumentEventOpenLevel::Additive: return "Additive";
            }
            
            return "Unknown";
        }

        static DocumentEventOpenLevel FromString(std::string value, bool checkCase = true)
        {
            if (checkCase)
            {
                if (value == "Unknown") return DocumentEventOpenLevel::Unknown;
                if (value == "EitherOr") return DocumentEventOpenLevel::EitherOr;
                if (value == "Exclusive") return DocumentEventOpenLevel::Exclusive;
                if (value == "Additive") return DocumentEventOpenLevel::Additive;
            }
            else
            {
                std::string valueLower = ToLower(value); 
                if (valueLower == "unknown") return DocumentEventOpenLevel::Unknown;
                if (valueLower == "eitheror") return DocumentEventOpenLevel::EitherOr;
                if (valueLower == "exclusive") return DocumentEventOpenLevel::Exclusive;
                if (valueLower == "additive") return DocumentEventOpenLevel::Additive;
            }
            
            return DocumentEventOpenLevel::Unknown;
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
