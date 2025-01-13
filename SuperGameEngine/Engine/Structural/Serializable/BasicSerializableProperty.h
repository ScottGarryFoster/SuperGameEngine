#pragma once
#include "SerializableProperty.h"

namespace SuperGameEngine
{
    /// <summary>
    /// A basic property which simply provides information.
    /// </summary>
    class BasicSerializableProperty : public SerializableProperty
    {
    public:
        BasicSerializableProperty();

        /// <summary>
        /// The name of the property.
        /// Must match the save and load otherwise nothing will be updated.
        /// </summary>
        /// <returns>The name of the property. </returns>
        virtual std::string GetName() const;

        /// <summary>
        /// Set a new name for the property.
        /// </summary>
        /// <param name="name">New name. </param>
        void SetName(const std::string& name);

        /// <summary>
        /// How treat the data entry for the property.
        /// </summary>
        /// <returns>The data type. </returns>
        virtual SerializableDataType GetType() const;

        /// <summary>
        /// Set a new type.
        /// </summary>
        /// <param name="type">New type. </param>
        void SetType(SerializableDataType type);

    private:
        /// <summary>
        /// The name of the property.
        /// </summary>
        std::string m_name;

        /// <summary>
        /// How treat the data entry for the property.
        /// </summary>
        SerializableDataType m_type;
    };
}


