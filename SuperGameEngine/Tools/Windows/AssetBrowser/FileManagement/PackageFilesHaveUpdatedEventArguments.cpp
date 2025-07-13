#include "PackageFilesHaveUpdatedEventArguments.h"

using namespace SuperGameTools;

PackageFilesHaveUpdatedEventArguments::PackageFilesHaveUpdatedEventArguments(
    const std::shared_ptr<AssetFolder>& root)
{
    m_rootFolder = root;
}

std::shared_ptr<AssetFolder> PackageFilesHaveUpdatedEventArguments::GetNewRoot()
{
    return m_rootFolder;
}
