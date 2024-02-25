#pragma once
#include <SDL.h>
#include "PrimitiveDrawableShapeTechnique.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Renders techniques which for the most part are primitives.
    /// </summary>
    class TechniqueRenderer
    {
    public:
        TechniqueRenderer(SDL_Renderer* renderer);
        ~TechniqueRenderer();

        /// <summary>
        /// A new Technique for the renderer.
        /// </summary>
        /// <param name="newTechnique">New Technique</param>
        void GiveTechnique(std::weak_ptr<DrawableTechnique> newTechnique);

        /// <summary>
        /// Only called by the GrandScene on Draw.
        /// </summary>
        void Draw();

    private:
        /// <summary>
        /// Renderer given by the owner.
        /// </summary>
        SDL_Renderer* m_renderer;

        /// <summary>
        /// Storage of all techniques.
        /// </summary>
        std::vector< std::weak_ptr<DrawableTechnique>> m_techniques;
    };
}