#pragma once
#include "FatedQuestLibraries.h"
#include <string>

using namespace FatedQuestLibraries;

namespace SuperEnumGenerator
{
    /// <summary>
    /// Represents an ungenerated enum file.
    /// </summary>
    class SuperEnum
    {
    public:
        SuperEnum();

        /// <summary>
        /// Load object using the format of a SuperEnum.
        /// </summary>
        /// <param name="superEnumFile">The contents of a super Enum file.</param>
        /// <returns>True means parsed. </returns>
        bool FromString(const std::string& superEnumFile);

        /// <summary>
        /// Generate an enum based upon what is loaded.
        /// </summary>
        std::string ToString();

    private:
        class ParsedString
        {
        public:
            bool Parsed = false;
            std::string Value = "";
        };

        class EnumValueString
        {
        public:
            std::string Value = "";
            std::string LowercaseValue = "";
            
            bool ValueIsSet = false;
            int SetValue = 0;
            int ImpliedValue = 0;

            std::string Comment = "";

            /// <summary>
            /// Hides from Array and Vector methods.
            /// </summary>
            bool HideFromLists = false;

            /// <summary>
            /// If true this will be used as the unknown value
            /// when a string cannot be parsed.
            /// </summary>
            bool IsUnknownValue = false;
        };

        /// <summary>
        /// The namespace to use.
        /// </summary>
        ParsedString m_namespace;

        /// <summary>
        /// Main enum comment.
        /// </summary>
        ParsedString m_enumComment;

        /// <summary>
        /// The enum name to use.
        /// </summary>
        ParsedString m_enumName;

        /// <summary>
        /// Header to the file.
        /// Should occur at the very top.
        /// </summary>
        ParsedString m_header;

        /// <summary>
        /// All the enum values.
        /// </summary>
        std::vector<std::shared_ptr<EnumValueString>> m_enumValues;

        bool ParseHeader(std::shared_ptr<StoredDocumentNode> headerNode);

        bool ParseNamespace(std::shared_ptr<StoredDocumentNode> namespaceNode);

        bool ParseEnumComment(std::shared_ptr<StoredDocumentNode> enumNode);

        bool ParseEnumName(std::shared_ptr<StoredDocumentNode> enumNode);

        bool SetUpImpliedEnumValues();

        std::string PrintDateTime();
        std::string PrintIndents(int number);

        std::string PrintHeader(int indents);
        std::string PrintEnum(int indents);
        std::string PrintEnumHelper(int indents);
        std::string PrintToArray(int indents);
        std::string PrintToVector(int indents);
        std::string PrintToString(int indents);
        std::string PrintFromString(int indents);
        std::string GetMinEnumValue();
        std::string GetMaxEnumValue();
        std::string GetUnknownValue();

        std::string PrintSingleComment(const std::string& rawComment, int indents);
    };
}

