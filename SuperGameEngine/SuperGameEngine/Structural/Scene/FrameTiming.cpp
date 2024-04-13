#include "FrameTiming.h"
#include <SDL.h>

using namespace SuperGameEngine;
using namespace StandardCLibrary;

FrameTiming::FrameTiming()
{
    m_fixedUpdateLoopTicks = 20;
    m_fixedUpdateAsSecond = m_fixedUpdateLoopTicks / 1000.0f;
}

FrameTiming::~FrameTiming()
{

}

int FrameTiming::GetFixedUpdateLoopTiming() const
{
    return m_fixedUpdateLoopTicks;
}

float SuperGameEngine::FrameTiming::GetFixedUpdateLoopTimingAsSecond() const
{
    return m_fixedUpdateAsSecond;
}

void FrameTiming::SetFixedUpdateLoopTiming(int newValue)
{
    m_fixedUpdateLoopTicks = newValue;
    m_fixedUpdateAsSecond = m_fixedUpdateLoopTicks / 1000.0f;
}