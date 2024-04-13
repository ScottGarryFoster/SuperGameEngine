#include "Rectangle.h"
#include "Circle.h"

using namespace SuperGameEngine;
using namespace StandardCLibrary;
Rectangle::Rectangle(float x, float y, float width, float height)
{
    m_location = FVector2D(x, y);
    m_size = FVector2D(width, height);
    m_center = FVector2D(x + width / 2, y + height / 2);
}
Rectangle::Rectangle(float xy, float widthHeight)
{
    m_location = FVector2D(xy, xy);
    m_size = FVector2D(widthHeight, widthHeight);
    m_center = FVector2D(xy + widthHeight / 2, xy + widthHeight / 2);
}

float Rectangle::GetLeft() const
{
    return m_location.GetX();
}

float Rectangle::GetRight() const
{
    return m_location.GetX() + m_size.GetX();
}

float Rectangle::GetTop() const
{
    return m_location.GetY();
}

float SuperGameEngine::Rectangle::GetBottom() const
{
    return m_location.GetY() + m_size.GetY();
}

float SuperGameEngine::Rectangle::GetWidth() const
{
    return m_size.GetX();
}

float SuperGameEngine::Rectangle::GetHeight() const
{
    return m_size.GetY();
}

FVector2D SuperGameEngine::Rectangle::GetTopLeft() const
{
    return m_location;
}

FVector2D SuperGameEngine::Rectangle::GetBottomRight() const
{
    return FVector2D(GetRight(), GetBottom());
}

void Rectangle::SetLocation(float x, float y)
{
    m_location.SetXYValue(x, y);
}

void Rectangle::SetX(float x)
{
    m_location.SetX(x);
    m_center.SetX(x + m_size.GetX() / 2);
}

void Rectangle::SetY(float y)
{
    m_location.SetY(y);
    m_center.SetX(y + m_size.GetY() / 2);
}

void Rectangle::SetSize(float width, float height)
{
    m_size.SetXYValue(width, height);
    m_center.SetX(m_location.GetX() + width / 2);
    m_center.SetX(m_location.GetY() + height / 2);
}

void Rectangle::SetWidth(float width)
{
    m_size.SetX(width);
    m_center.SetX(m_location.GetX() + width / 2);
}

void Rectangle::SetHeight(float height)
{
    m_size.SetY(height);
    m_center.SetX(m_location.GetY() + height / 2);
}

void Rectangle::MoveShape(const FVector2D& amount)
{
    float originalX = GetLeft();
    float originalY = GetTop();
    SetLocation(originalX + amount.GetX(), originalY + amount.GetY());
}

bool Rectangle::Overlaps(const Rectangle& other) const
{
    if (IsTouching(other))
    {
        return false;
    }

    if (GetLeft() > other.GetRight())
    {
        return false;
    }

    if (GetRight() < other.GetLeft())
    {
        return false;
    }

    if (GetTop() > other.GetBottom())
    {
        return false;
    }

    if (GetBottom() < other.GetTop())
    {
        return false;
    }

    return true;
}

bool Rectangle::Overlaps(const Circle& other) const
{
    Rectangle copy = Rectangle(GetLeft(), GetTop(), GetWidth(), GetHeight());
    return other.Overlaps(copy);
}

bool Rectangle::OverlapsOrIsTouching(const Rectangle& other) const
{
    return IsTouching(other) || Overlaps(other);
}

bool Rectangle::PointIsWithin(FVector2D& location) const
{
    float tX = location.GetX();
    float tY = location.GetY();
    
    if (tX < GetLeft())
    {
        return false;
    }

    if (tX > GetRight())
    {
        return false;
    }

    if (tY < GetTop())
    {
        return false;
    }

    if (tY > GetBottom())
    {
        return false;
    }

    return true;
}

FVector2D Rectangle::OverlapAmount(const Rectangle& other) const
{
    FVector2D returnVector = FVector2D();
    if (Overlaps(other))
    {
        if (m_center.GetX() > other.m_center.GetX())
        {
            returnVector.SetX(std::abs(GetLeft() - other.GetRight()));
        }
        else
        {
            returnVector.SetX(std::abs(GetRight() - other.GetLeft()));
        }

        if (m_center.GetY() > other.m_center.GetY())
        {
            returnVector.SetY(std::abs(GetTop() - other.GetBottom()));
        }
        else
        {
            returnVector.SetY(std::abs(GetBottom() - other.GetTop()));
        }
    }

    return returnVector;
}

void Rectangle::MoveOutOfOverlapRangeOf(const Rectangle& other)
{
    FVector2D overlap = OverlapAmount(other);
    FVector2D applied = FVector2D();
    if (m_center.GetX() > other.m_center.GetX())
    {
        applied.SetX(overlap.GetX());
    }
    else
    {
        applied.SetX(overlap.GetX() * -1);
    }

    if (m_center.GetY() > other.m_center.GetY())
    {
        applied.SetY(overlap.GetY());
    }
    else
    {
        applied.SetY(overlap.GetY() * -1);
    }

    MoveShape(applied);
}

bool Rectangle::IsTouching(const Rectangle& other) const
{
    if (FloatingPointHelpers::AreEqual(GetLeft(), other.GetRight()))
    {
        return true;
    }

    if (FloatingPointHelpers::AreEqual(GetRight(), other.GetLeft()))
    {
        return true;
    }

    if (FloatingPointHelpers::AreEqual(GetTop(), other.GetBottom()))
    {
        return true;
    }

    if (FloatingPointHelpers::AreEqual(GetBottom(), other.GetTop()))
    {
        return true;
    }

    return false;
}

FVector2D Rectangle::GetCenter() const
{
    return m_center;
}


