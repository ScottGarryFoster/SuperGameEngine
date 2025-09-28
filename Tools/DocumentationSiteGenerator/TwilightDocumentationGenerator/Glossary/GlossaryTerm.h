#pragma once
#include <string>

namespace TwilightDocumentationGenerator
{
    /// <summary>
    /// Represents a single glossary term.
    /// </summary>
    struct GlossaryTerm
    {
    public:
        /// <summary>
        /// The unique name to match the term to the glossary entry.
        /// </summary>
        std::string TermKeyName;

        /// <summary>
        /// Description of the glossary term.
        /// </summary>
        std::string Description;

        /// <summary>
        /// Page link to more info.
        /// </summary>
        std::string MoreInfoPage;
    };
}
