#include "FVector3D.h"
#include "FVector3I.h"
#include "FVector3F.h"
#include "FPoint.h"
#include "../../StandardOperations/AllReferences.h"
#include <cmath>

using namespace FatedQuestLibraries;

FVector3D::FVector3D()
{
    m_x = 0;
    m_y = 0;
    m_z = 0;
}

FVector3D::FVector3D(double x, double y, double z)
{
    m_x = x;
    m_y = y;
    m_z = z;
}

FVector3D::FVector3D(const FVector3D& other)
    : FVector3D(other.GetX(), other.GetY(), other.GetZ())
{
}

FVector3D::FVector3D(const FPoint& other)
    : FVector3D(static_cast<double>(other.GetX()), static_cast<double>(other.GetY()), 0)
{
}

FVector3D::FVector3D(const FVector3F& other)
{
    m_x = static_cast<double>(other.GetX());
    m_y = static_cast<double>(other.GetY());
    m_z = static_cast<double>(other.GetZ());
}

FVector3D::FVector3D(const FVector3I& other)
{
    m_x = static_cast<double>(other.GetX());
    m_y = static_cast<double>(other.GetY());
    m_z = static_cast<double>(other.GetZ());
}

FVector3D::~FVector3D() = default;

double FVector3D::GetX() const
{
    return m_x;
}

double FVector3D::GetY() const
{
    return m_y;
}

double FVector3D::GetZ() const
{
    return m_z;
}

void FVector3D::SetX(double newValue)
{
    m_x = newValue;
}

void FVector3D::SetY(double newValue)
{
    m_y = newValue;
}

void FVector3D::SetZ(double newValue)
{
    m_z = newValue;
}

void FVector3D::SetXYValue(double x, double y)
{
    if (x != m_x || y != m_y)
    {
        m_x = x;
        m_y = y;
    }
}

void FVector3D::SetXYValue(double x, double y, double z)
{
    if (x != m_x || y != m_y || z != m_z)
    {
        m_x = x;
        m_y = y;
        m_z = z;
    }
}

void FVector3D::SetXYValue(const FVector3D& other)
{
    SetXYValue(other.GetX(), other.GetY());
}

void FVector3D::SetXYValue(const FPoint& other)
{
    SetXYValue((double)other.GetX(), (double)other.GetY());
}

FVector3D FVector3D::operator+(const FVector3D& other) const
{
    return { m_x + other.m_x, m_y + other.m_y, m_z + other.m_z };
}

FVector3D& FVector3D::operator+=(const FVector3D& other)
{
    m_x += other.m_x;
    m_y += other.m_y;
    m_z += other.m_z;
    return *this;
}

FVector3D FVector3D::operator-(const FVector3D& other) const
{
    return { m_x - other.m_x, m_y - other.m_y, m_z - other.m_z };
}

FVector3D& FVector3D::operator-=(const FVector3D& other)
{
    m_x -= other.m_x;
    m_y -= other.m_y;
    m_z -= other.m_z;
    return *this;
}

FVector3D FVector3D::operator*(double scalar) const
{
    return { m_x * scalar, m_y * scalar, m_z * scalar };
}

FVector3D& FVector3D::operator*=(double scalar)
{
    m_x *= scalar;
    m_y *= scalar;
    m_z *= scalar;
    return *this;
}

FVector3D FVector3D::operator/(double scalar) const
{
    return { m_x / scalar, m_y / scalar, m_z / scalar };
}

FVector3D& FVector3D::operator/=(double scalar)
{
    m_x /= scalar;
    m_y /= scalar;
    m_z /= scalar;
    return *this;
}

bool FVector3D::operator==(const FVector3D& other) const
{
    return
        FloatingPointHelpers::AreEqual(m_x, other.m_x) &&
        FloatingPointHelpers::AreEqual(m_y, other.m_y) &&
        FloatingPointHelpers::AreEqual(m_z, other.m_z);
}

FVector3D FVector3D::Normalize() const
{
    double magnitude = Magnitude();
    if (magnitude != 0)
    {
        return *this / magnitude;
    }
    else
    {
        return { 0, 0, 0 };
    }
}

double FVector3D::Magnitude() const
{
    // We should add Inverse Square Root version
    // Using Newton's approximation method here
    // Square Root is not exactly performant and we
    // likely do not need an exact value.
    // TODO: [#32] Change Magnitude which does not use Square Root
    return (double)std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
}

double FVector3D::DotProduct(const FVector3D& other) const
{
    return m_x * other.m_x + m_y * other.m_y + m_z * other.m_z;
}

double FVector3D::DistanceBetween(const FVector3D& other) const
{
    return (double)std::sqrt(static_cast<double>(std::pow(other.m_x - m_x, 2))
        + static_cast<double>(std::pow(other.m_y - m_y, 2))
        + static_cast<double>(std::pow(other.m_z - m_z, 2)));
}

std::string FVector3D::Print() const
{
    std::stringstream ss;
    ss << "X: " << std::to_string(m_x) << " Y: " << std::to_string(m_y) << " Z: " << std::to_string(m_z);
    return ss.str();
}