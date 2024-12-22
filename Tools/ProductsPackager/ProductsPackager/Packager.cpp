#include "Packager.h"
#include "FatedQuestReferences.h"
#include "../../../FatedQuest.Libraries/BinaryOperations/BinaryZip/StandardBinaryZip.h"

using namespace ProductsPackager;
using namespace FatedQuestLibraries;

Packager::Packager()
{
    m_binaryZip = std::make_shared<StandardBinaryZip>();
}

Packager::~Packager()
{
}

bool Packager::PackageProductFolder(
    const std::string& fullPathFrom, 
    const std::string& fullPathTo,
    PackageFileType fileType)
{
    if (!Directory::Exists(fullPathFrom))
    {
#ifdef _DEBUG
        std::cout << "Packager::PackageProductFolder: Directory not found " << fullPathFrom << std::endl;
#endif // _DEBUG
        return false;
    }

    std::string parent = Directory::GetParent(fullPathTo);
    if (!Directory::Exists(parent))
    {
#ifdef _DEBUG
        std::cout << "Packager::PackageProductFolder: Parent of fullPathTo not found " << fullPathTo << std::endl;
#endif // _DEBUG
        return false;
    }

    std::vector<std::string> errors;
    bool answer = false;
    if (fileType == PackageFileType::Binary)
    {
        answer = m_binaryZip->DirectoryToZipWithFileToBinary(fullPathFrom, fullPathTo, errors);
    }
    else
    {
        answer = m_binaryZip->DirectoryToZip(fullPathFrom, fullPathTo, errors);
    }

    if (!answer)
    {
#ifdef _DEBUG
        for (const std::string& error : errors)
        {
            std::cout << "Packager::PackageProductFolder: " << error << "\n";
        }
#endif // _DEBUG
        return false;
    }

    return true;
}
