#include "TypeHelpers.h"

using namespace StandardCLibrary;

template<typename Base, typename Derived>
bool TypeHelpers::IsDerivedFrom()
{
    return std::is_base_of<Base, Derived>::value;
}

template<typename Derived, typename Base>
bool TypeHelpers::IsBaseOf()
{
    return std::is_base_of<Base, Derived>::value;
}
