#include "FVector2Int.h"

#include "FVector2D.h"
#include "FPoint.h"
#include "../../StandardOperations/AllReferences.h"
#include <cmath>

using namespace FatedQuestLibraries;

FVector2Int::FVector2Int()
{
    m_x = 0;
    m_y = 0;
}

FVector2Int::FVector2Int(int x, int y)
{
    m_x = x;
    m_y = y;
}

FVector2Int::FVector2Int(const FVector2Int& other)
    : FVector2Int(other.GetX(), other.GetY())
{
}

FVector2Int::FVector2Int(const FPoint& other)
    : FVector2Int(other.GetX(), other.GetY())
{
}

FVector2Int::~FVector2Int() = default;

int FVector2Int::GetX() const
{
    return m_x;
}

int FVector2Int::GetY() const
{
    return m_y;
}

void FVector2Int::SetX(int newValue)
{
    m_x = newValue;
}

void FVector2Int::SetY(int newValue)
{
    m_y = newValue;
}

void FVector2Int::SetXYValue(int x, int y)
{
    if (x != m_x || y != m_y)
    {
        m_x = x;
        m_y = y;
    }
}

void FVector2Int::SetXYValue(const FVector2Int& other)
{
    SetXYValue(other.GetX(), other.GetY());
}

void FVector2Int::SetXYValue(const FPoint& other)
{
    SetXYValue(other.GetX(), other.GetY());
}

FVector2Int FVector2Int::operator+(const FVector2Int& other) const
{
    return { m_x + other.GetX(), m_y + other.GetY() };
}

FVector2Int& FVector2Int::operator+=(const FVector2Int& other)
{
    m_x += other.m_x;
    m_y += other.m_y;
    return *this;
}

FVector2Int FVector2Int::operator-(const FVector2Int& other) const
{
    return { m_x - other.m_x, m_y - other.m_y };
}

FVector2Int& FVector2Int::operator-=(const FVector2Int& other)
{
    m_x -= other.m_x;
    m_y -= other.m_y;
    return *this;
}

FVector2Int FVector2Int::operator*(int scalar) const
{
    return { m_x * scalar, m_y * scalar };
}

FVector2Int& FVector2Int::operator*=(int scalar)
{
    m_x *= scalar;
    m_y *= scalar;
    return *this;
}

FVector2Int FVector2Int::operator/(int scalar) const
{
    return { m_x / scalar, m_y / scalar };
}

FVector2Int& FVector2Int::operator/=(int scalar)
{
    m_x /= scalar;
    m_y /= scalar;
    return *this;
}

bool FVector2Int::operator==(const FVector2Int& other) const
{
    return
        GetX() == other.GetX() &&
        GetY() == other.GetY();
}

FVector2Int FVector2Int::Normalize() const
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

float FVector2Int::Magnitude() const
{
    // We should add Inverse Square Root version
    // Using Newton's approximation method here
    // Square Root is not exactly performant and we
    // likely do not need an exact value.
    // TODO: [#32] Change Magnitude which does not use Square Root
    return static_cast<float>(std::sqrt(m_x * m_x + m_y * m_y));
}

int FVector2Int::DotProduct(const FVector2Int& other) const
{
    return m_x * other.m_x + m_y * other.m_y;
}

float FVector2Int::DistanceBetween(const FVector2Int& other) const
{
    return (float)std::sqrt(static_cast<float>(std::pow(other.m_x - m_x, 2))
        + static_cast<float>(std::pow(other.m_y - m_y, 2)));
}

std::string FVector2Int::Print() const
{
    std::stringstream ss;
    ss << "X: " << std::to_string(m_x) << " Y: " << std::to_string(m_y);
    return ss.str();
}