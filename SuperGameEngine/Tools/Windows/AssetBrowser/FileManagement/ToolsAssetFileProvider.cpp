#include "ToolsAssetFileProvider.h"

#include <mutex>

#include "../../../FatedQuestLibraries.h"

#include <string>

#include "PackageFilesHaveUpdatedEventArguments.h"
#include "ToolsAssetFolder.h"
#include "Engine/FileSystem/FileWatcher/FileUpdateEventArguments.h"
#include "Engine/FileSystem/FileWatcher/ToolsFileWatcher.h"

using namespace SuperGameEngine;
using namespace SuperGameTools;
using namespace FatedQuestLibraries;

ToolsAssetFileProvider::ToolsAssetFileProvider(
    const std::weak_ptr<GamePackage>& package,
    const std::weak_ptr<TextureManager>& texture,
    const std::shared_ptr<PackagePaths>& packagePaths)
{
    m_gamePackage = package;
    m_textureManager = texture;
    m_packagePaths = packagePaths;
    m_reloadPackage.store(false, std::memory_order_relaxed);

    auto folder = std::make_shared<ToolsAssetFolder>(package, texture, "");
    m_rootFolder = folder;
    folder->PopulateChildren({});

    m_watcherSubscription = {};
    m_onFileSystemUpdated = std::make_shared<FEvent>();
}

ToolsAssetFileProvider::~ToolsAssetFileProvider()
{
    if (std::shared_ptr<FEventSubscriptions> subscription = m_watcherSubscription.lock())
    {
        subscription->Unsubscribe(shared_from_this());
    }
}

void ToolsAssetFileProvider::Update()
{
    if (!m_watcherSubscription.lock())
    {
        m_fileWatcher = std::make_shared<ToolsFileWatcher>(m_packagePaths);
        m_watcherSubscription = m_fileWatcher->WatchFolder("");
        if (std::shared_ptr<FEventSubscriptions> subscription = m_watcherSubscription.lock())
        {
            subscription->Subscribe(shared_from_this());
            Log::Info("Subscribed to FileWatcher.", "ToolsAssetFileProvider::Update");
            m_fileWatcher->Start();
        }
    }

    if (!m_reloadPackage.load(std::memory_order_relaxed))
    {
        return;
    }

    if (std::shared_ptr<FatedQuestLibraries::GamePackage> gamePackage = m_gamePackage.lock())
    {
        //std::unique_lock lock(gamePackage);
        if (!gamePackage->Reload())
        {
            Log::Error("Could not reload GamePackage.", "ToolsAssetFileProvider::Update");
            return;
        }

        m_rootFolder->PopulateChildren({});

        auto packageUpdate = std::make_shared<PackageFilesHaveUpdatedEventArguments>(m_rootFolder);
        m_onFileSystemUpdated->Invoke(packageUpdate);
    }
    else
    {
        Log::Error("Lost a pointer to GamePackage.", "ToolsAssetFileProvider::Update");
    }

    m_reloadPackage.store(false, std::memory_order_relaxed);
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
        m_reloadPackage.store(true, std::memory_order_relaxed);
    }
}
