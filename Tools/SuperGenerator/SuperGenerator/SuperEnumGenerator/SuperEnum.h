#pragma once
#include "FatedQuestLibraries.h"
#include <string>
#include <unordered_set>

#include "SuperEnumType.h"

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

        class EnumValueString
        {
        public:
            std::string Value = {};
            std::string LowercaseValue = {};
            
            bool ValueIsSet = false;
            int SetValue = 0;
            int ImpliedValue = 0;

            /// <summary>
            /// The comment for the enum.
            /// </summary>
            std::string Comment = {};

            /// <summary>
            /// Hides from Array and Vector methods.
            /// </summary>
            bool HideFromLists = false;

            /// <summary>
            /// If true this will be used as the unknown value
            /// when a string cannot be parsed.
            /// </summary>
            bool IsUnknownValue = false;

            /// <summary>
            /// When making the enum, this updates with the flag value.
            /// </summary>
            size_t FlagValue = -1;

            /// <summary>
            /// The predefined group this enum is in.
            /// </summary>
            std::unordered_set<std::string> Groups;
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
        /// How to create the enum from a broad perspective.
        /// </summary>
        SuperEnumType m_enumType;

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
        /// All the enum values.
        /// </summary>
        std::vector<std::shared_ptr<EnumValueString>> m_enumValues;

        bool ParseRoot(std::shared_ptr<StoredDocumentNode> rootNode);

        bool ParseHeader(std::shared_ptr<StoredDocumentNode> headerNode);

        bool ParseFooter(std::shared_ptr<StoredDocumentNode> headerNode);

        bool ParseNamespaceFooter(std::shared_ptr<StoredDocumentNode> headerNode);

        bool ParseNamespace(std::shared_ptr<StoredDocumentNode> namespaceNode);

        bool ParseEnumComment(std::shared_ptr<StoredDocumentNode> enumNode);

        bool ParseEnumName(std::shared_ptr<StoredDocumentNode> enumNode);

        bool ParseAdditionalIncludes(std::shared_ptr<StoredDocumentNode> additionalIncludeNode);
        void AddToIncludes(const std::string& rootPath);

        bool SetUpImpliedEnumValues();

        std::string PrintDateTime();
        std::string PrintIndents(int number);

        std::string PrintHeader(int indents);
        std::string PrintFooter(int indents);
        std::string PrintNamespaceFooter(int indents);
        std::string PrintEnum(int indents);
        std::string PrintEnumHelper(int indents);
        std::string PrintToArray(int indents);
        std::string PrintToVector(int indents);
        std::string PrintToVectorValues(int indents);
        std::string PrintToString(int indents);
        std::string PrintFromString(int indents);
        std::string PrintGroups(int indents);
        std::string PrintToLower(int indents);
        std::string GetMinEnumValue();
        std::string GetMaxEnumValue();
        std::string GetUnknownValue();

        std::string PrintSingleComment(const std::string& rawComment, int indents);

        std::string PrintFlagMethods(int indents);
        std::string PrintFlagHelperMethods(int indents);

        /// <summary>
        /// Figure out the best type for the enum.
        /// </summary>
        /// <returns>Best type to use. </returns>
        std::string FigureOutType();

        int GetMinEnumNumberValue();
        int GetMaxEnumNumberValue();
    };
}

