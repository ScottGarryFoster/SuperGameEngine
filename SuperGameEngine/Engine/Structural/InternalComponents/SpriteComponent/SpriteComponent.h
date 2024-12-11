#pragma once
#include "../../GameObject/ComponentFactory.h"
#include "../../Component/SuperGameComponent.h"
#include "../../../FatedQuestReferences.h"

using namespace FatedQuestLibraries;

namespace SuperGameEngine
{
    class SuperTexture;

    /// <summary>
    /// A component to test basic functionality.
    /// </summary>
    class SpriteComponent : public SuperGameComponent
    {
    public:
        SpriteComponent();
        virtual ~SpriteComponent();

        /// <summary>
        /// Sets up the game component.
        /// </summary>
        /// <param name="componentLoadPackage">Everything a component needs to run. </param>
        /// <param name="parent">The parent of this component. </param>
        virtual void Setup(
            std::shared_ptr<ComponentLoadPackage> componentLoadPackage,
            std::shared_ptr<ExtremelyWeakWrapper<GameObject>> parent) override;

        /// <summary>
        /// Updates the component this frame.
        /// </summary>
        /// <param name="gameTime">The current state of time this frame. </param>
        virtual void Update(const std::shared_ptr<GameTime> gameTime) override;

        /// <summary>
        /// Draws the component.
        /// For most components this will do nothing.
        /// </summary>
        virtual void Draw() const override;

        virtual void Move(int x, int y);

        virtual int GetX() { return m_location.GetX(); }
        virtual int GetY() { return m_location.GetY(); }

    private:

        std::shared_ptr<SuperTexture> m_superTexture;

        FPoint m_location;

        /// <summary>
        /// Take up memory so I can see it being destroyed.
        /// </summary>
        char oneMB[1024 * 1024];
    };

    REGISTER_COMPONENT("SpriteComponent", SpriteComponent);
}

