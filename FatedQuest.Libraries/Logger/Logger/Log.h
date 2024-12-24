#pragma once
#include <memory>
#include <string>

namespace FatedQuestLibraries
{
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
    };
}