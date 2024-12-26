#include "DebugLogger.h"
#include "../../../FatedQuest.Libraries/Logger/AllReferences.h"

using namespace SuperGameEngine;

void DebugLogger::Invoke(std::shared_ptr<FEventArguments> arguments)
{
#ifdef _DEBUG
    if (auto logArguments = std::static_pointer_cast<LogEventArguments>(arguments))
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
