#include "SuperComponentLoadPackage.h"

#include <utility>

using namespace SuperGameEngine;

std::shared_ptr<ContentManager> SuperComponentLoadPackage::GetContentManager() const
{
    return m_contentManager;
}

void SuperComponentLoadPackage::SetContentManager(std::shared_ptr<ContentManager> contentManager)
{
    m_contentManager = std::move(contentManager);
}

std::shared_ptr<SerializableParser> SuperComponentLoadPackage::GetParser() const
{
    return m_serializableParser;
}

std::shared_ptr<InputHandler> SuperComponentLoadPackage::GetInput() const
{
    return m_inputHandler;
}

void SuperComponentLoadPackage::SetInputHandler(const std::shared_ptr<InputHandler>& inputHandler)
{
    m_inputHandler = inputHandler;
}

void SuperComponentLoadPackage::SetSerializableParser(const std::shared_ptr<SerializableParser>& serializableParser)
{
    m_serializableParser = serializableParser;
}
