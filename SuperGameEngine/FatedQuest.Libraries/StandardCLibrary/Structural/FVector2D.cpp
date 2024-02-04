#include "FVector2D.h"

using namespace StandardCLibrary;

FVector2D::FVector2D()
{
    m_x = 0;
    m_y = 0;
}

FVector2D::~FVector2D()
{

}

const float FVector2D::GetX() const
{
    return m_x;
}

const float FVector2D::GetY() const
{
    return m_y;
}

const FString FVector2D::Print() const
{
    return FString(FString("X: ") + m_x + FString(" Y:") + m_y);
}