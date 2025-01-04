#include "ModifiableDocument.h"

#include "ModifiableNode.h"
#include "../Logger/Logger/Log.h"

using namespace FatedQuestLibraries;

bool ModifiableDocument::LoadFromFile(const std::string& path)
{
    throw std::exception("ModifiableDocument::LoadFromFile(std::string) is not implemented and"
                         " cannot be implemented as there is no type.");
}

bool ModifiableDocument::Load(const std::string& fileContents)
{
    throw std::exception("ModifiableDocument::Load(std::string) is not implemented and "
                         "cannot be implemented as there is no type.");
}

bool ModifiableDocument::Load(const std::shared_ptr<StoredDocument>& storedDocument)
{
    if (!storedDocument)
    {
        Log::Error("Document does not exist.",
            "ModifiableDocument::Load(std::shared_ptr<StoredDocument>)");
        return false;
    }

    if (!storedDocument->GetRoot())
    {
        Log::Error("Document did not have a root.",
            "ModifiableDocument::Load(std::shared_ptr<StoredDocument>)");
        return false;
    }

    auto modNode = std::make_shared<ModifiableNode>();
    if (modNode->Load(storedDocument->GetRoot()))
    {
        m_root = modNode;
    }
    else
    {
        Log::Error("Could not parse root stored node into a modifiable node.",
            "ModifiableDocument::Load(std::shared_ptr<StoredDocument>)");
        return false;
    }

    return true;
}

std::shared_ptr<StoredDocumentNode> ModifiableDocument::GetRoot()
{
    return m_root;
}

std::shared_ptr<ModifiableNode> ModifiableDocument::GetModifiableRoot()
{
    return m_root;
}

void ModifiableDocument::SetRootElement(const std::shared_ptr<StoredDocumentNode>& rootDocument)
{
    auto modNode = std::make_shared<ModifiableNode>();
    if (modNode->Load(rootDocument))
    {
        m_root = modNode;
    }
    else
    {
        Log::Error("Could not parse root stored node into a modifiable node.",
            "ModifiableDocument::SetRootElement(std::shared_ptr<StoredDocumentNode>)");
    }
}

void ModifiableDocument::SetRootElement(const std::shared_ptr<ModifiableNode>& rootNode)
{
    m_root = rootNode;
}
