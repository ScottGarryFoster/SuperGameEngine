#include "SceneDocument.h"
#include "../../../FatedQuestLibraries.h"

using namespace FatedQuestLibraries;
using namespace SuperGameTools;

bool SceneDocument::IsDocument(const std::string& path) const
{
    return File::EndInExtension(path,".scene");
}

bool SceneDocument::IsDocument(const std::string& path, const std::weak_ptr<StoredDocument>& documentContents) const
{
    return File::EndInExtension(path, ".scene");
}
