#include "ToolsGamePackageFileSystemDirectory.h"
#include "../../../../../FatedQuest.Libraries/GamePackage/GamePackage/FileSystem/PackageFiles.h"
#include "../../../../../FatedQuest.Libraries/GamePackage/GamePackage/PackageFile.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

ToolsGamePackageFileSystemDirectory::ToolsGamePackageFileSystemDirectory(
    const std::shared_ptr<PackageFiles>& files) : GamePackageFileSystemDirectory(files)
{
}

void ToolsGamePackageFileSystemDirectory::AddPathToCollection(
    std::unordered_map<std::string, std::unordered_set<std::string>>& collection, const std::string& directory,
    const std::string& rawPath) const
{
    std::string pathWithCase = File::Sanitize(rawPath, CaseRespective::RetainExistingCase);
    std::vector<std::string> pathPieceWithCase = StringHelpers::Split(pathWithCase, "\\");
    AddToCollection(collection, directory, pathPieceWithCase.back());
}
