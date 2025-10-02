#pragma once
#include "DocumentElementFactory.h"

namespace FatedQuestLibraries
{
    class MarkdownElement;

    /// <summary>
    /// Creates document elements.
    /// </summary>
    class MarkdownElementFactory : public DocumentElementFactory
    {
        /// <summary>
        /// Creates a document element based on the text provided.
        /// </summary>
        /// <param name="text">Text to create from. </param>
        /// <returns>Document Element Created. </returns>
        virtual std::shared_ptr<DocumentElement> Create(const std::string& text) override;
    };
}
