#include "MoveViewportGizmo.h"

#include "FatedQuestLibraries.h"
#include "MoveInteractionChangedEvent.h"
#include "Engine/Content/TextureManager.h"
#include "Engine/Graphics/Geometry/PrimitiveRectangle.h"
#include "Engine/Graphics/Geometry/PrimitiveShapeProvider.h"
#include "Engine/Graphics/Texture/SuperTexture.h"

using namespace SuperGameTools;
using namespace SuperGameEngine;
using namespace FatedQuestLibraries;
using namespace SuperGameInput;

MoveViewportGizmo::MoveViewportGizmo(
    const std::shared_ptr<TextureManager>& textureManager,
    const std::shared_ptr<SuperGameEngine::PrimitiveShapeProvider>& primitiveShapeProvider)
{
    m_arrowAsset = textureManager->GetTexture(R"(Tools\Icons\LongArrow\LongArrow-50.png)");
    m_locationX = 0;
    m_locationY = 0;
    m_mouseX = 0;
    m_mouseY = 0;
    m_onInteractionChanged = std::make_shared<FEvent>();

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

void MoveViewportGizmo::UpdateMouseSelectionInput(int x, int y, KeyOrButtonState state)
{
    if (EKeyOrButtonState::HasFlag(state, KeyOrButtonState::Pressed))
    {
        SetupInteractionWhenMouseHasJustBeenPressed(x, y);
    }
    else if (EKeyOrButtonState::HasFlag(state, KeyOrButtonState::Up))
    {
        SetupInteractionWhenMouseHasJustBeenReleased(x, y);
    }
    else if (EKeyOrButtonState::HasFlag(state, KeyOrButtonState::Down))
    {
        SetupInteractionWhenMouseIsDown(x, y);
    }
}

void MoveViewportGizmo::UpdateOnMouseIsOutsideOfViewport()
{
    m_selectedGizmo = -1;
    m_elementHovered = GizmoElementName::None;
}

std::shared_ptr<FatedQuestLibraries::FEventSubscriptions> MoveViewportGizmo::OnInteractionChanged() const
{
    return m_onInteractionChanged;
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

void MoveViewportGizmo::SetupInteractionWhenMouseHasJustBeenPressed(int x, int y)
{
    if (m_selectedGizmo > -1)
    {
        Log::Error("Mouse just pressed and something already selected",
            "MoveViewportGizmo::SetupInteractionWhenMouseHasJustBeenPressed(int,int)");
    }

    auto mousePoint = FPoint(x, y);
    for (size_t i = 0; i < m_numberOfArrowElements; ++i)
    {
        GizmoElement current = m_arrowElements[i];
        if (current.FirstCollisionRectangle.PointIsWithin(mousePoint) || current.SecondCollisionRectangle.PointIsWithin(mousePoint))
        {
            m_selectedGizmo = static_cast<int>(i);
            m_originalLocation.SetXYValue(x, y);
            m_elementHovered = GizmoElementName::None;
            break;
        }
    }

    if (m_selectedGizmo > -1)
    {
        m_onInteractionChanged->Invoke(std::make_shared<MoveInteractionChangedEvent>(ToolsGizmoAction::GizmoSelected));
    }
}

void MoveViewportGizmo::SetupInteractionWhenMouseHasJustBeenReleased(int x, int y)
{
    if (m_selectedGizmo <= -1)
    {
        return;
    }

    GizmoElement current = m_arrowElements[m_selectedGizmo];
    m_selectedGizmo = -1;
    m_onInteractionChanged->Invoke(std::make_shared<MoveInteractionChangedEvent>(
        ToolsGizmoAction::GizmoUnselected, 
        x - m_originalLocation.GetX(),
        y - m_originalLocation.GetY()));
    m_originalLocation.SetXYValue(x, y);
}

void MoveViewportGizmo::SetupInteractionWhenMouseIsDown(int x, int y)
{
    if (m_selectedGizmo <= -1)
    {
        return;
    }

    // 1|2|3|4|5
    //  | |X| |O
    // X- Original O- Current
    // 5-3=2 Need to move 2 to get from X to O
    int differenceX = x - m_originalLocation.GetX();
    int differenceY = y - m_originalLocation.GetY();
    m_originalLocation.SetXYValue(x, y);

    GizmoElement current = m_arrowElements[m_selectedGizmo];
    m_onInteractionChanged->Invoke(std::make_shared<MoveInteractionChangedEvent>(
        ToolsGizmoAction::MoveBy, differenceX, differenceY));

    UpdateGizmoLocation(m_locationX + differenceX, m_locationY + differenceY);
}
