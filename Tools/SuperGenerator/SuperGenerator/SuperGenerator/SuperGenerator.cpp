// EnumGenerator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "DebugLogger.h"
#include "SingleEnum.h"
#include "../../../../FatedQuest.Libraries/Logger/Logger/Log.h"
#include "../../../../FatedQuest.Libraries/Observer/FEventSubscriptions.h"
#include "../../../../FatedQuest.Libraries/StandardOperations/FileHandling/File.h"
#include "../SuperEnumGenerator/GenerateEnum.h"

using namespace SuperEnumGenerator;

int main(int argc, char* args[])
{
    std::cout << "Super Generator!\n";

    auto debugLogger = std::make_shared<DebugLogger>();
    if (auto event = Log::GetEvent().lock())
    {
        event->Subscribe(debugLogger);
    }

    GenerateEnum generator;
    generator.AllEnums("E:\\Development\\SuperGameEngine-Myriad\\", ".superenum", ".h");
    Log::Info("Generated Enums");



    //std::string lines;
    //std::vector<SuperGameInput::MouseWheelDirection> codes = SuperGameInput::EMouseWheelDirection::ToVector();
    //for (const SuperGameInput::MouseWheelDirection& code : codes)
    //{
    //    std::string enumByName = SuperGameInput::EMouseWheelDirection::ToString(code);
    //    lines += "case " + enumByName + ": return WindowUpdateEventID::" + enumByName + ";\n";
    //}

    //File::WriteLine("D:\\enum.txt", lines);

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
