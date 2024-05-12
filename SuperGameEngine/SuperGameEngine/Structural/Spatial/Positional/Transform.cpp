#include "Transform.h"
#include "TransformChangedEventArguments.h"

using namespace SuperGameEngine;
using namespace StandardCLibrary;

Transform::Transform()
{
    m_location = std::make_unique<FObservableVector2D>();
    m_location->GetOnValueChanged()->Subscribe(this);

    m_scale = std::make_unique<FObservableVector2D>();
    m_scale->SetXYValue(1, 1);
    m_scale->GetOnValueChanged()->Subscribe(this);

    m_rotation = std::make_unique<FObservableVector2D>();
    m_rotation->GetOnValueChanged()->Subscribe(this);

    m_onLocationChanged = new FEvent();
}

Transform::~Transform()
{
    delete m_onLocationChanged;
}

const FVector2D* Transform::GetLocation() const
{
    return m_location.get();
}

void Transform::SetLocation(const float x, const float y)
{
    m_location->SetXYValue(x, y);
}

void Transform::SetLocation(const float xy)
{
    m_location->SetXYValue(xy, xy);
}

void Transform::SetLocation(const FVector2D& value)
{
    m_location->SetXYValue(value.GetX(), value.GetY());
}

const FVector2D* Transform::GetRotation() const
{
    return m_rotation.get();
}

FEventSubscriptions* Transform::OnLocationChanged()
{
    return m_onLocationChanged;
}

void Transform::Invoke(FEventArguments* arguments)
{
    TransformChangedEventArguments* transformArguments = new TransformChangedEventArguments();
    transformArguments->Location = m_location.get();
    transformArguments->Scale = m_scale.get();
    transformArguments->Rotation = m_rotation.get();

    m_onLocationChanged->Invoke(transformArguments);
}

void Transform::SetScale(const float xy)
{
    m_scale->SetXYValue(xy, xy);
}

void Transform::SetScale(const float x, const float y)
{
    m_scale->SetXYValue(x, y);
}

void Transform::SetScale(const FVector2D& value)
{
    m_scale->SetXYValue(value.GetX(), value.GetY());
}

const FVector2D* Transform::GetScale() const
{
    return m_scale.get();
}

void Transform::SetRotation(const float xy)
{
    m_rotation->SetXYValue(xy, xy);
}

void Transform::SetRotation(const float x, const float y)
{
    m_rotation->SetXYValue(x, y);
}

void Transform::SetRotation(const FVector2D& value)
{
    m_rotation->SetXYValue(value.GetX(), value.GetY());
}
