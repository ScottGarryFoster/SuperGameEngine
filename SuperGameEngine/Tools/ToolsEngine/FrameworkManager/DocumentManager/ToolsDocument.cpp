#include "ToolsDocument.h"
#include "../../../FatedQuestLibraries.h"
#include "../../../../../FatedQuest.Libraries/GamePackage/AllReferences.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

void ToolsDocument::Setup(const std::string& filepath, const std::shared_ptr<GamePackage>& gamePackage,
    const std::shared_ptr<PackagePaths>& packagePaths)
{
    m_gamePackage = gamePackage;
    m_packagePaths = packagePaths;
    m_filePath = filepath;
    m_fileName = File::GetFilename(m_filePath);

    std::string productsDirectory = m_packagePaths->ProductsDirectory();
    std::string productsDirectoryName = m_packagePaths->ProductsDirectoryName();
    m_productsPath = Directory::CombinePath(productsDirectory, productsDirectoryName);
}

std::string ToolsDocument::GetFilepath() const
{
    return m_filePath;
}

std::string ToolsDocument::GetFilename() const
{
    return m_fileName;
}
