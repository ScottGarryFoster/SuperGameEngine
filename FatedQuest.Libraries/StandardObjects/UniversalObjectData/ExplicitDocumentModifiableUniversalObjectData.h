#pragma once
#include <unordered_map>

#include "DocumentModifiableUniversalObjectData.h"

namespace FatedQuestLibraries
{
    class UniversalObjectParser;
}

namespace FatedQuestLibraries
{

    /// <summary>
    /// A modifiable version of a universal object that can exported to a document.
    /// </summary>
    class ExplicitDocumentModifiableUniversalObjectData : public virtual DocumentModifiableUniversalObjectData
    {
    public:
        ExplicitDocumentModifiableUniversalObjectData();

        /// <summary>
        /// Exports the data stored to a document format.
        /// </summary>
        /// <returns>The data within the object as a document. </returns>
        virtual std::shared_ptr<ModifiableDocument> ExportToDocument() override;

        /// <summary>
        /// Imports data as a document.
        /// </summary>
        /// <param name="document">The document to load the information from.</param>
        /// <returns>True means loaded successfully. </returns>
        virtual bool ImportAsDocument(const std::shared_ptr<StoredDocument>& document) override;

        /// <summary>
        /// Lists all the strings in the object.
        /// </summary>
        /// <returns>All the String keys. </returns>
        virtual std::vector<std::string> ListStrings() const override;

        /// <summary>
        /// Sets the string to the given value.
        /// </summary>
        /// <param name="key">Key to search for. </param>
        /// <param name="value">Value to set. </param>
        virtual void SetString(const std::string& key, const std::string& value) override;

        /// <summary>
        /// Removes key from the object.
        /// </summary>
        /// <param name="key">Key to search for. </param>
        /// <returns>True means Key was unset, false means key never existed. </returns>
        virtual bool UnsetString(const std::string& key) override;

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
        /// Lists all the Ints in the object.
        /// </summary>
        /// <returns>All the Int keys. </returns>
        virtual std::vector<std::string> ListInts() const override;

        /// <summary>
        /// Sets the int to the given value.
        /// </summary>
        /// <param name="key">Key to search for. </param>
        /// <param name="value">Value to set. </param>
        virtual void SetInt(const std::string& key, int value) override;

        /// <summary>
        /// Removes key from the object.
        /// </summary>
        /// <param name="key">Key to search for. </param>
        /// <returns>True means Key was unset, false means key never existed. </returns>
        virtual bool UnsetInt(const std::string& key) override;

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
        /// List vector4is in the object.
        /// </summary>
        /// <returns>All the keys for any Vector4Is. </returns>
        virtual std::vector<std::string> ListVector4Is() const override;

        /// <summary>
        /// Removes key from the object.
        /// </summary>
        /// <param name="key">Key to search for. </param>
        /// <returns>True means Key was unset, false means key never existed. </returns>
        virtual bool UnsetVector4I(const std::string& key) override;

        /// <summary>
        /// Sets the vector4I to the given value.
        /// </summary>
        /// <param name="key">Key to search for. </param>
        /// <param name="value">Value to set. </param>
        virtual void SetVector4I(const std::string& key, const FVector4I& value) override;

        /// <summary>
        /// Sets the vector4I to the given value.
        /// </summary>
        /// <param name="key">Key to search for. </param>
        /// <param name="x">X value to set. </param>
        /// <param name="y">Y value to set. </param>
        /// <param name="z">Z value to set. </param>
        /// <param name="w">W value to set. </param>
        virtual void SetVector4I(const std::string& key, int x, int y, int z, int w) override;

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

    private:
        /// <summary>
        /// A cached version of the document exported.
        /// </summary>
        std::shared_ptr<ModifiableDocument> m_modifiableDocument;

        /// <summary>
        /// True means this file has changed.
        /// </summary>
        bool isDirty;

        /// <summary>
        /// Loaded string values from file.
        /// </summary>
        std::unordered_map<std::string, std::string> m_stringValues;

        /// <summary>
        /// Loaded int values from file.
        /// </summary>
        std::unordered_map<std::string, int> m_intValues;

        /// <summary>
        /// Loaded FVector4I values from file.
        /// </summary>
        std::unordered_map<std::string, std::shared_ptr<FVector4I>> m_vector4IValues;

        /// <summary>
        /// Provides methods to parse in and out of Universal Object Data.
        /// </summary>
        std::shared_ptr<UniversalObjectParser> m_parser;
    };
}
