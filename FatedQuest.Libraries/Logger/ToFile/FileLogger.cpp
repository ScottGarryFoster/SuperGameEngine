#include "FileLogger.h"

#include <filesystem>
#include <fstream>

#include "Logger/LogEventArguments.h"
namespace FileSystem = std::filesystem;

using namespace FatedQuestLibraries;

FileLogger::FileLogger()
{
    m_stopping = false;
    m_currentFilePath = "";
    try
    {
        FileSystem::path temp = std::filesystem::temp_directory_path();
        FileSystem::path combinedPath = temp / "SuperGameEngine" / "Tools" / "Logs";
        FileSystem::create_directories(combinedPath);

        const auto logFilePath = combinedPath / ("SuperGameTools_" + GetDateTimeNow() + ".txt");
        m_currentFilePath = logFilePath.string();

        RemoveOldLogFiles(10, combinedPath.string(), "SuperGameTools_");
    }
    catch (const std::exception e)
    {
        // Cannot continue if we cannot find a temp location.
        Log::Error("Cannot find a temp path to log to. File logger will not work.");
    }

    m_thread = std::thread(&FileLogger::WriteThread, this);
}

FileLogger::~FileLogger()
{
    Stop();
}

void FileLogger::Invoke(const std::shared_ptr<FEventArguments>& arguments)
{
    if (m_currentFilePath.empty())
    {
        return;
    }

    AddLine(CreateActualLogMessage(arguments));
}

void FileLogger::Stop()
{
    {
        std::scoped_lock lock(m_queueLock);

        if (m_stopping)
        {
            return;
        }

        m_stopping = true;
    }

    m_writerWaker.notify_one();

    if (m_thread.joinable())
    {
        m_thread.join();
    }
}

void FileLogger::AddLine(const std::string& line)
{
    {
        std::scoped_lock lock(m_queueLock);

        if (m_stopping)
        {
            return;
        }

        m_linesCurrentlyToWrite.push_back(line);
    }

    m_writerWaker.notify_one();
}

std::string FileLogger::CreateActualLogMessage(const std::shared_ptr<FEventArguments>& arguments) const
{
    std::string output = {};
    if (auto logArguments = std::static_pointer_cast<LogEventArguments>(arguments))
    {
        output = "[" + GetDateTimeNow() + "]";
        output += "[" + ELogLevel::ToString(logArguments->GetLevel()) + "] ";
        if (!logArguments->GetFrom().empty())
        {
            output += "[" + logArguments->GetFrom() + "] ";
        }

        output += logArguments->GetLogMessage();
    }

    return output;
}

void FileLogger::WriteThread()
{
    std::deque<std::string> pendingLines;

    std::ofstream file(m_currentFilePath, std::ios::out | std::ios::app);
    while (true)
    {
        {
            std::unique_lock lock(m_queueLock);

            m_writerWaker.wait(lock, [this]
            {
                return m_stopping || !m_linesCurrentlyToWrite.empty();
            });

            // All queued lines have been written, so exit cleanly.
            if (m_stopping && m_linesCurrentlyToWrite.empty())
            {
                break;
            }

            // Move all current messages into a local queue quickly,
            // allowing other threads to continue calling AddLine().
            pendingLines.swap(m_linesCurrentlyToWrite);
        }

        for (const std::string& line : pendingLines)
        {
            file << line << '\n';
        }

        file.flush();
        pendingLines.clear();
    }

    file.flush();
}

std::string FileLogger::GetDateTimeNow() const
{
    // Parses an int. Keep in mind Logger project needs to be devoid of any other references.
    auto TryParse = [](const std::string& parsing, int& outValue)
        {
            outValue = -1;
            try
            {
                outValue = std::stoi(parsing);
                return true;
            }
            catch (const std::exception e)
            {

            }

            return false;
        };

    const auto now = std::chrono::system_clock::now();

    // We need to remove the decimal which comes with the default formatting.
    int outSeconds = -1;
    std::string secondsAsDecimal = std::format("{:%S}", now);
    if (!TryParse(secondsAsDecimal, outSeconds))
    {
        return {};
    }

    std::string timeFormated = std::format("{:%Y-%m-%d_%H-%M}", now);
    timeFormated += "-" + std::to_string(outSeconds);

    return timeFormated;
}

void FileLogger::RemoveOldLogFiles(int filesToKeep, const std::string& directory, const std::string& prefix)
{
    struct FileInfo
    {
        std::filesystem::path path;
        std::filesystem::file_time_type lastWriteTime;
    };

    std::vector<FileInfo> files;
    std::error_code error;

    for (const auto& entry : FileSystem::directory_iterator(directory, error))
    {
        if (error)
        {
            return;
        }

        // Ignore directories, symbolic links, etc.
        if (!entry.is_regular_file(error))
        {
            error.clear();
            continue;
        }

        if (!entry.path().filename().string().starts_with(prefix))
        {
            continue;
        }

        const auto lastWriteTime = entry.last_write_time(error);

        if (error)
        {
            error.clear();
            continue;
        }

        files.push_back({ entry.path(), lastWriteTime });
    }

    // Newest files first.
    std::sort(files.begin(), files.end(),
        [](const FileInfo& left, const FileInfo& right)
        {
            return left.lastWriteTime > right.lastWriteTime;
        });

    // Delete the oldest files above the number given.
    for (std::size_t index = filesToKeep; index < files.size(); ++index)
    {
        std::filesystem::remove(files[index].path, error);
        error.clear();
    }
}
