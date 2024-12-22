#pragma once
#include <memory>

#include "TextureManager.h"

namespace FatedQuestLibraries
{
    class GamePackage;
}

namespace SuperGameEngine
{
    /// <summary>
    /// Provides and manages all shared resources.
    /// </summary>
    class ContentManager
    {
    public:

        /// <summary>
        /// Creates, stores and manages all textures in the engine.
        /// </summary>
        /// <returns>Returns the texture manager. </returns>
        virtual const std::shared_ptr<TextureManager> Texture() = 0;

        /// <summary>
        /// Holds the content for the game.
        /// </summary>
        /// <returns>Holds the content for the game. </returns>
        virtual const std::shared_ptr<GamePackage> GamePackage() = 0;
    };
}

