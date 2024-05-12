#pragma once
#include "../../../../../UserInterface/Text/FontFace.h"
#include "../../../../../RapidXML.h"

using namespace SuperGameEngine;
using namespace rapidxml;
namespace SuperGameEngine
{
    class ContentManager;

    /// <summary>
    /// Creates a Font Face from the information in a file.
    /// </summary>
    class FontFaceFromText
    {
    public:
        FontFaceFromText(ContentManager* contentManager);
        virtual ~FontFaceFromText();

        /// <summary>
        /// Loads a font face from Asset File.
        /// </summary>
        /// <param name="answer">True if loaded. </param>
        /// <param name="text">Text to parse. </param>
        /// <returns>The font face if loaded. </returns>
        virtual std::shared_ptr<FontFace> LoadFromFile(std::shared_ptr<bool>& answer, const std::shared_ptr<FString> text);

    private:
        ContentManager* contentManager;

        /// <summary>
        /// A single character.
        /// Used for loading.
        /// </summary>
        struct FontCharacter
        {
        public:
            RectangleInt TextureRectangle = RectangleInt(0, 0, 0, 0);
            wchar_t Character = L' ';
        };

        /// <summary>
        /// Everything to make a font face.
        /// This is used to allow any order of the data in the XML without
        /// the order affecting how the asset is loaded.
        /// This is loaded into then we create the final asset.
        /// </summary>
        class FontFaceData
        {
        public:
            // Metadata
            std::shared_ptr<FText> MetaDataName;
            std::shared_ptr<FText> MetaDataBrand;

            // Texture
            std::shared_ptr<FText> TextureSource;

            // Characters
            std::shared_ptr<FList<FontCharacter>> Characters;
        };

        /// <summary>
        /// Tries to parse an XMLDocument.
        /// </summary>
        /// <param name="text">The Document contents. </param>
        /// <param name="document">The document to return. </param>
        /// <returns>True means loaded. </returns>
        bool TryParseXMLDocument(const std::shared_ptr<FString> text, XMLDocument* document);

        /// <summary>
        /// Parses the tag "Metadata"
        /// </summary>
        /// <param name="fontFaceData">The loaded information. </param>
        /// <param name="node">Node to look for the information. </param>
        /// <returns>True means loaded. </returns>
        bool ParseAssetMetadata(std::shared_ptr<FontFaceData>& fontFaceData, XMLNode* node);

        /// <summary>
        /// Parses the tag "Texture"
        /// </summary>
        /// <param name="fontFaceData">The loaded information. </param>
        /// <param name="node">Node to look for the information. </param>
        /// <returns>True means loaded. </returns>
        bool ParseAssetTexture(std::shared_ptr<FontFaceData>& fontFaceData, XMLNode* node);

        /// <summary>
        /// Parses the tag "Characters"
        /// </summary>
        /// <param name="fontFaceData">The loaded information. </param>
        /// <param name="node">Node to look for the information. </param>
        /// <returns>True means loaded. </returns>
        bool ParseCharacters(std::shared_ptr<FontFaceData>& fontFaceData, XMLNode* node);

        /// <summary>
        /// Parses the tag "Character"
        /// </summary>
        /// <param name="fontFaceData">The loaded information. </param>
        /// <param name="node">Node to look for the information. </param>
        /// <returns>True means loaded. </returns>
        bool ParseCharacter(std::shared_ptr<FontFaceData>& fontFaceData, XMLNode* node);

        /// <summary>
        /// Creates a font face from the data.
        /// </summary>
        /// <param name="answer">True means loaded. </param>
        /// <param name="fontFaceData">Data to use upon creation. </param>
        /// <returns>Created fontface or an empty pointer. </returns>
        std::shared_ptr<FontFace> CreateFontFace(std::shared_ptr<bool>& answer, std::shared_ptr<FontFaceData>& fontFaceData);


    };
}
