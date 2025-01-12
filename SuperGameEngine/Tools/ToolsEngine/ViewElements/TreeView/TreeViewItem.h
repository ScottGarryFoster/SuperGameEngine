#pragma once
#include <memory>

#include "TreeViewItemCollapsibleBehaviour.h"
#include "TreeViewItemCollapsibleIcon.h"
#include "../../../FatedQuestLibraries.h"
#include "../../GenericProperties/FunctionProperty.h"
#include "../../GenericProperties/ValueProperty.h"
#include "../../../ImGuiIncludes.h"

namespace SuperGameEngine
{
    class ContentManager;
    class SuperTexture;
}

using namespace FatedQuestLibraries;
using namespace SuperGameEngine;

namespace SuperGameTools
{
    /// <summary>
    /// A single item in a tree.
    /// </summary>
    class TreeViewItem : public std::enable_shared_from_this<TreeViewItem>
    {
    public:
        TreeViewItem(const std::shared_ptr<ContentManager>& contentManager);

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
        /// True means is framed.
        /// </summary>
        /// <returns>True means is framed. </returns>
        virtual std::shared_ptr<ValueProperty<bool>> GetIsFramed() const;

        /// <summary>
        /// True means this item will be rendered and will contribute to the indentation.
        /// False means this item is a placeholder and will not contribute to indentation by default.
        /// </summary>
        /// <returns>Should Render. </returns>
        virtual std::shared_ptr<ValueProperty<bool>> GetShouldRender() const;

        /// <summary>
        /// True means this should be open when the item loads.
        /// False is default.
        /// </summary>
        /// <returns>True means this should be open when the item loads. </returns>
        virtual std::shared_ptr<ValueProperty<bool>> GetOpenOnLoad() const;

        /// <summary>
        /// How the item should open and close.
        /// </summary>
        /// <returns>How the item should open and close. </returns>
        virtual std::shared_ptr<ValueProperty<TreeViewItemCollapsibleBehaviour>> GetCollapsibleType() const;

        /// <summary>
        /// How the item should display its indentation / open and close status.
        /// </summary>
        /// <returns>How the item should display its indentation / open and close status. </returns>
        virtual std::shared_ptr<ValueProperty<TreeViewItemCollapsibleIcon>> GetCollapsibleIcon() const;

        /// <summary>
        /// Children of this tree view item.
        /// </summary>
        /// <returns>Children of this tree view item. </returns>
        virtual std::shared_ptr<ValueProperty<std::vector<std::shared_ptr<TreeViewItem>>>> GetChildren() const;

        /// <summary>
        /// True means is open.
        /// </summary>
        /// <returns>True means is currently open. </returns>
        virtual std::shared_ptr<ValueProperty<bool>> GetIsOpen() const;

        /// <summary>
        /// True means is selected.
        /// </summary>
        /// <returns>True means is currently selected. </returns>
        virtual std::shared_ptr<ValueProperty<bool>> GetIsSelected() const;

        /// <summary>
        /// Called when selected.
        /// </summary>
        /// <returns>Called when selected. </returns>
        virtual std::shared_ptr<FEvent> OnSelected();

        /// <summary>
        /// Draw the tree view item.
        /// </summary>
        virtual void Draw();

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
        /// True means this should be open when the item loads.
        /// False is default.
        /// </summary>
        std::shared_ptr<ValueProperty<bool>> m_openOnStart;

        /// <summary>
        /// True means is framed.
        /// </summary>
        std::shared_ptr<ValueProperty<bool>> m_isFramed;

        /// <summary>
        /// True means this item will be rendered and will contribute to the indentation.
        /// False means this item is a placeholder and will not contribute to indentation by default.
        /// </summary>
        std::shared_ptr<ValueProperty<bool>> m_shouldRender;

        /// <summary>
        /// Children of the tree view item.
        /// </summary>
        std::shared_ptr<ValueProperty<std::vector<std::shared_ptr<TreeViewItem>>>> m_children;

        /// <summary>
        /// How the tree view item should open or close.
        /// </summary>
        std::shared_ptr<ValueProperty<TreeViewItemCollapsibleBehaviour>> m_treeViewItemCollapsibleBehaviour;

        /// <summary>
        /// How the tree view item should display with an icon.
        /// Does not affect if the element can open or close.
        /// </summary>
        std::shared_ptr<ValueProperty<TreeViewItemCollapsibleIcon>> m_treeViewItemCollapsibleIcon;

        /// <summary>
        /// True means is open.
        /// </summary>
        std::shared_ptr<ValueProperty<bool>> m_isOpen;

        /// <summary>
        /// True means is selected.
        /// </summary>
        std::shared_ptr<ValueProperty<bool>> m_isSelected;

        /// <summary>
        /// Called when item is selected.
        /// </summary>
        std::shared_ptr<FEvent> m_onSelectedEvent;

        /// <summary>
        /// The size of the arrow.
        /// </summary>
        ImVec2 m_arrowSize;

        /// <summary>
        /// Texture for up arrow.
        /// </summary>
        std::shared_ptr<SuperTexture> m_upArrow;

        /// <summary>
        /// Texture for down arrow.
        /// </summary>
        std::shared_ptr<SuperTexture> m_downArrow;

        void RenderSelectableArrow(ImVec2 originalPosition) const;
        void RenderFullBackground(ImVec2 originalPosition) const;
        void RenderSelectableRow(ImVec2 originalPosition);
        void RenderArrowImage(ImVec2 originalPosition) const;
        void RenderRowText(ImVec2 originalPosition) const;
    };
}
