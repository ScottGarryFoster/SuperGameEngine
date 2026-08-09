#pragma once
#include <deque>
#include <mutex>
#include <thread>

#include "../Observer/AllReferences.h"
#include "Logger/Log.h"

namespace FatedQuestLibraries
{
    /// <summary>
    /// Logs to file.
    /// </summary>
    class FileLogger : public FEventObserver
    {
    public:

        FileLogger();
        virtual ~FileLogger() override;

        /// <summary>
        /// Inform the observer an event has taken place.
        /// Do not store this pointer it is intended as a point for dynamic casting
        /// and not as long term storage. Directly after invocation it will be deleted.
        /// </summary>
        /// <param name="arguments">Arguments describing the event. </param>
        virtual void Invoke(const std::shared_ptr<FEventArguments>& arguments) override;

        /// <summary>
        /// Stops logging.
        /// </summary>
        void Stop();

    private:

        /// <summary>
        /// The current file path logged to.
        /// </summary>
        std::string m_currentFilePath;

        /// <summary>
        /// The thread which will actually do the writing.
        /// </summary>
        std::thread m_thread;

        /// <summary>
        /// Mutex to lock when writing files.
        /// </summary>
        std::mutex m_queueLock;

        /// <summary>
        /// Kicks the writer to perform actions.
        /// </summary>
        std::condition_variable m_writerWaker;

        /// <summary>
        /// Lines currently added to write.
        /// </summary>
        std::deque<std::string> m_linesCurrentlyToWrite;

        /// <summary>
        /// True when in the process of stopping.
        /// Should ensure you lock the mutex when reading.
        /// </summary>
        bool m_stopping;

        /// <summary>
        /// Add a line to be written.
        /// </summary>
        /// <param name="line">Line to write to the log.</param>
        void AddLine(const std::string& line);

        /// <summary>
        /// Create a log message from the outside invoke arguments.
        /// </summary>
        /// <param name="arguments">Arguments from the outside. </param>
        /// <returns>The log message to write. </returns>
        std::string CreateActualLogMessage(const std::shared_ptr<FEventArguments>& arguments) const;

        /// <summary>
        /// Performed on write thread and actually writes to file.
        /// </summary>
        void WriteThread();

        /// <summary>
        /// Get the date and time formatted.
        /// </summary>
        /// <returns>Formatted date and time. </returns>
        std::string GetDateTimeNow() const;

        /// <summary>
        /// Remove old log files from the given directory.
        /// </summary>
        /// <param name="filesToKeep">Number of files to retain in the directory. </param>
        /// <param name="directory">Directory to inspect. </param>
        /// <param name="prefix">Prefix of the log files. </param>
        void RemoveOldLogFiles(int filesToKeep, const std::string& directory, const std::string& prefix);
    };
}
