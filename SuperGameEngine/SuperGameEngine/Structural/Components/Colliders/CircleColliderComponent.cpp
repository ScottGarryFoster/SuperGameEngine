#include "CircleColliderComponent.h"
#include "../../GameObject/GameObject.h"
#include "../../Components/Spatial/TransformComponent.h"
#include "BoxColliderComponent.h"

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

    m_transform = parent->GetTransform();
    m_transform->OnLocationChanged()->Subscribe(this);
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

bool SuperGameEngine::CircleColliderComponent::Contain(Collider& other) const
{
    return false;
}

bool CircleColliderComponent::Update(GameTime gameTime)
{
    return false;
}

void CircleColliderComponent::Invoke(FEventArguments* arguments)
{
    if (TypeHelpers::IsDerivedFrom<FEventArguments, FVectorLocationEventArguments>())
    {
        FVectorLocationEventArguments* locationArguments =
            dynamic_cast<FVectorLocationEventArguments*>(arguments);

        FVector2D circleLocation = m_circle->GetLocation();
        circleLocation.SetX(locationArguments->X + circleLocation.GetX());
        circleLocation.SetY(locationArguments->Y + circleLocation.GetY());
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
