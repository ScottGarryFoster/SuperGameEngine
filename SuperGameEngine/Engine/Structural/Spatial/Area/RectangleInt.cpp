#include "RectangleInt.h"
#include "Rectangle.h"
#include "Circle.h"

using namespace SuperGameEngine;
using namespace FatedQuestLibraries;

RectangleInt::RectangleInt()
{
    // Explicitly calling these.
    m_location = FPoint();
    m_size = FPoint();
    m_center = FVector2D();
}

RectangleInt::RectangleInt(int x, int y, int width, int height)
{
    m_location = FPoint(x, y);
    m_size = FPoint(width, height);
    m_center = FVector2D(x + (width / 2.0f), y + (height / 2.0f));
}

RectangleInt::RectangleInt(int xy, int widthHeight)
{
    m_location = FPoint(xy, xy);
    m_size = FPoint(widthHeight, widthHeight);
    m_center = FVector2D(xy + (widthHeight / 2.0f), xy + (widthHeight / 2.0f));
}

RectangleInt::RectangleInt(const FVector4I& other)
{
    m_location = FPoint(other.GetX(), other.GetY());
    m_size = FPoint(other.GetZ(), other.GetW());
    m_center = FVector2D(other.GetX() + (other.GetZ() / 2.0f), other.GetY() + (other.GetW() / 2.0f));
}

RectangleInt::RectangleInt(const std::shared_ptr<FVector4I>& other)
{
    m_location = FPoint(other->GetX(), other->GetY());
    m_size = FPoint(other->GetZ(), other->GetW());
    m_center = FVector2D(other->GetX() + (other->GetZ() / 2.0f), other->GetY() + (other->GetW() / 2.0f));
}

bool RectangleInt::operator==(const RectangleInt& other) const
{
    return
        GetLeft() == other.GetLeft() &&
        GetRight() == other.GetRight() &&
        GetBottom() == other.GetBottom() &&
        GetTop() == other.GetTop();
}

int RectangleInt::GetLeft() const
{
    return m_location.GetX();
}

int RectangleInt::GetRight() const
{
    return m_location.GetX() + m_size.GetX();
}

int RectangleInt::GetTop() const
{
    return m_location.GetY();
}

int RectangleInt::GetBottom() const
{
    return m_location.GetY() + m_size.GetY();
}

int RectangleInt::GetWidth() const
{
    return m_size.GetX();
}

int RectangleInt::GetHeight() const
{
    return m_size.GetY();
}

FPoint RectangleInt::GetTopLeft() const
{
    return m_location;
}

FPoint RectangleInt::GetBottomRight() const
{
    return FPoint(GetRight(), GetBottom());
}

void RectangleInt::SetLocation(int x, int y)
{
    m_location.SetXYValue(x, y);
}

void RectangleInt::SetX(int x)
{
    m_location.SetX(x);
    m_center.SetX(x + m_size.GetX() / 2.0f);
}

void RectangleInt::SetY(int y)
{
    m_location.SetY(y);
    m_center.SetX(y + m_size.GetY() / 2.0f);
}

void RectangleInt::SetSize(int width, int height)
{
    m_size.SetXYValue(width, height);
    m_center.SetX(m_location.GetX() + width / 2.0f);
    m_center.SetX(m_location.GetY() + height / 2.0f);
}

void RectangleInt::SetWidth(int width)
{
    m_size.SetX(width);
    m_center.SetX(m_location.GetX() + width / 2.0f);
}

void RectangleInt::SetHeight(int height)
{
    m_size.SetY(height);
    m_center.SetX(m_location.GetY() + height / 2.0f);
}

void RectangleInt::MoveShape(const FPoint& amount)
{
    int originalX = GetLeft();
    int originalY = GetTop();
    SetLocation(originalX + amount.GetX(), originalY + amount.GetY());
}

bool SuperGameEngine::RectangleInt::Overlaps(const Rectangle& other) const
{
    if (IsTouching(other))
    {
        return false;
    }

    if (GetLeft() > std::round(other.GetRight()))
    {
        return false;
    }

    if (GetRight() < std::round(other.GetLeft()))
    {
        return false;
    }

    if (GetTop() > std::round(other.GetBottom()))
    {
        return false;
    }

    if (GetBottom() < std::round(other.GetTop()))
    {
        return false;
    }

    return true;
}

bool RectangleInt::Overlaps(const RectangleInt& other) const
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

bool RectangleInt::Overlaps(const Circle& other) const
{
    Rectangle copy = Rectangle((float)GetLeft(), (float)GetTop(), (float)GetWidth(), (float)GetHeight());
    return other.Overlaps(copy);
}

bool RectangleInt::OverlapsOrIsTouching(const Rectangle& other) const
{
    return IsTouching(other) || Overlaps(other);
}

bool RectangleInt::OverlapsOrIsTouching(const RectangleInt& other) const
{
    return IsTouching(other) || Overlaps(other);
}

bool RectangleInt::PointIsWithin(FPoint& location) const
{
    int tX = location.GetX();
    int tY = location.GetY();

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

FPoint RectangleInt::OverlapAmount(const Rectangle& other) const
{
    FPoint otherSize = FPoint((int)other.GetWidth(), (int)other.GetHeight());
    RectangleInt ri = RectangleInt(
        (int)other.GetLeft(), (int)other.GetTop(),
        otherSize.GetX(), otherSize.GetY());
    return OverlapAmount(ri);
}

FPoint RectangleInt::OverlapAmount(const RectangleInt& other) const
{
    FPoint returnVector = FPoint();
    if (Overlaps(other))
    {
        if (GetCenter().GetX() > other.GetCenter().GetX())
        {
            returnVector.SetX(std::abs(GetLeft() - other.GetRight()));
        }
        else
        {
            returnVector.SetX(std::abs(GetRight() - other.GetLeft()));
        }

        if (GetCenter().GetY() > other.GetCenter().GetY())
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

FPoint SuperGameEngine::RectangleInt::OverlapAmount(const Rectangle& other, const FPoint& previousLoctation) const
{
    FPoint otherSize = FPoint((int)other.GetWidth(), (int)other.GetHeight());
    RectangleInt ri = RectangleInt(
        (int)other.GetLeft(), (int)other.GetTop(),
        otherSize.GetX(), otherSize.GetY());
    return OverlapAmount(ri, previousLoctation);
}

FPoint RectangleInt::OverlapAmount(const RectangleInt& other, const FPoint& previousLoctation) const
{
    FPoint returnVector = FPoint();
    if (Overlaps(other))
    {
        if (previousLoctation.GetX() > other.GetCenter().GetX())
        {
            returnVector.SetX(std::abs(GetLeft() - other.GetRight()));
        }
        else
        {
            returnVector.SetX(std::abs(GetRight() - other.GetLeft()));
        }

        if (previousLoctation.GetY() > other.GetCenter().GetY())
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

void RectangleInt::MoveOutOfOverlapRangeOf(const Rectangle& other)
{
    FPoint otherSize = FPoint((int)other.GetWidth(), (int)other.GetHeight());
    RectangleInt ri = RectangleInt(
        (int)other.GetLeft(), (int)other.GetTop(),
        otherSize.GetX(), otherSize.GetY());
    MoveOutOfOverlapRangeOf(ri);
}

void RectangleInt::MoveOutOfOverlapRangeOf(const RectangleInt& other)
{
    FPoint overlap = OverlapAmount(other);
    FPoint applied = FPoint();
    if (GetCenter().GetX() > other.GetCenter().GetX())
    {
        applied.SetX(overlap.GetX());
    }
    else
    {
        applied.SetX(overlap.GetX() * -1);
    }

    if (GetCenter().GetY() > other.GetCenter().GetY())
    {
        applied.SetY(overlap.GetY());
    }
    else
    {
        applied.SetY(overlap.GetY() * -1);
    }

    // If moving X meaning moving less
    if (std::abs(applied.GetX()) < std::abs(applied.GetY()))
    {
        // Then only move X.
        applied.SetY(0);
    }
    else
    {
        applied.SetX(0);
    }

    MoveShape(applied);
}

void RectangleInt::MoveOutOfOverlapRangeOf(const Rectangle& other, const FPoint& previousLoctation)
{
    FPoint otherSize = FPoint((int)other.GetWidth(), (int)other.GetHeight());
    RectangleInt ri = RectangleInt(
        (int)other.GetLeft(), (int)other.GetTop(),
        otherSize.GetX(), otherSize.GetY());
    MoveOutOfOverlapRangeOf(ri, previousLoctation);
}

void RectangleInt::MoveOutOfOverlapRangeOf(const RectangleInt& other, const FPoint& previousLoctation)
{
    FPoint overlap = OverlapAmount(other, previousLoctation);
    FPoint applied = FPoint();
    if (previousLoctation.GetX() > other.GetCenter().GetX())
    {
        applied.SetX(overlap.GetX());
    }
    else
    {
        applied.SetX(overlap.GetX() * -1);
    }

    if (previousLoctation.GetY() > other.GetCenter().GetY())
    {
        applied.SetY(overlap.GetY());
    }
    else
    {
        applied.SetY(overlap.GetY() * -1);
    }

    // If moving X meaning moving less
    if (std::abs(applied.GetX()) < std::abs(applied.GetY()))
    {
        // Then only move X.
        applied.SetY(0);
    }
    else
    {
        applied.SetX(0);
    }

    MoveShape(applied);
}

FPoint SuperGameEngine::RectangleInt::GetNewLocationToNotOverlap(const Rectangle& other) const
{
    FPoint otherSize = FPoint((int)other.GetWidth(), (int)other.GetHeight());
    RectangleInt ri = RectangleInt(
        (int)other.GetLeft(), (int)other.GetTop(),
        otherSize.GetX(), otherSize.GetY());
    return GetNewLocationToNotOverlap(ri);
}

FPoint RectangleInt::GetNewLocationToNotOverlap(const RectangleInt& other) const
{
    FPoint overlap = OverlapAmount(other);
    FPoint applied = FPoint();
    if (GetCenter().GetX() > other.GetCenter().GetX())
    {
        applied.SetX(overlap.GetX());
    }
    else
    {
        applied.SetX(overlap.GetX() * -1);
    }

    if (GetCenter().GetY() > other.GetCenter().GetY())
    {
        applied.SetY(overlap.GetY());
    }
    else
    {
        applied.SetY(overlap.GetY() * -1);
    }

    // If moving X meaning moving less
    if (std::abs(applied.GetX()) < std::abs(applied.GetY()))
    {
        // Then only move X.
        applied.SetY(0);
    }
    else
    {
        applied.SetX(0);
    }

    FPoint returnLocation = FPoint(m_location);
    returnLocation += applied;
    return returnLocation;
}

FPoint RectangleInt::GetNewLocationToNotOverlap(
    const Rectangle& other, const FPoint& previousLoctation) const
{
    FPoint otherSize = FPoint((int)other.GetWidth(), (int)other.GetHeight());
    RectangleInt ri = RectangleInt(
        (int)other.GetLeft(), (int)other.GetTop(),
        otherSize.GetX(), otherSize.GetY());
    return GetNewLocationToNotOverlap(ri, previousLoctation);
}

FPoint RectangleInt::GetNewLocationToNotOverlap(const RectangleInt& other, const FPoint& previousLoctation) const
{
    FPoint overlap = OverlapAmount(other, previousLoctation);
    FPoint applied = FPoint();
    if (previousLoctation.GetX() > other.GetCenter().GetX())
    {
        applied.SetX(overlap.GetX());
    }
    else
    {
        applied.SetX(overlap.GetX() * -1);
    }

    if (previousLoctation.GetY() > other.GetCenter().GetY())
    {
        applied.SetY(overlap.GetY());
    }
    else
    {
        applied.SetY(overlap.GetY() * -1);
    }

    // If moving X meaning moving less
    if (std::abs(applied.GetX()) < std::abs(applied.GetY()))
    {
        // Then only move X.
        applied.SetY(0);
    }
    else
    {
        applied.SetX(0);
    }

    FPoint returnLocation = FPoint(m_location);
    returnLocation += applied;
    return returnLocation;
}

FPoint RectangleInt::GetNewLocationToNotOverlap(const Circle& other) const
{
    FVector2D otherLocation = other.GetLocation();
    FPoint otherLocationPoint = FPoint(static_cast<int>(otherLocation.GetX()), static_cast<int>(otherLocation.GetY()));

    FVector2D closest = ClosestPointTo(otherLocationPoint);
    float dx = closest.GetX() - otherLocation.GetX();
    float dy = closest.GetY() - otherLocation.GetY();
    float distance = sqrt(dx * dx + dy * dy);
    float overlap = other.GetRadius() - distance;

    FPoint newLocation = FPoint(m_location);
    if (overlap > 0)
    {
        dx /= distance;
        dy /= distance;
        newLocation.SetX(static_cast<int>(newLocation.GetX() + overlap * dx));
        newLocation.SetY(static_cast<int>(newLocation.GetY() + overlap * dy));
    }

    return newLocation;
}

FPoint RectangleInt::ClosestPointTo(const FPoint& other) const
{
    int closestX = other.GetX();
    int closestY = other.GetY();

    const int myX = other.GetX();
    const int left = GetLeft();
    const int right = GetRight();

    const int myY = other.GetY();
    const int top = GetTop();
    const int bottom = GetBottom();

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

    return {closestX, closestY};
}

bool RectangleInt::IsTouching(const RectangleInt& other) const
{
    if (GetLeft() == other.GetRight())
    {
        return true;
    }

    if (GetRight() == other.GetLeft())
    {
        return true;
    }

    if (GetTop() == other.GetBottom())
    {
        return true;
    }

    if (GetBottom() == other.GetTop())
    {
        return true;
    }

    return false;
}

bool RectangleInt::IsTouching(const Rectangle& other) const
{
    if (GetLeft() == static_cast<int>(std::round(other.GetRight())))
    {
        return true;
    }

    if (GetRight() == static_cast<int>(std::round(other.GetLeft())))
    {
        return true;
    }

    if (GetTop() == static_cast<int>(std::round(other.GetBottom())))
    {
        return true;
    }

    if (GetBottom() == static_cast<int>(std::round(other.GetTop())))
    {
        return true;
    }

    return false;
}

FVector2D RectangleInt::GetCenter() const
{
    // TODO: We tried caching this, but it appeared not to work in all cases.
    // This should be investigated.
    return GenerateCenter(m_location, m_size);
}

FVector2D RectangleInt::GenerateCenter(const FPoint& location, const FPoint& size) const
{
    FVector2D newCenter = FVector2D(
        location.GetX() + size.GetX() / 2.0f,
        location.GetY() + size.GetY() / 2.0f);
    return newCenter;
}

FVector2D RectangleInt::GenerateCenter(const FVector2D& location, const FVector2D& size) const
{
    FVector2D newCenter = FVector2D(
        location.GetX() + size.GetX() / 2.0f,
        location.GetY() + size.GetY() / 2.0f);
    return newCenter;
}