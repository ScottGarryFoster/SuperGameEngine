#include "ModifiableDocument.h"

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

std::shared_ptr<StoredDocumentNode> ModifiableDocument::GetRoot()
{
    return m_root;
}

void ModifiableDocument::SetRootElement(const std::shared_ptr<StoredDocumentNode>& rootDocument)
{
    m_root = rootDocument;
}
