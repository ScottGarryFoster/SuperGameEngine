#include "MoveViewportGizmo.h"

#include "FatedQuestLibraries.h"
#include "MoveInteractionChangedEvent.h"
#include "Engine/Content/TextureManager.h"
#include "Engine/Graphics/Geometry/PrimitiveRectangle.h"
#include "Engine/Graphics/Geometry/PrimitiveShapeProvider.h"
#include "Engine/Graphics/Texture/SuperTexture.h"
#include "Panels/ViewportTools/ViewportDebugOptionsChangedArguments.h"

using namespace SuperGameTools;
using namespace SuperGameEngine;
using namespace FatedQuestLibraries;
using namespace SuperGameInput;

MoveViewportGizmo::MoveViewportGizmo(
    const std::shared_ptr<TextureManager>& textureManager,
    const std::shared_ptr<SuperGameEngine::PrimitiveShapeProvider>& primitiveShapeProvider)
{
    m_arrowAsset = textureManager->GetTexture(R"(Tools\Icons\LongArrow\LongArrow-50.png)");
    m_moveAsset = textureManager->GetTexture(R"(Tools\Icons\Move\Move-25.png)");
    m_locationX = 0;
    m_locationY = 0;
    m_mouseX = 0;
    m_mouseY = 0;
    m_onInteractionChanged = std::make_shared<FEvent>();
    m_debugOption = ViewportDebugOption::None;

    m_debugRectangle = primitiveShapeProvider->CreateRectangle(FVector2F(), FVector2F(50, 50));

    m_inactiveColour = FColourHelpers::Red;
    m_hoverColour = FColourHelpers::Green;
    m_selectedColour = FColourHelpers::Blue;

    {
        GizmoElement& lowerLeft = m_arrowElements[0];
        lowerLeft = GizmoElement
        {
            .Texture = m_arrowAsset,
            .UsingBothCollisionRectangles = true,
            .LocationOffset = FPoint(-50, -7),
            .FirstCollisionOffset = FPoint(0, 7),
            .InactiveColour = {.Red= 229, .Green= 106, .Blue= 106, .Alpha= 255},
            .HoverColour = {.Red= 255, .Green= 188, .Blue= 188, .Alpha= 255},
            .SelectedColour = {.Red= 171, .Green= 79, .Blue= 79, .Alpha= 255},
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
            .InactiveColour = {.Red= 106, .Green= 229, .Blue= 106, .Alpha= 255},
            .HoverColour = {.Red= 188, .Green= 255, .Blue= 188, .Alpha= 255},
            .SelectedColour = {.Red= 79, .Green= 171, .Blue= 79, .Alpha= 255},
            .ElementName = GizmoElementName::UpperRightArrow,
        };
        upperRight.FirstCollisionRectangle.SetSize(10, 50);
        upperRight.SecondCollisionRectangle.SetSize(25, 15);
    }

    {
        GizmoElement& lowerRight = m_arrowElements[2];
        lowerRight = GizmoElement
        {
            .Texture = m_moveAsset,
            .UsingBothCollisionRectangles = false,
            .LocationOffset = FPoint(0, 0),
            .FirstCollisionOffset = FPoint(2, 2),
            .InactiveColour = {.Red = 106, .Green = 106, .Blue = 229, .Alpha = 255},
            .HoverColour = {.Red = 188, .Green = 188, .Blue = 255, .Alpha = 255},
            .SelectedColour = {.Red = 79, .Green = 79, .Blue = 171, .Alpha = 255},
            .ElementName = GizmoElementName::MoveAnywhereSquare,
        };
        lowerRight.FirstCollisionRectangle.SetSize(21, 21);
    }
}

void MoveViewportGizmo::Draw() const
{
    for (size_t i = 0; i < m_numberOfArrowElements; ++i)
    {
        GizmoElement current = m_arrowElements[i];

        if (current.Hovered)
        {
            current.Texture->Draw(FPoint(current.Location.GetX(), current.Location.GetY()), current.TransformationDetails, current.HoverColour);
        }
        else if (current.Selected)
        {
            current.Texture->Draw(FPoint(current.Location.GetX(), current.Location.GetY()), current.TransformationDetails, current.SelectedColour);
        }
        else
        {
            current.Texture->Draw(FPoint(current.Location.GetX(), current.Location.GetY()), current.TransformationDetails, current.InactiveColour);
        }

        if (EViewportDebugOption::HasFlag(m_debugOption, ViewportDebugOption::Gizmo))
        {
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

bool MoveViewportGizmo::UpdateMouseSelectionInput(int x, int y, KeyOrButtonState state)
{
    bool handled = false;
    if (EKeyOrButtonState::HasFlag(state, KeyOrButtonState::Pressed))
    {
        handled |= SetupInteractionWhenMouseHasJustBeenPressed(x, y);
    }
    else if (EKeyOrButtonState::HasFlag(state, KeyOrButtonState::Up))
    {
        handled |= SetupInteractionWhenMouseHasJustBeenReleased(x, y);
    }
    else if (EKeyOrButtonState::HasFlag(state, KeyOrButtonState::Down))
    {
        handled |= SetupInteractionWhenMouseIsDown(x, y);
    }

    return handled;
}

bool MoveViewportGizmo::UpdateOnMouseIsOutsideOfViewport()
{
    if (m_selectedGizmo > -1)
    {
        m_selectedGizmo = -1;

        for (GizmoElement& current : m_arrowElements)
        {
            current.Hovered = false;
            current.Selected = false;
        }

        return true;
    }

    return false;
}

std::shared_ptr<FatedQuestLibraries::FEventSubscriptions> MoveViewportGizmo::OnInteractionChanged() const
{
    return m_onInteractionChanged;
}

void MoveViewportGizmo::Invoke(const std::shared_ptr<FatedQuestLibraries::FEventArguments>& arguments)
{
    if (auto args = std::dynamic_pointer_cast<ViewportDebugOptionsChanged>(arguments))
    {
        m_debugOption = args->GetDebugOption();
    }
}

void MoveViewportGizmo::UpdateInteractionStateOfGizmo()
{
    if (m_selectedGizmo > -1)
    {
        return;
    }

    auto mousePoint = FPoint(m_mouseX, m_mouseY);
    for (GizmoElement& current : m_arrowElements)
    {
        current.Hovered = current.FirstCollisionRectangle.PointIsWithin(mousePoint) || current.SecondCollisionRectangle.PointIsWithin(mousePoint);
    }
}

bool MoveViewportGizmo::SetupInteractionWhenMouseHasJustBeenPressed(int x, int y)
{
    if (m_selectedGizmo > -1)
    {
        Log::Error("Mouse just pressed and something already selected",
            "MoveViewportGizmo::SetupInteractionWhenMouseHasJustBeenPressed(int,int)");
    }

    auto mousePoint = FPoint(x, y);
    for (size_t i = 0; i < m_numberOfArrowElements; ++i)
    {
        GizmoElement& current = m_arrowElements[i];
        if (current.FirstCollisionRectangle.PointIsWithin(mousePoint) || current.SecondCollisionRectangle.PointIsWithin(mousePoint))
        {
            m_selectedGizmo = static_cast<int>(i);
            m_originalLocation.SetXYValue(x, y);
            current.Hovered = false;
            current.Selected = true;
            break;
        }
    }

    if (m_selectedGizmo > -1)
    {
        m_onInteractionChanged->Invoke(std::make_shared<MoveInteractionChangedEvent>(ToolsGizmoAction::GizmoSelected));
    }

    return m_selectedGizmo > -1;
}

bool MoveViewportGizmo::SetupInteractionWhenMouseHasJustBeenReleased(int x, int y)
{
    if (m_selectedGizmo <= -1)
    {
        return false;
    }

    GizmoElement& current = m_arrowElements[m_selectedGizmo];
    current.Selected = false;

    m_selectedGizmo = -1;
    m_onInteractionChanged->Invoke(std::make_shared<MoveInteractionChangedEvent>(
        ToolsGizmoAction::GizmoUnselected));
    m_originalLocation.SetXYValue(x, y);

    return true;
}

bool MoveViewportGizmo::SetupInteractionWhenMouseIsDown(int x, int y)
{
    if (m_selectedGizmo <= -1)
    {
        return false;
    }

    // 1|2|3|4|5
    //  | |X| |O
    // X- Original O- Current
    // 5-3=2 Need to move 2 to get from X to O
    const GizmoElement& current = m_arrowElements[m_selectedGizmo];
    switch (current.ElementName)
    {
        case LowerLeftArrow: y = m_originalLocation.GetY(); break;
        case UpperRightArrow: x = m_originalLocation.GetX(); break;
    }

    int differenceX = x - m_originalLocation.GetX();
    int differenceY = y - m_originalLocation.GetY();
    m_originalLocation.SetXYValue(x, y);

    m_onInteractionChanged->Invoke(std::make_shared<MoveInteractionChangedEvent>(
        ToolsGizmoAction::MoveBy, differenceX, differenceY));

    UpdateGizmoLocation(m_locationX + differenceX, m_locationY + differenceY);

    return true;
}
