#include "Log.h"

#include "LogEventArguments.h"
#include "../../Observer/AllReferences.h"

using namespace FatedQuestLibraries;

bool Log::m_setup = false;
std::shared_ptr<FEvent> Log::m_logEvent;

void Log::Info(const std::string& message)
{
    LogMessage(LogLevel::Info, message, {}, {});
}

void Log::Info(const std::string& message, const std::string& from)
{
    LogMessage(LogLevel::Info, message, from, {});
}

void Log::Warning(const std::string& message)
{
    LogMessage(LogLevel::Warning, message, {}, {});
}

void Log::Warning(const std::string& message, const std::string& from)
{
    LogMessage(LogLevel::Warning, message, from, {});
}

void Log::Error(const std::string& message)
{
    LogMessage(LogLevel::Error, message, {}, {});
}

void Log::Error(const std::string& message, const std::string& from)
{
    LogMessage(LogLevel::Error, message, from, {});
}

void Log::Exception(const std::string& message)
{
    LogMessage(LogLevel::Exception, message, {}, {});
}

void Log::Exception(const std::string& message, const std::string& from, const std::string& exception)
{
    LogMessage(LogLevel::Exception, message, from, {});
}

std::weak_ptr<FEventSubscriptions> Log::GetEvent()
{
    if (!m_setup)
    {
        Initialise();
    }

    return m_logEvent;
}

void Log::Initialise()
{
    if (m_setup)
    {
        return;
    }

    m_logEvent = std::make_shared<FEvent>();
    m_setup = true;
}

void Log::LogMessage(LogLevel level, const std::string& message, const std::string& from, const std::string& exception)
{
    if (!m_setup)
    {
        Initialise();
    }

    auto arguments = std::make_shared<LogEventArguments>();
    arguments->SetLevel(level);
    arguments->SetLogMessage(message);
    m_logEvent->Invoke(arguments);
}
