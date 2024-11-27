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

        /// <summary>
        /// The namespace to use.
        /// </summary>
        ParsedString m_namespace;

        /// <summary>
        /// The enum name to use.
        /// </summary>
        ParsedString m_enumName;

        bool ParseNamespace(std::shared_ptr<XMLNode> namespaceNode);

        bool ParseEnumName(std::shared_ptr<XMLNode> enumNode);

        std::string PrintDateTime();
        std::string PrintIndents(int number);

        std::string PrintEnum(int indents);
    };
}

