#include "FVector2F.h"
#include "FVector2I.h"
#include "FVector2D.h"
#include "FPoint.h"
#include "../../StandardOperations/AllReferences.h"
#include <cmath>

using namespace FatedQuestLibraries;

FVector2F::FVector2F()
{
    m_x = 0;
    m_y = 0;
}

FVector2F::FVector2F(float x, float y)
{
    m_x = x;
    m_y = y;
}

FVector2F::FVector2F(const FVector2F& other)
    : FVector2F(other.GetX(), other.GetY())
{
}

FVector2F::FVector2F(const FPoint& other)
    : FVector2F(static_cast<float>(other.GetX()), static_cast<float>(other.GetY()))
{
}

FVector2F::FVector2F(const FVector2D& other)
{
    m_x = static_cast<float>(other.GetX());
    m_y = static_cast<float>(other.GetY());
}

FVector2F::FVector2F(const FVector2I& other)
{
    m_x = static_cast<float>(other.GetX());
    m_y = static_cast<float>(other.GetY());
}

FVector2F::~FVector2F() = default;

float FVector2F::GetX() const
{
    return m_x;
}

float FVector2F::GetY() const
{
    return m_y;
}

void FVector2F::SetX(float newValue)
{
    m_x = newValue;
}

void FVector2F::SetY(float newValue)
{
    m_y = newValue;
}

void FVector2F::SetXYValue(float x, float y)
{
    if (x != m_x || y != m_y)
    {
        m_x = x;
        m_y = y;
    }
}

void FVector2F::SetXYValue(const FVector2F& other)
{
    SetXYValue(other.GetX(), other.GetY());
}

void FVector2F::SetXYValue(const FPoint& other)
{
    SetXYValue((float)other.GetX(), (float)other.GetY());
}

FVector2F FVector2F::operator+(const FVector2F& other) const
{
    return { m_x + other.m_x, m_y + other.m_y };
}

FVector2F& FVector2F::operator+=(const FVector2F& other)
{
    m_x += other.m_x;
    m_y += other.m_y;
    return *this;
}

FVector2F FVector2F::operator-(const FVector2F& other) const
{
    return { m_x - other.m_x, m_y - other.m_y };
}

FVector2F& FVector2F::operator-=(const FVector2F& other)
{
    m_x -= other.m_x;
    m_y -= other.m_y;
    return *this;
}

FVector2F FVector2F::operator*(float scalar) const
{
    return { m_x * scalar, m_y * scalar };
}

FVector2F& FVector2F::operator*=(float scalar)
{
    m_x *= scalar;
    m_y *= scalar;
    return *this;
}

FVector2F FVector2F::operator/(float scalar) const
{
    return { m_x / scalar, m_y / scalar };
}

FVector2F& FVector2F::operator/=(float scalar)
{
    m_x /= scalar;
    m_y /= scalar;
    return *this;
}

bool FVector2F::operator==(const FVector2F& other) const
{
    return
        FloatingPointHelpers::AreEqual(m_x, other.m_x) &&
        FloatingPointHelpers::AreEqual(m_y, other.m_y);
}

FVector2F FVector2F::Normalize() const
{
    float magnitude = Magnitude();
    if (magnitude != 0)
    {
        return *this / magnitude;
    }
    else
    {
        return { 0, 0 };
    }
}

float FVector2F::Magnitude() const
{
    // We should add Inverse Square Root version
    // Using Newton's approximation method here
    // Square Root is not exactly performant and we
    // likely do not need an exact value.
    // TODO: [#32] Change Magnitude which does not use Square Root
    return (float)std::sqrt(m_x * m_x + m_y * m_y);
}

float FVector2F::DotProduct(const FVector2F& other) const
{
    return m_x * other.m_x + m_y * other.m_y;
}

float FVector2F::DistanceBetween(const FVector2F& other) const
{
    return (float)std::sqrt(static_cast<float>(std::pow(other.m_x - m_x, 2))
        + static_cast<float>(std::pow(other.m_y - m_y, 2)));
}

const std::string FVector2F::Print() const
{
    std::stringstream ss;
    ss << "X: " << std::to_string(m_x) << " Y: " << std::to_string(m_y);
    return ss.str();
}