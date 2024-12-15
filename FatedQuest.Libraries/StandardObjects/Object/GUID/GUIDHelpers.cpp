#include "GUIDHelpers.h"
#include "GUID.h"
#include "WindowsGUID.h"

using namespace FatedQuestLibraries;
std::shared_ptr<Guid> GUIDHelpers::CreateGUID()
{
    std::shared_ptr<Guid> guid = std::make_shared<WindowsGUID>();
    guid->Generate();
    return guid;
}

std::shared_ptr<Guid> GUIDHelpers::CreateFromString(std::string value)
{
    std::shared_ptr<Guid> guid = std::make_shared<WindowsGUID>();
    guid->FromString(value);
    return guid;
}

std::string GUIDHelpers::ToString(Guid& guid)
{
    return guid.ToString();
}