#include "Object.h"
#include <typeinfo>

using namespace StandardCLibrary;

FString StandardCLibrary::Object::GetTypeName()
{
    return FString(typeid(*this).name());
}
