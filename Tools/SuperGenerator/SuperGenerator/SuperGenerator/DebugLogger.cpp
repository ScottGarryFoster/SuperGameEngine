#include "DebugLogger.h"
#include <iostream>
#include "../../../../FatedQuest.Libraries/Logger/AllReferences.h"

void DebugLogger::Invoke(std::shared_ptr<FEventArguments> arguments)
{
#if defined _DEBUG || defined _TESTS
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