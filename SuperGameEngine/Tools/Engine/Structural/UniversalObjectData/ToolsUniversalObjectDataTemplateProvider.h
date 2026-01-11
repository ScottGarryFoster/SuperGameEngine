#pragma once
#include "UniversalObjectDataTemplateProvider.h"

namespace FatedQuestLibraries
{
    class GamePackage;
}

namespace SuperGameTools
{
    class LayoutEditorFactory;

    /// <summary>
    /// Loads, holds and provides <see cref="AssetTemplate"/> in a single location.
    /// </summary>
    class ToolsUniversalObjectDataTemplateProvider : public UniversalObjectDataTemplateProvider
    {
    public:

        ToolsUniversalObjectDataTemplateProvider(const std::shared_ptr<FatedQuestLibraries::GamePackage>& gamePackage);

        /// <summary>
        /// Retrieve all the <see cref="SingleLayoutMetaData"/> objects loaded. 
        /// </summary>
        /// <returns>All the <see cref="SingleLayoutMetaData"/> objects loaded. </returns>
        virtual std::vector<std::shared_ptr<const SingleLayoutMetaData>> GetObjectDataTemplates() const override;

        /// <summary>
        /// Load all the metadata into the provider.
        /// This should only be called once but if it is called again
        /// it will act as a reload and empty the templates it already has.
        /// </summary>
        /// <returns>
        /// True means load was successful.
        /// False means could not load templates.
        /// </returns>
        bool LoadAllTemplateMetaData();

    private:
        /// <summary>
        /// Where to store the templates within the game package.
        /// </summary>
        const char* m_templateFolder = "Tools\\UniversalObjectDataTemplates";

        /// <summary>
        /// Holds the content for the game.
        /// </summary>
        std::shared_ptr<FatedQuestLibraries::GamePackage> m_gamePackage;

        /// <summary>
        /// The factory to create layouts.
        /// </summary>
        std::shared_ptr<LayoutEditorFactory> m_layoutEditorFactory;

        /// <summary>
        /// All universal data object templates.
        /// </summary>
        std::vector<std::shared_ptr<const SingleLayoutMetaData>> m_objectTemplates;
    };
}
