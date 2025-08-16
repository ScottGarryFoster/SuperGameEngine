#pragma once
#include "ModifiableUniversalObjectData.h"

namespace FatedQuestLibraries
{
    class StoredDocument;
    class ModifiableDocument;

    /// <summary>
    /// A Modifiable Object which can be exported to a document.
    /// </summary>
    class DocumentModifiableUniversalObjectData : public virtual ModifiableUniversalObjectData
    {
    public:

        /// <summary>
        /// Exports the data stored to a document format.
        /// </summary>
        /// <returns>The data within the object as a document. </returns>
        virtual std::shared_ptr<ModifiableDocument> ExportToDocument() = 0;

        /// <summary>
        /// Imports data as a document.
        /// </summary>
        /// <param name="document">The document to load the information from.</param>
        /// <returns>True means loaded successfully. </returns>
        virtual bool ImportAsDocument(const std::shared_ptr<StoredDocument>& document) = 0;
    };
}
