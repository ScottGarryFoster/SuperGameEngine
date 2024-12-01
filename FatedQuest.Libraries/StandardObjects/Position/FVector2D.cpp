#include "FVector2D.h"
#include "FPoint.h"
#include "../../StandardOperations/AllReferences.h"
#include <cmath>

using namespace FatedQuestLibraries;

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

FVector2D::FVector2D(const FVector2D& other)
    : FVector2D(other.GetX(), other.GetY())
{
}

FVector2D::FVector2D(const FPoint& other)
    : FVector2D(static_cast<float>(other.GetX()), static_cast<float>(other.GetY()))
{
}

FVector2D::~FVector2D() = default;

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

void FVector2D::SetXYValue(const FVector2D& other)
{
    SetXYValue(other.GetX(), other.GetY());
}

void FVector2D::SetXYValue(const FPoint& other)
{
    SetXYValue((float)other.GetX(), (float)other.GetY());
}

FVector2D FVector2D::operator+(const FVector2D& other) const
{
    return {m_x + other.m_x, m_y + other.m_y};
}

FVector2D& FVector2D::operator+=(const FVector2D& other)
{
    m_x += other.m_x;
    m_y += other.m_y;
    return *this;
}

FVector2D FVector2D::operator-(const FVector2D& other) const
{
    return {m_x - other.m_x, m_y - other.m_y};
}

FVector2D& FVector2D::operator-=(const FVector2D& other)
{
    m_x -= other.m_x;
    m_y -= other.m_y;
    return *this;
}

FVector2D FVector2D::operator*(float scalar) const
{
    return {m_x * scalar, m_y * scalar};
}

FVector2D& FVector2D::operator*=(float scalar)
{
    m_x *= scalar;
    m_y *= scalar;
    return *this;
}

FVector2D FVector2D::operator/(float scalar) const
{
    return {m_x / scalar, m_y / scalar};
}

FVector2D& FVector2D::operator/=(float scalar)
{
    m_x /= scalar;
    m_y /= scalar;
    return *this;
}

bool FVector2D::operator==(const FVector2D& other) const
{
    return
        FloatingPointHelpers::AreEqual(m_x, other.m_x) &&
        FloatingPointHelpers::AreEqual(m_y, other.m_y);
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
        return {0, 0};
    }
}

float FVector2D::Magnitude() const
{
    // We should add Inverse Square Root version
    // Using Newton's approximation method here
    // Square Root is not exactly performant and we
    // likely do not need an exact value.
    // TODO: [#32] Change Magnitude which does not use Square Root
    return (float)std::sqrt(m_x * m_x + m_y * m_y);
}

float FVector2D::DotProduct(const FVector2D& other) const
{
    return m_x * other.m_x + m_y * other.m_y;
}

float FVector2D::DistanceBetween(const FVector2D& other) const
{
    return (float)std::sqrt(static_cast<float>(std::pow(other.m_x - m_x, 2))
        + static_cast<float>(std::pow(other.m_y - m_y, 2)));
}

const std::string FVector2D::Print() const
{
    std::stringstream ss;
    ss << "X: " << std::to_string(m_x) << " Y: " << std::to_string(m_y);
    return ss.str();
}