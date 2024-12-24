#pragma once
#include "../../FatedQuestLibraries.h"

using namespace FatedQuestLibraries;

namespace SuperGameTools
{
    /// <summary>
    /// A single log entry.
    /// </summary>
    class LogEntry
    {
    public:
        LogEntry();
        virtual ~LogEntry();

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

        /// <summary>
        /// Writes the logger out to a message to display.
        /// </summary>
        /// <returns>Writes the logger out to a message to display. </returns>
        std::string Write() const;

    private:
        /// <summary>
        /// Complete message to write out.
        /// </summary>
        std::string m_completeMessage;

        /// <summary>
        /// Complete timestamp.
        /// </summary>
        std::string m_timestamp;

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

        /// <summary>
        /// Updates the output.
        /// </summary>
        void UpdateCompleteMessage();
    };
}


