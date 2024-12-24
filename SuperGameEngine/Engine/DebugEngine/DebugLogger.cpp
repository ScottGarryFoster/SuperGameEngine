#include "DebugLogger.h"
#include "../../../FatedQuest.Libraries/Logger/AllReferences.h"

void SuperGameEngine::DebugLogger::Invoke(std::shared_ptr<FEventArguments> arguments)
{
#ifdef _DEBUG
    std::shared_ptr<LogEventArguments> logArguments = std::static_pointer_cast<LogEventArguments>(arguments);
    if (logArguments)
    {
        std::string from = logArguments->GetFrom();
        if (!from.empty())
        {
            std::cout << "[" << logArguments->GetFrom() << "] ";
        }

        std::cout << logArguments->GetLogMessage() << "\n";
    }
#endif

}
