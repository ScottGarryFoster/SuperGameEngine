#include "FPoint.h"
#include <sstream>

using namespace FatedQuestLibraries;
FPoint::FPoint()
{
    m_x = 0;
    m_y = 0;
}

FPoint::FPoint(int x, int y)
{
    m_x = x;
    m_y = y;
}

FPoint::~FPoint()
{
}

const int FPoint::GetX() const
{
    return m_x;
}

const int FPoint::GetY() const
{
    return m_y;
}

void FPoint::SetX(int newValue)
{
    if (newValue != m_x)
    {
        m_x = newValue;
    }
}

void FPoint::SetY(int newValue)
{
    if (newValue != m_y)
    {
        m_y = newValue;
    }
}

void FPoint::SetXYValue(int x, int y)
{
    SetX(x);
    SetY(y);
}

bool FPoint::operator==(const FPoint& other) const
{
    int leftX = other.GetX();
    int leftY = other.GetY();

    int rightX = GetX();
    int rightY = GetY();
    return leftX == rightX && leftY == rightY;
}

FPoint FPoint::operator+(const FPoint& other) const
{
    return FPoint(GetX() + other.GetX(), GetY() + other.GetY());
}

FPoint& FPoint::operator+=(const FPoint& other)
{
    SetXYValue(GetX() + other.GetX(), GetY() + other.GetY());
    return *this;
}

const std::string FPoint::Print() const
{
    std::stringstream ss;
    ss << "X: " << std::to_string(m_x) << " Y: " << std::to_string(m_y);
    return ss.str();
}