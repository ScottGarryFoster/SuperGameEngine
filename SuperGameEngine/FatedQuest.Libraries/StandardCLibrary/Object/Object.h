#pragma once

#include "../Text/FString.h"

namespace StandardCLibrary
{
    /// <summary>
    /// Parent of all objects.
    /// </summary>
    class Object
    {
    public:
        virtual ~Object(){}

        /// <summary>
        /// The name of the type.
        /// This is the most derived name.
        /// </summary>
        /// <returns>Type as a string. </returns>
        FString GetTypeName();
    };
}