#pragma once
#include "SceneLoader.h"
#include <memory>
#include <string>

namespace FatedQuestLibraries
{
    class GamePackage;
}

namespace FatedQuestLibraries
{
    class ModifiableDocument;
}

using namespace FatedQuestLibraries;

namespace SuperGameTools
{
    /// <summary>
    /// Loads scene for the Tools.
    /// </summary>
    class ToolsSceneLoader : public SceneLoader
    {
    public:
        ToolsSceneLoader(const std::shared_ptr<GamePackage>& gamePackage);
        virtual ~ToolsSceneLoader() override = default;

        /// <summary>
        /// Loads a scene from filepath.
        /// </summary>
        /// <param name="filepath">Filepath from game package location. </param>
        /// <returns>
        /// A document representing the scene or
        /// empty if we cannot create document.
        /// </returns>
        virtual std::shared_ptr<ModifiableDocument> LoadScene(const std::string& filepath) override;

    private:

        /// <summary>
        /// Holds the content for the game.
        /// </summary>
        std::shared_ptr<GamePackage> m_gamePackage;
    };
}

