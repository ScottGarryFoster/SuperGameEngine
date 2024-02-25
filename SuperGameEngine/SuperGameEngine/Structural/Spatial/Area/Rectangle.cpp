#include "Rectangle.h"

using namespace SuperGameEngine;
using namespace StandardCLibrary;
Rectangle::Rectangle(float x, float y, float width, float height)
{
    m_location = FVector2D(x, y);
    m_size = FVector2D(width, height);
}
Rectangle::Rectangle(float xy, float widthHeight)
{
    m_location = FVector2D(xy, xy);
    m_size = FVector2D(widthHeight, widthHeight);
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
}

void Rectangle::SetY(float y)
{
    m_location.SetY(y);
}

void Rectangle::SetSize(float width, float height)
{
    m_size.SetXYValue(width, height);
}

void Rectangle::SetWidth(float width)
{
    m_size.SetX(width);
}

void Rectangle::SetHeight(float height)
{
    m_size.SetY(height);
}

bool Rectangle::Overlaps(Rectangle& other) const
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

bool Rectangle::OverlapsOrIsTouching(Rectangle& other) const
{
    return IsTouching(other) || Overlaps(other);
}

bool Rectangle::IsTouching(Rectangle& other) const
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

