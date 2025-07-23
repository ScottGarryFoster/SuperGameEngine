#include "ToolsGamePackageFileSystem.h"

#include "ToolsGamePackageFileSystemDirectory.h"
#include "../../../../../FatedQuest.Libraries/GamePackage/GamePackage/FileSystem/PackageFiles.h"


using namespace SuperGameTools;
ToolsGamePackageFileSystem::ToolsGamePackageFileSystem()
{
    m_packageFiles = std::make_shared<FatedQuestLibraries::PackageFiles>();
    m_fileSystem = std::make_shared<FatedQuestLibraries::GamePackageFileSystemFile>(m_packageFiles);
    m_directorySystem = std::make_shared<ToolsGamePackageFileSystemDirectory>(m_packageFiles);
}
