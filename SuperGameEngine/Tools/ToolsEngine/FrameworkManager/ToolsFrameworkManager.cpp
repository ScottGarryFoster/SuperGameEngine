#include "ToolsFrameworkManager.h"
#include "DocumentManager/ToolsDocumentManager.h"

using namespace SuperGameTools;

ToolsFrameworkManager::ToolsFrameworkManager(const std::weak_ptr<WindowPackage>& windowsPackage)
{
    m_windowsPackage = windowsPackage;
    m_documentManager = std::make_shared<ToolsDocumentManager>(windowsPackage);
}

void ToolsFrameworkManager::Setup()
{
    m_documentManager->Setup();
}

std::shared_ptr<DocumentManager> ToolsFrameworkManager::GetDocumentManager() const
{
    return m_documentManager;
}
