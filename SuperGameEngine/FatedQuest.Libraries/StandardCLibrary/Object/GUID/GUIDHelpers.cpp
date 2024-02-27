#include "GUIDHelpers.h"
#include "GUID.h"
#include "WindowsGUID.h"

using namespace StandardCLibrary;
std::shared_ptr<StandardCLibrary::GUID> StandardCLibrary::GUIDHelpers::CreateGUID()
{
    std::shared_ptr<GUID> guid = std::make_shared<WindowsGUID>();
    guid->Generate();
    return guid;
}

std::shared_ptr<StandardCLibrary::GUID> GUIDHelpers::CreateFromString(std::string value)
{
    std::shared_ptr<GUID> guid = std::make_shared<WindowsGUID>();
    guid->FromString(value);
    return guid;
}

std::string GUIDHelpers::ToString(StandardCLibrary::GUID& guid)
{
    return guid.ToString();
}

FString StandardCLibrary::GUIDHelpers::ToFString(StandardCLibrary::GUID& guid)
{
    return guid.ToFString();
}
