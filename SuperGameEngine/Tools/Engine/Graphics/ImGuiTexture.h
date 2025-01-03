#pragma once
#include "../../../Engine/Engine/Graphics/Texture/Texture.h"
#include "../../ImGuiIncludes.h"

using namespace SuperGameEngine;

namespace SuperGameTools
{
    /// <summary>
    /// A Texture used to display in ImGui.
    /// </summary>
    class ImGuiTexture : public Texture
    {
    public:
        ImGuiTexture(const std::shared_ptr<SDLRendererReader>& renderer);
        virtual ~ImGuiTexture() override;

        /// <summary>
        /// Gets the Texture ID for the texture this
        /// represents.
        /// </summary>
        /// <param name="textureID">ImGui Texture ID. </param>
        /// <returns>True means texture could be rendered. </returns>
        bool GetTextureID(ImTextureID& textureID) const;

        /// <summary>
        /// Loads the given Texture into this class from the File Path.
        /// </summary>
        /// <param name="filePath">File path to the texture. </param>
        /// <param name="errors">If there are errors this is the reason why the texture could not be created. </param>
        /// <returns>True means created, false means not. </returns>
        virtual bool LoadImageFromFile(const std::string& filePath, std::vector<std::string>& errors) override;

        /// <summary>
        /// Loads a texture from raw data.
        /// </summary>
        /// <param name="data">Data to load the texture from. </param>
        /// <param name="filepath">
        /// Filepath to store when making the texture -
        /// this does not exist and is used to create the texture as part of the comparer.
        /// </param>
        /// <param name="errors">Errors if not created. </param>
        /// <returns>True means created. </returns>
        virtual bool LoadImageFromData(std::vector<unsigned char>& data, const std::string& filepath, std::vector<std::string>& errors) override;

    private:
        /// <summary>
        /// The Texture ID for the texture this
        /// represents.
        /// </summary>
        ImTextureID m_textureID;

        /// <summary>
        /// True when there is no texture id.
        /// </summary>
        bool m_noTextureID;
    };

}

