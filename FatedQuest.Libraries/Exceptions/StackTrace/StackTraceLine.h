#pragma once
#include <string>

namespace FatedQuestLibraries
{
    /// <summary>
    /// A single line of a stack trace.
    /// </summary>
    class StackTraceLine
    {
    public:

        StackTraceLine(const std::string& name, const std::string& address);
        StackTraceLine(const std::string& name, const std::string& address, const std::string& filename, int lineNumber);

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        std::string GetName() const;

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        std::string GetAddress() const;

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        std::string GetFilename() const;

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        int GetLineNumber() const;

    private:

        /// <summary>
        /// Name of the place in the code.
        /// </summary>
        std::string m_name;

        /// <summary>
        /// Address of the code.
        /// </summary>
        std::string m_address;

        /// <summary>
        /// Filename for the stack trace, might be empty.
        /// </summary>
        std::string m_filename;

        /// <summary>
        /// Line number. -1 if there is no line number.
        /// </summary>
        int m_line;
    };
}
