#pragma once
#include <objbase.h>
#include <Windows.h>
#include "GUID.h"

namespace FatedQuestLibraries
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

        virtual bool operator==(const Guid& other) const override;

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
        /// Returns the GUID converted to a number for comparison purposes.
        /// </summary>
        /// <returns>The number representation of the GUID. </returns>
        virtual uint64_t AsNumber() const override;

    private:
        /// <summary>
        /// Actual guid storage.
        /// </summary>
        ::GUID m_guid;

        /// <summary>
        /// Preconverted number on set.
        /// </summary>
        uint64_t m_asNumber;

        uint64_t ToNumber(const GUID& guid);
    };
}