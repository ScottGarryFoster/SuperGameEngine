#include "Guid.h"

using namespace FatedQuestLibraries;

void Guid::Generate()
{
    // TODO: LOG: "Guid::Generate: called. Ensure to call an actual generator not the original as this does nothing."
}

bool Guid::operator==(const Guid& other) const
{
    // TODO: LOG: "Guid::operator==: called. Ensure to call an actual implementation as this does nothing."
    return false;
}

bool Guid::operator<(const Guid& other) const
{
    return AsNumber() < other.AsNumber();
}

void Guid::FromString(std::string value)
{
    //TODO: LOG: "Guid::FromString: called. Ensure to call an actual implementation as this does nothing."
}

std::string Guid::ToString() const
{
    // TODO: LOG: "Guid::ToString: called. Ensure to call an actual implementation as this does nothing."
    return {};
}

uint64_t Guid::AsNumber() const
{
    //Logger::Warning(FString("Guid::AsNumber: called. Ensure to call an actual implementation as this does nothing."));
    return 0;
}