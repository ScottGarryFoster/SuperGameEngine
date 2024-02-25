#include "BoxColliderComponent.h"
#include "../../GameObject/GameObject.h"
#include "../../Components/Spatial/TransformComponent.h"
#include "../../../Engine/Graphics/Technique/RectangleDrawableTechnique.h"

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
}

void BoxColliderComponent::Setup(SceneLoadPackage* loadPackage, GameObject* parent)
{
    ColliderComponent::Setup(loadPackage, parent);

    m_transform = parent->GetTransform();
    m_transform->OnLocationChanged()->Subscribe(this);

    m_loadPackage->GetTechniqueRender()->GiveTechnique(m_rectangleDrawableTechnique);

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

    return false;
}

bool BoxColliderComponent::Contain(Collider& other) const
{
    return false;
}

bool BoxColliderComponent::Update(GameTime gameTime)
{
    ColliderComponent::Update(gameTime);


    return false;
}

void BoxColliderComponent::Draw()
{
    // Happens after the technique draws. This is for testing.
    m_rectangleDrawableTechnique->UpdateColour(0, 0, 0, 255);
}

void BoxColliderComponent::Invoke(FEventArguments* arguments)
{
    if (TypeHelpers::IsDerivedFrom<FEventArguments, FVectorLocationEventArguments>())
    {
        FVectorLocationEventArguments* locationArguments =
            dynamic_cast<FVectorLocationEventArguments*>(arguments);

        m_retangleActual->SetLocation(
            locationArguments->X + m_retangle->GetLeft() - (m_retangle->GetWidth() / 2.0f),
            locationArguments->Y + m_retangle->GetTop() - (m_retangle->GetHeight() / 2.0f));
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

void BoxColliderComponent::OnCollisionOccuring(Collision& collision)
{
    m_rectangleDrawableTechnique->UpdateColour(0, 255, 0, 255);
}
