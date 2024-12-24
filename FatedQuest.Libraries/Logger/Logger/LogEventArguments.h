#pragma once
#include "LogLevel.h"
#include "../../StandardObjects/Events/FEventArguments.h"

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

    private:
        /// <summary>
        /// The level of severity of the log.
        /// </summary>
        LogLevel m_logLevel;

        /// <summary>
        /// The main message to display.
        /// </summary>
        std::string m_message;
    };
}

