#pragma once
#include "UniversalObjectData.h"

namespace FatedQuestLibraries
{
    /// <summary>
    /// A modifiable version of a universal object.
    /// </summary>
    class ModifiableUniversalObjectData : public virtual UniversalObjectData
    {
    public:

        /// <summary>
        /// Sets the string to the given value.
        /// </summary>
        /// <param name="key">Key to search for. </param>
        /// <param name="value">Value to set. </param>
        virtual void SetString(const std::string& key, const std::string& value) = 0;

        /// <summary>
        /// Removes key from the object.
        /// </summary>
        /// <param name="key">Key to search for. </param>
        /// <returns>True means Key was unset, false means key never existed. </returns>
        virtual bool UnsetString(const std::string& key) = 0;

        /// <summary>
        /// Sets the int to the given value.
        /// </summary>
        /// <param name="key">Key to search for. </param>
        /// <param name="value">Value to set. </param>
        virtual void SetInt(const std::string& key, int value) = 0;

        /// <summary>
        /// Removes key from the object.
        /// </summary>
        /// <param name="key">Key to search for. </param>
        /// <returns>True means Key was unset, false means key never existed. </returns>
        virtual bool UnsetInt(const std::string& key) = 0;

        /// <summary>
        /// Sets the vector4I to the given value.
        /// </summary>
        /// <param name="key">Key to search for. </param>
        /// <param name="value">Value to set. </param>
        virtual void SetVector4I(const std::string& key, const FVector4I& value) = 0;

        /// <summary>
        /// Sets the vector4I to the given value.
        /// </summary>
        /// <param name="key">Key to search for. </param>
        /// <param name="x">X value to set. </param>
        /// <param name="y">Y value to set. </param>
        /// <param name="z">Z value to set. </param>
        /// <param name="w">W value to set. </param>
        virtual void SetVector4I(const std::string& key, int x, int y, int z, int w) = 0;

        /// <summary>
        /// Removes key from the object.
        /// </summary>
        /// <param name="key">Key to search for. </param>
        /// <returns>True means Key was unset, false means key never existed. </returns>
        virtual bool UnsetVector4I(const std::string& key) = 0;
    };
}
