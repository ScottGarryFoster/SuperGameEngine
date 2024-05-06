#pragma once
#include "FontFaceAssetLoader.h"
#include "../../../../../UserInterface/Text/FontFace.h"

namespace SuperGameEngine
{
    using namespace SuperGameEngine_UserInterface;

    class ContentManager;

    class FontFaceLoader : public FontFaceAssetLoader
    {
    public:
        FontFaceLoader(ContentManager* contentManager);

        /// <summary>
        /// Loads an asset from a file, products, from some source of truth about
        /// the asset. The key should remain the same regardless as the asset location.
        /// </summary>
        /// <param name="key">Asset Key which is a location releative from products. </param>
        /// <returns>True means loaded, false means failed to load. </returns>
        virtual bool LoadAsset(std::shared_ptr<Object>& subject, FString key) override;

        /// <summary>
        /// Loads an asset from a file, products, from some source of truth about
        /// the asset. The key should remain the same regardless as the asset location.
        /// </summary>
        /// <param name="key">Asset Key which is a location releative from products. </param>
        /// <returns>True means loaded, false means failed to load. </returns>
        virtual bool LoadAsset(Object* subject, FString key) override;

    private:
        /// <summary>
        /// Gives the ability to load textures.
        /// </summary>
        ContentManager* contentManager;
    };
}