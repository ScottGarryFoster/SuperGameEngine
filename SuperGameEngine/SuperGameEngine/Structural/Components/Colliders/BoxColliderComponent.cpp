#include "BoxColliderComponent.h"
#include "../../GameObject/GameObject.h"
#include "../../Components/Spatial/TransformComponent.h"
#include "../../../Engine/Graphics/Technique/RectangleDrawableTechnique.h"
#include "CircleColliderComponent.h"
#include "../../Spatial/Positional/TransformChangedEventArguments.h"

using namespace SuperGameEngine;
using namespace StandardCLibrary;
BoxColliderComponent::BoxColliderComponent() : ColliderComponent()
{
    m_retangle = std::make_shared<Rectangle>(0, 0, 1, 1);
    m_retangleActual = std::make_shared<Rectangle>(0, 0, 1, 1);
    m_rectangleDrawableTechnique = std::make_shared<RectangleDrawableTechnique>(m_retangleActual);
    m_transform = nullptr;
}

BoxColliderComponent::~BoxColliderComponent()
{
    m_retangle.reset();
    m_retangleActual.reset();
    m_rectangleDrawableTechnique.reset();
    m_transform.reset();
}

void BoxColliderComponent::Setup(SceneLoadPackage* loadPackage, GameObject* parent)
{
    ColliderComponent::Setup(loadPackage, parent);

    m_transform = parent->GetTransformComponent();
    m_transform->OnLocationChanged()->Subscribe(this);

    GetLoadPackage()->GetTechniqueRender()->GiveTechnique(m_rectangleDrawableTechnique);

    m_retangleActual->SetLocation(
        m_transform->GetLocation()->GetX() + m_retangle->GetLeft() - (m_retangle->GetWidth() / 2.0f),
        m_transform->GetLocation()->GetY() + m_retangle->GetTop() - (m_retangle->GetHeight() / 2.0f));
}

bool BoxColliderComponent::Overlaps(Collider& other) const
{
    if (typeid(other) == typeid(BoxColliderComponent))
    {
        BoxColliderComponent* otherBox =
            dynamic_cast<BoxColliderComponent*>(&other);

        Rectangle* otherRectangle = otherBox->m_retangleActual.get();
        return m_retangleActual->Overlaps(*otherRectangle);
    }
    else if (typeid(other) == typeid(CircleColliderComponent))
    {
        CircleColliderComponent* otherAreaComponent =
            dynamic_cast<CircleColliderComponent*>(&other);

        Circle otherArea = otherAreaComponent->GetArea();
        return otherArea.Overlaps(*m_retangleActual);
    }

    return false;
}

bool BoxColliderComponent::Contain(Collider& other) const
{
    return false;
}

void BoxColliderComponent::MoveOutOfOverlapRangeOf(const Collider& other, const FVector2D& previousLocation)
{
    // Previous point is the top left, the compared point in rectangle is the center point.
    FVector2D centerPoint = ConvertTopLeftToCenter(previousLocation);

    // We cache the location so that transform occurs once on the object
    // and there is one implementation of the rec to world space rec translation.
    FVector2D cachedLocation = FVector2D(m_retangleActual->GetTopLeft());
    FVector2D newLocation = FVector2D();

    if (typeid(other) == typeid(BoxColliderComponent))
    {
        const BoxColliderComponent* otherBox =
            dynamic_cast<const BoxColliderComponent*>(&other);

        Rectangle* otherRectangle = otherBox->m_retangleActual.get();
        newLocation = m_retangleActual->GetNewLocationToNotOverlap(*otherRectangle, centerPoint);
    }
    else if (typeid(other) == typeid(CircleColliderComponent))
    {
        const CircleColliderComponent* otherAreaComponent =
            dynamic_cast<const CircleColliderComponent*>(&other);

        Circle otherArea = otherAreaComponent->GetArea();
        newLocation = m_retangleActual->GetNewLocationToNotOverlap(otherArea);
    }

    FVector2D moved = newLocation - cachedLocation;
    const FVector2D* location = m_transform->GetLocation();
    FVector2D newLoc = *location + moved;
    m_transform->SetLocation(newLoc.GetX(), newLoc.GetY());
}

bool BoxColliderComponent::Update(GameTime gameTime)
{
    ColliderComponent::Update(gameTime);


    return false;
}

void BoxColliderComponent::Invoke(FEventArguments* arguments)
{
    TransformChangedEventArguments* locationArguments =
        dynamic_cast<TransformChangedEventArguments*>(arguments);
    if (locationArguments)
    {
        m_retangleActual->SetLocation(
            locationArguments->Location->GetX() + m_retangle->GetLeft() - (m_retangle->GetWidth() / 2.0f),
            locationArguments->Location->GetY() + m_retangle->GetTop() - (m_retangle->GetHeight() / 2.0f));
    }
}

FVector2D BoxColliderComponent::GetColliderLocation() const
{
    FVector2D location;
    location.SetXYValue(m_retangle->GetLeft(), m_retangle->GetTop());
    return location;
}

void BoxColliderComponent::SetColliderLocation(FVector2D& location)
{
    m_retangle->SetLocation(location.GetX(), location.GetY());
}

FVector2D BoxColliderComponent::GetColliderSize() const
{
    FVector2D size;
    size.SetXYValue(m_retangle->GetWidth(), m_retangle->GetHeight());
    return size;
}

void BoxColliderComponent::SetColliderSize(FVector2D& size)
{
    m_retangle->SetSize(size.GetX(), size.GetY());
    m_retangleActual->SetSize(size.GetX(), size.GetY());
}

void BoxColliderComponent::OnCollisionBegin(Collision& collision)
{
    m_rectangleDrawableTechnique->SetColour(255, 0, 0, 255);
}

void BoxColliderComponent::OnCollisionOccuring(Collision& collision)
{
    //m_rectangleDrawableTechnique->SetColour(0, 255, 0, 255);
}

void BoxColliderComponent::OnCollisionEnd(Collision& collision)
{
    m_rectangleDrawableTechnique->SetColour(0, 0, 255, 255);
}

Rectangle BoxColliderComponent::GetArea() const
{
    return *m_retangleActual;
}

FVector2D BoxColliderComponent::ConvertTopLeftToCenter(const FVector2D& location) const
{
    float x = location.GetX() + m_retangle->GetWidth() / 2.0f;
    float y = location.GetY() + m_retangle->GetHeight() / 2.0f;
    return FVector2D(x, y);
}
