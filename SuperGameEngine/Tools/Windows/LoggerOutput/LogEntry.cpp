#include "LogEntry.h"

using namespace SuperGameTools;

LogEntry::LogEntry()
{
    m_message = {};
    m_logLevel = LogLevel::Unknown;
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
}
