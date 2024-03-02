#include "Guid.h"
#include "../../../Logging/Logger.h"

using namespace StandardCLibrary;

void Guid::Generate()
{
    Logger::Warning(FString("Guid::Generate: called. Ensure to call an actual generator not the original as this does nothing."));
}

bool Guid::operator==(const Guid& other) const
{
    Logger::Warning(FString("Guid::operator==: called. Ensure to call an actual implementation as this does nothing."));
    return false;
}

bool StandardCLibrary::Guid::operator<(const Guid& other) const
{
    return AsNumber() < other.AsNumber();
}

void Guid::FromString(std::string value)
{
    Logger::Warning(FString("Guid::FromString: called. Ensure to call an actual implementation as this does nothing."));
}

std::string Guid::ToString() const
{
    Logger::Warning(FString("Guid::ToString: called. Ensure to call an actual implementation as this does nothing."));
    return std::string();
}

FString Guid::ToFString() const
{
    Logger::Warning(FString("Guid::ToFString: called. Ensure to call an actual implementation as this does nothing."));
    return FString();
}

uint64_t StandardCLibrary::Guid::AsNumber() const
{
    //Logger::Warning(FString("Guid::AsNumber: called. Ensure to call an actual implementation as this does nothing."));
    return 0;
}
