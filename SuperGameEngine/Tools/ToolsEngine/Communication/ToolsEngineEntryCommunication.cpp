#include "ToolsEngineEntryCommunication.h"

using namespace SuperGameTools;

std::shared_ptr<EnginePlayControl> ToolsEngineEntryCommunication::GetPlayControls() const
{
    return m_playControl;
}

void ToolsEngineEntryCommunication::SetPlayControls(
    const std::shared_ptr<EnginePlayControl>& playControls)
{
    m_playControl = playControls;
}
