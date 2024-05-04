#include "Transform.h"

using namespace SuperGameEngine;
using namespace StandardCLibrary;

Transform::Transform()
{
    m_location = new FObservableVector2D();
    m_location->GetOnValueChanged()->Subscribe(this);
    m_onLocationChanged = new FEvent();
}

Transform::~Transform()
{
    delete m_location;
    delete m_onLocationChanged;
}

const FVector2D* Transform::GetLocation() const
{
    return m_location;
}

void Transform::SetLocation(float x, float y)
{
    m_location->SetXYValue(x, y);
}

FEventSubscriptions* Transform::OnLocationChanged()
{
    return m_onLocationChanged;
}

void Transform::Invoke(FEventArguments* arguments)
{
    m_onLocationChanged->Invoke(arguments);
}