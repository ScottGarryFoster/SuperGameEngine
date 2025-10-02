#pragma once
#include <memory>
#include <string>

namespace FatedQuestLibraries
{
    class DocumentElement;

    /// <summary>
    /// Creates document elements.
    /// </summary>
    class DocumentElementFactory
    {
        /// <summary>
        /// Creates a document element based on the text provided.
        /// </summary>
        /// <param name="text">Text to create from. </param>
        /// <returns>Document Element Created. </returns>
        virtual std::shared_ptr<DocumentElement> Create(const std::string& text) = 0;
    };
}
