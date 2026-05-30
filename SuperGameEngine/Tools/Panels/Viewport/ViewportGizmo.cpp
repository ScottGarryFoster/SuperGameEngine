#include "ViewportGizmo.h"
#include "ViewportGizmo.h"

#include "FatedQuestLibraries.h"
#include "Engine/Content/TextureManager.h"
#include "Engine/Graphics/Geometry/PrimitiveRectangle.h"
#include "Engine/Graphics/Geometry/PrimitiveShapeProvider.h"
#include "Engine/Graphics/Texture/SuperTexture.h"
#include "Engine/Graphics/Texture/Texture.h"
#include "Structural/Assets/Texture/TextureAsset.h"

using namespace SuperGameTools;
using namespace SuperGameEngine;
using namespace FatedQuestLibraries;

ViewportGizmo::ViewportGizmo(
    const std::shared_ptr<TextureManager>& textureManager,
    const std::shared_ptr<SuperGameEngine::PrimitiveShapeProvider>& primitiveShapeProvider) : m_lowerRightArrowCollision(0, 0)
{
    m_arrowAsset = textureManager->GetTexture(R"(Tools\Icons\LongArrow\LongArrow-50.png)");
    m_locationX = 0;
    m_locationY = 0;
    m_mouseX = 0;
    m_mouseY = 0;
    m_bottomRightArrowX = 0;
    m_bottomRightArrowY = 0;

    m_lowerRightArrowCollision.SetSize(50, 10);

    m_debugRectangle = primitiveShapeProvider->CreateRectangle(FVector2F(), FVector2F(50, 50));
    m_elementHovered = GizmoElement::None;

    m_inactiveColour = FColour{ .Red = 255,.Green = 0, .Blue = 0, .Alpha = 255 };
    m_hoverColour = FColour{ .Red = 0,.Green = 255, .Blue = 0, .Alpha = 255 };
}

void ViewportGizmo::Draw() const
{
    if (m_elementHovered == GizmoElement::None)
    {
        m_arrowAsset->Draw(FPoint(m_bottomRightArrowX, m_bottomRightArrowY), m_inactiveColour);
    }
    else if (m_elementHovered == GizmoElement::LowerRightArrow)
    {
        m_arrowAsset->Draw(FPoint(m_bottomRightArrowX, m_bottomRightArrowY), m_hoverColour);
    }

    m_debugRectangle->DrawInPlace(
        m_lowerRightArrowCollision.GetLeft(),
        m_lowerRightArrowCollision.GetTop(),
        m_lowerRightArrowCollision.GetWidth(),
        m_lowerRightArrowCollision.GetHeight());
}

void ViewportGizmo::UpdateGizmoLocation(int x, int y)
{
    m_locationX = x;
    m_locationY = y;

    // TODO: Continue with positioning from here
    m_bottomRightArrowX = m_locationX - 50;
    m_bottomRightArrowY = m_locationY - 7;

    m_lowerRightArrowCollision.SetLocation(m_bottomRightArrowX, m_bottomRightArrowY + 7);

    auto mousePoint = FPoint(m_mouseX, m_mouseY);
    if (m_lowerRightArrowCollision.PointIsWithin(mousePoint))
    {
        m_elementHovered = GizmoElement::LowerRightArrow;
    }
    else
    {
        m_elementHovered = GizmoElement::None;
    }
}

void ViewportGizmo::UpdateMouseLocation(int x, int y)
{
    m_mouseX = x;
    m_mouseY = y;

    auto mousePoint = FPoint(m_mouseX, m_mouseY);
    if (m_lowerRightArrowCollision.PointIsWithin(mousePoint))
    {
        m_elementHovered = GizmoElement::LowerRightArrow;
    }
    else
    {
        m_elementHovered = GizmoElement::None;
    }
}
