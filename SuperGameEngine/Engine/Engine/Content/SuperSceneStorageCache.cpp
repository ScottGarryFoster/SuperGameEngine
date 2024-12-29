#include "SuperSceneStorageCache.h"
#include "../../FatedQuestReferences.h"
#include "../../../../FatedQuest.Libraries/XmlDocument/RapidXMLDocument.h"
#include "../../Structural/Loaders/SceneLoader.h"

using namespace SuperGameEngine;
using namespace FatedQuestLibraries;

void SuperSceneStorageCache::Setup(const std::shared_ptr<SceneLoader>& sceneLoader,
    const std::shared_ptr<GamePackage>& gamePackage)
{
    m_sceneLoader = sceneLoader;
    m_gamePackage = gamePackage;
}

std::shared_ptr<Scene> SuperSceneStorageCache::GetScene(const std::string& filePath)
{
    std::string path = File::Sanitize(filePath);

    std::shared_ptr<StoredDocument> storedDocument;
    if (m_sceneFileCache.contains(filePath))
    {
        storedDocument = m_sceneFileCache.at(filePath);
    }
    else
    {
        storedDocument = LoadFromFileDirectly(filePath);
        if (storedDocument)
        {
            m_sceneFileCache.insert_or_assign(filePath, storedDocument);
        }
    }

    // Errors should fire in their respective loaders.
    if (!storedDocument)
    {
        return {};
    }

    std::shared_ptr<Scene> scene = m_sceneLoader->Load(storedDocument);
    if (!scene)
    {
        Log::Error("Could not create scene from stored document. File path: " + filePath,
            "SuperSceneStorageCache::GetScene(std::string)");
        m_sceneFileCache.erase(filePath);
    }

    return scene;
}

bool SuperSceneStorageCache::SaveScene(const std::shared_ptr<Scene>& scene, const std::string& filePath)
{
    std::string path = File::Sanitize(filePath);

    std::shared_ptr<StoredDocument> document = m_sceneLoader->Save(scene);
    if (!document)
    {
        Log::Error("Could not save scene from file. File path: " + filePath, 
            "SuperSceneStorageCache::SaveScene(std::shared_ptr<Scene>,std::string)");
        return false;
    }

    if (m_sceneFileCache.contains(filePath))
    {
        m_sceneFileCache.at(filePath) = document;
    }
    else
    {
        m_sceneFileCache.insert_or_assign(filePath, document);
    }

    return true;
}

std::shared_ptr<StoredDocument> SuperSceneStorageCache::LoadFromFileDirectly(const std::string& filePath) const
{
    // Do not bother if the file is invalid.
    if (!m_gamePackage->File()->Exists(filePath))
    {
        Log::Error("Could not load scene file from contents. File did not exist. "
                   "Path: " + filePath, "SuperSceneStorageCache::LoadFromFileDirectly(std::string)");
        return {};
    }

    std::string fileContents = m_gamePackage->File()->ReadFileContents(filePath);
    std::shared_ptr<StoredDocument> xml = std::make_shared<RapidXMLDocument>();
    if (!xml->Load(fileContents))
    {
        Log::Error("Could not load scene file from contents. File existed contents was corrupt. "
                   "Path: " + filePath, "SuperSceneStorageCache::LoadFromFileDirectly(std::string)");
        return {};
    }

    return xml;
}
