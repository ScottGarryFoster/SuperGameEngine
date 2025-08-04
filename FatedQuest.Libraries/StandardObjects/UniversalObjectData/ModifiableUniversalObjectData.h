#pragma once
#include "UniversalObjectData.h"

namespace FatedQuestLibraries
{
    class Guid;

    /// <summary>
    /// A modifiable version of a universal object.
    /// </summary>
    class ModifiableUniversalObjectData : public virtual UniversalObjectData
    {
    public:
        /// <summary>
        /// Get the guid for this universal Object Data.
        /// </summary>
        /// <returns>The unique ID for this object. </returns>
        virtual std::shared_ptr<Guid> GetGuid() const = 0;

        /// <summary>
        /// True means there were changes in this object differing from creation which would affect an export of the data.
        /// </summary>
        /// <returns>True means there were changes in this object differing from creation which would affect an export of the data. </returns>
        virtual bool IsDirty() const = 0;

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

        //
        //  These are Universal Object Data Methods changed to be public
        //

        /// <summary>
        /// Lists all the strings in the object.
        /// </summary>
        /// <returns>All the String keys. </returns>
        virtual std::vector<std::string> ListStrings() const override = 0;

        /// <summary>
        /// Get a loaded string value.
        /// Will return empty if nothing found.
        /// </summary>
        /// <param name="key">Key to search for. </param>
        /// <returns>The value found or empty if nothing. </returns>
        virtual std::string GetString(const std::string& key) const override = 0;

        /// <summary>
        /// True when a key is loaded.
        /// </summary>
        /// <param name="key">Key to search for. </param>
        /// <returns>True when a key is loaded. </returns>
        virtual bool IsStringLoaded(const std::string& key) const override = 0;

        /// <summary>
        /// Lists all the Ints in the object.
        /// </summary>
        /// <returns>All the Int keys. </returns>
        virtual std::vector<std::string> ListInts() const override = 0;

        /// <summary>
        /// Get a loaded int value.
        /// </summary>
        /// <param name="key">Key to search for. </param>
        /// <returns>The value found or -1 if nothing. </returns>
        virtual int GetInt(const std::string& key) const override = 0;

        /// <summary>
        /// True when a key is loaded. 
        /// </summary>
        /// <param name="key">Key to search for. </param>
        /// <returns>True when a key is loaded. </returns>
        virtual bool IsIntLoaded(const std::string& key) const override = 0;

        /// <summary>
        /// List vector4is in the object.
        /// </summary>
        /// <returns>All the keys for any Vector4Is. </returns>
        virtual std::vector<std::string> ListVector4Is() const override = 0;

        /// <summary>
        /// Get a loaded Vector4I value.
        /// </summary>
        /// <param name="key">Key to search for. </param>
        /// <returns>The value found or empty if not found. </returns>
        virtual std::shared_ptr<FVector4I> GetVector4I(const std::string& key) const override = 0;

        /// <summary>
        /// True when a key is loaded. 
        /// </summary>
        /// <param name="key">Key to search for. </param>
        /// <returns>True when a key is loaded. </returns>
        virtual bool IsVector4ILoaded(const std::string& key) const override = 0;
    };
}
