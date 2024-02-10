#include "FPoint.h"
#include "FPointLocationEventArguments.h"

using namespace StandardCLibrary;

FPoint::FPoint()
{
    m_x = 0;
    m_y = 0;
    m_onValueChangedEvent = new FEvent();
}

StandardCLibrary::FPoint::FPoint(int x, int y)
{
    m_x = x;
    m_y = y;
    m_onValueChangedEvent = new FEvent();
}

FPoint::~FPoint()
{
    delete m_onValueChangedEvent;
}

const int FPoint::GetX() const
{
    return m_x;
}

const int FPoint::GetY() const
{
    return m_y;
}

void FPoint::SetX(int newValue)
{
    if (newValue != m_x)
    {
        m_x = newValue;
        InvokeOnValueChanged();
    }
}

void FPoint::SetY(int newValue)
{
    if (newValue != m_y)
    {
        m_y = newValue;
        InvokeOnValueChanged();
    }
}

void FPoint::SetXYValue(int x, int y)
{
    if (x != m_y || y != m_y)
    {
        m_x = x;
        m_y = y;
        InvokeOnValueChanged();
    }
}

const FString FPoint::Print() const
{
    return FString(FString("X: ") + m_x + FString(" Y:") + m_y);
}

FEventSubscriptions* StandardCLibrary::FPoint::GetOnValueChanged()
{
    return m_onValueChangedEvent;
}

void FPoint::InvokeOnValueChanged()
{
    FPointLocationEventArguments* arguments = new FPointLocationEventArguments();
    arguments->X = m_x;
    arguments->Y = m_y;
    m_onValueChangedEvent->Invoke(arguments);

    delete arguments;
}