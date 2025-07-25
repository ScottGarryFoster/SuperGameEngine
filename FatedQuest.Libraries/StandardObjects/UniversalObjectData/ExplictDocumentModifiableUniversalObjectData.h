#pragma once
#include "DocumentModifiableUniversalObjectData.h"

namespace FatedQuestLibraries
{
    class StoredDocument;

    /// <summary>
    /// A modifiable version of a universal object that can exported to a document.
    /// </summary>
    class ExplictDocumentModifiableUniversalObjectData : public virtual DocumentModifiableUniversalObjectData
    {
    public:
        ExplictDocumentModifiableUniversalObjectData();

        /// <summary>
        /// Exports the data stored to a document format.
        /// </summary>
        /// <returns>The data within the object as a document. </returns>
        virtual std::shared_ptr<StoredDocument> ExportToDocument() const override;

        /// <summary>
        /// Sets the string to the given value.
        /// </summary>
        /// <param name="key">Key to search for. </param>
        /// <param name="value">Value to set. </param>
        virtual void SetString(const std::string& key, const std::string& value) const override;

        /// <summary>
        /// Get a loaded string value.
        /// Will return empty if nothing found.
        /// </summary>
        /// <param name="key">Key to search for. </param>
        /// <returns>The value found or empty if nothing. </returns>
        virtual std::string GetString(const std::string& key) const override;

        /// <summary>
        /// True when a key is loaded.
        /// </summary>
        /// <param name="key">Key to search for. </param>
        /// <returns>True when a key is loaded. </returns>
        virtual bool IsStringLoaded(const std::string& key) const override;

        /// <summary>
        /// Sets the int to the given value.
        /// </summary>
        /// <param name="key">Key to search for. </param>
        /// <param name="value">Value to set. </param>
        virtual void SetInt(const std::string& key, int value) const override;

        /// <summary>
        /// Get a loaded int value.
        /// </summary>
        /// <param name="key">Key to search for. </param>
        /// <returns>The value found or -1 if nothing. </returns>
        virtual int GetInt(const std::string& key) const override;

        /// <summary>
        /// True when a key is loaded. 
        /// </summary>
        /// <param name="key">Key to search for. </param>
        /// <returns>True when a key is loaded. </returns>
        virtual bool IsIntLoaded(const std::string& key) const override;

        /// <summary>
        /// Sets the vector4I to the given value.
        /// </summary>
        /// <param name="key">Key to search for. </param>
        /// <param name="value">Value to set. </param>
        virtual void SetVector4I(const std::string& key, const FVector4I& value) const override;

        /// <summary>
        /// Sets the vector4I to the given value.
        /// </summary>
        /// <param name="key">Key to search for. </param>
        /// <param name="x">X value to set. </param>
        /// <param name="y">Y value to set. </param>
        /// <param name="z">Z value to set. </param>
        /// <param name="w">W value to set. </param>
        virtual void SetVector4I(const std::string& key, int x, int y, int z, int w) const override;

        /// <summary>
        /// Get a loaded Vector4I value.
        /// </summary>
        /// <param name="key">Key to search for. </param>
        /// <returns>The value found or empty if not found. </returns>
        virtual std::shared_ptr<FVector4I> GetVector4I(const std::string& key) const override;

        /// <summary>
        /// True when a key is loaded. 
        /// </summary>
        /// <param name="key">Key to search for. </param>
        /// <returns>True when a key is loaded. </returns>
        virtual bool IsVector4ILoaded(const std::string& key) const override;
    };
}
