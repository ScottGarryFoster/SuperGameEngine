#include "SuperGameTime.h"

using namespace SuperGameEngine;

SuperGameTime::SuperGameTime()
{
    m_allTime = 0;
    m_timeDelta = 0;
    m_windowUpTime = 0;
}

SuperGameTime::~SuperGameTime() = default;

Uint64 SuperGameTime::TimeDelta() const
{
    return m_timeDelta;
}

Uint64 SuperGameTime::AllTime() const
{
    return m_allTime;
}

Uint64 SuperGameTime::WindowTime() const
{
    return m_windowUpTime;
}

void SuperGameTime::SetTicksSinceLastFrame(Uint64 ticks)
{
    m_timeDelta = ticks;
    m_allTime += ticks;
    m_windowUpTime += ticks;
}

void SuperGameTime::ResetWindowTime()
{
    m_windowUpTime = 0;
}
