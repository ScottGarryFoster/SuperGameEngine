#include "ToolsDocument.h"
#include "../../../FatedQuestLibraries.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

void ToolsDocument::Setup(const std::string& filepath, const std::weak_ptr<WindowPackage>& windowsPackage)
{
    m_windowsPackage = windowsPackage;
    m_filePath = filepath;
    m_fileName = File::GetFilename(m_filePath);
}

std::string ToolsDocument::GetFilepath() const
{
    return m_filePath;
}

std::string ToolsDocument::GetFilename() const
{
    return m_fileName;
}
