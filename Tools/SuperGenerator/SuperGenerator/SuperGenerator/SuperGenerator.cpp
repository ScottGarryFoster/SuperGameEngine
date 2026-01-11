// EnumGenerator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "DebugLogger.h"
#include "GenerateEnumConverter.h"
#include "SingleEnum.h"
#include "../../../../FatedQuest.Libraries/Logger/Logger/Log.h"
#include "../../../../FatedQuest.Libraries/Observer/FEventSubscriptions.h"
#include "../../../../FatedQuest.Libraries/StandardOperations/FileHandling/File.h"
#include "../SuperEnumGenerator/GenerateEnum.h"
#include "../../../../FatedQuest.Libraries/StandardOperations/AllReferences.h"

using namespace SuperEnumGenerator;

int main(int argc, char* args[])
{
    std::cout << "Super Generator!\n";

    auto debugLogger = std::make_shared<DebugLogger>();
    if (auto event = Log::GetEvent().lock())
    {
        event->Subscribe(debugLogger);
    }

    std::string repoDirectory = FilePaths::RepositoryDirectory();
    {
        Log::Info("Generating with: " + repoDirectory);

        GenerateEnum generator;
        generator.AllEnums(repoDirectory, ".superenum", ".h", {});
        Log::Info("Generated Enums");
    }

    {
        Log::Info("Generating enum converters with " + repoDirectory);

        GenerateEnumConverter generator;
        generator.AllEnums(repoDirectory, ".superenumconverter", ".h", {});
        Log::Info("Generated Enums");
    }

    return 0;
}