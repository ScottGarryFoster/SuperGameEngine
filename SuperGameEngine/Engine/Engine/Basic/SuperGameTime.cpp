#include "SuperGameTime.h"

using namespace SuperGameEngine;

SuperGameTime::SuperGameTime()
{
    m_allTime = 0;
    m_timeDelta = 0;
    m_windowUpTime = 0;
}

SuperGameTime::~SuperGameTime() = default;

uint64_t SuperGameTime::TimeDelta() const
{
    return m_timeDelta;
}

uint64_t SuperGameTime::AllTime() const
{
    return m_allTime;
}

uint64_t SuperGameTime::WindowTime() const
{
    return m_windowUpTime;
}

void SuperGameTime::SetTicksSinceLastFrame(uint64_t ticks)
{
    m_timeDelta = ticks;
    m_allTime += ticks;
    m_windowUpTime += ticks;
}

void SuperGameTime::ResetWindowTime()
{
    m_windowUpTime = 0;
}
