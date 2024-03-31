#include "Circle.h"

using namespace SuperGameEngine;
using namespace StandardCLibrary;
Circle::Circle(int radius)
{
    m_radius = radius;
}

Circle::~Circle()
{
}

void Circle::SetLocation(FVector2D& location)
{
    m_location = location;
}

FVector2D Circle::GetLocation() const
{
    return m_location;
}

void Circle::SetRadius(int radius)
{
    m_radius = radius;
}

int Circle::GetRadius() const
{
    return m_radius;
}

bool Circle::Overlaps(Circle& other) const
{
    FVector2D myLocation = GetLocation();
    FVector2D otherLocation = other.GetLocation();
    float distance = myLocation.DistanceBetween(otherLocation);
    int radius = GetRadius();
    int otherRadius = other.GetRadius();
    return distance < (radius + otherRadius);
}
