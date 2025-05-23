#include "FVector2I.h"

#include "FVector2D.h"
#include "FVector2I.h"
#include "FVector2F.h"
#include "FPoint.h"
#include "../../StandardOperations/AllReferences.h"
#include <cmath>

using namespace FatedQuestLibraries;

FVector2I::FVector2I()
{
    m_x = 0;
    m_y = 0;
}

FVector2I::FVector2I(int x, int y)
{
    m_x = x;
    m_y = y;
}

FVector2I::FVector2I(const FVector2I& other)
    : FVector2I(other.GetX(), other.GetY())
{
}

FVector2I::FVector2I(const FPoint& other)
    : FVector2I(other.GetX(), other.GetY())
{
}

FVector2I::FVector2I(const FVector2F& other)
{
    m_x = static_cast<int>(other.GetX());
    m_y = static_cast<int>(other.GetY());
}

FVector2I::FVector2I(const FVector2D& other)
{
    m_x = static_cast<int>(other.GetX());
    m_y = static_cast<int>(other.GetY());
}

FVector2I::~FVector2I() = default;

int FVector2I::GetX() const
{
    return m_x;
}

int FVector2I::GetY() const
{
    return m_y;
}

void FVector2I::SetX(int newValue)
{
    m_x = newValue;
}

void FVector2I::SetY(int newValue)
{
    m_y = newValue;
}

void FVector2I::SetXYValue(int x, int y)
{
    if (x != m_x || y != m_y)
    {
        m_x = x;
        m_y = y;
    }
}

void FVector2I::SetXYValue(const FVector2I& other)
{
    SetXYValue(other.GetX(), other.GetY());
}

void FVector2I::SetXYValue(const FPoint& other)
{
    SetXYValue(other.GetX(), other.GetY());
}

FVector2I FVector2I::operator+(const FVector2I& other) const
{
    return { m_x + other.GetX(), m_y + other.GetY() };
}

FVector2I& FVector2I::operator+=(const FVector2I& other)
{
    m_x += other.m_x;
    m_y += other.m_y;
    return *this;
}

FVector2I FVector2I::operator-(const FVector2I& other) const
{
    return { m_x - other.m_x, m_y - other.m_y };
}

FVector2I& FVector2I::operator-=(const FVector2I& other)
{
    m_x -= other.m_x;
    m_y -= other.m_y;
    return *this;
}

FVector2I FVector2I::operator*(int scalar) const
{
    return { m_x * scalar, m_y * scalar };
}

FVector2I& FVector2I::operator*=(int scalar)
{
    m_x *= scalar;
    m_y *= scalar;
    return *this;
}

FVector2I FVector2I::operator/(int scalar) const
{
    return { m_x / scalar, m_y / scalar };
}

FVector2I& FVector2I::operator/=(int scalar)
{
    m_x /= scalar;
    m_y /= scalar;
    return *this;
}

bool FVector2I::operator==(const FVector2I& other) const
{
    return
        GetX() == other.GetX() &&
        GetY() == other.GetY();
}

FVector2I FVector2I::Normalize() const
{
    int magnitude = static_cast<int>(Magnitude());
    if (magnitude != 0)
    {
        return *this / magnitude;
    }
    else
    {
        return { 0, 0 };
    }
}

float FVector2I::Magnitude() const
{
    // We should add Inverse Square Root version
    // Using Newton's approximation method here
    // Square Root is not exactly performant and we
    // likely do not need an exact value.
    // TODO: [#32] Change Magnitude which does not use Square Root
    return static_cast<float>(std::sqrt(m_x * m_x + m_y * m_y));
}

int FVector2I::DotProduct(const FVector2I& other) const
{
    return m_x * other.m_x + m_y * other.m_y;
}

float FVector2I::DistanceBetween(const FVector2I& other) const
{
    return (float)std::sqrt(static_cast<float>(std::pow(other.m_x - m_x, 2))
        + static_cast<float>(std::pow(other.m_y - m_y, 2)));
}

std::string FVector2I::Print() const
{
    std::stringstream ss;
    ss << "X: " << std::to_string(m_x) << " Y: " << std::to_string(m_y);
    return ss.str();
}