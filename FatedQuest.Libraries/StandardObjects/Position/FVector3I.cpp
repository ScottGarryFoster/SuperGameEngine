#include "FVector3I.h"
#include "FVector3D.h"
#include "FVector3F.h"
#include "FPoint.h"
#include "../../StandardOperations/AllReferences.h"
#include <cmath>

using namespace FatedQuestLibraries;

FVector3I::FVector3I()
{
    m_x = 0;
    m_y = 0;
    m_z = 0;
}

FVector3I::FVector3I(int x, int y, int z)
{
    m_x = x;
    m_y = y;
    m_z = z;
}

FVector3I::FVector3I(const FVector3I& other)
    : FVector3I(other.GetX(), other.GetY(), other.GetZ())
{
}

FVector3I::FVector3I(const FPoint& other)
    : FVector3I(static_cast<int>(other.GetX()), static_cast<int>(other.GetY()), 0)
{
}

FVector3I::FVector3I(const FVector3F& other)
{
    m_x = static_cast<int>(other.GetX());
    m_y = static_cast<int>(other.GetY());
    m_z = static_cast<int>(other.GetZ());
}

FVector3I::FVector3I(const FVector3D& other)
{
    m_x = static_cast<int>(other.GetX());
    m_y = static_cast<int>(other.GetY());
    m_z = static_cast<int>(other.GetZ());
}

FVector3I::~FVector3I() = default;

int FVector3I::GetX() const
{
    return m_x;
}

int FVector3I::GetY() const
{
    return m_y;
}

int FVector3I::GetZ() const
{
    return m_z;
}

void FVector3I::SetX(int newValue)
{
    m_x = newValue;
}

void FVector3I::SetY(int newValue)
{
    m_y = newValue;
}

void FVector3I::SetZ(int newValue)
{
    m_z = newValue;
}

void FVector3I::SetXYValue(int x, int y)
{
    if (x != m_x || y != m_y)
    {
        m_x = x;
        m_y = y;
    }
}

void FVector3I::SetXYZValue(int x, int y, int z)
{
    if (x != m_x || y != m_y || z != m_z)
    {
        m_x = x;
        m_y = y;
        m_z = z;
    }
}

void FVector3I::SetXYValue(const FVector3I& other)
{
    SetXYValue(other.GetX(), other.GetY());
}

void FVector3I::SetXYValue(const FPoint& other)
{
    SetXYValue((int)other.GetX(), (int)other.GetY());
}

FVector3I FVector3I::operator+(const FVector3I& other) const
{
    return { m_x + other.m_x, m_y + other.m_y, m_z + other.m_z };
}

FVector3I& FVector3I::operator+=(const FVector3I& other)
{
    m_x += other.m_x;
    m_y += other.m_y;
    m_z += other.m_z;
    return *this;
}

FVector3I FVector3I::operator-(const FVector3I& other) const
{
    return { m_x - other.m_x, m_y - other.m_y, m_z - other.m_z };
}

FVector3I& FVector3I::operator-=(const FVector3I& other)
{
    m_x -= other.m_x;
    m_y -= other.m_y;
    m_z -= other.m_z;
    return *this;
}

FVector3I FVector3I::operator*(int scalar) const
{
    return { m_x * scalar, m_y * scalar, m_z * scalar };
}

FVector3I& FVector3I::operator*=(int scalar)
{
    m_x *= scalar;
    m_y *= scalar;
    m_z *= scalar;
    return *this;
}

FVector3I FVector3I::operator/(int scalar) const
{
    return { m_x / scalar, m_y / scalar, m_z / scalar };
}

FVector3I& FVector3I::operator/=(int scalar)
{
    m_x /= scalar;
    m_y /= scalar;
    m_z /= scalar;
    return *this;
}

bool FVector3I::operator==(const FVector3I& other) const
{
    return m_x == other.m_x &&
            m_y == other.m_y &&
            m_z == other.m_z;
}

FVector3I FVector3I::Normalize() const
{
    int magnitude = Magnitude();
    if (magnitude != 0)
    {
        return *this / magnitude;
    }
    else
    {
        return { 0, 0, 0 };
    }
}

float FVector3I::Magnitude() const
{
    // We should add Inverse Square Root version
    // Using Newton's approximation method here
    // Square Root is not exactly performant and we
    // likely do not need an exact value.
    // TODO: [#32] Change Magnitude which does not use Square Root
    return static_cast<float>(std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z));
}

int FVector3I::DotProduct(const FVector3I& other) const
{
    return m_x * other.m_x + m_y * other.m_y + m_z * other.m_z;
}

float FVector3I::DistanceBetween(const FVector3I& other) const
{
    return std::sqrt(static_cast<float>(std::pow(other.m_x - m_x, 2))
        + static_cast<float>(std::pow(other.m_y - m_y, 2))
        + static_cast<float>(std::pow(other.m_z - m_z, 2)));
}

std::string FVector3I::Print() const
{
    std::stringstream ss;
    ss << "X: " << std::to_string(m_x) << " Y: " << std::to_string(m_y) << " Z: " << std::to_string(m_z);
    return ss.str();
}