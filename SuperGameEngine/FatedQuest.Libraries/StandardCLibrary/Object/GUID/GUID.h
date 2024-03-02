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
        virtual void Generate();

        virtual bool operator==(const Guid& other) const;
        virtual bool operator<(const Guid& other) const;

        /// <summary>
        /// Creates a GUID from string.
        /// </summary>
        /// <param name="value">Value to generate from. </param>
        virtual void FromString(std::string value);

        /// <summary>
        /// Convert GUID to string and return result.
        /// </summary>
        /// <returns>GUID as a string. </returns>
        virtual std::string ToString() const;

        /// <summary>
        /// Convert GUID to FString and return result.
        /// </summary>
        /// <returns>GUID as FString. </returns>
        virtual FString ToFString() const;

        /// <summary>
        /// Returns the GUID converted to a number for comparison purposes.
        /// </summary>
        /// <returns>The number representation of the GUID. </returns>
        virtual uint64_t AsNumber() const;
    };
}