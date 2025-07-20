#pragma once
#include <memory>
#include <string>

namespace FatedQuestLibraries
{
    class StackTrace;

    class Exception : public std::exception
    {
    public:
        Exception(const std::string& message);

        /// <summary>
        /// The message of the exception.
        /// </summary>
        /// <returns>The message of the exception. </returns>
        std::string Message() const;

        /// <summary>
        /// The type of the exception. Used when displaying the exception.
        /// </summary>
        /// <returns>The type of the exception. Used when displaying the exception. </returns>
        std::string Type() const;

        /// <summary>
        /// The call stack of the exception.
        /// </summary>
        /// <returns>The call stack of the exception. </returns>
        std::string CallStack() const;

        /// <summary>
        /// Outputs the exception to string.
        /// </summary>
        /// <returns></returns>
        virtual std::string ToString();

    protected:
        /// <summary>
        /// The message from the exception.
        /// </summary>
        /// <remarks>
        /// This is protected to allow other types to add their own
        /// information such as what arguments are involved.
        /// </remarks>
        std::string m_message;

        /// <summary>
        /// The type of the exception as a name.
        /// </summary>
        std::string m_type;

    private:

        /// <summary>
        /// The call stack of the exception.
        /// </summary>
        std::shared_ptr<StackTrace> m_callStack;
    };
}
