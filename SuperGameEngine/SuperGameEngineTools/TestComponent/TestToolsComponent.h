#pragma once
#include "../../SuperGameEngine/Structural/GameObject/GameComponent.h"
#include "../../SuperGameEngine/Structural/Components/Visual/TextComponent.h"

using namespace SuperGameEngine;

namespace SuperGameEngineTools
{
    /// <summary>
    /// Tests the ability to create a component in the Engine which it
    /// does not know about.
    /// </summary>
    class TestToolsComponent : public GameComponent
    {
    public:
        /// <summary>
        /// Sets up the Component.
        /// </summary>
        /// <param name="loadPackage">Everything a Component needs to be a game object. </param>
        virtual void Setup(SceneLoadPackage* loadPackage, GameObject* parent) override;

    private:

        std::shared_ptr<TextComponent> m_text;
    };

    REGISTER_COMPONENT(TestToolsComponent)
}