#pragma once
#include "../../GameObject/GameComponent.h"
#include "../../Scene/SceneLoadPackage.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Renders a texture.
    /// </summary>
    class SpriteComponent : public GameComponent
    {
    public:
        SpriteComponent();

        /// <summary>
        /// Sets up the Component.
        /// </summary>
        /// <param name="loadPackage">Everything a Component needs to be a game object. </param>
        virtual void Setup(SceneLoadPackage* loadPackage, GameObject* parent) override;

        /// <summary>
        /// Entry point for the entire game.
        /// </summary>
        /// <param name="tick">Ticks since last frame. </param>
        /// <returns>True means continue. False means close. </returns>
        virtual bool Update(GameTime gameTime) override;

        /// <summary>
        /// Draw everything in the game.
        /// </summary>
        virtual void Draw() override;

    private:
        /// <summary>
        /// A texture stored in the content manager.
        /// </summary>
        std::shared_ptr<SuperTexture> m_superTexture;
    };
}