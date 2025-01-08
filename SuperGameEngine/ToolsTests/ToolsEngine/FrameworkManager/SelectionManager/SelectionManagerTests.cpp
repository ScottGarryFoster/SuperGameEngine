#include "../../../../Tools/ToolsEngine/FrameworkManager/SelectionManager/ToolsSelectionManager.h"
#include "../../../../Tools/FatedQuestLibraries.h"
#include <gtest/gtest.h>
#include <memory>

#include "SelectableStub.h"
#include "../../../../Engine/DebugEngine/DebugLogger.h"

using namespace SuperGameTools;
using namespace SuperGameToolsTests;
using namespace FatedQuestLibraries;

namespace ToolsTests_ToolsEngine_FrameworkManager
{
    class SelectionManagerTests : public ::testing::Test
    {
    public:
        SelectionManagerTests()
        {
        }

    protected:

        std::shared_ptr<SelectionManager> m_selectionManager;
        std::shared_ptr<SuperGameEngine::DebugLogger> m_logger;

        void SetUp() override
        {
            m_selectionManager = std::make_shared<ToolsSelectionManager>();

            m_logger = std::make_shared<SuperGameEngine::DebugLogger>();
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

    TEST_F(SelectionManagerTests, GetSelection_ReturnsSelection_WhenAddedToGroupWhenUsingSingleGroup)
    {
        // Arrange
        SelectionGroup givenGroup = SelectionGroup::Inspectable;
        auto givenSelection = std::make_shared<SelectableStub>(SelectionGroup::Inspectable);
        m_selectionManager->AddToSelection(givenSelection);

        // Act
        std::vector<std::weak_ptr<Selectable>> actual = m_selectionManager->GetSelection(givenGroup);

        // Assert
        ASSERT_EQ(1, actual.size()) << "The correct number of selectables was not found.";
        auto shared = actual.at(0).lock();
        ASSERT_TRUE(shared) << "Pointer to selection did not exist.";
        ASSERT_EQ(givenSelection->m_guid, shared->GetGuid()) << "Guids did not match. ";
    }
}
