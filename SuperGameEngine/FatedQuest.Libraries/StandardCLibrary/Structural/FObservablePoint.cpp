#include "FObservablePoint.h"
#include "FPointLocationEventArguments.h"

using namespace StandardCLibrary;
FObservablePoint::FObservablePoint() : FPoint()
{
    m_onValueChangedEvent = new FEvent();
}

FObservablePoint::FObservablePoint(int x, int y) : FPoint(x, y)
{
    m_onValueChangedEvent = new FEvent();
}

FObservablePoint::~FObservablePoint()
{
    delete m_onValueChangedEvent;
}

void FObservablePoint::SetX(int newValue)
{
    if (newValue != GetX())
    {
        FPoint::SetX(newValue);
        InvokeOnValueChanged();
    }
}

void FObservablePoint::SetY(int newValue)
{
    if (newValue != GetY())
    {
        FPoint::SetY(newValue);
        InvokeOnValueChanged();
    }
}

void FObservablePoint::SetXYValue(int x, int y)
{
    if (x != GetX() || y != GetY())
    {
        FPoint::SetX(x);
        FPoint::SetY(y);
        InvokeOnValueChanged();
    }
}

FEventSubscriptions* FObservablePoint::GetOnValueChanged()
{
    return m_onValueChangedEvent;
}

void FObservablePoint::InvokeOnValueChanged()
{
    FPointLocationEventArguments* arguments = new FPointLocationEventArguments();
    arguments->X = GetX();
    arguments->Y = GetY();
    m_onValueChangedEvent->Invoke(arguments);

    delete arguments;
}
