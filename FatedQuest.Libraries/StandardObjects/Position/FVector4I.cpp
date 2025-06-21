#include "FVector4I.h"
#include "FVector4D.h"
#include "FVector4F.h"
#include "FPoint.h"
#include "../../StandardOperations/AllReferences.h"
#include <cmath>

using namespace FatedQuestLibraries;

FVector4I::FVector4I()
{
    m_x = 0;
    m_y = 0;
    m_z = 0;
    m_w = 0;
}

FVector4I::FVector4I(int x, int y, int z, int w)
{
    m_x = x;
    m_y = y;
    m_z = z;
    m_w = w;
}

FVector4I::FVector4I(const FVector4I& other)
    : FVector4I(other.GetX(), other.GetY(), other.GetZ(), other.GetW())
{
}

FVector4I::FVector4I(const FPoint& other)
    : FVector4I(other.GetX(), other.GetY(), 0, 0)
{
}

FVector4I::FVector4I(const FVector4F& other)
{
    m_x = static_cast<int>(other.GetX());
    m_y = static_cast<int>(other.GetY());
    m_z = static_cast<int>(other.GetZ());
    m_w = static_cast<int>(other.GetW());
}

FVector4I::FVector4I(const FVector4D& other)
{
    m_x = static_cast<int>(other.GetX());
    m_y = static_cast<int>(other.GetY());
    m_z = static_cast<int>(other.GetZ());
    m_w = static_cast<int>(other.GetW());
}

FVector4I::~FVector4I() = default;

int FVector4I::GetX() const
{
    return m_x;
}

int FVector4I::GetY() const
{
    return m_y;
}

int FVector4I::GetZ() const
{
    return m_z;
}

int FVector4I::GetW() const
{
    return m_w;
}

void FVector4I::SetX(int newValue)
{
    m_x = newValue;
}

void FVector4I::SetY(int newValue)
{
    m_y = newValue;
}

void FVector4I::SetZ(int newValue)
{
    m_z = newValue;
}

void FVector4I::SetW(int newValue)
{
    m_w = newValue;
}

void FVector4I::SetXYValue(int x, int y)
{
    if (x != m_x || y != m_y)
    {
        m_x = x;
        m_y = y;
    }
}

void FVector4I::SetXYZValue(int x, int y, int z)
{
    if (x != m_x || y != m_y || z != m_z)
    {
        m_x = x;
        m_y = y;
        m_z = z;
    }
}

void FVector4I::SetXYZWValue(int x, int y, int z, int w)
{
    if (x != m_x || y != m_y || z != m_z || w != m_w)
    {
        m_x = x;
        m_y = y;
        m_z = z;
        m_w = w;
    }
}

void FVector4I::SetValue(const FVector4I& other)
{
    SetXYZWValue(other.GetX(), other.GetY(), other.GetZ(), other.GetW());
}

void FVector4I::SetXYValue(const FPoint& other)
{
    SetXYValue(other.GetX(), other.GetY());
}

FVector4I FVector4I::operator+(const FVector4I& other) const
{
    return { m_x + other.m_x, m_y + other.m_y, m_z + other.m_z, m_w + other.m_w };
}

FVector4I& FVector4I::operator+=(const FVector4I& other)
{
    m_x += other.m_x;
    m_y += other.m_y;
    m_z += other.m_z;
    m_w += other.m_w;
    return *this;
}

FVector4I FVector4I::operator-(const FVector4I& other) const
{
    return { m_x - other.m_x, m_y - other.m_y, m_z - other.m_z, m_w - other.m_w };
}

FVector4I& FVector4I::operator-=(const FVector4I& other)
{
    m_x -= other.m_x;
    m_y -= other.m_y;
    m_z -= other.m_z;
    m_w -= other.m_w;
    return *this;
}

FVector4I FVector4I::operator*(int scalar) const
{
    return { m_x * scalar, m_y * scalar, m_z * scalar, m_w * scalar };
}

FVector4I& FVector4I::operator*=(int scalar)
{
    m_x *= scalar;
    m_y *= scalar;
    m_z *= scalar;
    m_w *= scalar;
    return *this;
}

FVector4I FVector4I::operator/(int scalar) const
{
    return { m_x / scalar, m_y / scalar, m_z / scalar, m_w / scalar };
}

FVector4I& FVector4I::operator/=(int scalar)
{
    m_x /= scalar;
    m_y /= scalar;
    m_z /= scalar;
    m_w /= scalar;
    return *this;
}

bool FVector4I::operator==(const FVector4I& other) const
{
    return  m_x == other.m_x &&
            m_y == other.m_y &&
            m_z == other.m_z &&
            m_w == other.m_w;
}

FVector4I FVector4I::Normalize() const
{
    float magnitude = Magnitude();
    if (magnitude != 0)
    {
        return *this / magnitude;
    }
    else
    {
        return { 0, 0, 0, 0 };
    }
}

float FVector4I::Magnitude() const
{
    // We should add Inverse Square Root version
    // Using Newton's approximation method here
    // Square Root is not exactly performant and we
    // likely do not need an exact value.
    // TODO: [#32] Change Magnitude which does not use Square Root
    return static_cast<float>(std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w));
}

int FVector4I::DotProduct(const FVector4I& other) const
{
    return m_x * other.m_x + m_y * other.m_y + m_z * other.m_z + m_w * other.m_w;
}

float FVector4I::DistanceBetween(const FVector4I& other) const
{
    return (float)std::sqrt(static_cast<float>(std::pow(other.m_x - m_x, 2))
        + static_cast<float>(std::pow(other.m_y - m_y, 2))
        + static_cast<float>(std::pow(other.m_z - m_z, 2))
        + static_cast<float>(std::pow(other.m_w - m_w, 2)));
}

std::string FVector4I::Print() const
{
    std::stringstream ss;
    ss << "X: " << std::to_string(m_x)
        << " Y: " << std::to_string(m_y)
        << " Z: " << std::to_string(m_z)
        << " W: " << std::to_string(m_w);
    return ss.str();
}