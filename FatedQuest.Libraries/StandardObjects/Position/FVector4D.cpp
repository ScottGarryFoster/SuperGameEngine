#include "FVector4D.h"
#include "FVector4I.h"
#include "FVector4F.h"
#include "FPoint.h"
#include "../../StandardOperations/AllReferences.h"
#include <cmath>

using namespace FatedQuestLibraries;

FVector4D::FVector4D()
{
    m_x = 0;
    m_y = 0;
    m_z = 0;
    m_w = 0;
}

FVector4D::FVector4D(double x, double y, double z, double w)
{
    m_x = x;
    m_y = y;
    m_z = z;
    m_w = w;
}

FVector4D::FVector4D(const FVector4D& other)
    : FVector4D(other.GetX(), other.GetY(), other.GetZ(), other.GetW())
{
}

FVector4D::FVector4D(const FPoint& other)
    : FVector4D(static_cast<double>(other.GetX()), static_cast<double>(other.GetY()), 0, 0)
{
}

FVector4D::FVector4D(const FVector4F& other)
{
    m_x = static_cast<double>(other.GetX());
    m_y = static_cast<double>(other.GetY());
    m_z = static_cast<double>(other.GetZ());
    m_w = static_cast<double>(other.GetW());
}

FVector4D::FVector4D(const FVector4I& other)
{
    m_x = static_cast<double>(other.GetX());
    m_y = static_cast<double>(other.GetY());
    m_z = static_cast<double>(other.GetZ());
    m_w = static_cast<double>(other.GetW());
}

FVector4D::~FVector4D() = default;

double FVector4D::GetX() const
{
    return m_x;
}

double FVector4D::GetY() const
{
    return m_y;
}

double FVector4D::GetZ() const
{
    return m_z;
}

double FVector4D::GetW() const
{
    return m_w;
}

void FVector4D::SetX(double newValue)
{
    m_x = newValue;
}

void FVector4D::SetY(double newValue)
{
    m_y = newValue;
}

void FVector4D::SetZ(double newValue)
{
    m_z = newValue;
}

void FVector4D::SetW(double newValue)
{
    m_w = newValue;
}

void FVector4D::SetXYValue(double x, double y)
{
    if (x != m_x || y != m_y)
    {
        m_x = x;
        m_y = y;
    }
}

void FVector4D::SetXYZValue(double x, double y, double z)
{
    if (x != m_x || y != m_y || z != m_z)
    {
        m_x = x;
        m_y = y;
        m_z = z;
    }
}

void FVector4D::SetXYZWValue(double x, double y, double z, double w)
{
    if (x != m_x || y != m_y || z != m_z || w != m_w)
    {
        m_x = x;
        m_y = y;
        m_z = z;
        m_w = w;
    }
}

void FVector4D::SetValue(const FVector4D& other)
{
    SetXYZWValue(other.GetX(), other.GetY(), other.GetZ(), other.GetW());
}

void FVector4D::SetXYValue(const FPoint& other)
{
    SetXYValue((double)other.GetX(), (double)other.GetY());
}

FVector4D FVector4D::operator+(const FVector4D& other) const
{
    return { m_x + other.m_x, m_y + other.m_y, m_z + other.m_z, m_w + other.m_w };
}

FVector4D& FVector4D::operator+=(const FVector4D& other)
{
    m_x += other.m_x;
    m_y += other.m_y;
    m_z += other.m_z;
    m_w += other.m_w;
    return *this;
}

FVector4D FVector4D::operator-(const FVector4D& other) const
{
    return { m_x - other.m_x, m_y - other.m_y, m_z - other.m_z, m_w - other.m_w };
}

FVector4D& FVector4D::operator-=(const FVector4D& other)
{
    m_x -= other.m_x;
    m_y -= other.m_y;
    m_z -= other.m_z;
    m_w -= other.m_w;
    return *this;
}

FVector4D FVector4D::operator*(double scalar) const
{
    return { m_x * scalar, m_y * scalar, m_z * scalar, m_w * scalar };
}

FVector4D& FVector4D::operator*=(double scalar)
{
    m_x *= scalar;
    m_y *= scalar;
    m_z *= scalar;
    m_w *= scalar;
    return *this;
}

FVector4D FVector4D::operator/(double scalar) const
{
    return { m_x / scalar, m_y / scalar, m_z / scalar, m_w / scalar };
}

FVector4D& FVector4D::operator/=(double scalar)
{
    m_x /= scalar;
    m_y /= scalar;
    m_z /= scalar;
    m_w /= scalar;
    return *this;
}

bool FVector4D::operator==(const FVector4D& other) const
{
    return
        FloatingPointHelpers::AreEqual(m_x, other.m_x) &&
        FloatingPointHelpers::AreEqual(m_y, other.m_y) &&
        FloatingPointHelpers::AreEqual(m_z, other.m_z) &&
        FloatingPointHelpers::AreEqual(m_w, other.m_w);
}

FVector4D FVector4D::Normalize() const
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

double FVector4D::Magnitude() const
{
    // We should add Inverse Square Root version
    // Using Newton's approximation method here
    // Square Root is not exactly performant and we
    // likely do not need an exact value.
    // TODO: [#32] Change Magnitude which does not use Square Root
    return (double)std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w);
}

double FVector4D::DotProduct(const FVector4D& other) const
{
    return m_x * other.m_x + m_y * other.m_y + m_z * other.m_z + m_w * other.m_w;
}

double FVector4D::DistanceBetween(const FVector4D& other) const
{
    return (double)std::sqrt(static_cast<double>(std::pow(other.m_x - m_x, 2))
        + static_cast<double>(std::pow(other.m_y - m_y, 2))
        + static_cast<double>(std::pow(other.m_z - m_z, 2))
        + static_cast<double>(std::pow(other.m_w - m_w, 2)));
}

std::string FVector4D::Print() const
{
    std::stringstream ss;
    ss <<  "X: " << std::to_string(m_x)
       << " Y: " << std::to_string(m_y)
       << " Z: " << std::to_string(m_z)
       << " W: " << std::to_string(m_w);
    return ss.str();
}