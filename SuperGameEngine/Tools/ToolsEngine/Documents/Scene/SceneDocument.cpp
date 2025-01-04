#include "SceneDocument.h"
#include "../../../FatedQuestLibraries.h"
#include "../../../../../FatedQuest.Libraries/StoredDocument/ModifiableDocument.h"
#include "../../../../../FatedQuest.Libraries/StoredDocument/Converters/SimpleDocumentToXml.h"
#include "../../../../../FatedQuest.Libraries/XmlDocument/RapidXMLDocument.h"

namespace FatedQuestLibraries
{
    class DocumentToXml;
}

using namespace FatedQuestLibraries;
using namespace SuperGameTools;

bool SceneDocument::Load()
{
    std::string path = File::Sanitize(m_filePath);
    if (!m_gamePackage->File()->Exists(path))
    {
        Log::Error("File does not exist. Filepath: " + path,
            "SceneDocument::Load");
        return false;
    }

    std::string contents = m_gamePackage->File()->ReadFileContents(path);
    if (contents.empty())
    {
        Log::Error("Could not read file contents. Filepath: " + path,
            "SceneDocument::Load");
        return false;
    }

    auto rapidDocument = std::make_shared<RapidXMLDocument>();
    if (!rapidDocument->Load(contents))
    {
        Log::Error("Could not load XML for file. Filepath: " + path,
            "SceneDocument::Load");
        return false;
    }

    auto modifiableDocument = std::make_shared<ModifiableDocument>();
    if (!modifiableDocument->Load(rapidDocument))
    {
        Log::Error("Could not transform a stored document into a modifiable document. Filepath: " + path,
            "SceneDocument::Load");
        return false;
    }

    m_storedDocument = modifiableDocument;
    return true;
}

bool SceneDocument::Save()
{
    std::shared_ptr<DocumentToXml> documentToXml = std::make_shared<SimpleDocumentToXml>();
    std::string fileContents = documentToXml->ConvertToXml(m_storedDocument);
    if (fileContents.empty())
    {
        Log::Error("File content was empty, potentially something corrupt. Path: " + m_filePath,
            "bool SceneDocument::Save()");
        return false;
    }

    const std::string fullPath = Directory::CombinePath(m_productsPath, m_filePath);
    if (!File::WriteLine(fullPath, fileContents))
    {
        Log::Error("Could not write file. Path: " + fullPath,
            "bool SceneDocument::Save()");
        return false;
    }

    return true;
}

bool SceneDocument::IsDocument(const std::string& path) const
{
    return File::EndInExtension(path,".scene");
}

bool SceneDocument::IsDocument(const std::string& path, const std::weak_ptr<StoredDocument>& documentContents) const
{
    return File::EndInExtension(path, ".scene");
}

std::shared_ptr<ModifiableDocument> SceneDocument::GetDocument() const
{
    return m_storedDocument;
}
