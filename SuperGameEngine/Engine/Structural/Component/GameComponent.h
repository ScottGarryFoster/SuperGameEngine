#pragma once
#include <memory>

#include "../../Engine/Basic/ExtremelyWeakWrapper.h"

namespace FatedQuestLibraries
{
    class StoredDocumentNode;
}

using namespace FatedQuestLibraries;

namespace SuperGameEngine
{
    class ComponentLoadPackage;
    class GameObject;
    class GameTime;

    class GameComponent
    {
    public:
        virtual ~GameComponent() = default;

        /// <summary>
        /// Sets up the game component.
        /// </summary>
        /// <param name="componentLoadPackage">Everything a component needs to run. </param>
        /// <param name="parent">The parent of this component. </param>
        virtual void Setup(
            const std::shared_ptr<ComponentLoadPackage>& componentLoadPackage,
            const std::shared_ptr<ExtremelyWeakWrapper<GameObject>>& parent) = 0;

        /// <summary>
        /// True means Setup was run and it is ready to be used.
        /// </summary>
        /// <returns>True means Setup was run and it is ready to be used. </returns>
        virtual bool IsSetup() const = 0;

        /// <summary>
        /// The type to create to recreate this component.
        /// Override this on each component so that it always matches the type name for the class.
        /// </summary>
        /// <returns>The type to create to recreate this component. </returns>
        virtual std::string TypeName() const = 0;

        /// <summary>
        /// Updates the component this frame.
        /// </summary>
        /// <param name="gameTime">The current state of time this frame. </param>
        virtual void Update(const std::shared_ptr<GameTime> gameTime) = 0;

        /// <summary>
        /// Updates the component in fixed time.
        /// </summary>
        /// <param name="gameTime">The current state of time this frame. </param>
        virtual void FixedUpdate(const std::shared_ptr<GameTime> gameTime) = 0;

        /// <summary>
        /// Draws the component.
        /// For most components this will do nothing.
        /// </summary>
        virtual void Draw() const = 0;

        /// <summary>
        /// Gets the parent GameObject of this Component.
        /// This is given and stored as a raw pointer.
        /// For as long as the component exists this reference should exist.
        /// This reference however should never be stored or used outside a single method run
        /// by the game loop, Setup, Updates and Draw.
        /// </summary>
        /// <returns>The parent game object of this parent. </returns>
        virtual std::shared_ptr<ExtremelyWeakWrapper<GameObject>> GetParent() const = 0;

        /// <summary>
        /// True when this component should render.
        /// </summary>
        /// <returns>True when this component should render. </returns>
        virtual bool DoRender() const = 0;

        /// <summary>
        /// Updates whether this component should draw.
        /// </summary>
        /// <param name="newValue">True means this component should render. </param>
        virtual void SetDoRender(bool newValue) = 0;

        /// <summary>
        /// Destroys the game object.
        /// </summary>
        virtual void Destroy() = 0;

        /// <summary>
        /// Is this GameObject marks for destruction.
        /// </summary>
        /// <returns>True means is marked for Destroyed. </returns>
        virtual bool IsDestroyed() const = 0;

        /// <summary>
        /// Destroys the component immediately, calling all the code
        /// to destroy the component and all it owns.
        /// </summary>
        virtual void DestroyImmediately() = 0;

        /// <summary>
        /// Any further cleanup after being destroyed by the parent
        /// should take place here. This is called after the parent
        /// has classed you as removed.
        /// </summary>
        virtual void OnDestroyed() = 0;

        /// <summary>
        /// Load component from a stored document.
        /// </summary>
        /// <param name="documentNode">Document node to load from.</param>
        virtual void Load(const std::shared_ptr<StoredDocumentNode>& documentNode) = 0;

        /// <summary>
        /// Save component to stored document node ready to move to file.
        /// </summary>
        /// <returns>Document node to save to. </returns>
        virtual std::shared_ptr<StoredDocumentNode> Save() = 0;
    };
}
