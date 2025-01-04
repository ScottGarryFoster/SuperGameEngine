#include "MenuItemView.h"
#include "../../../ImGuiIncludes.h"
#include "../../../FatedQuestLibraries.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

MenuItemView::MenuItemView()
{
    Log::Warning("A menu item was created without a key. "
        "This means that it might be linked by default or be unlink-able.",
        "MenuItemView::MenuItemView()");

    m_label = std::make_shared<ValueProperty<std::string>>("Label");

    m_enabled = std::make_shared<FunctionProperty<bool>>("Enabled", true);

    m_selected = std::make_shared<FunctionProperty<bool>>("Selected", false);

    m_onSelected = std::make_shared<FEvent>();
}

MenuItemView::MenuItemView(const std::string& key, const std::string& label)
{
    m_key = key;

    m_label = std::make_shared<ValueProperty<std::string>>("Label", label);

    m_enabled = std::make_shared<FunctionProperty<bool>>("Enabled", true);

    m_selected = std::make_shared<FunctionProperty<bool>>("Selected", false);

    m_onSelected = std::make_shared<FEvent>();
}

MenuItemView::MenuItemView(const std::string& key, const std::string& label, const std::function<bool()>& enabled)
{
    m_key = key;

    m_label = std::make_shared<ValueProperty<std::string>>("Label", label);

    m_enabled = std::make_shared<FunctionProperty<bool>>("Enabled", true, enabled);
    m_enabled->Update();

    m_selected = std::make_shared<FunctionProperty<bool>>("Selected", false);

    m_onSelected = std::make_shared<FEvent>();
}

MenuItemView::MenuItemView(
    const std::string& key, 
    const std::string& label,
    const std::function<bool()>& enabled,
    const std::function<bool()>& selected)
{
    m_key = key;

    m_label = std::make_shared<ValueProperty<std::string>>("Label", label);

    m_enabled = std::make_shared<FunctionProperty<bool>>("Enabled", true, enabled);
    m_enabled->Update();

    m_selected = std::make_shared<FunctionProperty<bool>>("Selected", false, selected);
    m_selected->Update();

    m_onSelected = std::make_shared<FEvent>();
}

void MenuItemView::OnPropertyChanged(const std::string& name)
{
    if (name == m_enabled->GetName())
    {
        m_enabled->Update();
    }
    else if (name == m_selected->GetName())
    {
        m_selected->Update();
    }
}

std::string MenuItemView::GetKey() const
{
    return m_key;
}

std::shared_ptr<ValueProperty<std::string>> MenuItemView::GetLabel() const
{
    return m_label;
}

std::shared_ptr<FunctionProperty<bool>> MenuItemView::GetEnabled()
{
    return m_enabled;
}

std::shared_ptr<FunctionProperty<bool>> MenuItemView::GetSelected()
{
    return m_selected;
}

std::shared_ptr<FEventSubscriptions> MenuItemView::OnSelected()
{
    return m_onSelected;
}

void MenuItemView::Draw()
{
    // TODO: Submenus
    if (ImGui::MenuItem(
        m_label->GetValue().c_str(), 
        "CTRL+Y",
        m_selected->GetValue(),
        m_enabled->GetValue()))
    {
        m_onSelected->Invoke(nullptr);
    }
}
