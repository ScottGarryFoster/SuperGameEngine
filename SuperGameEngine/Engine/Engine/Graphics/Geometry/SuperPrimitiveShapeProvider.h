#pragma once
#include "PrimitiveShapeProvider.h"

namespace SuperGameEngine
{
    class SDLRendererReader;

    /// <summary>
    /// Provides render-able debug primitive shapes.
    /// </summary>
    class SuperPrimitiveShapeProvider : public virtual PrimitiveShapeProvider
    {
    public:

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="renderer">
        /// Gives access to the SDL renderer.
        /// Note it might not exist however this gives access to it.
        /// </param>
        SuperPrimitiveShapeProvider(const std::shared_ptr<SDLRendererReader>& renderer);

        /// <summary>
        /// Creates a primitive rectangle.
        /// </summary>
        /// <param name="location">The location to place the rectangle. </param>
        /// <param name="size">The size of the rectangle. </param>
        /// <returns>The created rectangle. </returns>
        virtual std::shared_ptr<PrimitiveRectangle> CreateRectangle(
            const FatedQuestLibraries::FVector2F& location,
            const FatedQuestLibraries::FVector2F& size) const override;

    private:

        /// <summary>
        /// Allows objects to render.
        /// </summary>
        std::shared_ptr<SDLRendererReader> m_renderer;
    };
}
