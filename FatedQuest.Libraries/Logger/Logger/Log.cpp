#include "Log.h"

#include "LogEventArguments.h"
#include "../../StandardObjects/Events/FEvent.h"

using namespace FatedQuestLibraries;

bool Log::m_setup = false;
std::shared_ptr<FEvent> Log::m_logEvent;

void Log::Info(const std::string& message)
{
    LogMessage(LogLevel::Info, message);
}

void Log::Warning(const std::string& message)
{
    LogMessage(LogLevel::Warning, message);
}

void Log::Error(const std::string& message)
{
    LogMessage(LogLevel::Error, message);
}

void Log::Exception(const std::string& message)
{
    LogMessage(LogLevel::Exception, message);
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

void Log::LogMessage(LogLevel level, const std::string& message)
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
