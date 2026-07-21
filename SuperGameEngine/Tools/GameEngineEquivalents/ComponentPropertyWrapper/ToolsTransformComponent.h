#pragma once
#include <memory>

namespace SuperGameTools
{
    class Vector2FSerializableProperty;
}

namespace SuperGameTools
{
    class Component;

    /// <summary>
    /// Wraps the properties within a transform component.
    /// The purpose of this (and all wrappers) is to standardise tools actions 
    /// </summary>
    class ToolsTransformComponent
    {
    public:

        bool operator==(const ToolsTransformComponent& a) const;
        bool operator==(const Component& a) const;

        /// <summary>
        /// Sets the transform component up.
        /// </summary>
        /// <param name="component">The transform component. </param>
        bool Initialize(const std::shared_ptr<Component>& component);

        /// <summary>
        /// Remove the transform component.
        /// Used when the transform is removed.
        /// </summary>
        void Uninitialize();

        /// <summary>
        /// True when a transform component is set.
        /// </summary>
        /// <returns>True when a transform component is set. </returns>
        bool HasTransformComponent() const;

        /// <summary>
        /// Sets position of the transform.
        /// </summary>
        /// <param name="x">X position. </param>
        /// <param name="y">Y position. </param>
        void SetPosition(float x, float y) const;

        /// <summary>
        /// Moves position of the transform by.
        /// </summary>
        /// <param name="x">X position. </param>
        /// <param name="y">Y position. </param>
        void MovePositionBy(float x, float y) const;

    private:

        /// <summary>
        /// The transform component saved.
        /// </summary>
        std::shared_ptr<Component> m_toolsComponent;

        /// <summary>
        /// Saved position property.
        /// </summary>
        std::shared_ptr<Vector2FSerializableProperty> m_positionTransform;

        /// <summary>
        /// On setting or unsetting components this will update links to the serializable properties.
        /// </summary>
        void UpdateProperties();
    };
}
