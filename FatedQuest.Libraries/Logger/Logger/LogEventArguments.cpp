#include "LogEventArguments.h"

using namespace FatedQuestLibraries;

LogEventArguments::LogEventArguments()
{
    m_message = {};
    m_logLevel = LogLevel::Unknown;
}

LogLevel LogEventArguments::GetLevel() const
{
    return m_logLevel;
}

void LogEventArguments::SetLevel(LogLevel level)
{
    m_logLevel = level;
}

std::string LogEventArguments::GetLogMessage() const
{
    return m_message;
}

void LogEventArguments::SetLogMessage(const std::string& message)
{
    m_message = message;
}

std::string LogEventArguments::GetFrom() const
{
    return m_from;
}

void LogEventArguments::SetFrom(const std::string& message)
{
    m_from = message;
}

std::string LogEventArguments::GetException() const
{
    return m_exception;
}

void LogEventArguments::SetException(const std::string& message)
{
    m_exception = message;
}
