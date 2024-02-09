#pragma once

#include <type_traits>

namespace StandardCLibrary
{
    /// <summary>
    /// Offers help with methods used with types.
    /// </summary>
    class TypeHelpers
    {
    public:

        /// <summary>
        /// Determines if the second type is derived from the first.
        /// </summary>
        /// <typeparam name="Base">Base class. </typeparam>
        /// <typeparam name="Derived">Test derived class. </typeparam>
        /// <returns>True means is derived. </returns>
        template <typename Base, typename Derived>
        inline static bool IsDerivedFrom()
        {
            return std::is_base_of<Base, Derived>::value;
        }

        /// <summary>
        /// Determines if the second type is the base of the given type.
        /// </summary>
        /// <typeparam name="Base">Base class to test. </typeparam>
        /// <typeparam name="Derived">Derived class. </typeparam>
        /// <returns>True means is a base class. </returns>
        template <typename Base, typename Derived>
        inline static bool IsBaseOf()
        {
            return std::is_base_of<Derived, Base>::value;
        }
    };
}