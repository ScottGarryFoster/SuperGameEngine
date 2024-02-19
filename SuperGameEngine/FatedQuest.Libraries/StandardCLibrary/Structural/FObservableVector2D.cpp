#include "FObservableVector2D.h"
#include "FVectorLocationEventArguments.h"

using namespace StandardCLibrary;
FObservableVector2D::FObservableVector2D()
{
    m_onValueChangedEvent = new FEvent();
}

FObservableVector2D::~FObservableVector2D()
{
    delete m_onValueChangedEvent;
}

void FObservableVector2D::SetX(float newValue)
{
    if (newValue != GetX())
    {
        FVector2D::SetX(newValue);
        InvokeOnValueChanged();
    }
}

void FObservableVector2D::SetY(float newValue)
{
    if (newValue != GetY())
    {
        FVector2D::SetY(newValue);
        InvokeOnValueChanged();
    }
}

void FObservableVector2D::SetXYValue(float x, float y)
{
    if (x != GetX() || y != GetY())
    {
        FVector2D::SetX(x);
        FVector2D::SetY(y);
        InvokeOnValueChanged();
    }
}

FEventSubscriptions* FObservableVector2D::GetOnValueChanged()
{
    return m_onValueChangedEvent;
}

void FObservableVector2D::InvokeOnValueChanged()
{
    FVectorLocationEventArguments* arguments = new FVectorLocationEventArguments();
    arguments->X = GetX();
    arguments->Y = GetY();
    m_onValueChangedEvent->Invoke(arguments);

    delete arguments;
}