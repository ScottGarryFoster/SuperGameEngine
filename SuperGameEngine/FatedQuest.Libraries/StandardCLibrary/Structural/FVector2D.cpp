#include "FVector2D.h"
#include <cmath>

using namespace StandardCLibrary;

FVector2D::FVector2D()
{
    m_x = 0;
    m_y = 0;
}

FVector2D::FVector2D(float x, float y)
{
    m_x = x;
    m_y = y;
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

void FVector2D::SetX(float newValue)
{
    m_x = newValue;
}

void FVector2D::SetY(float newValue)
{
    m_y = newValue;
}

void FVector2D::SetXYValue(float x, float y)
{
    if (x != m_x || y != m_y)
    {
        m_x = x;
        m_y = y;
    }
}

FVector2D FVector2D::operator+(const FVector2D& other) const
{
    return FVector2D(m_x + other.m_x, m_y + other.m_y);
}

FVector2D FVector2D::operator-(const FVector2D& other) const
{
    return FVector2D(m_x - other.m_x, m_y - other.m_y);
}

FVector2D FVector2D::operator*(float scalar) const
{
    return FVector2D(m_x * scalar, m_y * scalar);
}

FVector2D FVector2D::operator/(float scalar) const
{
    return FVector2D(m_x / scalar, m_y / scalar);
}

bool FVector2D::operator==(const FVector2D& other) const
{
    // The places to be accurate within.
    float epsilon = 0.00001f;

    return 
        std::abs(m_x - other.m_x) < epsilon &&
        std::abs(m_y - other.m_y) < epsilon;
}

FVector2D FVector2D::Normalize() const
{
    float magnitude = Magnitude();
    if (magnitude != 0)
    {
        return *this / magnitude;
    }
    else
    {
        return FVector2D(0, 0);
    }
}

float FVector2D::Magnitude() const
{
    // We should add Inverse Square Root version
    // Using Newton's approximation method here
    // Square Root is not exactly performant and we
    // likely do not need an exact value.
    // TODO: [#32] Change Magnitude which does not use Square Root
    return std::sqrt(m_x * m_x + m_y * m_y);
}

float FVector2D::DotProduct(const FVector2D& other) const
{
    return m_x * other.m_x + m_y * other.m_y;
}

float FVector2D::DistanceBetween(const FVector2D& other) const
{
    return sqrt(pow(other.m_x - m_x, 2) + pow(other.m_y - m_y, 2));
}

const FString FVector2D::Print() const
{
    return FString(FString("X: ") + m_x + FString(" Y:") + m_y);
}