#pragma once
#include <memory>
#include "../../FatedQuestLibraries.h"
#include "../GenericProperties/FunctionProperty.h"
#include "../GenericProperties/ValueProperty.h"

using namespace FatedQuestLibraries;

namespace SuperGameTools
{
    /// <summary>
    /// A single item in a tree.
    /// </summary>
    class TreeViewItem
    {
    public:
        TreeViewItem();

        /// <summary>
        /// The unique ID for the tree view item.
        /// </summary>
        /// <returns></returns>
        virtual std::shared_ptr<Guid> GetUniqueID() const;

        /// <summary>
        /// Property has changed.
        /// </summary>
        /// <param name="name">Property which has changed. </param>
        virtual void OnPropertyChanged(const std::string& name);

        /// <summary>
        /// Label shown to the user.
        /// </summary>
        /// <returns>Label shown to the user. </returns>
        virtual std::shared_ptr<ValueProperty<std::string>> GetLabel() const;

        /// <summary>
        /// Children of this tree view item.
        /// </summary>
        /// <returns>Children of this tree view item. </returns>
        virtual std::shared_ptr<ValueProperty<std::vector<std::shared_ptr<TreeViewItem>>>> GetChildren() const;

        /// <summary>
        /// Called when selected.
        /// </summary>
        /// <returns>Called when selected. </returns>
        //virtual std::shared_ptr<FEventSubscriptions> OnSelected();

    private:

        /// <summary>
        /// Unique id.
        /// </summary>
        std::shared_ptr<Guid> m_guid;

        /// <summary>
        /// Label shown to the user.
        /// </summary>
        std::shared_ptr<ValueProperty<std::string>> m_label;

        /// <summary>
        /// Children of the tree view item.
        /// </summary>
        std::shared_ptr<ValueProperty<std::vector<std::shared_ptr<TreeViewItem>>>> m_children;
    };
}
