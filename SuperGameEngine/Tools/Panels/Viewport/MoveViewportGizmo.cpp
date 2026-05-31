#include "MoveViewportGizmo.h"

#include "FatedQuestLibraries.h"
#include "Engine/Content/TextureManager.h"
#include "Engine/Graphics/Geometry/PrimitiveRectangle.h"
#include "Engine/Graphics/Geometry/PrimitiveShapeProvider.h"
#include "Engine/Graphics/Texture/SuperTexture.h"

using namespace SuperGameTools;
using namespace SuperGameEngine;
using namespace FatedQuestLibraries;

MoveViewportGizmo::MoveViewportGizmo(
    const std::shared_ptr<TextureManager>& textureManager,
    const std::shared_ptr<SuperGameEngine::PrimitiveShapeProvider>& primitiveShapeProvider)
{
    m_arrowAsset = textureManager->GetTexture(R"(Tools\Icons\LongArrow\LongArrow-50.png)");
    m_locationX = 0;
    m_locationY = 0;
    m_mouseX = 0;
    m_mouseY = 0;

    m_debugRectangle = primitiveShapeProvider->CreateRectangle(FVector2F(), FVector2F(50, 50));
    m_elementHovered = GizmoElementName::None;

    m_inactiveColour = FColour{ .Red = 255,.Green = 0, .Blue = 0, .Alpha = 255 };
    m_hoverColour = FColour{ .Red = 0,.Green = 255, .Blue = 0, .Alpha = 255 };

    m_lowerLeftArrow = GizmoElement
    {
        .Texture = m_arrowAsset,
        .UsingBothCollisionRectangles = true,
        .ElementName = GizmoElementName::LowerLeftArrow,
    };
    m_lowerLeftArrow.FirstCollisionRectangle.SetSize(50, 10);
    m_lowerLeftArrow.SecondCollisionRectangle.SetSize(15, 25);
}

void MoveViewportGizmo::Draw() const
{
    if (m_elementHovered == GizmoElementName::None)
    {
        m_lowerLeftArrow.Texture->Draw(FPoint(m_lowerLeftArrow.Location.GetX(), m_lowerLeftArrow.Location.GetY()), m_inactiveColour);
    }
    else if (m_elementHovered == GizmoElementName::LowerLeftArrow)
    {
        m_lowerLeftArrow.Texture->Draw(FPoint(m_lowerLeftArrow.Location.GetX(), m_lowerLeftArrow.Location.GetY()), m_hoverColour);
    }

    m_debugRectangle->DrawInPlace(
        m_lowerLeftArrow.FirstCollisionRectangle.GetLeft(),
        m_lowerLeftArrow.FirstCollisionRectangle.GetTop(),
        m_lowerLeftArrow.FirstCollisionRectangle.GetWidth(),
        m_lowerLeftArrow.FirstCollisionRectangle.GetHeight());

    m_debugRectangle->DrawInPlace(
        m_lowerLeftArrow.SecondCollisionRectangle.GetLeft(),
        m_lowerLeftArrow.SecondCollisionRectangle.GetTop(),
        m_lowerLeftArrow.SecondCollisionRectangle.GetWidth(),
        m_lowerLeftArrow.SecondCollisionRectangle.GetHeight());
}

void MoveViewportGizmo::UpdateGizmoLocation(int x, int y)
{
    m_locationX = x;
    m_locationY = y;

    // TODO: Continue with positioning from here
    m_lowerLeftArrow.Location.SetXYValue(m_locationX - 50, m_locationY - 7);

    m_lowerLeftArrow.FirstCollisionRectangle.SetLocation(m_lowerLeftArrow.Location.GetX(), m_lowerLeftArrow.Location.GetY() + 7);
    m_lowerLeftArrow.SecondCollisionRectangle.SetLocation(m_lowerLeftArrow.Location.GetX(), m_lowerLeftArrow.Location.GetY());

    auto mousePoint = FPoint(m_mouseX, m_mouseY);
    if (m_lowerLeftArrow.FirstCollisionRectangle.PointIsWithin(mousePoint) || m_lowerLeftArrow.SecondCollisionRectangle.PointIsWithin(mousePoint))
    {
        m_elementHovered = GizmoElementName::LowerLeftArrow;
    }
    else
    {
        m_elementHovered = GizmoElementName::None;
    }
}

void MoveViewportGizmo::UpdateMouseLocation(int x, int y)
{
    m_mouseX = x;
    m_mouseY = y;

    auto mousePoint = FPoint(m_mouseX, m_mouseY);
    if (m_lowerLeftArrow.FirstCollisionRectangle.PointIsWithin(mousePoint) || m_lowerLeftArrow.SecondCollisionRectangle.PointIsWithin(mousePoint))
    {
        m_elementHovered = GizmoElementName::LowerLeftArrow;
    }
    else
    {
        m_elementHovered = GizmoElementName::None;
    }
}
