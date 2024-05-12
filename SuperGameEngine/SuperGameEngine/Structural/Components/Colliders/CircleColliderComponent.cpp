#include "CircleColliderComponent.h"
#include "../../GameObject/GameObject.h"
#include "../../Components/Spatial/TransformComponent.h"
#include "BoxColliderComponent.h"
#include "../../Spatial/Positional/TransformChangedEventArguments.h"

using namespace SuperGameEngine;
using namespace StandardCLibrary;

CircleColliderComponent::CircleColliderComponent()
{
    m_circle = std::make_shared<Circle>(50);
    m_circleActual = std::make_shared<Circle>(50);
    m_circleDrawableTechnique = std::make_shared<CircleDrawableTechnique>(m_circleActual);
    m_transform = nullptr;
}

CircleColliderComponent::~CircleColliderComponent()
{
    m_circle.reset();
    m_circleActual.reset();
    m_transform.reset();
    m_circleDrawableTechnique.reset();
}

void CircleColliderComponent::Setup(SceneLoadPackage* loadPackage, GameObject* parent)
{
    ColliderComponent::Setup(loadPackage, parent);

    GetLoadPackage()->GetTechniqueRender()->GiveTechnique(m_circleDrawableTechnique);

    m_transform = parent->GetTransformComponent();
    m_transform->OnLocationChanged()->Subscribe(this);

    FVector2D newLocation = FVector2D(
        m_transform->GetLocation()->GetX() + m_circle->GetLocation().GetX(),
        m_transform->GetLocation()->GetY() + m_circle->GetLocation().GetY());
    m_circleActual->SetLocation(newLocation);
}

bool CircleColliderComponent::Overlaps(Collider& other) const
{
    if (typeid(other) == typeid(CircleColliderComponent))
    {
        CircleColliderComponent* otherBox =
            dynamic_cast<CircleColliderComponent*>(&other);

        Circle otherArea = otherBox->GetArea();
        return m_circleActual->Overlaps(otherArea);
    }
    else if (typeid(other) == typeid(BoxColliderComponent))
    {
        BoxColliderComponent* otherBox =
            dynamic_cast<BoxColliderComponent*>(&other);

        Rectangle otherArea = otherBox->GetArea();
        return m_circleActual->Overlaps(otherArea);
    }

    return false;
}

bool CircleColliderComponent::Contain(Collider& other) const
{
    return false;
}

void CircleColliderComponent::MoveOutOfOverlapRangeOf(const Collider& other, const FVector2D& previousLocation)
{
    // We cache the location so that transform occurs once on the object
    // and there is one implementation of the shape to world space shape translation.
    FVector2D cachedLocation = FVector2D(m_circleActual->GetLocation());
    FVector2D newLocation = FVector2D();
    if (typeid(other) == typeid(BoxColliderComponent))
    {
        const BoxColliderComponent* otherBox =
            dynamic_cast<const BoxColliderComponent*>(&other);

        Rectangle otherRectangle = otherBox->GetArea();
        newLocation = m_circleActual->GetNewLocationToNotOverlap(otherRectangle);
    }
    else if (typeid(other) == typeid(CircleColliderComponent))
    {
        const CircleColliderComponent* otherAreaComponent =
           dynamic_cast<const CircleColliderComponent*>(&other);

        Circle otherArea = otherAreaComponent->GetArea();
        newLocation = m_circleActual->GetNewLocationToNotOverlap(otherArea);
    }

    FVector2D moved = newLocation - cachedLocation;
    const FVector2D* location = m_transform->GetLocation();
    FVector2D newLoc = *location + moved;
    m_transform->SetLocation(newLoc.GetX(), newLoc.GetY());
}

bool CircleColliderComponent::Update(const GameTime gameTime)
{
    return false;
}

void CircleColliderComponent::Invoke(FEventArguments* arguments)
{
    TransformChangedEventArguments* locationArguments =
        dynamic_cast<TransformChangedEventArguments*>(arguments);
    if (locationArguments)
    {
        FVector2D circleLocation = m_circle->GetLocation();
        circleLocation.SetX(locationArguments->Location->GetX() + circleLocation.GetX());
        circleLocation.SetY(locationArguments->Location->GetY() + circleLocation.GetY());
        m_circleActual->SetLocation(circleLocation);
    }
}

FVector2D CircleColliderComponent::GetColliderLocation() const
{
    return m_circle->GetLocation();
}

void CircleColliderComponent::SetColliderLocation(FVector2D& location)
{
    m_circle->SetLocation(location);
}

int CircleColliderComponent::GetColliderSize() const
{
    return m_circle->GetRadius();
}

void CircleColliderComponent::SetColliderSize(int size)
{
    m_circle->SetRadius(size);
    m_circleActual->SetRadius(size);
}

void CircleColliderComponent::OnCollisionBegin(Collision& collision)
{
    m_circleDrawableTechnique->SetColour(255, 0, 0, 255);
}

void CircleColliderComponent::OnCollisionOccuring(Collision& collision)
{
    //m_circleDrawableTechnique->SetColour(0, 255, 0, 255);
}

void CircleColliderComponent::OnCollisionEnd(Collision& collision)
{
    m_circleDrawableTechnique->SetColour(0, 0, 255, 255);
}

Circle SuperGameEngine::CircleColliderComponent::GetArea() const
{
    return *m_circleActual;
}
