#pragma once
#include <memory>
#include <string>
#include <vector>

namespace FatedQuestLibraries
{
    class FVector4I;

    /// <summary>
    /// Stores basic data loaded from file.
    /// </summary>
    class UniversalObjectData
    {
    protected:
        /// <summary>
        /// Lists all the strings in the object.
        /// </summary>
        /// <returns>All the String keys. </returns>
        virtual std::vector<std::string> ListStrings() const = 0;

        /// <summary>
        /// Get a loaded string value.
        /// Will return empty if nothing found.
        /// </summary>
        /// <param name="key">Key to search for. </param>
        /// <returns>The value found or empty if nothing. </returns>
        virtual std::string GetString(const std::string& key) const = 0;

        /// <summary>
        /// True when a key is loaded.
        /// </summary>
        /// <param name="key">Key to search for. </param>
        /// <returns>True when a key is loaded. </returns>
        virtual bool IsStringLoaded(const std::string& key) const = 0;

        /// <summary>
        /// Lists all the Ints in the object.
        /// </summary>
        /// <returns>All the Int keys. </returns>
        virtual std::vector<std::string> ListInts() const = 0;

        /// <summary>
        /// Get a loaded int value.
        /// </summary>
        /// <param name="key">Key to search for. </param>
        /// <returns>The value found or -1 if nothing. </returns>
        virtual int GetInt(const std::string& key) const = 0;

        /// <summary>
        /// True when a key is loaded. 
        /// </summary>
        /// <param name="key">Key to search for. </param>
        /// <returns>True when a key is loaded. </returns>
        virtual bool IsIntLoaded(const std::string& key) const = 0;

        /// <summary>
        /// List vector4is in the object.
        /// </summary>
        /// <returns>All the keys for any Vector4Is. </returns>
        virtual std::vector<std::string> ListVector4Is() const = 0;

        /// <summary>
        /// Get a loaded Vector4I value.
        /// </summary>
        /// <param name="key">Key to search for. </param>
        /// <returns>The value found or empty if not found. </returns>
        virtual std::shared_ptr<FVector4I> GetVector4I(const std::string& key) const = 0;

        /// <summary>
        /// True when a key is loaded. 
        /// </summary>
        /// <param name="key">Key to search for. </param>
        /// <returns>True when a key is loaded. </returns>
        virtual bool IsVector4ILoaded(const std::string& key) const = 0;
    };
}
