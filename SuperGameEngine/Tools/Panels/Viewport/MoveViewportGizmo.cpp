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

    {
        GizmoElement& lowerLeft = m_arrowElements[0];
        lowerLeft = GizmoElement
        {
            .Texture = m_arrowAsset,
            .UsingBothCollisionRectangles = true,
            .LocationOffset = FPoint(-50, -7),
            .FirstCollisionOffset = FPoint(0, 7),
            .ElementName = GizmoElementName::LowerLeftArrow,
        };
        lowerLeft.FirstCollisionRectangle.SetSize(50, 10);
        lowerLeft.SecondCollisionRectangle.SetSize(15, 25);
    }

    {
        GizmoElement& upperRight = m_arrowElements[1];
        upperRight = GizmoElement
        {
            .Texture = m_arrowAsset,
            .UsingBothCollisionRectangles = true,
            .LocationOffset = FPoint(18, -50),
            .FirstCollisionOffset = FPoint(-18, 0),
            .SecondCollisionOffset = FPoint(-25, 0),
            .TransformationDetails = {.Angle = 90},
            .ElementName = GizmoElementName::UpperRightArrow,
        };
        upperRight.FirstCollisionRectangle.SetSize(10, 50);
        upperRight.SecondCollisionRectangle.SetSize(25, 15);
    }
}

void MoveViewportGizmo::Draw() const
{
    for (size_t i = 0; i < m_numberOfArrowElements; ++i)
    {
        GizmoElement current = m_arrowElements[i];

        if (m_elementHovered == current.ElementName)
        {
            current.Texture->Draw(FPoint(current.Location.GetX(), current.Location.GetY()), current.TransformationDetails, m_hoverColour);
        }
        else
        {
            current.Texture->Draw(FPoint(current.Location.GetX(), current.Location.GetY()), current.TransformationDetails, m_inactiveColour);
        }

        m_debugRectangle->DrawInPlace(
            current.FirstCollisionRectangle.GetLeft(),
            current.FirstCollisionRectangle.GetTop(),
            current.FirstCollisionRectangle.GetWidth(),
            current.FirstCollisionRectangle.GetHeight());

        m_debugRectangle->DrawInPlace(
            current.SecondCollisionRectangle.GetLeft(),
            current.SecondCollisionRectangle.GetTop(),
            current.SecondCollisionRectangle.GetWidth(),
            current.SecondCollisionRectangle.GetHeight());
    }
}

void MoveViewportGizmo::UpdateGizmoLocation(int x, int y)
{
    m_locationX = x;
    m_locationY = y;

    for (size_t i = 0; i < m_numberOfArrowElements; ++i)
    {
        GizmoElement& current = m_arrowElements[i];

        current.Location.SetXYValue(m_locationX + current.LocationOffset.GetX(), m_locationY + current.LocationOffset.GetY());

        current.FirstCollisionRectangle.SetLocation(
            current.Location.GetX() + current.FirstCollisionOffset.GetX(),
            current.Location.GetY() + current.FirstCollisionOffset.GetY());
        current.SecondCollisionRectangle.SetLocation(
            current.Location.GetX() + current.SecondCollisionOffset.GetX(),
            current.Location.GetY() + current.SecondCollisionOffset.GetY());

    }

    UpdateInteractionStateOfGizmo();
}

void MoveViewportGizmo::UpdateMouseLocation(int x, int y)
{
    m_mouseX = x;
    m_mouseY = y;

    UpdateInteractionStateOfGizmo();
}

void MoveViewportGizmo::UpdateInteractionStateOfGizmo()
{
    auto mousePoint = FPoint(m_mouseX, m_mouseY);
    m_elementHovered = GizmoElementName::None;
    for (size_t i = 0; i < m_numberOfArrowElements; ++i)
    {
        GizmoElement current = m_arrowElements[i];
        if (current.FirstCollisionRectangle.PointIsWithin(mousePoint) || current.SecondCollisionRectangle.PointIsWithin(mousePoint))
        {
            m_elementHovered = current.ElementName;
        }
    }

}