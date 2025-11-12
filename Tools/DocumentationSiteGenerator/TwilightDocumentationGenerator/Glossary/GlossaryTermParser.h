#pragma once
#include <string>
#include <unordered_map>

#include "GlossaryTerm.h"

namespace TwilightDocumentationGenerator
{
    /// <summary>
    /// Parses glossary terms.
    /// </summary>
    class GlossaryTermParser
    {
    public:
        /// <summary>
        /// Parses a page of glossary terms into a set of information.
        /// </summary>
        /// <param name="pathToGlossary">File containing glossary terms. </param>
        /// <returns>All glossary terms parsed. </returns>
        virtual std::unordered_map<std::string, GlossaryTerm> ParseGlossary(const std::string& pathToGlossary) = 0;
    };
}
