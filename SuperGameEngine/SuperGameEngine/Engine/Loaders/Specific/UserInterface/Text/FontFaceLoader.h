#pragma once
#include "FontFaceAssetLoader.h"
#include "../../../../../UserInterface/Text/FontFace.h"

namespace SuperGameEngine
{
    using namespace SuperGameEngine_UserInterface;

    class FontFaceLoader : public FontFaceAssetLoader
    {
    public:
        /// <summary>
        /// Loads an asset from a file, products, from some source of truth about
        /// the asset. The key should remain the same regardless as the asset location.
        /// </summary>
        /// <param name="key">Asset Key which is a location releative from products. </param>
        /// <returns>True means loaded, false means failed to load. </returns>
        virtual bool LoadAsset(Object* subject, FString key) override;
    };
}