#include "FPoint.h"
#include "FPointLocationEventArguments.h"

using namespace StandardCLibrary;
FPoint::FPoint()
{
    m_x = 0;
    m_y = 0;
}

StandardCLibrary::FPoint::FPoint(int x, int y)
{
    m_x = x;
    m_y = y;
}

FPoint::~FPoint()
{
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
    }
}

void FPoint::SetY(int newValue)
{
    if (newValue != m_y)
    {
        m_y = newValue;
    }
}

void FPoint::SetXYValue(int x, int y)
{
    if (x != m_y || y != m_y)
    {
        m_x = x;
        m_y = y;
    }
}

const FString FPoint::Print() const
{
    return FString(FString("X: ") + m_x + FString(" Y:") + m_y);
}