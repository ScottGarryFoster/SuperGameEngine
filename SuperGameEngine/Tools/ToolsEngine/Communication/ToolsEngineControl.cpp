#include "ToolsEngineControl.h"

using namespace SuperGameTools;

ToolsEngineControl::ToolsEngineControl()
{
    m_arePlaying = false;
    m_eventsHaveRunSinceAskingForOneFrame = false;
    m_playForOneFrame = false;
    m_stoppedPlayingLastFrame = false;
    m_neverCreated = true;
}

void ToolsEngineControl::Stop()
{
    m_arePlaying = false;
    m_playForOneFrame = false;
    m_eventsHaveRunSinceAskingForOneFrame = false;
    m_stoppedPlayingLastFrame = true;
}

void ToolsEngineControl::Play()
{
    m_arePlaying = true;
    m_playForOneFrame = false;
    m_eventsHaveRunSinceAskingForOneFrame = false;
}

void ToolsEngineControl::PlayForOneFrame()
{
    if (m_stoppedPlayingLastFrame)
    {
        return;
    }

    // Cannot play for one frame if stopped.
    if (m_arePlaying || m_playForOneFrame)
    {
        m_arePlaying = false;
        m_playForOneFrame = true;
        m_eventsHaveRunSinceAskingForOneFrame = false;
    }
}

bool ToolsEngineControl::DoRecreate() const
{
    if (m_arePlaying && m_stoppedPlayingLastFrame)
    {
        return true;
    }
    else if (m_arePlaying && m_neverCreated)
    {
        return true;
    }

    return false;
}

bool ToolsEngineControl::DoRunEvents() const
{
    return m_arePlaying || m_playForOneFrame;
}

bool ToolsEngineControl::DoRunUpdate() const
{
    return m_arePlaying || m_playForOneFrame;
}

bool ToolsEngineControl::DoRunDraw() const
{
    return m_arePlaying || m_playForOneFrame;
}

bool ToolsEngineControl::DoDestroy() const
{
    return !m_arePlaying;
}

void ToolsEngineControl::RanEvents()
{
    if (m_playForOneFrame)
    {
        m_eventsHaveRunSinceAskingForOneFrame = true;
    }

    m_neverCreated = false;
}

void ToolsEngineControl::RanUpdate()
{
    m_neverCreated = false;
}

void ToolsEngineControl::RanDraw()
{
    if (m_playForOneFrame && m_eventsHaveRunSinceAskingForOneFrame)
    {
        m_arePlaying = false;
        m_playForOneFrame = false;
        m_eventsHaveRunSinceAskingForOneFrame = false;
    }

    // The frame is over. We were no longer stopped.
    if (m_arePlaying && m_stoppedPlayingLastFrame)
    {
        m_stoppedPlayingLastFrame = false;
    }

    m_neverCreated = false;
}
