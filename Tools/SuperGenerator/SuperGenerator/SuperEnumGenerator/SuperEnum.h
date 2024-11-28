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

            bool OverrideAsMin = false;
            bool OverrideAsMax = false;

            std::string Comment = "";
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
        /// All the enum values.
        /// </summary>
        std::vector<std::shared_ptr<EnumValueString>> m_enumValues;

        bool ParseNamespace(std::shared_ptr<XMLNode> namespaceNode);

        bool ParseEnumComment(std::shared_ptr<XMLNode> enumNode);

        bool ParseEnumName(std::shared_ptr<XMLNode> enumNode);

        std::string PrintDateTime();
        std::string PrintIndents(int number);

        std::string PrintEnum(int indents);

        std::string PrintSingleComment(const std::string& rawComment, int indents);
    };
}

