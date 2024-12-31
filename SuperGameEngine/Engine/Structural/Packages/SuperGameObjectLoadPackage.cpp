#include "SuperGameObjectLoadPackage.h"

#include <utility>

#include "SuperComponentLoadPackage.h"

using namespace SuperGameEngine;

std::shared_ptr<ContentManager> SuperGameObjectLoadPackage::GetContentManager() const
{
    return m_contentManager;
}

void SuperGameObjectLoadPackage::SetContentManager(std::shared_ptr<ContentManager> contentManager)
{
    m_contentManager = std::move(contentManager);
    AttemptToCreateAComponentLoadPackage();
}

std::shared_ptr<SerializableParser> SuperGameObjectLoadPackage::GetParser() const
{
    return m_serializableParser;
}

void SuperGameObjectLoadPackage::SetSerializableParser(const std::shared_ptr<SerializableParser>& serializableParser)
{
    m_serializableParser = serializableParser;
    AttemptToCreateAComponentLoadPackage();
}

std::shared_ptr<ComponentLoadPackage> SuperGameObjectLoadPackage::GetComponentLoadPackage() const
{
    return m_componentLoadPackage;
}

void SuperGameObjectLoadPackage::AttemptToCreateAComponentLoadPackage()
{
    if (m_contentManager || m_serializableParser)
    {
        auto sceneLoadPackage = std::make_shared<SuperComponentLoadPackage>();
        sceneLoadPackage->SetContentManager(m_contentManager);
        sceneLoadPackage->SetSerializableParser(m_serializableParser);

        m_componentLoadPackage = sceneLoadPackage;
    }
}
