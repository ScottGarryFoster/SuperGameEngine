#pragma once
#include <memory>

#include "GameComponent.h"

namespace FatedQuestLibraries
{
    class ModifiableNode;
}

namespace SuperGameEngine
{
    /// <summary>
    /// The implementation of a component.
    /// </summary>
    class SuperGameComponent : public GameComponent
    {
    public:
        SuperGameComponent();
        virtual ~SuperGameComponent() override;

        /// <summary>
        /// Copy constructor
        /// </summary>
        SuperGameComponent(const SuperGameComponent& other);

        /// <summary>
        /// Copy assignment operator
        /// </summary>
        SuperGameComponent& operator=(const SuperGameComponent& other);

        /// <summary>
        /// Move constructor
        /// </summary>
        SuperGameComponent(SuperGameComponent&& other) noexcept;

        /// <summary>
        /// Move assignment operator
        /// </summary>
        SuperGameComponent& operator=(SuperGameComponent&& other) noexcept;

        /// <summary>
        /// Sets up the game component.
        /// </summary>
        /// <param name="componentLoadPackage">Everything a component needs to run. </param>
        /// <param name="parent">The parent of this component. </param>
        virtual void Setup(
            const std::shared_ptr<ComponentLoadPackage>& componentLoadPackage,
            const std::weak_ptr <GameObject>& parent) override;

        /// <summary>
        /// The type to create to recreate this component.
        /// Override this on each component so that it always matches the type name for the class.
        /// </summary>
        /// <returns>The type to create to recreate this component. </returns>
        virtual std::string TypeName() const override;

        /// <summary>
        /// True means Setup was run and it is ready to be used.
        /// </summary>
        /// <returns>True means Setup was run and it is ready to be used. </returns>
        virtual bool IsSetup() const override;

        /// <summary>
        /// Updates the component this frame.
        /// </summary>
        /// <param name="gameTime">The current state of time this frame. </param>
        virtual void Update(const std::shared_ptr<GameTime> gameTime) override;

        /// <summary>
        /// Updates the component in fixed time.
        /// </summary>
        /// <param name="gameTime">The current state of time this frame. </param>
        virtual void FixedUpdate(const std::shared_ptr<GameTime> gameTime) override;

        /// <summary>
        /// Draws the component.
        /// For most components this will do nothing.
        /// </summary>
        virtual void Draw() const override;

        /// <summary>
        /// Gets the parent GameObject of this Component.
        /// Do not store this! Use it as you need it and then get rid of it.
        /// The game object you are a part of could be destroyed at the point of the update,
        /// keeping this as a shared pointer would mean you could keep the object alive whilst dead.
        /// </summary>
        /// <returns>The parent game object of this parent. </returns>
        virtual std::weak_ptr<GameObject> GetParent() const override;

        /// <summary>
        /// True when this component should render.
        /// </summary>
        /// <returns>True when this component should render. </returns>
        virtual bool DoRender() const override;

        /// <summary>
        /// Updates whether this component should draw.
        /// </summary>
        /// <param name="newValue">True means this component should render. </param>
        virtual void SetDoRender(bool newValue) override;

        /// <summary>
        /// Destroys the game object.
        /// </summary>
        virtual void Destroy() override;

        /// <summary>
        /// Is this GameObject marks for destruction.
        /// </summary>
        /// <returns>True means is marked for Destroyed. </returns>
        virtual bool IsDestroyed() const override;

        /// <summary>
        /// Destroys the component immediately, calling all the code
        /// to destroy the component and all it owns.
        /// </summary>
        virtual void DestroyImmediately() override;

        /// <summary>
        /// Any further cleanup after being destroyed by the parent
        /// should take place here. This is called after the parent
        /// has classed you as removed.
        /// </summary>
        virtual void OnDestroyed() override;

        /// <summary>
        /// Load component from a stored document.
        /// </summary>
        /// <param name="documentNode">Document node to load from.</param>
        virtual void Load(const std::shared_ptr<StoredDocumentNode>& documentNode) override;

        /// <summary>
        /// Save component to stored document node ready to move to file.
        /// </summary>
        /// <returns>Document node to save to. </returns>
        virtual std::shared_ptr<StoredDocumentNode> Save() override;

        /// <summary>
        /// Get all properties which can be authored.
        /// </summary>
        /// <returns>All author-able properties. </returns>
        /// <remarks>
        /// This should be able to be called after construction of the component.
        /// </remarks>
        virtual std::vector<std::shared_ptr<SerializableProperty>> Properties() const override;
    protected:

        /// <summary>
        /// All properties this component can save and load.
        /// </summary>
        std::vector<std::shared_ptr<SerializableProperty>> m_serializableProperties;

        /// <summary>
        /// Gets the scene load package.
        /// </summary>
        /// <returns>Everything a component needs to run. </returns>
        [[nodiscard]] std::shared_ptr<ComponentLoadPackage> LoadPackage() const;

        /// <summary>
        /// When saving call this method to add items stores at this level of the component.
        /// </summary>
        /// <param name="documentNode">Document node already created. </param>
        void AddAnySuperGameComponentSaves(const std::shared_ptr<ModifiableNode>& documentNode);
    private:

        /// <summary>
        /// The parent game object.
        /// This is given and stored as a raw pointer.
        /// For as long as the component exists this reference should exist.
        /// This reference however should never be stored or used outside a single method run
        /// by the game loop, Setup, Updates and Draw.
        /// </summary>
        std::weak_ptr <GameObject> m_parent;

        /// <summary>
        /// Everything a component needs to run.
        /// </summary>
        std::shared_ptr<ComponentLoadPackage> m_loadPackage;

        /// <summary>
        /// True means run a draw loop.
        /// By default, this is set to false as most Components will not need to draw anything
        /// and will instead use a Sprite Component to draw.
        /// </summary>
        bool m_doRender;

        /// <summary>
        /// True means setup has been called successfully in the base.
        /// </summary>
        bool m_isSetup;

        /// <summary>
        /// True means marked for destruction.
        /// </summary>
        bool m_isDestroyed;
    };
}
