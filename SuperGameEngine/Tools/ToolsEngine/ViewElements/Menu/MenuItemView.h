#pragma once
#include <memory>
#include <string>
#include "../../ModelElements/FunctionModel.h"
#include "../../PropertyChanged/PropertyChangedEvent.h"
#include "../../PropertyChanged/PropertyChangedObserver.h"
#include "../../GenericProperties/FunctionProperty.h"
#include "../../GenericProperties/ValueProperty.h"

namespace SuperGameTools
{
    /// <summary>
    /// A single item on a menu.
    /// </summary>
    class MenuItemView : public PropertyChangedEvent, public PropertyChangedObserver, public std::enable_shared_from_this<MenuItemView>
    {
    public:
        MenuItemView();
        MenuItemView(const std::string& key, const std::string& label);
        MenuItemView(const std::string& key, const std::string& label, const std::function<bool()>& enabled);
        MenuItemView(const std::string& key, const std::string& label, const std::function<bool()>& enabled, const std::function<bool()>& selected);
        virtual ~MenuItemView() override = default;

        /// <summary>
        /// Property has changed.
        /// </summary>
        /// <param name="name">Property which has changed. </param>
        virtual void OnPropertyChanged(const std::string& name) override;

        /// <summary>
        /// A key you can give to a menu item which you should ideally not change.
        /// This allows you to change a label or the display of an item without
        /// changing the link to elements in the tools.
        /// The key is what you search for from the MenuView.
        /// </summary>
        /// <returns>A unique identification, given at construction. </returns>
        virtual std::string GetKey() const;

        /// <summary>
        /// Label shown to the user.
        /// </summary>
        /// <returns>Label shown to the user. </returns>
        virtual std::shared_ptr<ValueProperty<std::string>> GetLabel() const;

        /// <summary>
        /// Gets the function call for Enabled.
        /// True means enabled.
        /// </summary>
        /// <returns>True means enabled. </returns>
        virtual std::shared_ptr<FunctionProperty<bool>> GetEnabled();

        /// <summary>
        /// Gets IsSelected.
        /// True means shows as selected.
        /// </summary>
        /// <returns>True means shows as selected. </returns>
        virtual std::shared_ptr<FunctionProperty<bool>> GetSelected();

        /// <summary>
        /// Called when the item is selected.
        /// </summary>
        /// <returns>Called when the item is selected. </returns>
        virtual std::shared_ptr<FEventSubscriptions> OnSelected();

        /// <summary>
        /// Call to draw the menu item. 
        /// </summary>
        virtual void Draw();

    private:
        /// <summary>
        /// A key you can give to a menu item which you should ideally not change.
        /// This allows you to change a label or the display of an item without
        /// changing the link to elements in the tools.
        /// The key is what you search for from the MenuView.
        /// </summary>
        std::string m_key;

        /// <summary>
        /// Label shown to the user.
        /// </summary>
        std::shared_ptr<ValueProperty<std::string>> m_label;

        /// <summary>
        /// Gets the function call for Enabled.
        /// True means enabled.
        /// </summary>
        std::shared_ptr<FunctionProperty<bool>> m_enabled;

        /// <summary>
        /// Gets IsSelected.
        /// True means shows as selected.
        /// </summary>
        std::shared_ptr<FunctionProperty<bool>> m_selected;

        /// <summary>
        /// Called when the item is selected.
        /// </summary>
        std::shared_ptr<FEvent> m_onSelected;
    };
}
