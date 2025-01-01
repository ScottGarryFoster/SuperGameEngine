#pragma once
#include <memory>
#include <string>

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
    class SceneLoader
    {
    public:
        virtual ~SceneLoader() = default;

        /// <summary>
        /// Loads a scene from filepath.
        /// </summary>
        /// <param name="filepath">Filepath from game package location. </param>
        /// <returns>
        /// A document representing the scene or
        /// empty if we cannot create document.
        /// </returns>
        virtual std::shared_ptr<ModifiableDocument> LoadScene(const std::string& filepath) = 0;
    };
}

