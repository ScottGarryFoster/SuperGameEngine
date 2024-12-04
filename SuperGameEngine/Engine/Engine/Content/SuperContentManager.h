#pragma once
#include "ContentManager.h"
#include "SuperTextureManager.h"
#include "TextureManager.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Provides and manages all shared resources.
    /// </summary>
    class SuperContentManager : public ContentManager
    {
    public:
        SuperContentManager();
        virtual ~SuperContentManager();

        /// <summary>
        /// Creates, stores and manages all textures in the engine.
        /// </summary>
        /// <returns>Returns the texture manager. </returns>
        virtual const std::shared_ptr<TextureManager> Texture() override;

        /// <summary>
        /// Give the content manager the texture manager.
        /// </summary>
        /// <param name="superTextureManager">
        /// The new texture manager.
        /// </param>
        void GiveSuperTextureManager(std::shared_ptr<SuperTextureManager> superTextureManager);

        /// <summary>
        /// Gets the super texture manager to access methods only at this level.
        /// </summary>
        /// <returns>Returns the Texture Manager. </returns>
        std::shared_ptr<SuperTextureManager> GetSuperTextureManager();

    private:
        /// <summary>
        /// Creates, stores and manages all textures in the engine.
        /// </summary>
        std::shared_ptr<SuperTextureManager> m_superTextureManager;
    };
}

