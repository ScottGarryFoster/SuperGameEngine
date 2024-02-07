#include "TransformComponent.h"

using namespace SuperGameEngine;
using namespace StandardCLibrary;

TransformComponent::TransformComponent()
{
    m_location = new FVector2D();
    m_onLocationChanged = new FEvent();
}

TransformComponent::~TransformComponent()
{
    delete m_location;
    delete m_onLocationChanged;
}

FVector2D* TransformComponent::GetLocation()
{
    return m_location;
}

FEventSubscriptions* TransformComponent::OnLocationChanged()
{
    return m_onLocationChanged;
}

void TransformComponent::Invoke(FEventArguments* arguments)
{
    m_onLocationChanged->Invoke(arguments);
}
