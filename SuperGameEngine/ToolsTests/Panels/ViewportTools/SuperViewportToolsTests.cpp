#include "../../../../Tools/FatedQuestLibraries.h"
#include "../../../Tools/Panels/ViewportTools/SuperViewportTools.h"
#include <gtest/gtest.h>
#include <memory>

#include "ToolsEngine/Packages/WindowPackage.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

namespace ToolsTests_Panels_ViewportTools
{
    class SuperViewportToolsTests : public ::testing::Test
    {
    public:
        SuperViewportToolsTests()
        {
        }

    protected:

        std::shared_ptr<ViewportTools> m_superViewportTools;
        std::shared_ptr<ConsoleLog> m_logger;

        void SetUp() override
        {
            auto windowPackage = std::make_shared<WindowPackage>();
            auto super = std::make_shared<SuperViewportTools>(windowPackage);
            super->Setup();
            m_superViewportTools = super;

            m_logger = std::make_shared<ConsoleLog>();
            if (auto shared = Log::GetEvent().lock())
            {
                shared->Subscribe(m_logger);
            }
        }

        void TearDown() override
        {
            if (auto shared = Log::GetEvent().lock())
            {
                shared->Unsubscribe(m_logger);
            }
        }
        
    };

    TEST_F(SuperViewportToolsTests, OnConstruction_GetSelectedTools_ReturnsSelect)
    {
        // Arrange
        auto expected = ViewportToolsType::Select;

        // Act
        ViewportToolsType actual = m_superViewportTools->GetSelectedTool();

        // Assert
        ASSERT_EQ(expected, actual);
    }

    TEST_F(SuperViewportToolsTests, GetSelectedTool_ReturnsLastSetTool_WhenSelectToolIsCalled)
    {
        // Arrange
        auto firstGiven = ViewportToolsType::Move;
        auto secondGiven = ViewportToolsType::Select;

        // Act
        m_superViewportTools->SelectTool(firstGiven);
        ViewportToolsType firstActual = m_superViewportTools->GetSelectedTool();

        m_superViewportTools->SelectTool(secondGiven);
        ViewportToolsType secondActual = m_superViewportTools->GetSelectedTool();

        // Assert
        ASSERT_EQ(firstGiven, firstActual);
        ASSERT_EQ(secondGiven, secondActual);
    }
}