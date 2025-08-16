#include "FVector2D.h"
#include "FVector2I.h"
#include "FVector2F.h"
#include "FPoint.h"
#include "../../StandardOperations/AllReferences.h"
#include <cmath>

using namespace FatedQuestLibraries;

FVector2D::FVector2D()
{
    m_x = 0;
    m_y = 0;
}

FVector2D::FVector2D(double x, double y)
{
    m_x = x;
    m_y = y;
}

FVector2D::FVector2D(const FVector2D& other)
    : FVector2D(other.GetX(), other.GetY())
{
}

FVector2D::FVector2D(const FPoint& other)
    : FVector2D(static_cast<double>(other.GetX()), static_cast<double>(other.GetY()))
{
}

FVector2D::FVector2D(const FVector2F& other)
{
    m_x = static_cast<double>(other.GetX());
    m_y = static_cast<double>(other.GetY());
}

FVector2D::FVector2D(const FVector2I& other)
{
    m_x = static_cast<double>(other.GetX());
    m_y = static_cast<double>(other.GetY());
}

FVector2D::~FVector2D() = default;

double FVector2D::GetX() const
{
    return m_x;
}

double FVector2D::GetY() const
{
    return m_y;
}

void FVector2D::SetX(double newValue)
{
    m_x = newValue;
}

void FVector2D::SetY(double newValue)
{
    m_y = newValue;
}

void FVector2D::SetXYValue(double x, double y)
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
    SetXYValue((double)other.GetX(), (double)other.GetY());
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

FVector2D FVector2D::operator*(double scalar) const
{
    return {m_x * scalar, m_y * scalar};
}

FVector2D& FVector2D::operator*=(double scalar)
{
    m_x *= scalar;
    m_y *= scalar;
    return *this;
}

FVector2D FVector2D::operator/(double scalar) const
{
    return {m_x / scalar, m_y / scalar};
}

FVector2D& FVector2D::operator/=(double scalar)
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
    double magnitude = Magnitude();
    if (magnitude != 0)
    {
        return *this / magnitude;
    }
    else
    {
        return {0, 0};
    }
}

double FVector2D::Magnitude() const
{
    // We should add Inverse Square Root version
    // Using Newton's approximation method here
    // Square Root is not exactly performant and we
    // likely do not need an exact value.
    // TODO: [#32] Change Magnitude which does not use Square Root
    return (double)std::sqrt(m_x * m_x + m_y * m_y);
}

double FVector2D::DotProduct(const FVector2D& other) const
{
    return m_x * other.m_x + m_y * other.m_y;
}

double FVector2D::DistanceBetween(const FVector2D& other) const
{
    return (double)std::sqrt(static_cast<double>(std::pow(other.m_x - m_x, 2))
        + static_cast<double>(std::pow(other.m_y - m_y, 2)));
}

const std::string FVector2D::Print() const
{
    std::stringstream ss;
    ss << "X: " << std::to_string(m_x) << " Y: " << std::to_string(m_y);
    return ss.str();
}