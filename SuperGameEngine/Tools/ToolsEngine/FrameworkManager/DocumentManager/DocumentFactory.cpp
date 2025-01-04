#include "DocumentFactory.h"
#include "DocumentCriteria.h"
#include "DocumentMatcher.h"
#include "../../../FatedQuestLibraries.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

void DocumentFactory::RegisterDocument(
    const std::shared_ptr<DocumentMatcher>& matcher,
    const std::function<std::shared_ptr<Document>()>& constructor)
{
    GetMap()[matcher] = constructor;
}

std::shared_ptr<Document> DocumentFactory::CreateDocument(const DocumentCriteria& criteria)
{
    std::string path = criteria.FilePath;
    std::weak_ptr<StoredDocument> contents = criteria.Document;

    bool testContents = false;
    if (contents.lock())
    {
        testContents = true;
    }

    for (auto documentConstructors : GetMap())
    {
        bool isDocument = false;
        if (testContents)
        {
            isDocument = documentConstructors.first->IsDocument(path, contents);
        }
        else
        {
            isDocument = documentConstructors.first->IsDocument(path);
        }

        if (isDocument)
        {
            return documentConstructors.second();
        }
    }

    return {};
}
