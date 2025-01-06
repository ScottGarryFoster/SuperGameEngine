#pragma once
#include "GameObject.h"

namespace SuperGameTools
{
    /// <summary>
    /// A game object with the things which Tools are concerned with.
    /// </summary>
    class ToolsGameObject : public GameObject
    {
    public:
        virtual ~ToolsGameObject() override = default;
        ToolsGameObject();

        /// <summary>
        /// Guid for the game object.
        /// </summary>
        /// <returns>Guid for the game object. </returns>
        virtual std::shared_ptr<Guid> GetGuid() const override;

        /// <summary>
        /// Set guid for the game object.
        /// </summary>
        /// <param name="guid">New guid. </param>
        virtual void SetGuid(const std::shared_ptr<Guid>& guid) override;

        /// <summary>
        /// Get components.
        /// </summary>
        /// <returns>Components on game object. </returns>
        virtual std::shared_ptr<std::vector<std::shared_ptr<Component>>> GetComponents() const override;

    private:
        /// <summary>
        /// Components on the game object.
        /// </summary>
        std::shared_ptr<std::vector<std::shared_ptr<Component>>> m_components;

        /// <summary>
        /// Guid for the game object.
        /// </summary>
        std::shared_ptr<Guid> m_guid;
    };
}
