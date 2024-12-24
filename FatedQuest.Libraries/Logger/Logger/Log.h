#pragma once
#include <memory>
#include <string>

namespace FatedQuestLibraries
{
    enum class LogLevel;
    class FEvent;
    class FEventSubscriptions;

    /// <summary>
    /// Logger for the Engine.
    /// </summary>
    class Log
    {
    public:
        /// <summary>
        /// Logs a message to the logger as an info message.
        /// </summary>
        /// <param name="message">Message to log. </param>
        static void Info(const std::string& message);

        /// <summary>
        /// Logs a message to the logger as a warning message.
        /// </summary>
        /// <param name="message">Message to log.</param>
        static void Warning(const std::string& message);

        /// <summary>
        /// Logs a message as an error.
        /// </summary>
        /// <param name="message">Message to log. </param>
        static void Error(const std::string& message);

        /// <summary>
        /// Logs a message as an exception.
        /// </summary>
        /// <param name="message">Message to log. </param>
        static void Exception(const std::string& message);

        /// <summary>
        /// Gets the event to listen to Log events.
        /// </summary>
        /// <returns>
        /// The event to subscribe to in order to listen to log events.
        /// </returns>
        static std::weak_ptr<FEventSubscriptions> GetEvent();

        /// <summary>
        /// Start the Logger.
        /// </summary>
        static void Initialise();

    private:
        /// <summary>
        /// True means have initialised.
        /// </summary>
        static bool m_setup;

        /// <summary>
        /// Event called each time we log.
        /// </summary>
        static std::shared_ptr<FEvent> m_logEvent;

        /// <summary>
        /// Logs a message of the given type.
        /// </summary>
        /// <param name="level">Level to log. </param>
        /// <param name="message">Message to add. </param>
        static void LogMessage(LogLevel level, const std::string& message);
    };
}