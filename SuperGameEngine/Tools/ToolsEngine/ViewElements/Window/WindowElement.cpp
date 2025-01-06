#include "WindowElement.h"
#include "../ColoursAndStyles/ColoursAndStyles.h"
#include "../../../ImGuiIncludes.h"

using namespace SuperGameTools;

WindowElement::WindowElement()
{
    m_currentOpenClosedState = false;
    m_tabIsHovered = false;
}

void WindowElement::Setup(const std::shared_ptr<ColoursAndStyles>& colorsAndStyles)
{
    m_coloursAndStyles = colorsAndStyles;
}

bool WindowElement::RenderWindow(const char* name)
{
    m_coloursAndStyles->SetWindowTabColoursAndStyles(m_currentOpenClosedState, m_tabIsHovered);

    m_currentOpenClosedState = ImGui::Begin(name);
    m_tabIsHovered = ImGui::IsItemHovered();

    return m_currentOpenClosedState;
}

void WindowElement::EndWindowRender(const char* name)
{
    m_coloursAndStyles->PopWindowTabColoursAndStyles();
    ImGui::End();
}
