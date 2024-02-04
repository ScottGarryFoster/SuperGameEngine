#include "FPoint.h"

using namespace StandardCLibrary;

FPoint::FPoint()
{
    m_x = 0;
    m_y = 0;
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

const FString FPoint::Print() const
{
    return FString(FString("X: ") + m_x + FString(" Y:") + m_y);
}