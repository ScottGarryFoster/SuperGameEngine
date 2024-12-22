#include "PackageFiles.h"

#include <utility>

using namespace FatedQuestLibraries;

std::vector<std::shared_ptr<PackageFile>> PackageFiles::GetFiles() const
{
    return m_packageFile;
}

void PackageFiles::SetFiles(const std::vector<std::shared_ptr<PackageFile>>& files)
{
    m_packageFile = files;
}
