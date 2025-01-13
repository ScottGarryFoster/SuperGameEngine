#pragma once
#include <string>

#include "SerializableDataType.h"

namespace SuperGameEngine
{
    /// <summary>
    /// A property exposed and serialised in the Tools.
    /// </summary>
    class SerializableProperty
    {
    public:
        ~SerializableProperty() = default;

        /// <summary>
        /// The name of the property.
        /// Must match the save and load otherwise nothing will be updated.
        /// </summary>
        /// <returns>The name of the property. </returns>
        virtual std::string GetName() const = 0;

        /// <summary>
        /// How treat the data entry for the property.
        /// </summary>
        /// <returns>The data type. </returns>
        virtual SerializableDataType GetType() const = 0;
    };
}
