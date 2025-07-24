#include <gtest/gtest.h>
#include "../../Exceptions/StackTrace/WindowsStackTrace.h"
#include "../../StandardOperations/Text/StringHelpers.h"
#include "Console/ConsoleLog.h"
#include "StackTrace/StackTraceLine.h"


using namespace FatedQuestLibraries;

namespace FatedQuestLibraries_Exceptions
{
    class WindowsStackTraceTests : public ::testing::Test
    {
    public:

        std::shared_ptr<ConsoleLog> m_logger;
        WindowsStackTraceTests()
        {
            m_logger = std::make_shared<ConsoleLog>();
            if (auto shared = Log::GetEvent().lock())
            {
                shared->Subscribe(m_logger);
            }
        }

    protected:

        void SetUp() override
        {
#ifndef _WINDOWS
            Log::Error("These tests must be run on the windows platform.",
                "WindowsStackTraceTests::SetUp");
#endif

        }

        void TearDown() override
        {

        }

    };

// If not run on windows all these will fail as we are testing the windows call stack
#ifdef _WINDOWS
    TEST_F(WindowsStackTraceTests, OnConstruction_TopLineContainsThisTest)
    {
        // Arrange
        const std::string testName = "OnConstruction_TopLineContainsThisTest";

        // Act
        auto stack = std::make_shared<WindowsStackTrace>();

        // Assert
        std::string name = stack->Lines().front()->GetName();
        ASSERT_FALSE(name.empty()) << "No name found";

        bool isTestFound = StringHelpers::Contains(testName, name);
        ASSERT_TRUE(isTestFound);
    }

#endif
}