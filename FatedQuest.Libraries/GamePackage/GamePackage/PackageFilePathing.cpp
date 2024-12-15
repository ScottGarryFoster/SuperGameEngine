#include "PackageFilePathing.h"
#include "../../StandardOperations/AllReferences.h"
#include <sstream>
#include "PackagePaths.h"

using namespace FatedQuestLibraries;

PackageFilePathing::PackageFilePathing(std::weak_ptr<PackagePaths> paths, std::string path)
{
    m_productPath = path;
    m_fullPath = "";

    if (const std::shared_ptr<PackagePaths> sharedPtr = paths.lock())
    {
        std::stringstream ss;
        ss << sharedPtr->ProductsDirectory() << File::Separator() << path;
        m_fullPath = ss.str();
    }

    std::filesystem::path productPath(m_productPath);
    std::vector<std::string> allSteps = StringHelpers::Split(productPath.string(), File::Separator());
    for (size_t i = 0; i < allSteps.size() - 1; ++i)
    {
        m_directories.push_back(allSteps.at(i));
    }

    if (!allSteps.empty())
    {
        m_fileName = allSteps.back();
    }
    else
    {
        m_fileName = path;
    }


    m_extension = "";
    std::vector<std::string> extension = StringHelpers::Split(m_fileName, ".");
    for (size_t i = 1; i < extension.size(); ++i)
    {
        if (m_extension.empty())
        {
            m_extension += extension.at(i);
        }
        else
        {
            m_extension += "." + extension.at(i);
        }
    }
}

std::string PackageFilePathing::Path() const
{
    return m_productPath;
}

std::vector<std::string> PackageFilePathing::PathByDirectory() const
{
    return m_directories;
}

bool PackageFilePathing::EndInExtension(const std::string& extension) const
{
    return m_extension == extension;
}

std::string PackageFilePathing::FileName() const
{
    return m_fileName;
}

std::string PackageFilePathing::Extension() const
{
    return m_extension;
}