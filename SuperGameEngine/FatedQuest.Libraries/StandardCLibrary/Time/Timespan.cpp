#include "Timespan.h"

using namespace StandardCLibrary;

Timespan::Timespan()
{
    m_totalTicks = 0;
}

/// <summary>
/// As a complete time statement, how many ticks are on the clock before
/// counting the tick as a millisecond?
/// </summary>
/// <returns>The number of ticks on the clock. </returns>
int Timespan::GetTicks()
{
    unsigned long long int ticks = m_totalTicks % 1000;
    return (int)ticks;
}

/// <summary>
/// As a complete time statement, how many milliseconds are on the clock before
/// counting the milliseconds as a second?
/// </summary>
/// <returns>The number of milliseconds on the clock. </returns>
int Timespan::GetMilliseconds()
{
    unsigned long long int ticks = m_totalTicks % 1000;
    unsigned long long int milliseconds = m_totalTicks - ticks;
    unsigned long long int seconds = milliseconds / 60;
    unsigned long long int minutes = seconds / 60;
    unsigned long long int hours = minutes / 60;
    unsigned long long int days = hours / 24;

    unsigned long long int finalValue = milliseconds - (seconds * 60) - (minutes * 60) - (hours * 60) - (days * 24);
    return (int)(finalValue == 0 ? 0 : finalValue);
}

/// <summary>
/// As a complete time statement, how many seconds are on the clock before
/// counting the seconds as a minute?
/// </summary>
/// <returns>The number of seconds on the clock. </returns>
int Timespan::GetSeconds()
{
    unsigned long long int ticks = m_totalTicks % 1000;
    unsigned long long int milliseconds = m_totalTicks - ticks;
    unsigned long long int seconds = milliseconds / 60;
    unsigned long long int minutes = seconds / 60;
    unsigned long long int hours = minutes / 60;
    unsigned long long int days = hours / 24;

    unsigned long long int finalValue = (seconds * 60) - (minutes * 60) - (hours * 60) - (days * 24);
    return (int)(finalValue == 0 ? 0 : finalValue);
}

/// <summary>
/// As a complete time statement, how many minutes are on the clock before
/// counting the seconds as an hour?
/// </summary>
/// <returns>The number of minutes on the clock. </returns>
int Timespan::GetMinutes()
{
    unsigned long long int ticks = m_totalTicks % 1000;
    unsigned long long int milliseconds = m_totalTicks - ticks;
    unsigned long long int seconds = milliseconds / 60;
    unsigned long long int minutes = seconds / 60;
    unsigned long long int hours = minutes / 60;
    unsigned long long int days = hours / 24;

    unsigned long long int finalValue = (minutes * 60) - (hours * 60) - (days * 24);
    return (int)(finalValue == 0 ? 0 : finalValue);
}

/// <summary>
/// As a complete time statement, how many hours are on the clock before
/// counting the hours as a day?
/// </summary>
/// <returns>The number of hours on the clock. </returns>
int Timespan::GetHours()
{
    unsigned long long int ticks = m_totalTicks % 1000;
    unsigned long long int milliseconds = m_totalTicks - ticks;
    unsigned long long int seconds = milliseconds / 60;
    unsigned long long int minutes = seconds / 60;
    unsigned long long int hours = minutes / 60;
    unsigned long long int days = hours / 24;

    unsigned long long int finalValue = (hours * 60) - (days * 60);
    return (int)(finalValue == 0 ? 0 : finalValue);
}

/// <summary>
/// As a complete time statement, how many days are on the clock.
/// </summary>
/// <returns>The number of days on the clock. </returns>
int Timespan::GetDays()
{
    unsigned long long int ticks = m_totalTicks % 1000;
    unsigned long long int milliseconds = m_totalTicks - ticks;
    unsigned long long int seconds = milliseconds / 60;
    unsigned long long int minutes = seconds / 60;
    unsigned long long int hours = minutes / 60;
    unsigned long long int days = hours / 24;

    unsigned long long int finalValue = (days * 24);
    return (int)(finalValue == 0 ? 0 : finalValue);
}

/// <summary>
/// In total the number of ticks.
/// </summary>
/// <returns>In total on the clock the number of ticks. </returns>
/// <remark>Roughly 49 days in this will overflow. </remark>
unsigned long long int Timespan::GetTotalTicks()
{
    return m_totalTicks;
}

/// <summary>
/// In total the number of milliseconds.
/// </summary>
/// <returns>In total on the clock the number of milliseconds. </returns>
unsigned long long int Timespan::GetTotalMilliseconds()
{
    unsigned long long int ticks = m_totalTicks % 1000;
    unsigned long long int milliseconds = m_totalTicks - ticks;
    unsigned long long int seconds = milliseconds / 60;
    unsigned long long int minutes = seconds / 60;
    unsigned long long int hours = minutes / 60;
    unsigned long long int days = hours / 24;
    return milliseconds;
}

void Timespan::SetTimeByTick(int newTick)
{
    if (newTick >= 0)
    {
        m_totalTicks = newTick;
    }
}

void Timespan::SetTimeByTick(long int newTick)
{
    if (newTick >= 0)
    {
        m_totalTicks = newTick;
    }
}

void Timespan::SetTimeByTick(unsigned long int newTick)
{
    m_totalTicks = newTick;
}

void Timespan::SetTimeByMilliseconds(int newValue)
{
    if (newValue >= 0)
    {
        m_totalTicks = newValue * 1000;
    }
}

void Timespan::SetTimeBySeconds(int newValue)
{
    if (newValue >= 0)
    {
        m_totalTicks = newValue * 1000 * 60;
    }
}

void Timespan::SetTimeByMinutes(int newValue)
{
    if (newValue >= 0)
    {
        m_totalTicks = newValue * 1000 * 60 * 60;
    }
}

void Timespan::SetTimeByHours(int newValue)
{
    if (newValue >= 0)
    {
        m_totalTicks = newValue * 1000 * 60 * 60 * 60;
    }
}

void Timespan::SetTimeByDays(int newValue)
{
    if (newValue >= 0)
    {
        m_totalTicks = newValue * 1000 * 60 * 60 * 60 * 24;
    }
}

void Timespan::AddTicks(int addValue)
{
    // There is a flaw here that this could simply overflow.
    unsigned long long int potentialValue = m_totalTicks;
    potentialValue += addValue;
    if (potentialValue >= 0)
    {
        m_totalTicks = potentialValue;
    }
}

void Timespan::AddTicks(long int addValue)
{
    // There is a flaw here that this could simply overflow.
    unsigned long long int potentialValue = m_totalTicks;
    potentialValue += addValue;
    if (potentialValue >= 0)
    {
        m_totalTicks = potentialValue;
    }
}

void Timespan::AddTicks(unsigned long int addValue)
{
    // There is a flaw here that this could simply overflow.
    unsigned long long int potentialValue = m_totalTicks;
    potentialValue += addValue;
    if (potentialValue >= 0)
    {
        m_totalTicks = potentialValue;
    }
}

void Timespan::AddMilliseconds(int addValue)
{
    // There is a flaw here that this could simply overflow.
    unsigned long long int potentialValue = m_totalTicks;
    potentialValue += addValue * 1000;
    if (potentialValue >= 0)
    {
        m_totalTicks = potentialValue;
    }
}

void Timespan::AddSeconds(int addValue)
{
    // There is a flaw here that this could simply overflow.
    unsigned long long int potentialValue = m_totalTicks;
    potentialValue += addValue * 1000 * 60;
    if (potentialValue >= 0)
    {
        m_totalTicks = potentialValue;
    }
}

void Timespan::AddMinutes(int addValue)
{
    // There is a flaw here that this could simply overflow.
    unsigned long long int potentialValue = m_totalTicks;
    potentialValue += addValue * 1000 * 60 * 60;
    if (potentialValue >= 0)
    {
        m_totalTicks = potentialValue;
    }
}

void Timespan::AddHours(int addMinutes)
{
    // There is a flaw here that this could simply overflow.
    unsigned long long int potentialValue = m_totalTicks;
    potentialValue += addMinutes * 1000 * 60 * 60 * 60;
    if (potentialValue >= 0)
    {
        m_totalTicks = potentialValue;
    }
}

void Timespan::AddDays(int addValue)
{
    // There is a flaw here that this could simply overflow.
    unsigned long long int potentialValue = m_totalTicks;
    potentialValue += addValue * 1000 * 60 *60 * 60 * 24;
    if (potentialValue >= 0)
    {
        m_totalTicks = potentialValue;
    }
}