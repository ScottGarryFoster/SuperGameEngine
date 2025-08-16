#pragma once
#include <memory>
#include <string>
#include <vector>

namespace FatedQuestLibraries
{
    class StackTraceLine;

    /// <summary>
    /// Traces the stack for the steps it has taken.
    /// </summary>
    class StackTrace
    {
    public:

        /// <summary>
        /// Prints the stack trace to string.
        /// </summary>
        /// <returns>The stack trace as a string. </returns>
        virtual std::string ToString() const = 0;

        /// <summary>
        /// Get the Lines of the stack trace.
        /// </summary>
        /// <returns>The lines of the stack trace. </returns>
        virtual std::vector<std::shared_ptr<StackTraceLine>> Lines() const = 0;
    };
}
