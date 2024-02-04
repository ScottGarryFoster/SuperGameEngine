#include "Transform.h"

using namespace SuperGameEngine;
using namespace StandardCLibrary;

Transform::Transform()
{
    m_location = new FVector2D();
    m_onLocationChanged = new FEvent();
}

Transform::~Transform()
{
    delete m_location;
    delete m_onLocationChanged;
}

FVector2D* Transform::GetLocation()
{
    return m_location;
}

FEventSubscriptions* Transform::OnLocationChanged()
{
    return m_onLocationChanged;
}

void Transform::Invoke(FEventArguments* arguments)
{
    m_onLocationChanged->Invoke(arguments);
}
