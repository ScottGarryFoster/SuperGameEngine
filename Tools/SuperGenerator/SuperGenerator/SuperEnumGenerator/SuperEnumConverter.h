#pragma once
#include "FatedQuestLibraries.h"
#include <string>
#include <unordered_set>

#include "SuperEnumConverterType.h"
#include "SuperEnumType.h"

using namespace FatedQuestLibraries;

namespace SuperEnumGenerator
{
    /// <summary>
    /// Represents an ungenerated enum file.
    /// </summary>
    class SuperEnumConverter
    {
    public:
        SuperEnumConverter();

        /// <summary>
        /// Load object using the format of a SuperEnum.
        /// </summary>
        /// <param name="superEnumFile">The contents of a super Enum file.</param>
        /// <param name="path">The contents of a super Enum file.</param>
        /// <returns>True means parsed. </returns>
        bool FromString(const std::string& superEnumFile, const std::string& path);

        /// <summary>
        /// Generate an enum based upon what is loaded.
        /// </summary>
        std::string ToString();

    private:
        class ParsedString
        {
        public:
            bool Parsed = false;
            std::string Value = {};
        };

        class Conversion
        {
        public:
            std::string Left = {};
            std::string Right = {};
        };

        class EnumDefinition
        {
        public:
            std::string Type;

            /// <summary>
            /// If true is left. If false is right.
            /// </summary>
            bool IsLeft = true;

            /// <summary>
            /// When referring to enum names use this as the prefix.
            /// If False do not.
            /// </summary>
            bool UseTypeAsPrefix = true;
        };

        /// <summary>
        /// The location of this file from the root directory.
        /// </summary>
        std::string m_path;

        /// <summary>
        /// A path to prefix which anything after wards will be relative to the root directory.
        /// </summary>
        std::string m_pathPrefixToRoot;

        /// <summary>
        /// How to match two enums (convert them) together.
        /// </summary>
        SuperEnumConverterType m_converterType;

        /// <summary>
        /// Header to the file.
        /// Should occur at the very top.
        /// </summary>
        ParsedString m_header;

        /// <summary>
        /// The footer of the file.
        /// Should occur at the very bottom.
        /// </summary>
        ParsedString m_footer;

        /// <summary>
        /// The footer is code at the end of the extra class but not in the extras class.
        /// The extras class is the one with all the extra methods named EENUMNAME.
        /// </summary>
        ParsedString m_namespaceFooter;

        /// <summary>
        /// The namespace to use.
        /// </summary>
        ParsedString m_namespace;

        /// <summary>
        /// Main enum comment.
        /// </summary>
        ParsedString m_enumComment;

        /// <summary>
        /// The name of the enum.
        /// </summary>
        ParsedString m_enumConverterName;

        /// <summary>
        /// Default value if explicitly set.
        /// </summary>
        std::shared_ptr<Conversion> m_defaultValue;

        /// <summary>
        /// All conversions outside of the default if there is an explicit default.
        /// </summary>
        std::vector<std::shared_ptr<Conversion>> m_allConversions;

        /// <summary>
        /// The first enum.
        /// </summary>
        EnumDefinition m_left;

        /// <summary>
        /// The second enum.
        /// </summary>
        EnumDefinition m_right;

        bool ParseRoot(std::shared_ptr<StoredDocumentNode> rootNode);

        bool ParseHeader(std::shared_ptr<StoredDocumentNode> headerNode);

        bool ParseFooter(std::shared_ptr<StoredDocumentNode> headerNode);

        bool ParseNamespaceFooter(std::shared_ptr<StoredDocumentNode> headerNode);

        bool ParseNamespace(std::shared_ptr<StoredDocumentNode> namespaceNode);

        bool ParseEnumComment(std::shared_ptr<StoredDocumentNode> enumNode);

        bool ParseConverter(std::shared_ptr<StoredDocumentNode> enumNode);

        bool ParseAdditionalIncludes(std::shared_ptr<StoredDocumentNode> additionalIncludeNode);

        bool ParseEnumDefinition(std::shared_ptr<StoredDocumentNode> additionalIncludeNode);

        std::string PrintIndents(int number);

        std::string PrintHeader(int indents);
        std::string PrintFooter(int indents);
        std::string PrintNamespaceFooter(int indents);

        std::string PrintEnumConverter(int indents);
        std::string PrintEnumConverterStandard(int indents);
        std::string PrintEnumConverterBitflag(int indents);

        /// <summary>
        /// Prints the prefix for an enum if this is required.
        /// </summary>
        /// <param name="left">True means print lefts prefix. </param>
        /// <returns>The prefix if any. </returns>
        std::string PrintEnumPrefixIfAny(bool left = true);

        std::string PrintSingleComment(const std::string& rawComment, int indents);
    };
}

