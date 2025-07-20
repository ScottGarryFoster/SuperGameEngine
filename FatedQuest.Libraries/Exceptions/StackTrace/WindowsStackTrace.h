#pragma once
#include "StackTrace.h"

namespace FatedQuestLibraries
{
    /// <summary>
    /// Traces the stack for the steps it has taken.
    /// </summary>
    class WindowsStackTrace : public StackTrace
    {
    public:

        WindowsStackTrace(unsigned int startFrame = 0, unsigned int maxFrames = 64);

        /// <summary>
        /// Prints the stack trace to string.
        /// </summary>
        /// <returns>The stack trace as a string. </returns>
        virtual std::string ToString() const override;

        /// <summary>
        /// Get the Lines of the stack trace.
        /// </summary>
        /// <returns>The lines of the stack trace. </returns>
        virtual std::vector<std::shared_ptr<StackTraceLine>> Lines() const override;

    private:
        /// <summary>
        /// The lines of the stack trace.
        /// </summary>
        std::vector<std::shared_ptr<StackTraceLine>> m_lines;
    };
}
