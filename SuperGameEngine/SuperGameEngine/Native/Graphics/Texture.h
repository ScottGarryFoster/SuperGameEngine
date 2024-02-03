#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "../../LibraryIncludes.h"

using namespace StandardCLibrary;

class Texture
{
public:
    
    Texture(SDL_Renderer* renderer);

    /// <summary>
    /// Loads the given Texture into this class from the File Path.
    /// </summary>
    /// <param name="filePath">File path to the texture. </param>
    /// <param name="errors">If there are errors this is the reason why the texture could not be created. </param>
    /// <returns>True means created, false means not. </returns>
    bool LoadImageFromFile(FString filePath, std::vector<FString>& errors);

    /// <summary>
    /// Draws to screen.
    /// </summary>
    void Draw();

private:
    /// <summary>
    /// Allows us to render to the screen.
    /// </summary>
    SDL_Renderer* m_renderer;

    /// <summary>
    /// The actual texture.
    /// </summary>
    SDL_Texture* m_texture;
};

