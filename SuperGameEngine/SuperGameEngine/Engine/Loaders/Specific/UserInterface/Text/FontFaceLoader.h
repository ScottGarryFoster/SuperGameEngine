#pragma once
#include "FontFaceAssetLoader.h"
#include "FontFaceFromText.h"

namespace SuperGameEngine
{
    class ContentManager;

    /// <summary>
    /// Loads Font Faces using XML.
    /// </summary>
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
        /// Loads the asset from raw data.
        /// </summary>
        /// <param name="subject">The output. </param>
        /// <param name="subject">The data. </param>
        /// <returns>True means loaded. </returns>
        virtual bool LoadAssetFromData(std::shared_ptr<Object>& subject, std::vector<unsigned char>& data) override;

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

        /// <summary>
        /// Allows us to parse the font from text.
        /// </summary>
        std::shared_ptr<FontFaceFromText> fromText;
    };
}