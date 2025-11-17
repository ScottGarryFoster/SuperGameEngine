#pragma once
#include "FatedQuestLibraries.h"

namespace FatedQuestLibraries
{
    class DocumentModifiableUniversalObjectData;
    class ModifiableUniversalObjectData;
}

namespace SuperGameTools
{
    class AssetFile;
    class WindowPackage;

    /// <summary>
    /// Inspect window functionality when inspecting an asset browser asset.
    /// </summary>
    class InspectAssetObject : public FatedQuestLibraries::FEventObserver
    {
    public:
        InspectAssetObject();

        /// <summary>
        /// Called once on setup.
        /// </summary>
        /// <param name="windowPackage">Everything needed to run a window. </param>
        void Setup(const std::shared_ptr<WindowPackage>& windowPackage);

        /// <summary>
        /// Called every frame.
        /// </summary>
        void Update();

        /// <summary>
        /// Called on draw.
        /// </summary>
        void Draw();

        /// <summary>
        /// Called on destroy.
        /// </summary>
        void TearDown();

        /// <summary>
        /// Inform the observer an event has taken place.
        /// Do not store this pointer it is intended as a point for dynamic casting
        /// and not as long term storage. Directly after invocation it will be deleted.
        /// </summary>
        /// <param name="arguments">Arguments describing the event. </param>
        virtual void Invoke(std::shared_ptr<FatedQuestLibraries::FEventArguments> arguments) override;

        /// <summary>
        /// Called when a user action to say all items opened is called.
        /// </summary>
        void OnSaveAll();

    private:

        /// <summary>
        /// Everything a Window Package might need to run.
        /// </summary>
        std::shared_ptr<WindowPackage> m_windowPackage;

        /// <summary>
        /// True means setup was called.
        /// </summary>
        bool m_isSetup;

        /// <summary>
        /// If currently selected this is the asset file currently being edited.
        /// </summary>
        std::shared_ptr<AssetFile> m_assetFileCurrentlyEdited;

        /// <summary>
        /// Helps to create XML document. Used to save Asset Objects.
        /// </summary>
        std::shared_ptr<FatedQuestLibraries::DocumentToXml> m_documentToXml;

        /// <summary>
        /// If asset file is currently being edited this is the current data. It may not be saved.
        /// </summary>
        std::shared_ptr<FatedQuestLibraries::DocumentModifiableUniversalObjectData> m_currentlyEditedDocument;
    };
}
