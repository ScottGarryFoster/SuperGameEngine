#include "GenerateEnumConverter.h"

#include "SuperEnumConverter.h"
#include "../../FatedQuest.Libraries/StandardOperations/AllReferences.h"
#include "../../FatedQuest.Libraries/Logger/AllReferences.h"

using namespace SuperEnumGenerator;
using namespace FatedQuestLibraries;

bool GenerateEnumConverter::SingleFile(
    const std::string& enumFilepath, 
    const std::string& outputPath, 
    const std::string& currentFolder) const
{
    if (!File::Exists(enumFilepath))
    {
        Log::Error("File not found. Path: " + enumFilepath,
            "GenerateEnumConverter::SingleFile(std::string, std::string)");
        return false;
    }

    if (!File::Exists(outputPath))
    {
        if (!File::WriteLine(outputPath, ""))
        {
            Log::Error("Could not create file. Path: " + enumFilepath,
                "GenerateEnumConverter::SingleFile(std::string, std::string)");
            return false;
        }
    }

    std::string enumFileContents = File::ReadFileContents(enumFilepath);
    if (enumFileContents == "")
    {
        Log::Error("Could not open file. Path: " + enumFilepath,
            "GenerateEnumConverter::SingleFile(std::string, std::string)");
        return false;
    }

    std::shared_ptr<SuperEnumConverter> superEnum = std::make_shared<SuperEnumConverter>();
    if (!superEnum->FromString(enumFileContents, Directory::CombinePath(currentFolder, File::GetFilename(enumFilepath))))
    {
        Log::Error("Could not parse enum file. Path: " + enumFilepath,
            "GenerateEnumConverter::SingleFile(std::string, std::string)");
        return false;
    }

    std::string enumContents = superEnum->ToString();
    if (!FatedQuestLibraries::File::WriteLine(outputPath, enumContents))
    {
        FatedQuestLibraries::Log::Error("Could not create file. Path: " + outputPath,
                                        "GenerateEnumConverter::SingleFile(std::string, std::string)");
        return false;
    }

    return true;
}

void GenerateEnumConverter::AllEnums(
    const std::string& topLevel, 
    const std::string& superEnumExtension, 
    const std::string& destinationExtension, 
    const std::string& currentFolder) const
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
        if (SingleFile(fullFilePath, headerFilepath, currentFolder))
        {
            Log::Info("Generated: " + fullFilePath);
        }
        else
        {
            Log::Error("Enum converter not generated. From: " + fullFilePath + " to " + headerFilepath,
                "GenerateEnumConverter::AllEnums(const std::string&,const std::string&,const std::string&,const std::string&)");
        }
    }

    std::vector<std::string> directories = Directory::ListDirectoryNames(topLevel);
    for (const std::string& directoryName : directories)
    {
        std::string folder = Directory::CombinePath(currentFolder, directoryName);
        std::string newTopLevel = Directory::CombinePath(topLevel, directoryName);
        AllEnums(newTopLevel, superEnumExtension, destinationExtension, folder);
    }
}
