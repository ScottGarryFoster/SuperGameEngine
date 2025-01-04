#pragma once

namespace FatedQuestLibraries
{
    class FEventSubscriptions;
}

using namespace FatedQuestLibraries;

namespace SuperGameTools
{
    /// <summary>
    /// Manages actions around documents.
    /// </summary>
    class DocumentManager
    {
    public:
        virtual ~DocumentManager() = default;

        /// <summary>
        /// Subscribe to event when any document action occurs.
        /// See DocumentActionEventArguments.
        /// </summary>
        /// <returns>Subscribe to event when any document action occurs. </returns>
        virtual std::shared_ptr<FEventSubscriptions> OnDocumentAction() const = 0;
    };
}

