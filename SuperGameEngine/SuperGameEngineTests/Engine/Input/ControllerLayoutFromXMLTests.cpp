#include "../../LibraryIncludes.h"
#include "../../../SuperGameEngine/Engine/Input/ControllerLayoutFromXML.h"

using namespace StandardCLibrary;
using namespace SuperGameEngine;

namespace SuperGameEngine_Engine_Input_ControllerLayoutFromXMLTests
{
    TEST(ControllerLayoutFromXMLTests, OnConstruction)
    {
        std::string expected = "";

        FString actual = FString();

        EXPECT_TRUE(actual == expected) << "Expected: " << expected << " Actual: " << actual.AsStdString();
    }
}