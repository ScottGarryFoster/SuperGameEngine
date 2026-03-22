#include "ViewportEngineAndPanelCommunication.h"

using namespace SuperGameTools;

ViewportEngineAndPanelCommunication::ViewportEngineAndPanelCommunication()
{
    m_viewport = SuperGameEngine::RectangleInt(0, 0, 0, 0);
}

SuperGameEngine::RectangleInt ViewportEngineAndPanelCommunication::GetViewportLocation() const
{
    return m_viewport;
}

void ViewportEngineAndPanelCommunication::UpdateViewportLocation(int x, int y, int width, int height)
{
    m_viewport.SetLocation(x, y);
    m_viewport.SetSize(width, height);
}