#pragma once

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
        static bool IsDerivedFrom();

        /// <summary>
        /// Determines if the second type is the base of the given type.
        /// </summary>
        /// <typeparam name="Derived">Derived class. </typeparam>
        /// <typeparam name="Base">Base class to test. </typeparam>
        /// <returns>True means is a base class. </returns>
        template <typename Derived, typename Base>
        static bool IsBaseOf();
    };
}