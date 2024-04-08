#include "FrameTiming.h"
#include <SDL.h>

using namespace SuperGameEngine;
using namespace StandardCLibrary;

FrameTiming::FrameTiming()
{
    m_fixedUpdateLoopTicks = 20;
}

FrameTiming::~FrameTiming()
{

}

int FrameTiming::GetFixedUpdateLoopTiming() const
{
    return m_fixedUpdateLoopTicks;
}

void FrameTiming::SetFixedUpdateLoopTiming(int newValue)
{
    m_fixedUpdateLoopTicks = newValue;
}