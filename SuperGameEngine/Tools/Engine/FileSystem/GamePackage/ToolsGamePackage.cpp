#include "ToolsGamePackage.h"

#include "ToolsGamePackageFileSystem.h"
#include "../../../../../FatedQuest.Libraries/BinaryOperations/BinaryZip/StandardBinaryZip.h"

SuperGameTools::ToolsGamePackage::ToolsGamePackage()
{
    m_binaryZip = std::make_shared<FatedQuestLibraries::StandardBinaryZip>();
    m_fileSystem = std::make_shared<ToolsGamePackageFileSystem>();
}
