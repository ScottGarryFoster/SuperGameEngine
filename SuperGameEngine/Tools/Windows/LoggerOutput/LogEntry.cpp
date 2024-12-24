#include "LogEntry.h"

using namespace SuperGameTools;

LogEntry::LogEntry()
{
    m_message = {};
    m_logLevel = LogLevel::Unknown;
    m_timestamp = {};
    m_completeMessage = {};
    m_from = {};
    m_exception = {};

    std::time_t currentTime = std::time(nullptr);
    std::tm localTime;

    if (localtime_s(&localTime, &currentTime) != 0)
    {
        // Ironically I can't log this.
        return;
    }

    std::string month = std::to_string(localTime.tm_mon + 1);
    if (month.size() == 1)
    {
        month = "0" + month;
    }

    std::string day = std::to_string(localTime.tm_mday);
    if (day.size() == 1)
    {
        day = "0" + day;
    }

    std::string hour = std::to_string(localTime.tm_hour);
    if (hour.size() == 1)
    {
        hour = "0" + hour;
    }

    std::string minute = std::to_string(localTime.tm_min);
    if (minute.size() == 1)
    {
        minute = "0" + minute;
    }

    std::string second = std::to_string(localTime.tm_sec);
    if (second.size() == 1)
    {
        second = "0" + second;
    }

    std::stringstream outputStream;
    outputStream << day;
    outputStream << "/" << month;
    outputStream << "/" << (localTime.tm_year + 1900);
    outputStream << " " << hour;
    outputStream << ":" << minute;
    outputStream << ":" << second;

    m_timestamp = outputStream.str();
}

LogEntry::~LogEntry()
{
}

LogLevel LogEntry::GetLevel() const
{
    return m_logLevel;
}

void LogEntry::SetLevel(LogLevel level)
{
    m_logLevel = level;
}

std::string LogEntry::GetLogMessage() const
{
    return m_message;
}

void LogEntry::SetLogMessage(const std::string& message)
{
    m_message = message;
    UpdateCompleteMessage();
}

std::string LogEntry::GetFrom() const
{
    return m_from;
}

void LogEntry::SetFrom(const std::string& message)
{
    m_from = message;
    UpdateCompleteMessage();
}

std::string LogEntry::GetException() const
{
    return m_exception;
}

void LogEntry::SetException(const std::string& message)
{
    m_exception = message;
    UpdateCompleteMessage();
}

std::string LogEntry::Write() const
{
    return m_completeMessage;
}

void LogEntry::UpdateCompleteMessage()
{
    std::stringstream ss;
    if (!m_timestamp.empty())
    {
        ss << "[" << m_timestamp << "] ";
    }

    if (!m_from.empty())
    {
        ss << "[" << m_from << "] ";
    }

    if (!m_exception.empty())
    {
        ss << m_exception << ": ";
    }

    ss << m_message;
    m_completeMessage = ss.str();
}
