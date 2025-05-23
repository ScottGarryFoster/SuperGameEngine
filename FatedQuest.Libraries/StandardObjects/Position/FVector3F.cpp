#include "FVector3F.h"
#include "FVector3D.h"
#include "FVector3I.h"
#include "FPoint.h"
#include "../../StandardOperations/AllReferences.h"
#include <cmath>

using namespace FatedQuestLibraries;

FVector3F::FVector3F()
{
    m_x = 0;
    m_y = 0;
    m_z = 0;
}

FVector3F::FVector3F(float x, float y, float z)
{
    m_x = x;
    m_y = y;
    m_z = z;
}

FVector3F::FVector3F(const FVector3F& other)
    : FVector3F(other.GetX(), other.GetY(), other.GetZ())
{
}

FVector3F::FVector3F(const FPoint& other)
    : FVector3F(static_cast<float>(other.GetX()), static_cast<float>(other.GetY()), 0)
{
}

FVector3F::FVector3F(const FVector3D& other)
{
    m_x = static_cast<float>(other.GetX());
    m_y = static_cast<float>(other.GetY());
    m_z = static_cast<float>(other.GetZ());
}

FVector3F::FVector3F(const FVector3I& other)
{
    m_x = static_cast<float>(other.GetX());
    m_y = static_cast<float>(other.GetY());
    m_z = static_cast<float>(other.GetZ());
}

FVector3F::~FVector3F() = default;

float FVector3F::GetX() const
{
    return m_x;
}

float FVector3F::GetY() const
{
    return m_y;
}

float FVector3F::GetZ() const
{
    return m_z;
}

void FVector3F::SetX(float newValue)
{
    m_x = newValue;
}

void FVector3F::SetY(float newValue)
{
    m_y = newValue;
}

void FVector3F::SetZ(float newValue)
{
    m_z = newValue;
}

void FVector3F::SetXYValue(float x, float y)
{
    if (x != m_x || y != m_y)
    {
        m_x = x;
        m_y = y;
    }
}

void FVector3F::SetXYValue(float x, float y, float z)
{
    if (x != m_x || y != m_y || z != m_z)
    {
        m_x = x;
        m_y = y;
        m_z = z;
    }
}

void FVector3F::SetXYValue(const FVector3F& other)
{
    SetXYValue(other.GetX(), other.GetY());
}

void FVector3F::SetXYValue(const FPoint& other)
{
    SetXYValue((float)other.GetX(), (float)other.GetY());
}

FVector3F FVector3F::operator+(const FVector3F& other) const
{
    return { m_x + other.m_x, m_y + other.m_y, m_z + other.m_z };
}

FVector3F& FVector3F::operator+=(const FVector3F& other)
{
    m_x += other.m_x;
    m_y += other.m_y;
    m_z += other.m_z;
    return *this;
}

FVector3F FVector3F::operator-(const FVector3F& other) const
{
    return { m_x - other.m_x, m_y - other.m_y, m_z - other.m_z };
}

FVector3F& FVector3F::operator-=(const FVector3F& other)
{
    m_x -= other.m_x;
    m_y -= other.m_y;
    m_z -= other.m_z;
    return *this;
}

FVector3F FVector3F::operator*(float scalar) const
{
    return { m_x * scalar, m_y * scalar, m_z * scalar };
}

FVector3F& FVector3F::operator*=(float scalar)
{
    m_x *= scalar;
    m_y *= scalar;
    m_z *= scalar;
    return *this;
}

FVector3F FVector3F::operator/(float scalar) const
{
    return { m_x / scalar, m_y / scalar, m_z / scalar };
}

FVector3F& FVector3F::operator/=(float scalar)
{
    m_x /= scalar;
    m_y /= scalar;
    m_z /= scalar;
    return *this;
}

bool FVector3F::operator==(const FVector3F& other) const
{
    return
        FloatingPointHelpers::AreEqual(m_x, other.m_x) &&
        FloatingPointHelpers::AreEqual(m_y, other.m_y) &&
        FloatingPointHelpers::AreEqual(m_z, other.m_z);
}

FVector3F FVector3F::Normalize() const
{
    float magnitude = Magnitude();
    if (magnitude != 0)
    {
        return *this / magnitude;
    }
    else
    {
        return { 0, 0, 0 };
    }
}

float FVector3F::Magnitude() const
{
    // We should add Inverse Square Root version
    // Using Newton's approximation method here
    // Square Root is not exactly performant and we
    // likely do not need an exact value.
    // TODO: [#32] Change Magnitude which does not use Square Root
    return std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
}

float FVector3F::DotProduct(const FVector3F& other) const
{
    return m_x * other.m_x + m_y * other.m_y + m_z * other.m_z;
}

float FVector3F::DistanceBetween(const FVector3F& other) const
{
    return (float)std::sqrt(static_cast<float>(std::pow(other.m_x - m_x, 2))
        + static_cast<float>(std::pow(other.m_y - m_y, 2))
        + static_cast<float>(std::pow(other.m_z - m_z, 2)));
}

std::string FVector3F::Print() const
{
    std::stringstream ss;
    ss << "X: " << std::to_string(m_x) << " Y: " << std::to_string(m_y) << " Z: " << std::to_string(m_z);
    return ss.str();
}