#pragma once
#include <string>

namespace FatedQuestLibraries
{
    /// <summary>
    /// Methods to perform replacements of one string in another.
    /// </summary>
    class StringAdvancedReplace
    {
    public:

        /// <summary>
        /// Searches for criteria in source and replaces it with replacement.
        /// Returns answer.
        /// </summary>
        /// <param name="source">Where to find criteria to replace. </param>
        /// <param name="criteria">What to search for. </param>
        /// <param name="replacement">What to replace with. </param>
        /// <returns>Replaced result. </returns>
        static std::string Replace(
            const std::string& source, 
            const std::string& criteria,
            const std::string& replacement);

        /// <summary>
        /// Searches for criteria in source and replaces it with replacement.
        /// Replaces source with the replaced version.
        /// </summary>
        /// <param name="source">Where to find criteria to replace. </param>
        /// <param name="criteria">What to search for. </param>
        /// <param name="replacement">What to replace with. </param>
        static void ReplaceInPlace(
            std::string& source,
            const std::string& criteria,
            const std::string& replacement);
    };
}

