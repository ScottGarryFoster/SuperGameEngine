#include "SuperProjectProperties.h"
#include "../../../../FatedQuest.Libraries/Logger/AllReferences.h"

using namespace SuperGameEngine;
using namespace FatedQuestLibraries;

SuperProjectProperties::SuperProjectProperties(
    const std::shared_ptr<StoredDocument>& universalObject)
    : DocumentUniversalObjectData(universalObject)
{
#ifdef _DEBUG
    const std::vector<std::string> requiredStrings = { "StartScene", "WindowTitle" };
    for (const std::string& requiredValue : requiredStrings)
    {
        if (!IsStringLoaded(requiredValue))
        {
            Log::Error("Could not load Project Properties. Could not find: " + requiredValue);
        }
    }
#endif
}

std::string SuperProjectProperties::GetStartScene() const
{
    return GetString("StartScene");
}

std::string SuperProjectProperties::GetWindowTitle() const
{
    return GetString("WindowTitle");
}
