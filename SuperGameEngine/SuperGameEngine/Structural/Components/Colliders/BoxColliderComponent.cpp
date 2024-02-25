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
}

void BoxColliderComponent::Setup(SceneLoadPackage* loadPackage, GameObject* parent)
{
    ColliderComponent::Setup(loadPackage, parent);

    m_transform = parent->GetTransform();
    m_loadPackage->GetTechniqueRender()->GiveTechnique(m_rectangleDrawableTechnique);
}

bool BoxColliderComponent::Overlaps(Collider& other) const
{
    return false;
}

bool BoxColliderComponent::Contain(Collider& other) const
{
    return false;
}

bool BoxColliderComponent::Update(GameTime gameTime)
{
    ColliderComponent::Update(gameTime);

    // TODO: Do this on Transform location changed.
    m_retangleActual->SetLocation(
        m_transform->GetLocation()->GetX() + m_retangle->GetLeft() - (m_retangle->GetWidth() / 2.0f),
        m_transform->GetLocation()->GetY() + m_retangle->GetTop() - (m_retangle->GetHeight() / 2.0f));
    return true;
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
