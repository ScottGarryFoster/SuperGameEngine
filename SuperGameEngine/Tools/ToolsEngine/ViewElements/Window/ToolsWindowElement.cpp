#include "ToolsWindowElement.h"
#include "../ColoursAndStyles/ColoursAndStyles.h"
#include "../../../ImGuiIncludes.h"

using namespace SuperGameTools;

ToolsWindowElement::ToolsWindowElement()
{
    m_currentOpenClosedState = false;
    m_tabIsHovered = false;
}

void ToolsWindowElement::SetupWindow(const std::shared_ptr<ColoursAndStyles>& colorsAndStyles)
{
    m_coloursAndStyles = colorsAndStyles;
}

bool ToolsWindowElement::RenderWindow(const char* name)
{
    m_coloursAndStyles->SetWindowTabColoursAndStyles(m_currentOpenClosedState, m_tabIsHovered);

    m_currentOpenClosedState = ImGui::Begin(name);
    m_tabIsHovered = ImGui::IsItemHovered();

    return m_currentOpenClosedState;
}

void ToolsWindowElement::EndWindowRender(const char* name)
{
    m_coloursAndStyles->PopWindowTabColoursAndStyles();
    ImGui::End();
}
