#include "Circle.h"
#include "Rectangle.h"

using namespace SuperGameEngine;
using namespace FatedQuestLibraries;

Circle::Circle(int radius)
{
    SetRadius(radius);
    m_location = FVector2D(0, 0);
}

Circle::Circle(float x, float y, int radius)
{
    SetRadius(radius);
    m_location = FVector2D(x, y);
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
    if (radius < 0)
    {
        radius = 0;
    }

    m_radius = radius;
}

int Circle::GetRadius() const
{
    return m_radius;
}

bool Circle::Overlaps(const Circle& other) const
{
    FVector2D myLocation = GetLocation();
    FVector2D otherLocation = other.GetLocation();
    float distance = myLocation.DistanceBetween(otherLocation);
    int radius = GetRadius();
    int otherRadius = other.GetRadius();
    return distance < (radius + otherRadius);
}

bool Circle::OverlapsOrTouches(const Circle& other) const
{
    FVector2D myLocation = GetLocation();
    FVector2D otherLocation = other.GetLocation();
    float distance = myLocation.DistanceBetween(otherLocation);
    int radius = GetRadius();
    int otherRadius = other.GetRadius();
    bool areEqual = FloatingPointHelpers::AreEqual(distance, (radius + otherRadius));
    return areEqual || distance < (radius + otherRadius);
}

/// <remark>
/// The Circle version is the main version of Overlap. as it makes more sence to test
/// a point is within the rectangle. The Rectangle version would be a repeat and would
/// link more methods. For this reason the Rectangle version just calls this Overlap.
/// </remark>
bool Circle::Overlaps(const Rectangle& other) const
{
    FVector2D myLocation = GetLocation();

    float closestX = myLocation.GetX();
    float closestY = myLocation.GetY();

    float myX = myLocation.GetX();
    float left = other.GetLeft();
    float right = other.GetRight();

    float myY = myLocation.GetY();
    float top = other.GetTop();
    float bottom = other.GetBottom();

    if (myX < left)
    {
        closestX = left;
    }
    else if (myX > right)
    {
        closestX = right;
    }

    if (myY < top)
    {
        closestY = top;
    }
    else if (myY > bottom)
    {
        closestY = bottom;
    }

    FVector2D testPoint = FVector2D(closestX, closestY);
    return PointIsWithin(testPoint);
}

bool Circle::PointIsWithin(FVector2D& location) const
{
    FVector2D myLocation = GetLocation();
    float distance = myLocation.DistanceBetween(location);
    int radius = GetRadius();
    return distance < radius;
}

float Circle::OverlapAmount(const Circle& other) const
{
    FVector2D myLocation = GetLocation();
    FVector2D otherLocation = other.GetLocation();

    float distance = myLocation.DistanceBetween(otherLocation);
    int radius = GetRadius();
    int otherRadius = other.GetRadius();
    float overlap = radius + otherRadius - distance;

    return overlap > 0 ? overlap : 0;
}

FVector2D Circle::GetNewLocationToNotOverlap(const Circle& other) const
{
    float overlap = OverlapAmount(other);
    FVector2D myLocation = GetLocation();
    if (overlap > 0)
    {
        float myX = myLocation.GetX();
        float myY = myLocation.GetY();

        FVector2D otherLocation = other.GetLocation();
        float otherX = otherLocation.GetX();
        float otherY = otherLocation.GetY();

        float angle = atan2(myY - otherY, myX - otherX);
        myX += overlap * cos(angle);
        myY += overlap * sin(angle);
        myLocation.SetXYValue(myX, myY);
    }

    return myLocation;
}

void Circle::MoveOutOfOverlapRangeOf(const Circle& other)
{
    float overlap = OverlapAmount(other);
    FVector2D myLocation = GetLocation();
    if (overlap > 0)
    {
        float myX = myLocation.GetX();
        float myY = myLocation.GetY();

        FVector2D otherLocation = other.GetLocation();
        float otherX = otherLocation.GetX();
        float otherY = otherLocation.GetY();

        float angle = atan2(myY - otherY, myX - otherX);
        myX += overlap * cos(angle);
        myY += overlap * sin(angle);
        FVector2D newLocation = FVector2D(myX, myY);
        SetLocation(newLocation);
    }
}

FVector2D Circle::GetNewLocationToNotOverlap(const Rectangle& other) const
{
    FVector2D myLocation = GetLocation();

    FVector2D cloest = other.ClosestPointTo(myLocation);
    float dx = cloest.GetX() - myLocation.GetX();
    float dy = cloest.GetY() - myLocation.GetY();
    float distance = sqrt(dx * dx + dy * dy);
    float overlap = GetRadius() - distance;

    FVector2D newLocation = FVector2D(myLocation);
    if (overlap > 0)
    {
        dx /= distance;
        dy /= distance;

        newLocation.SetX(newLocation.GetX() - (overlap * dx));
        newLocation.SetY(newLocation.GetY() - (overlap * dy));
    }

    return newLocation;
}