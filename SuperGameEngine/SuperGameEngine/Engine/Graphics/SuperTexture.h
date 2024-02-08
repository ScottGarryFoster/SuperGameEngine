#pragma once
#include "../../LibraryIncludes.h"
using namespace StandardCLibrary;

namespace SuperGameEngine
{
    class Texture;

    /// <summary>
    /// A texture owned by the content manager.
    /// </summary>
    class SuperTexture
    {
    public:
        SuperTexture(Texture* texture);

        void Draw();

        /// <summary>
        /// Determines if the two textures are the same image.
        /// </summary>
        /// <param name="texture">Texture to test. </param>
        /// <returns>True means are the same. </returns>
        bool RepresentSameImage(SuperTexture* texture);

        /// <summary>
        /// Determines if the texture uses this file path.
        /// </summary>
        /// <param name="filePath">File path to text. </param>
        /// <returns>True means this uses the same file path. </returns>
        bool RepresentSameImage(FString filePath);

    private:

        Texture* m_actualTexture;
    };
}
