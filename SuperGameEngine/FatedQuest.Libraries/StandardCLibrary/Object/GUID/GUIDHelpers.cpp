#include "GUIDHelpers.h"
#include "GUID.h"
#include "WindowsGUID.h"

using namespace StandardCLibrary;
std::shared_ptr<StandardCLibrary::Guid> StandardCLibrary::GUIDHelpers::CreateGUID()
{
    std::shared_ptr<Guid> guid = std::make_shared<WindowsGUID>();
    guid->Generate();
    return guid;
}

std::shared_ptr<StandardCLibrary::Guid> GUIDHelpers::CreateFromString(std::string value)
{
    std::shared_ptr<Guid> guid = std::make_shared<WindowsGUID>();
    guid->FromString(value);
    return guid;
}

std::string GUIDHelpers::ToString(StandardCLibrary::Guid& guid)
{
    return guid.ToString();
}

FString StandardCLibrary::GUIDHelpers::ToFString(StandardCLibrary::Guid& guid)
{
    return guid.ToFString();
}
