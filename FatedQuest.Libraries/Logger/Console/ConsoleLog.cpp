#include "ConsoleLog.h"

#include <iostream>

#include "../../../FatedQuest.Libraries/Logger/AllReferences.h"

using namespace FatedQuestLibraries;

void ConsoleLog::Invoke(std::shared_ptr<FEventArguments> arguments)
{
    if (auto logArguments = std::static_pointer_cast<LogEventArguments>(arguments))
    {
        std::string from = logArguments->GetFrom();
        if (!from.empty())
        {
            std::cout << "[" << logArguments->GetFrom() << "] ";
        }

        std::cout << logArguments->GetLogMessage() << "\n";
    }
}
