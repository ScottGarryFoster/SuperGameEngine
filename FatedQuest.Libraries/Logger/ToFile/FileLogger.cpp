#include "FileLogger.h"

#include <filesystem>
#include <fstream>

#include "Logger/LogEventArguments.h"
namespace FileSystem = std::filesystem;

using namespace FatedQuestLibraries;

FileLogger::FileLogger()
{
    m_currentFilePath = "";
    try
    {
        FileSystem::path temp = std::filesystem::temp_directory_path();
        FileSystem::path combinedPath = temp / "SuperGameEngine" / "Tools" / "Logs";
        FileSystem::create_directories(combinedPath);

        const auto now = std::chrono::system_clock::now();
        const std::string timeFormated = std::format("{:%Y-%m-%d_%H-%M-%S}", now);
        const auto logFilePath = combinedPath / ("SuperGameTools_" + timeFormated + ".txt");

        m_currentFilePath = logFilePath.string();
    }
    catch (const std::exception e)
    {
        // Cannot continue if we cannot find a temp location.
        Log::Error("Cannot find a temp path to log to. File logger will not work.");
    }
}

void FileLogger::Invoke(const std::shared_ptr<FEventArguments>& arguments)
{
    if (m_currentFilePath.empty())
    {
        return;
    }

    std::ofstream file(m_currentFilePath, std::ios::out | std::ios::app);

    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open log file.");
    }

    std::string output = CreateActualLogMessage(arguments);
    if (output.empty())
    {
        return;
    }

    file << output << '\n';

    if (!file) {
        throw std::runtime_error("Failed while writing to log file.");
    }
}

std::string FileLogger::CreateActualLogMessage(const std::shared_ptr<FEventArguments>& arguments) const
{
    std::string output = "";
    if (auto logArguments = std::static_pointer_cast<LogEventArguments>(arguments))
    {
        output = logArguments->GetFrom();
        if (!output.empty())
        {
            output += "[" + logArguments->GetFrom() + "] ";
        }

        output += logArguments->GetLogMessage() + "\n";
    }

    return output;
}
