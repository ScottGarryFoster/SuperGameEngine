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

#pragma region AddSelection GetSelection Single
    TEST_F(SelectionManagerTests, GetSelection_ReturnsEmpty_WhenNoGuidAdded)
    {
        // Arrange
        SelectionGroup givenGroup = SelectionGroup::Inspectable;
        auto givenSelection = std::make_shared<SelectableStub>(SelectionGroup::Inspectable);
        givenSelection->m_guid = {};
        m_selectionManager->AddToSelection(givenSelection);

        // Act
        std::vector<std::weak_ptr<Selectable>> actual = m_selectionManager->GetSelection(givenGroup);

        // Assert
        ASSERT_EQ(0, actual.size()) << "The correct number of selectables was not found.";
    }

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

    TEST_F(SelectionManagerTests, GetSelection_DoesNotReturnSelection_WhenGroupDoesNotMatch)
    {
        // Arrange
        SelectionGroup givenGroup = SelectionGroup::Inspectable;
        SelectionGroup queriedGroup = SelectionGroup::Unknown;
        auto givenSelection = std::make_shared<SelectableStub>(SelectionGroup::Inspectable);
        m_selectionManager->AddToSelection(givenSelection);

        // Act
        std::vector<std::weak_ptr<Selectable>> actual = m_selectionManager->GetSelection(queriedGroup);

        // Assert
        ASSERT_EQ(0, actual.size()) << "The correct number of selectables was not found.";
    }

    TEST_F(SelectionManagerTests, GetSelection_AddsToExistingSelection_WhenMultipleGiven)
    {
        // Arrange
        SelectionGroup givenGroup = SelectionGroup::Inspectable;
        auto givenSelection = std::make_shared<SelectableStub>(SelectionGroup::Inspectable);
        auto givenSelection2 = std::make_shared<SelectableStub>(SelectionGroup::Inspectable);
        m_selectionManager->AddToSelection(givenSelection);
        m_selectionManager->AddToSelection(givenSelection2);

        // Act
        std::vector<std::weak_ptr<Selectable>> actual = m_selectionManager->GetSelection(givenGroup);

        // Assert
        ASSERT_EQ(2, actual.size()) << "The correct number of selectables was not found.";

        auto shared = actual.at(0).lock();
        ASSERT_TRUE(shared) << "Pointer to selection did not exist.";
        ASSERT_EQ(givenSelection->m_guid, shared->GetGuid()) << "Guids did not match. ";

        auto shared2 = actual.at(1).lock();
        ASSERT_TRUE(shared2) << "Pointer to selection did not exist.";
        ASSERT_EQ(givenSelection2->m_guid, shared2->GetGuid()) << "Guids did not match. ";
    }

#pragma endregion

#pragma region SetSelection

    TEST_F(SelectionManagerTests, GetSelection_DoesNotChangeSelection_WhenGuidIsNotFound)
    {
        // Arrange
        SelectionGroup givenGroup = SelectionGroup::Inspectable;

        auto validSelection = std::make_shared<SelectableStub>(SelectionGroup::Inspectable);
        m_selectionManager->SetSelection(validSelection);
        std::vector<std::weak_ptr<Selectable>> before = m_selectionManager->GetSelection(givenGroup);
        ASSERT_EQ(1, before.size()) << "Set selection did not put a selectable in before.";

        auto givenSelection = std::make_shared<SelectableStub>(SelectionGroup::Inspectable);
        givenSelection->m_guid = {};
        m_selectionManager->SetSelection(givenSelection);

        // Act
        std::vector<std::weak_ptr<Selectable>> actual = m_selectionManager->GetSelection(givenGroup);

        // Assert
        ASSERT_EQ(1, actual.size()) << "The correct number of selectables was not found.";

        auto shared = actual.at(0).lock();
        ASSERT_TRUE(shared) << "Pointer to selection did not exist.";
        ASSERT_EQ(validSelection->m_guid, shared->GetGuid()) << "Guids did not match. ";
    }

    TEST_F(SelectionManagerTests, GetSelection_ReturnsSelection_WhenSetToSameGroup)
    {
        // Arrange
        SelectionGroup givenGroup = SelectionGroup::Inspectable;
        auto givenSelection = std::make_shared<SelectableStub>(SelectionGroup::Inspectable);
        m_selectionManager->SetSelection(givenSelection);

        // Act
        std::vector<std::weak_ptr<Selectable>> actual = m_selectionManager->GetSelection(givenGroup);

        // Assert
        ASSERT_EQ(1, actual.size()) << "The correct number of selectables was not found.";

        auto shared = actual.at(0).lock();
        ASSERT_TRUE(shared) << "Pointer to selection did not exist.";
        ASSERT_EQ(givenSelection->m_guid, shared->GetGuid()) << "Guids did not match. ";
    }

    TEST_F(SelectionManagerTests, GetSelection_DoesNotAffectOtherGroup_WhenOtherGroupHasSomethingIn)
    {
        // Arrange
        SelectionGroup otherGroup = SelectionGroup::Unknown;
        auto otherGroupSelectable = std::make_shared<SelectableStub>(otherGroup);
        m_selectionManager->SetSelection(otherGroupSelectable);
        std::vector<std::weak_ptr<Selectable>> before = m_selectionManager->GetSelection(otherGroup);
        ASSERT_EQ(1, before.size()) << "Set selection did not put a selectable in before.";

        SelectionGroup givenGroup = SelectionGroup::Inspectable;
        auto givenSelection = std::make_shared<SelectableStub>(SelectionGroup::Inspectable);
        m_selectionManager->SetSelection(givenSelection);

        // Act
        std::vector<std::weak_ptr<Selectable>> actual = m_selectionManager->GetSelection(otherGroup);
        std::vector<std::weak_ptr<Selectable>> actualGiven = m_selectionManager->GetSelection(givenGroup);

        // Assert
        ASSERT_EQ(1, actual.size()) << "The correct number of selectables was not found.";

        auto shared = actual.at(0).lock();
        ASSERT_TRUE(shared) << "Pointer to selection did not exist.";
        ASSERT_EQ(otherGroupSelectable->m_guid, shared->GetGuid()) << "Guids did not match. ";

        ASSERT_EQ(1, actualGiven.size()) << "The correct number of selectables was not found.";

        auto shared2 = actualGiven.at(0).lock();
        ASSERT_TRUE(shared2) << "Pointer to selection did not exist.";
        ASSERT_EQ(givenSelection->m_guid, shared2->GetGuid()) << "Guids did not match. ";
    }

#pragma endregion
}
