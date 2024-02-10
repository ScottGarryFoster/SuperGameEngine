#include "Object.h"
#include <typeinfo>

using namespace StandardCLibrary;

FString StandardCLibrary::Object::GetTypeName() const
{
    return FString(typeid(*this).name());
}
