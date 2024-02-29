#pragma once
#include <objbase.h>
#include <Windows.h>
#include "GUID.h"

namespace StandardCLibrary
{
    /// <summary>
    /// A unique identifier.
    /// A GUID should be unique.
    /// </summary>
    class WindowsGUID : public Guid
    {
    public:
        WindowsGUID();

        /// <summary>
        /// Generates a random GUID.
        /// </summary>
        virtual void Generate() override;

        virtual bool operator==(Guid& other) const override;

        /// <summary>
        /// Creates a GUID from string.
        /// </summary>
        /// <param name="value">Value to generate from. </param>
        virtual void FromString(std::string value) override;

        /// <summary>
        /// Convert GUID to string and return result.
        /// </summary>
        /// <returns>GUID as a string. </returns>
        virtual std::string ToString() const override;

        /// <summary>
        /// Convert GUID to FString and return result.
        /// </summary>
        /// <returns>GUID as FString. </returns>
        virtual FString ToFString() const override;

    private:
        /// <summary>
        /// Actual guid storage.
        /// </summary>
        ::GUID m_guid;
    };
}