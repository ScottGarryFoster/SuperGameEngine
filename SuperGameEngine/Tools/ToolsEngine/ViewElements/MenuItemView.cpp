#include "MenuItemView.h"
#include "../../ImGuiIncludes.h"

using namespace SuperGameTools;

MenuItemView::MenuItemView()
{
    m_label = std::make_shared<ValueProperty<std::string>>("Label");

    m_enabled = std::make_shared<FunctionProperty<bool>>("Enabled", true);

    m_selected = std::make_shared<FunctionProperty<bool>>("Selected", false);
}

MenuItemView::MenuItemView(const std::string& label)
{
    m_label = std::make_shared<ValueProperty<std::string>>("Label", label);

    m_enabled = std::make_shared<FunctionProperty<bool>>("Enabled", true);

    m_selected = std::make_shared<FunctionProperty<bool>>("Selected", false);
}

MenuItemView::MenuItemView(const std::string& label, const std::function<bool()>& enabled)
{
    m_label = std::make_shared<ValueProperty<std::string>>("Label", label);

    m_enabled = std::make_shared<FunctionProperty<bool>>("Enabled", true, enabled);
    m_enabled->Update();

    m_selected = std::make_shared<FunctionProperty<bool>>("Selected", false);
}

MenuItemView::MenuItemView(
    const std::string& label, 
    const std::function<bool()>& enabled,
    const std::function<bool()>& selected)
{
    m_label = std::make_shared<ValueProperty<std::string>>("Label", label);

    m_enabled = std::make_shared<FunctionProperty<bool>>("Enabled", true, enabled);
    m_enabled->Update();

    m_selected = std::make_shared<FunctionProperty<bool>>("Selected", false, selected);
    m_selected->Update();
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

void MenuItemView::Draw()
{
    // TODO: Submenus
    ImGui::MenuItem(
        m_label->GetValue().c_str(), 
        "CTRL+Y",
        m_selected->GetValue(),
        m_enabled->GetValue());
}
