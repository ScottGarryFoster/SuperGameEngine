#pragma once
#include "../Object.h"
#include "Guid.h"

namespace StandardCLibrary
{
    /// <summary>
    /// Helper methods for GUID which sits outside of GUID implementation.
    /// </summary>
    class GUIDHelpers : public Object
    {
    public:
        /// <summary>
        /// Creates a new unique GUID.
        /// </summary>
        /// <returns>New Unique GUID. </returns>
        /// <remark>
        /// Using this means you do not need to think about platform.
        /// It will change with Windows, Linux etc.
        /// </remark>
        static std::shared_ptr<Guid> CreateGUID();

        /// <summary>
        /// Creates a GUID from String.
        /// </summary>
        /// <param name="value">Value to generate from. </param>
        /// <returns>GUID generated. </returns>
        static std::shared_ptr<Guid> CreateFromString(std::string value);

        /// <summary>
        /// Convert GUID to string and return result.
        /// </summary>
        /// <param name="guid">GUID to convert. </param>
        /// <returns>GUID as a string. </returns>
        static std::string ToString(Guid& guid);

        /// <summary>
        /// Convert GUID to fstring and return result.
        /// </summary>
        /// <param name="guid">GUID to convert. </param>
        /// <returns>GUID as a fstring. </returns>
        static FString ToFString(Guid& guid);
    };

}