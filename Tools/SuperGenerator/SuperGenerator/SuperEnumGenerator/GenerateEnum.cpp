#include "GenerateEnum.h"
#include "FatedQuestLibraries.h"
#include "SuperEnum.h"
#include "../../../../FatedQuest.Libraries/Logger/Logger/Log.h"

using namespace SuperEnumGenerator;
using namespace FatedQuestLibraries;

bool GenerateEnum::SingleFile(const std::string& enumFilepath, const std::string& outputPath) const
{
    if (!File::Exists(enumFilepath))
    {
        Log::Error("GenerateEnum::SingleFile: File not found. Path: " + enumFilepath,
            "GenerateEnum::SingleFile(std::string, std::string)");
        return false;
    }

    if (!File::Exists(outputPath))
    {
        if (!File::WriteLine(outputPath, ""))
        {
            Log::Error("GenerateEnum::SingleFile: Could not create file. Path: " + enumFilepath,
                "GenerateEnum::SingleFile(std::string, std::string)");
            return false;
        }
    }

    std::string enumFileContents = File::ReadFileContents(enumFilepath);
    if (enumFileContents == "")
    {
        Log::Error("GenerateEnum::SingleFile: Could not open file. Path: " + enumFilepath,
            "GenerateEnum::SingleFile(std::string, std::string)");
        return false;
    }

    std::shared_ptr<SuperEnum> superEnum = std::make_shared<SuperEnum>();
    if (!superEnum->FromString(enumFileContents))
    {
        Log::Error("GenerateEnum::SingleFile: Could not parse enum file. Path: " + enumFilepath,
            "GenerateEnum::SingleFile(std::string, std::string)");
        return false;
    }

    std::string enumContents = superEnum->ToString();
    if (!File::WriteLine(outputPath, enumContents))
    {
        Log::Error("GenerateEnum::SingleFile: Could not create file. Path: " + outputPath,
            "GenerateEnum::SingleFile(std::string, std::string)");
        return false;
    }

    return true;
}

void GenerateEnum::AllEnums(
    const std::string& topLevel, 
    const std::string& superEnumExtension,
    const std::string& destinationExtension) const
{
    std::vector<std::string> files = Directory::GetFiles(topLevel);
    for (const std::string& file : files)
    {
        if (!File::EndInExtension(file, superEnumExtension))
        {
            continue;
        }

        std::string fullFilePath = Directory::CombinePath(topLevel, file);
        std::string headerFilepath =
            File::ChangeExtension(fullFilePath, superEnumExtension, destinationExtension);
        if (!SingleFile(fullFilePath, headerFilepath))
        {
            Log::Error("Enum not generated. From: " + fullFilePath + " to " + headerFilepath,
                "GenerateEnum::GenerateEnums(std::string, std::string, std::string)");
        }
    }

    std::vector<std::string> directories = Directory::ListDirectories(topLevel);
    for (const std::string& directory : directories)
    {
        AllEnums(directory, superEnumExtension, destinationExtension);
    }
}