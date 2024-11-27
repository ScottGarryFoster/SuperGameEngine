#include "GenerateEnum.h"
#include "FatedQuestLibraries.h"
#include "SuperEnum.h"

using namespace SuperEnumGenerator;
using namespace FatedQuestLibraries;

bool GenerateEnum::SingleFile(const std::string& enumFilepath, const std::string& outputPath) const
{
    if (!File::Exists(enumFilepath))
    {
#ifdef _DEBUG
        std::cout << "GenerateEnum::SingleFile: File not found " << enumFilepath << std::endl;
#endif // _DEBUG
        return false;
    }

    if (!File::Exists(outputPath))
    {
        if (!File::WriteLine(outputPath, ""))
        {
#ifdef _DEBUG
            std::cout << "GenerateEnum::SingleFile: Could not create file " << outputPath << std::endl;
#endif // _DEBUG
            return false;
        }
    }

    std::string enumFileContents = File::ReadFileContents(enumFilepath);
    if (enumFileContents == "")
    {
#ifdef _DEBUG
        std::cout << "GenerateEnum::SingleFile: Could not open file " << enumFilepath << std::endl;
#endif // _DEBUG
        return false;
    }

    std::shared_ptr<SuperEnum> superEnum = std::make_shared<SuperEnum>();
    if (!superEnum->FromString(enumFileContents))
    {
#ifdef _DEBUG
        std::cout << "GenerateEnum::SingleFile: Could not parse enum file " << enumFilepath << std::endl;
#endif // _DEBUG
        return false;
    }

    std::string enumContents = superEnum->ToString();
    if (!File::WriteLine(outputPath, enumContents))
    {
#ifdef _DEBUG
        std::cout << "GenerateEnum::SingleFile: Could not create file " << outputPath << std::endl;
#endif // _DEBUG
        return false;
    }

    return true;
}
