#include "FVector2D.h"
#include "FVectorLocationEventArguments.h"

using namespace StandardCLibrary;

FVector2D::FVector2D()
{
    m_x = 0;
    m_y = 0;

    //m_onValueChangedEvent = new FEvent();
}

FVector2D::~FVector2D()
{
    //delete m_onValueChangedEvent;
}

const float FVector2D::GetX() const
{
    return m_x;
}

const float FVector2D::GetY() const
{
    return m_y;
}

void FVector2D::SetX(float newValue)
{
    if (newValue != m_x)
    {
        m_x = newValue;
        //InvokeOnValueChanged();
    }
}

void FVector2D::SetY(float newValue)
{
    if (newValue != m_y)
    {
        m_y = newValue;
        //InvokeOnValueChanged();
    }
}

void FVector2D::SetXYValue(float x, float y)
{
    if (x != m_y || y != m_y)
    {
        m_x = x;
        m_y = y;
        //InvokeOnValueChanged();
    }
}

const FString FVector2D::Print() const
{
    return FString(FString("X: ") + m_x + FString(" Y:") + m_y);
}

//FEventSubscriptions* FVector2D::GetOnValueChanged()
//{
//    return m_onValueChangedEvent;
//}
//
//void FVector2D::InvokeOnValueChanged()
//{
//    FVectorLocationEventArguments* arguments = new FVectorLocationEventArguments();
//    arguments->X = m_x;
//    arguments->Y = m_y;
//    m_onValueChangedEvent->Invoke(arguments);
//
//    delete arguments;
//}