#include "ToolsAssetFileProvider.h"

#include <mutex>

#include "../../../FatedQuestLibraries.h"

#include <string>

#include "PackageFilesHaveUpdatedEventArguments.h"
#include "ToolsAssetFolder.h"
#include "../../../../../FatedQuest.Libraries/XmlDocument/RapidXMLDocument.h"
#include "Engine/FileSystem/FileWatcher/FileUpdateEventArguments.h"
#include "Engine/FileSystem/FileWatcher/ToolsFileWatcher.h"
#include "Engine/Structural/Asset/AssetTemplateProvider.h"
#include "Engine/Structural/Asset/Template/AssetTemplate.h"
#include "Engine/Structural/Asset/Template/ToolsAssetMetaData.h"

using namespace SuperGameEngine;
using namespace SuperGameTools;
using namespace FatedQuestLibraries;

ToolsAssetFileProvider::ToolsAssetFileProvider(
    const std::weak_ptr<GamePackage>& package,
    const std::weak_ptr<TextureManager>& texture,
    const std::shared_ptr<PackagePaths>& packagePaths,
    const std::shared_ptr<AssetTemplateProvider>& assetTemplateProvider)
{
    m_gamePackage = package;
    m_textureManager = texture;
    m_packagePaths = packagePaths;
    m_assetTemplateProvider = assetTemplateProvider;

    SearchAllFilesForPotentialMissingAssetFiles();
    if (std::shared_ptr<GamePackage> gamePackage = package.lock())
    {
        gamePackage->Reload();
    }

    auto folder = std::make_shared<ToolsAssetFolder>(package, texture, "");
    m_rootFolder = folder;
    folder->PopulateChildren({});

    m_watcherSubscription = {};
    m_onFileSystemUpdated = std::make_shared<FEvent>();
}

ToolsAssetFileProvider::~ToolsAssetFileProvider()
{
    // Do not need to unsub to watcher. This will resolve itself at the event level.
}

void ToolsAssetFileProvider::Update()
{
    ListenToFilePackageChanges();
    ProcessFilePackageChanges();
}

std::vector<std::shared_ptr<AssetFolder>> ToolsAssetFileProvider::GetFoldersInRootDirectory() const
{
    return m_rootFolder->GetContainingFolders();
}

std::vector<std::shared_ptr<AssetFile>> ToolsAssetFileProvider::GetFilesInRootDirectory() const
{
    return m_rootFolder->GetContainingFiles();
}

std::shared_ptr<AssetFolder> ToolsAssetFileProvider::GetRootFolder() const
{
    return m_rootFolder;
}

std::weak_ptr<FEventSubscriptions> ToolsAssetFileProvider::OnFileSystemUpdated() const
{
    return m_onFileSystemUpdated;
}

void ToolsAssetFileProvider::Invoke(std::shared_ptr<FEventArguments> arguments)
{
    if (std::shared_ptr<FileUpdateEventArguments> fileUpdateEventArguments = 
        std::dynamic_pointer_cast<FileUpdateEventArguments>(arguments))
    {
        // We should run this on the main thread to avoid threading conflicts.
        m_reloadPackageQueueLock.lock();
        m_reloadPackageQueue.push(fileUpdateEventArguments);
        m_reloadPackageQueueLock.unlock();
    }
}

void ToolsAssetFileProvider::SearchAllFilesForPotentialMissingAssetFiles()
{
    std::shared_ptr<GamePackage> gamePackage = m_gamePackage.lock();
    if (!gamePackage)
    {
        Log::Error("No game package given. Cannot create asset files.",
            "ToolsAssetFileProvider::SearchAllFilesForPotentialMissingAssetFiles");
        return;
    }

    SearchAllFilesForPotentialMissingAssetFiles(gamePackage, {});
}

void ToolsAssetFileProvider::SearchAllFilesForPotentialMissingAssetFiles(const std::shared_ptr<GamePackage>& gamePackage, const std::string& currentDirectory)
{

    std::vector<std::string> filenames = gamePackage->Directory()->GetFiles(currentDirectory);
    for (const std::string& filename : filenames)
    {
        std::string gamePackagePath = Directory::CombinePath(currentDirectory, filename);
        TryAddAssetFile(gamePackage, gamePackagePath);
    }

    std::vector<std::string> directories = gamePackage->Directory()->ListDirectories(currentDirectory);
    for (const std::string& directory : directories)
    {
        SearchAllFilesForPotentialMissingAssetFiles(gamePackage, directory);
    }
}

void ToolsAssetFileProvider::CreateAssetFilesForValidAssets()
{

}

bool ToolsAssetFileProvider::TryFindAssetFileTemplate(const std::string& packagePath, std::string& assetFileContents)
{
    for (const std::shared_ptr<const AssetMetaData>& metaData : m_assetTemplateProvider->GetAssetTemplates())
    {
        if (metaData->GetTemplate())
        {
            if (metaData->GetTemplate()->ShouldUseTemplate(packagePath))
            {
                assetFileContents = metaData->GetTemplate()->CreateAssetFile(packagePath);
                return true;
            }
        }
    }

    return false;
}

void ToolsAssetFileProvider::TryAddAssetFile(
    const std::shared_ptr<GamePackage>& gamePackage,
    const std::string& packagePath)
{
    std::string extension = StringHelpers::ToLower(File::GetExtension(packagePath));
    if (extension != ".ast")
    {
        std::string assetFilepath = packagePath + ".ast";
        if (!gamePackage->File()->Exists(assetFilepath))
        {
            // There is a file without an asset file and we are not an asset file.
            std::string newFileContents = {};
            if (TryFindAssetFileTemplate(packagePath, newFileContents))
            {
                std::string fullpath = Directory::CombinePath(m_packagePaths->ProductsDirectory(), m_packagePaths->ProductsDirectoryName(), assetFilepath);
                File::WriteLine(fullpath, newFileContents);

                // In next commit create these files.
                Log::Info("Written asset: " + assetFilepath);
            }
        }
    }
}

void ToolsAssetFileProvider::ListenToFilePackageChanges()
{
    if (!m_watcherSubscription.lock())
    {
        m_fileWatcher = std::make_shared<ToolsFileWatcher>(m_packagePaths);
        m_watcherSubscription = m_fileWatcher->WatchFolder("");
        if (std::shared_ptr<FEventSubscriptions> subscription = m_watcherSubscription.lock())
        {
            subscription->Subscribe(shared_from_this());
            Log::Info("Subscribed to FileWatcher.", "ToolsAssetFileProvider::ListenToFilePackageChanges");
            m_fileWatcher->Start();
        }
    }
}

void ToolsAssetFileProvider::ProcessFilePackageChanges()
{
    m_reloadPackageQueueLock.lock();
    if (m_reloadPackageQueue.empty())
    {
        m_reloadPackageQueueLock.unlock();
        return;
    }
    m_reloadPackageQueueLock.unlock();

    if (std::shared_ptr<GamePackage> gamePackage = m_gamePackage.lock())
    {
        //std::unique_lock lock(gamePackage);
        if (!gamePackage->Reload())
        {
            Log::Error("Could not reload GamePackage.", "ToolsAssetFileProvider::ProcessFilePackageChanges");
            return;
        }

        m_reloadPackageQueueLock.lock();
        std::shared_ptr<FileUpdateEventArguments> arguments = m_reloadPackageQueue.front();
        m_reloadPackageQueue.pop();
        m_reloadPackageQueueLock.unlock();

        for (const std::string& path : arguments->GetFilesAdded())
        {
            TryAddAssetFile(gamePackage, path);
        }

        if (!arguments->GetFilesAdded().empty() && !gamePackage->Reload())
        {
            Log::Error("Could not reload GamePackage.", "ToolsAssetFileProvider::ProcessFilePackageChanges");
            return;
        }

        m_rootFolder->PopulateChildren({});

        auto packageUpdate = std::make_shared<PackageFilesHaveUpdatedEventArguments>(m_rootFolder);
        m_onFileSystemUpdated->Invoke(packageUpdate);
    }
    else
    {
        Log::Error("Lost a pointer to GamePackage.", "ToolsAssetFileProvider::ProcessFilePackageChanges");
    }
}
