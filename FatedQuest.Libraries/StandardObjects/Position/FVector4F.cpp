#include "FVector4F.h"
#include "FVector4I.h"
#include "FVector4D.h"
#include "FPoint.h"
#include "../../StandardOperations/AllReferences.h"
#include <cmath>

using namespace FatedQuestLibraries;

FVector4F::FVector4F()
{
    m_x = 0;
    m_y = 0;
    m_z = 0;
    m_w = 0;
}

FVector4F::FVector4F(float x, float y, float z, float w)
{
    m_x = x;
    m_y = y;
    m_z = z;
    m_w = w;
}

FVector4F::FVector4F(const FVector4F& other)
    : FVector4F(other.GetX(), other.GetY(), other.GetZ(), other.GetW())
{
}

FVector4F::FVector4F(const FPoint& other)
    : FVector4F(static_cast<float>(other.GetX()), static_cast<float>(other.GetY()), 0, 0)
{
}

FVector4F::FVector4F(const FVector4D& other)
{
    m_x = static_cast<float>(other.GetX());
    m_y = static_cast<float>(other.GetY());
    m_z = static_cast<float>(other.GetZ());
    m_w = static_cast<float>(other.GetW());
}

FVector4F::FVector4F(const FVector4I& other)
{
    m_x = static_cast<float>(other.GetX());
    m_y = static_cast<float>(other.GetY());
    m_z = static_cast<float>(other.GetZ());
    m_w = static_cast<float>(other.GetW());
}

FVector4F::~FVector4F() = default;

float FVector4F::GetX() const
{
    return m_x;
}

float FVector4F::GetY() const
{
    return m_y;
}

float FVector4F::GetZ() const
{
    return m_z;
}

float FVector4F::GetW() const
{
    return m_w;
}

void FVector4F::SetX(float newValue)
{
    m_x = newValue;
}

void FVector4F::SetY(float newValue)
{
    m_y = newValue;
}

void FVector4F::SetZ(float newValue)
{
    m_z = newValue;
}

void FVector4F::SetW(float newValue)
{
    m_w = newValue;
}

void FVector4F::SetXYValue(float x, float y)
{
    if (x != m_x || y != m_y)
    {
        m_x = x;
        m_y = y;
    }
}

void FVector4F::SetXYZValue(float x, float y, float z)
{
    if (x != m_x || y != m_y || z != m_z)
    {
        m_x = x;
        m_y = y;
        m_z = z;
    }
}

void FVector4F::SetXYZWValue(float x, float y, float z, float w)
{
    if (x != m_x || y != m_y || z != m_z || w != m_w)
    {
        m_x = x;
        m_y = y;
        m_z = z;
        m_w = w;
    }
}

void FVector4F::SetValue(const FVector4F& other)
{
    SetXYZWValue(other.GetX(), other.GetY(), other.GetZ(), other.GetW());
}

void FVector4F::SetXYValue(const FPoint& other)
{
    SetXYValue(static_cast<float>(other.GetX()), static_cast<float>(other.GetY()));
}

FVector4F FVector4F::operator+(const FVector4F& other) const
{
    return { m_x + other.m_x, m_y + other.m_y, m_z + other.m_z, m_w + other.m_w };
}

FVector4F& FVector4F::operator+=(const FVector4F& other)
{
    m_x += other.m_x;
    m_y += other.m_y;
    m_z += other.m_z;
    m_w += other.m_w;
    return *this;
}

FVector4F FVector4F::operator-(const FVector4F& other) const
{
    return { m_x - other.m_x, m_y - other.m_y, m_z - other.m_z, m_w - other.m_w };
}

FVector4F& FVector4F::operator-=(const FVector4F& other)
{
    m_x -= other.m_x;
    m_y -= other.m_y;
    m_z -= other.m_z;
    m_w -= other.m_w;
    return *this;
}

FVector4F FVector4F::operator*(float scalar) const
{
    return { m_x * scalar, m_y * scalar, m_z * scalar, m_w * scalar };
}

FVector4F& FVector4F::operator*=(float scalar)
{
    m_x *= scalar;
    m_y *= scalar;
    m_z *= scalar;
    m_w *= scalar;
    return *this;
}

FVector4F FVector4F::operator/(float scalar) const
{
    return { m_x / scalar, m_y / scalar, m_z / scalar, m_w / scalar };
}

FVector4F& FVector4F::operator/=(float scalar)
{
    m_x /= scalar;
    m_y /= scalar;
    m_z /= scalar;
    m_w /= scalar;
    return *this;
}

bool FVector4F::operator==(const FVector4F& other) const
{
    return
        FloatingPointHelpers::AreEqual(m_x, other.m_x) &&
        FloatingPointHelpers::AreEqual(m_y, other.m_y) &&
        FloatingPointHelpers::AreEqual(m_z, other.m_z) &&
        FloatingPointHelpers::AreEqual(m_w, other.m_w);
}

FVector4F FVector4F::Normalize() const
{
    double magnitude = Magnitude();
    if (magnitude != 0)
    {
        return *this / magnitude;
    }
    else
    {
        return { 0, 0, 0, 0 };
    }
}

float FVector4F::Magnitude() const
{
    // We should add Inverse Square Root version
    // Using Newton's approximation method here
    // Square Root is not exactly performant and we
    // likely do not need an exact value.
    // TODO: [#32] Change Magnitude which does not use Square Root
    return std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w);
}

float FVector4F::DotProduct(const FVector4F& other) const
{
    return m_x * other.m_x + m_y * other.m_y + m_z * other.m_z + m_w * other.m_w;
}

float FVector4F::DistanceBetween(const FVector4F& other) const
{
    return std::sqrt((std::pow(other.m_x - m_x, 2))
        + (std::pow(other.m_y - m_y, 2))
        + (std::pow(other.m_z - m_z, 2))
        + (std::pow(other.m_w - m_w, 2)));
}

std::string FVector4F::Print() const
{
    std::stringstream ss;
    ss << "X: " << std::to_string(m_x)
        << " Y: " << std::to_string(m_y)
        << " Z: " << std::to_string(m_z)
        << " W: " << std::to_string(m_w);
    return ss.str();
}