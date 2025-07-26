#pragma once
#include "ModifiableUniversalObjectData.h"

namespace FatedQuestLibraries
{
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
    };
}
