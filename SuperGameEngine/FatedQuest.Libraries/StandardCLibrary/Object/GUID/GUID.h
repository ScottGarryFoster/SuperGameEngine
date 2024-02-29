#pragma once
#include "../../Text/FString.h"

namespace StandardCLibrary
{
    /// <summary>
    /// A unique identifier.
    /// A GUID should be unique.
    /// </summary>
    class Guid
    {
    public:
        /// <summary>
        /// Generates a random GUID.
        /// </summary>
        virtual void Generate() = 0;

        virtual bool operator==(Guid& other) const = 0;

        /// <summary>
        /// Creates a GUID from string.
        /// </summary>
        /// <param name="value">Value to generate from. </param>
        virtual void FromString(std::string value) = 0;

        /// <summary>
        /// Convert GUID to string and return result.
        /// </summary>
        /// <returns>GUID as a string. </returns>
        virtual std::string ToString() const = 0;

        /// <summary>
        /// Convert GUID to FString and return result.
        /// </summary>
        /// <returns>GUID as FString. </returns>
        virtual FString ToFString() const = 0;
    };
}