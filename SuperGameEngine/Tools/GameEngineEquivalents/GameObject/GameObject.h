#pragma once
#include <memory>
#include <vector>

#include "../../ToolsEngine/FrameworkManager/SelectionManager/Selectable.h"

namespace FatedQuestLibraries
{
    class Guid;
}

using namespace FatedQuestLibraries;

namespace SuperGameTools
{
    class Component;

    /// <summary>
    /// A game object with the things which Tools are concerned with.
    /// </summary>
    class GameObject : public Selectable
    {
    public:
        virtual ~GameObject() = default;

        /// <summary>
        /// Guid for the game object.
        /// </summary>
        /// <returns>Guid for the game object. </returns>
        virtual std::shared_ptr<Guid> GetGuid() const override = 0;

        /// <summary>
        /// Describes the group for the selectable which helps to decide the
        /// buckets that the selectable will be added to.
        /// </summary>
        /// <returns>The group or groups for this selectable. </returns>
        virtual std::unordered_set<SelectionGroup> GetSelectionGroup() const override = 0;

        /// <summary>
        /// Set guid for the game object.
        /// </summary>
        /// <param name="guid">New guid. </param>
        virtual void SetGuid(const std::shared_ptr<Guid>& guid) = 0;

        /// <summary>
        /// Get components.
        /// </summary>
        /// <returns>Components on game object. </returns>
        virtual std::shared_ptr<std::vector<std::shared_ptr<Component>>> GetComponents() const = 0;
    };
}