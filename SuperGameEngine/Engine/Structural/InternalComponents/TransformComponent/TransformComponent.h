#pragma once
#include "../../../../../FatedQuest.Libraries/StandardObjects/Position/FVector2F.h"
#include "../../GameObject/ComponentFactory.h"
#include "../../Component/SuperGameComponent.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Holds the render shape.
    /// </summary>
    class TransformComponent : public SuperGameComponent
    {
    public:
        TransformComponent();
        virtual ~TransformComponent() override;

        /// <summary>
        /// Sets up the game component.
        /// </summary>
        /// <param name="componentLoadPackage">Everything a component needs to run. </param>
        /// <param name="parent">The parent of this component. </param>
        virtual void Setup(
            const std::shared_ptr<ComponentLoadPackage>& componentLoadPackage,
            const std::shared_ptr<ExtremelyWeakWrapper<GameObject>>& parent) override;

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
        /// The type to create to recreate this component.
        /// Override this on each component so that it always matches the type name for the class.
        /// </summary>
        /// <returns>The type to create to recreate this component. </returns>
        virtual std::string TypeName() const override;

        /// <summary>
        /// Get the position within the transform.
        /// </summary>
        /// <returns></returns>
        [[nodiscard]] const FVector2F& Position() const;

    private:

        /// <summary>
        /// The position in local space.
        /// </summary>
        FVector2F m_position;

        /// <summary>
        /// The name of position as saved in the file.
        /// </summary>
        const std::string m_positionName = "Position";
    };

    REGISTER_COMPONENT("TransformComponent", TransformComponent);
}