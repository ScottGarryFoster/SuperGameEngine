#pragma once
#include "LogLevel.h"
#include "../../Observer/AllReferences.h"

namespace FatedQuestLibraries
{
    /// <summary>
    /// Arguments when creating logs.
    /// </summary>
    class LogEventArguments : public FEventArguments
    {
    public:
        LogEventArguments();
        virtual ~LogEventArguments() override = default;

        /// <summary>
        /// The level of severity of the log.
        /// </summary>
        /// <returns>
        /// The level of severity of the log.
        /// </returns>
        LogLevel GetLevel() const;

        /// <summary>
        /// Sets the log level.
        /// </summary>
        /// <param name="level">New level. </param>
        void SetLevel(LogLevel level);

        /// <summary>
        /// The main message to display.
        /// </summary>
        /// <returns>The main message to display. </returns>
        std::string GetLogMessage() const;

        /// <summary>
        /// Sets the message for the log.
        /// </summary>
        /// <param name="message">New message. </param>
        void SetLogMessage(const std::string& message);

        /// <summary>
        /// Get the location the log comes from.
        /// </summary>
        /// <returns>Get the location the log comes from.</returns>
        std::string GetFrom() const;

        /// <summary>
        /// Set the location the log comes from.
        /// </summary>
        /// <param name="message">The location the log comes from.</param>
        void SetFrom(const std::string& message);

        /// <summary>
        /// The exception thrown.
        /// </summary>
        /// <returns>The exception thrown. </returns>
        std::string GetException() const;

        /// <summary>
        /// Set the exception thrown.
        /// </summary>
        /// <param name="message">New exception. </param>
        void SetException(const std::string& message);

    private:
        /// <summary>
        /// The level of severity of the log.
        /// </summary>
        LogLevel m_logLevel;

        /// <summary>
        /// The main message to display.
        /// </summary>
        std::string m_message;

        /// <summary>
        /// The location the log comes from.
        /// </summary>
        std::string m_from;

        /// <summary>
        /// The exception thrown.
        /// </summary>
        std::string m_exception;
    };
}

