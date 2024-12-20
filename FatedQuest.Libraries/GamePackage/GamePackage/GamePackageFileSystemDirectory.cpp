#include "GamePackageFileSystemDirectory.h"

using namespace FatedQuestLibraries;

GamePackageFileSystemDirectory::GamePackageFileSystemDirectory(const std::shared_ptr<PackageFiles>& files)
{
}

GamePackageFileSystemDirectory::~GamePackageFileSystemDirectory()
{
}

bool GamePackageFileSystemDirectory::Exists(const std::string& path) const
{
    return false;
}

std::vector<std::string> GamePackageFileSystemDirectory::GetFiles(const std::string& path) const
{
    return {};
}

std::vector<std::string> GamePackageFileSystemDirectory::ListDirectories(const std::string& path) const
{
    return {};
}

std::vector<std::string> GamePackageFileSystemDirectory::ListDirectoryNames(const std::string& path) const
{
    return {};
}
