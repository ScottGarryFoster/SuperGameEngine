#pragma once

#include "../../../../Engine/Engine/Content/TextureManager.h"
#include "../../../../Engine/Engine/Graphics/Texture/SuperTexture.h"

namespace SuperGameEngineTests_Stubs
{
    class TextureManagerStub : public SuperGameEngine::TextureManager
    {
    public:
        ~TextureManagerStub() override = default;
        TextureManagerStub()
        {
        }

        /// <summary>
        /// Creates or gets the given Texture.
        /// </summary>
        /// <param name="filePath">File Path relative to the products folder. </param>
        /// <returns>The texture or <c>nullptr</c> if not found. </returns>
        virtual std::shared_ptr<SuperGameEngine::SuperTexture> GetTexture(const std::string& filePath) override
        {
            std::string cleanPath = File::Sanitize(filePath);
            if (m_textures.contains(cleanPath))
            {
                return m_textures.at(cleanPath);
            }

            return std::shared_ptr<SuperGameEngine::SuperTexture>();
        }

        void GiveTexture(
            const std::shared_ptr<SuperGameEngine::SuperTexture>& 
            texture, const std::string& filePath)
        {
            std::string cleanPath = File::Sanitize(filePath);
            m_textures.insert_or_assign(cleanPath, texture);
        }

    private:

        /// <summary>
        /// All textures loaded.
        /// </summary>
        std::unordered_map<std::string, std::shared_ptr<SuperGameEngine::SuperTexture>> m_textures;
    };
}
