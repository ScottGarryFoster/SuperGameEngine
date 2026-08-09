#include "SuperEngineControls.h"
#include "ViewportSizeChangedEventArguments.h"
#include "../../../../FatedQuest.Libraries/Logger/AllReferences.h"

using namespace SuperGameEngine;
using namespace FatedQuestLibraries;

SuperEngineControls::SuperEngineControls(const std::string& name)
{
    m_name = name;

    m_viewportWidth = 0;
    m_viewportHeight = 0;

    m_onViewportSizeChanged = std::make_shared<FEvent>();
}

std::string SuperEngineControls::GetName() const
{
    return m_name;
}

void SuperEngineControls::SetNewViewportSize(int width, int height)
{
    if (width <= 0 || height <= 0)
    {
        Log::Error("Invalid width and height set, cannot update viewport. "
                   "Width: " + std::to_string(width) + 
                    " Height: " + std::to_string(height),
            "SuperEngineControls::SetNewViewportSize(int, int)");
        return;
    }

    bool sizesHaveChanged = width != m_viewportWidth || height != m_viewportHeight;

    m_viewportWidth = width;
    m_viewportWidth = height;

    if (sizesHaveChanged)
    {
        auto arguments = std::make_shared<ViewportSizeChangedEventArguments>(m_name, width, height);
        m_onViewportSizeChanged->Invoke(arguments);
    }
}

std::shared_ptr<FatedQuestLibraries::FEventSubscriptions> SuperEngineControls::OnViewportSizeChanged() const
{
    return m_onViewportSizeChanged;
}

