#include "ToolsWindowElement.h"

#include "ToolsWindowShownArguments.h"
#include "../ColoursAndStyles/ColoursAndStyles.h"
#include "../../../ImGuiIncludes.h"
#include "../../../../FatedQuest.Libraries/Observer/AllReferences.h"

using namespace SuperGameTools;

ToolsWindowElement::ToolsWindowElement()
{
    m_currentOpenClosedState = false;
    m_tabIsHovered = false;
    m_windowIsShown = true;
    m_onWindowShownOrHidden = std::make_shared<FatedQuestLibraries::FEvent>();
    m_windowUniqueName = {};
}

void ToolsWindowElement::SetupWindow(const std::shared_ptr<ColoursAndStyles>& colorsAndStyles, const std::string& uniqueName)
{
    m_coloursAndStyles = colorsAndStyles;
    m_windowUniqueName = uniqueName;
}

bool ToolsWindowElement::RenderWindow(const char* name)
{
    if (!m_windowIsShown)
    {
        return m_windowIsShown;
    }

    m_coloursAndStyles->SetWindowTabColoursAndStyles(m_currentOpenClosedState, m_tabIsHovered);

    m_currentOpenClosedState = ImGui::Begin(name, &m_windowIsShown);
    if (!m_windowIsShown)
    {
        // Ensure we pop anything and close the window.
        m_coloursAndStyles->PopWindowTabColoursAndStyles();
        ImGui::End();

        HideWindow();
        return false;
    }

    m_tabIsHovered = ImGui::IsItemHovered();
    return m_currentOpenClosedState;
}

void ToolsWindowElement::EndWindowRender(const char* name)
{
    if (!m_windowIsShown)
    {
        return;
    }

    m_coloursAndStyles->PopWindowTabColoursAndStyles();
    ImGui::End();
}

void ToolsWindowElement::ShowWindow()
{
    m_windowIsShown = true;
    m_onWindowShownOrHidden->Invoke
        (std::make_shared<ToolsWindowShownArguments>
        (m_windowIsShown, m_windowUniqueName));
}

void ToolsWindowElement::HideWindow()
{
    m_windowIsShown = false;
    m_onWindowShownOrHidden->Invoke
        (std::make_shared<ToolsWindowShownArguments>
        (m_windowIsShown, m_windowUniqueName));
}

std::shared_ptr<FatedQuestLibraries::FEventSubscriptions> ToolsWindowElement::OnWindowShownOrHidden()
{
    return m_onWindowShownOrHidden;
}
