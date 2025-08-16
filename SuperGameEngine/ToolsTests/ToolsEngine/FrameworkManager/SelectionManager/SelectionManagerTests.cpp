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


        bool SelectionContains(const std::vector<std::weak_ptr<Selectable>>& selectables, const std::weak_ptr<Selectable>& selectable)
        {
            if (std::shared_ptr<Selectable> compare = selectable.lock())
            {
                for (const std::weak_ptr<Selectable>& current : selectables)
                {
                    if (std::shared_ptr<Selectable> sharedPtr = current.lock())
                    {
                        if (sharedPtr->GetGuid() == compare->GetGuid())
                        {
                            return true;
                        }
                    }
                }
            }

            return false;
        }
    };

#pragma region AddSelection GetSelection Single
    TEST_F(SelectionManagerTests, AddToSelection_ReturnsEmpty_WhenNoGuidAdded)
    {
        // Arrange
        SelectionGroup givenGroup = SelectionGroup::Inspectable;
        auto givenSelection = std::make_shared<SelectableStub>(SelectionGroup::Inspectable);
        givenSelection->m_guid = {};

        // Act
        m_selectionManager->AddToSelection(givenSelection);

        // Assert
        std::vector<std::weak_ptr<Selectable>> actual = m_selectionManager->GetSelection(givenGroup);
        ASSERT_EQ(0, actual.size()) << "The correct number of selectables was not found.";
    }

    TEST_F(SelectionManagerTests, AddToSelection_ReturnsSelection_WhenAddedToGroupWhenUsingSingleGroup)
    {
        // Arrange
        SelectionGroup givenGroup = SelectionGroup::Inspectable;
        auto givenSelection = std::make_shared<SelectableStub>(SelectionGroup::Inspectable);

        // Act
        m_selectionManager->AddToSelection(givenSelection);

        // Assert
        std::vector<std::weak_ptr<Selectable>> actual = m_selectionManager->GetSelection(givenGroup);
        ASSERT_EQ(1, actual.size()) << "The correct number of selectables was not found.";
        auto shared = actual.at(0).lock();
        ASSERT_TRUE(shared) << "Pointer to selection did not exist.";
        ASSERT_EQ(givenSelection->m_guid, shared->GetGuid()) << "Guids did not match. ";
    }

    TEST_F(SelectionManagerTests, AddToSelection_DoesNotReturnSelection_WhenGroupDoesNotMatch)
    {
        // Arrange
        SelectionGroup givenGroup = SelectionGroup::Inspectable;
        SelectionGroup queriedGroup = SelectionGroup::Unknown;
        auto givenSelection = std::make_shared<SelectableStub>(SelectionGroup::Inspectable);

        // Act
        m_selectionManager->AddToSelection(givenSelection);

        // Assert
        std::vector<std::weak_ptr<Selectable>> actual = m_selectionManager->GetSelection(queriedGroup);
        ASSERT_EQ(0, actual.size()) << "The correct number of selectables was not found.";
    }

    TEST_F(SelectionManagerTests, AddToSelection_AddsToExistingSelection_WhenMultipleGiven)
    {
        // Arrange
        SelectionGroup givenGroup = SelectionGroup::Inspectable;
        auto givenSelection = std::make_shared<SelectableStub>(SelectionGroup::Inspectable);
        auto givenSelection2 = std::make_shared<SelectableStub>(SelectionGroup::Inspectable);

        // Act
        m_selectionManager->AddToSelection(givenSelection);
        m_selectionManager->AddToSelection(givenSelection2);

        // Assert
        std::vector<std::weak_ptr<Selectable>> actual = m_selectionManager->GetSelection(givenGroup);
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

    TEST_F(SelectionManagerTests, SetSelection_DoesNotChangeSelection_WhenGuidIsNotFound)
    {
        // Arrange
        SelectionGroup givenGroup = SelectionGroup::Inspectable;

        auto validSelection = std::make_shared<SelectableStub>(SelectionGroup::Inspectable);
        m_selectionManager->SetSelection(validSelection);
        std::vector<std::weak_ptr<Selectable>> before = m_selectionManager->GetSelection(givenGroup);
        ASSERT_EQ(1, before.size()) << "Set selection did not put a selectable in before.";

        auto givenSelection = std::make_shared<SelectableStub>(SelectionGroup::Inspectable);
        givenSelection->m_guid = {};

        // Act
        m_selectionManager->SetSelection(givenSelection);

        // Assert
        std::vector<std::weak_ptr<Selectable>> actual = m_selectionManager->GetSelection(givenGroup);
        ASSERT_EQ(1, actual.size()) << "The correct number of selectables was not found.";

        auto shared = actual.at(0).lock();
        ASSERT_TRUE(shared) << "Pointer to selection did not exist.";
        ASSERT_EQ(validSelection->m_guid, shared->GetGuid()) << "Guids did not match. ";
    }

    TEST_F(SelectionManagerTests, SetSelection_ReturnsSelection_WhenSetToSameGroup)
    {
        // Arrange
        SelectionGroup givenGroup = SelectionGroup::Inspectable;
        auto givenSelection = std::make_shared<SelectableStub>(SelectionGroup::Inspectable);

        // Act
        m_selectionManager->SetSelection(givenSelection);

        // Assert
        std::vector<std::weak_ptr<Selectable>> actual = m_selectionManager->GetSelection(givenGroup);
        ASSERT_EQ(1, actual.size()) << "The correct number of selectables was not found.";

        auto shared = actual.at(0).lock();
        ASSERT_TRUE(shared) << "Pointer to selection did not exist.";
        ASSERT_EQ(givenSelection->m_guid, shared->GetGuid()) << "Guids did not match. ";
    }

    TEST_F(SelectionManagerTests, SetSelection_DoesNotAffectOtherGroup_WhenOtherGroupHasSomethingIn)
    {
        // Arrange
        SelectionGroup otherGroup = SelectionGroup::Unknown;
        auto otherGroupSelectable = std::make_shared<SelectableStub>(otherGroup);
        m_selectionManager->SetSelection(otherGroupSelectable);
        std::vector<std::weak_ptr<Selectable>> before = m_selectionManager->GetSelection(otherGroup);
        ASSERT_EQ(1, before.size()) << "Set selection did not put a selectable in before.";

        SelectionGroup givenGroup = SelectionGroup::Inspectable;
        auto givenSelection = std::make_shared<SelectableStub>(SelectionGroup::Inspectable);

        // Act
        m_selectionManager->SetSelection(givenSelection);

        // Assert
        std::vector<std::weak_ptr<Selectable>> actual = m_selectionManager->GetSelection(otherGroup);
        std::vector<std::weak_ptr<Selectable>> actualGiven = m_selectionManager->GetSelection(givenGroup);

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

#pragma region RemoveSelection

    TEST_F(SelectionManagerTests, RemoveFromSelection_DoesNotRemoveSelection_WhenGuidIsNotFound)
    {
        // Arrange
        SelectionGroup givenGroup = SelectionGroup::Inspectable;

        auto validSelection = std::make_shared<SelectableStub>(SelectionGroup::Inspectable);
        m_selectionManager->SetSelection(validSelection);
        std::vector<std::weak_ptr<Selectable>> before = m_selectionManager->GetSelection(givenGroup);
        ASSERT_EQ(1, before.size()) << "Set selection did not put a selectable in before.";

        auto givenSelection = std::make_shared<SelectableStub>(SelectionGroup::Inspectable);
        givenSelection->m_guid = {};

        // Act
        m_selectionManager->RemoveFromSelection(givenSelection);

        // Assert
        std::vector<std::weak_ptr<Selectable>> actual = m_selectionManager->GetSelection(givenGroup);
        ASSERT_EQ(1, actual.size()) << "The correct number of selectables was not found.";

        auto shared = actual.at(0).lock();
        ASSERT_TRUE(shared) << "Pointer to selection did not exist.";
        ASSERT_EQ(validSelection->m_guid, shared->GetGuid()) << "Guids did not match. ";
    }

    TEST_F(SelectionManagerTests, RemoveFromSelection_HasNoSelection_WhenRemoveIsInSelectionAndIsOnlyItemInSelection)
    {
        // Arrange
        SelectionGroup givenGroup = SelectionGroup::Inspectable;

        auto validSelection = std::make_shared<SelectableStub>(SelectionGroup::Inspectable);
        m_selectionManager->SetSelection(validSelection);
        std::vector<std::weak_ptr<Selectable>> before = m_selectionManager->GetSelection(givenGroup);
        ASSERT_EQ(1, before.size()) << "Set selection did not put a selectable in before.";

        // Act
        m_selectionManager->RemoveFromSelection(validSelection);

        // Assert
        std::vector<std::weak_ptr<Selectable>> actual = m_selectionManager->GetSelection(givenGroup);
        ASSERT_EQ(0, actual.size()) << "The correct number of selectables was not found.";
    }

    TEST_F(SelectionManagerTests, RemoveFromSelection_OnlyAffectRemovedSelection_WhenItemRemovedAndThereAreMoreThingsInSelection)
    {
        // Arrange
        SelectionGroup givenGroup = SelectionGroup::Inspectable;

        auto validSelection = std::make_shared<SelectableStub>(SelectionGroup::Inspectable);
        m_selectionManager->SetSelection(validSelection);

        auto toRemove = std::make_shared<SelectableStub>(SelectionGroup::Inspectable);
        m_selectionManager->AddToSelection(toRemove);

        std::vector<std::weak_ptr<Selectable>> before = m_selectionManager->GetSelection(givenGroup);
        ASSERT_EQ(2, before.size()) << "Set selection did not put a selectable in before.";

        // Act
        m_selectionManager->RemoveFromSelection(toRemove);

        // Assert
        std::vector<std::weak_ptr<Selectable>> actual = m_selectionManager->GetSelection(givenGroup);
        ASSERT_EQ(1, actual.size()) << "The correct number of selectables was not found.";

        auto shared = actual.at(0).lock();
        ASSERT_TRUE(shared) << "Pointer to selection did not exist.";
        ASSERT_EQ(validSelection->m_guid, shared->GetGuid()) << "Guids did not match. ";
    }

#pragma endregion

#pragma region AddToSelection-Multiple

    TEST_F(SelectionManagerTests, AddToSelectionMultiple_AddsToExistingSelection_WhenMultipleGiven)
    {
        // Arrange
        SelectionGroup givenGroup = SelectionGroup::Inspectable;
        auto givenSelection = std::make_shared<SelectableStub>(SelectionGroup::Inspectable);
        auto givenSelection2 = std::make_shared<SelectableStub>(SelectionGroup::Inspectable);
        std::vector<std::weak_ptr<Selectable>> selectables;
        selectables.emplace_back(givenSelection);
        selectables.emplace_back(givenSelection2);

        // Act
        m_selectionManager->AddToSelection(selectables);

        // Assert
        std::vector<std::weak_ptr<Selectable>> actual = m_selectionManager->GetSelection(givenGroup);
        ASSERT_EQ(2, actual.size()) << "The correct number of selectables was not found.";

        auto shared = actual.at(0).lock();
        ASSERT_TRUE(shared) << "Pointer to selection did not exist.";
        ASSERT_EQ(givenSelection->m_guid, shared->GetGuid()) << "Guids did not match. ";

        auto shared2 = actual.at(1).lock();
        ASSERT_TRUE(shared2) << "Pointer to selection did not exist.";
        ASSERT_EQ(givenSelection2->m_guid, shared2->GetGuid()) << "Guids did not match. ";
    }

    TEST_F(SelectionManagerTests, AddToSelectionMultiple_DoesNotAddAnyWithNoGuids_WhenASelectableHasNoGuid)
    {
        // Arrange
        SelectionGroup givenGroup = SelectionGroup::Inspectable;
        auto givenSelection = std::make_shared<SelectableStub>(SelectionGroup::Inspectable);
        auto givenSelection2 = std::make_shared<SelectableStub>(SelectionGroup::Inspectable);
        givenSelection2->m_guid = {};

        std::vector<std::weak_ptr<Selectable>> selectables;
        selectables.emplace_back(givenSelection);
        selectables.emplace_back(givenSelection2);

        // Act
        m_selectionManager->AddToSelection(selectables);

        // Assert
        std::vector<std::weak_ptr<Selectable>> actual = m_selectionManager->GetSelection(givenGroup);
        ASSERT_EQ(1, actual.size()) << "The correct number of selectables was not found.";

        auto shared = actual.at(0).lock();
        ASSERT_TRUE(shared) << "Pointer to selection did not exist.";
        ASSERT_EQ(givenSelection->m_guid, shared->GetGuid()) << "Guids did not match. ";
    }

    TEST_F(SelectionManagerTests, AddToSelectionMultiple_AddsCorrectly_WhenTheFirstInTheListHasNoGuid)
    {
        // Arrange
        SelectionGroup givenGroup = SelectionGroup::Inspectable;
        auto givenSelection = std::make_shared<SelectableStub>(SelectionGroup::Inspectable);
        givenSelection->m_guid = {};
        auto givenSelection2 = std::make_shared<SelectableStub>(SelectionGroup::Inspectable);

        std::vector<std::weak_ptr<Selectable>> selectables;
        selectables.emplace_back(givenSelection);
        selectables.emplace_back(givenSelection2);

        // Act
        m_selectionManager->AddToSelection(selectables);

        // Assert
        std::vector<std::weak_ptr<Selectable>> actual = m_selectionManager->GetSelection(givenGroup);
        ASSERT_EQ(1, actual.size()) << "The correct number of selectables was not found.";

        auto shared = actual.at(0).lock();
        ASSERT_TRUE(shared) << "Pointer to selection did not exist.";
        ASSERT_EQ(givenSelection2->m_guid, shared->GetGuid()) << "Guids did not match. ";
    }

#pragma endregion

#pragma region SelectSelection-Multiple

    TEST_F(SelectionManagerTests, SelectSelectionMultiple_SetsAllGiven_WhenGivenMultiple)
    {
        // Arrange
        SelectionGroup givenGroup = SelectionGroup::Inspectable;
        auto givenSelection = std::make_shared<SelectableStub>(SelectionGroup::Inspectable);
        auto givenSelection2 = std::make_shared<SelectableStub>(SelectionGroup::Inspectable);

        std::vector<std::weak_ptr<Selectable>> selectables;
        selectables.emplace_back(givenSelection);
        selectables.emplace_back(givenSelection2);

        // Act
        m_selectionManager->SetSelection(selectables);

        // Assert
        std::vector<std::weak_ptr<Selectable>> actual = m_selectionManager->GetSelection(givenGroup);
        ASSERT_EQ(2, actual.size()) << "The correct number of selectables was not found.";

        auto shared = actual.at(0).lock();
        ASSERT_TRUE(shared) << "Pointer to selection did not exist.";
        ASSERT_EQ(givenSelection->m_guid, shared->GetGuid()) << "Guids did not match. ";

        auto shared2 = actual.at(1).lock();
        ASSERT_TRUE(shared2) << "Pointer to selection did not exist.";
        ASSERT_EQ(givenSelection2->m_guid, shared2->GetGuid()) << "Guids did not match. ";
    }

    TEST_F(SelectionManagerTests, SelectSelectionMultiple_DoesNotSetSelectable_WhenThereIsNoGuid)
    {
        // Arrange
        SelectionGroup givenGroup = SelectionGroup::Inspectable;
        auto givenSelection = std::make_shared<SelectableStub>(SelectionGroup::Inspectable);
        givenSelection->m_guid = {};
        auto givenSelection2 = std::make_shared<SelectableStub>(SelectionGroup::Inspectable);

        std::vector<std::weak_ptr<Selectable>> selectables;
        selectables.emplace_back(givenSelection);
        selectables.emplace_back(givenSelection2);

        // Act
        m_selectionManager->SetSelection(selectables);

        // Assert
        std::vector<std::weak_ptr<Selectable>> actual = m_selectionManager->GetSelection(givenGroup);
        ASSERT_EQ(1, actual.size()) << "The correct number of selectables was not found.";

        auto shared = actual.at(0).lock();
        ASSERT_TRUE(shared) << "Pointer to selection did not exist.";
        ASSERT_EQ(givenSelection2->m_guid, shared->GetGuid()) << "Guids did not match. ";
    }

    TEST_F(SelectionManagerTests, SelectSelectionMultiple_SetsSelectablesInToCorrectGroups_WhenMultiplesGiven)
    {
        // Arrange
        SelectionGroup givenGroup = SelectionGroup::Inspectable;
        auto givenSelection = std::make_shared<SelectableStub>(SelectionGroup::Inspectable);

        std::unordered_set<SelectionGroup> selection2Groups;
        selection2Groups.insert(SelectionGroup::Inspectable);
        selection2Groups.insert(SelectionGroup::Unknown);
        auto givenSelection2 = std::make_shared<SelectableStub>(selection2Groups);

        std::vector<std::weak_ptr<Selectable>> selectables;
        selectables.emplace_back(givenSelection);
        selectables.emplace_back(givenSelection2);

        // Act
        m_selectionManager->SetSelection(selectables);

        // Assert
        // Main group
        std::vector<std::weak_ptr<Selectable>> actual = m_selectionManager->GetSelection(givenGroup);
        ASSERT_EQ(2, actual.size()) << "The correct number of selectables was not found.";

        auto shared = actual.at(0).lock();
        ASSERT_TRUE(shared) << "Pointer to selection did not exist.";
        ASSERT_EQ(givenSelection->m_guid, shared->GetGuid()) << "Guids did not match. ";

        auto shared2 = actual.at(1).lock();
        ASSERT_TRUE(shared2) << "Pointer to selection did not exist.";
        ASSERT_EQ(givenSelection2->m_guid, shared2->GetGuid()) << "Guids did not match. ";

        // Check the other group
        std::vector<std::weak_ptr<Selectable>> unknownGroups = m_selectionManager->GetSelection(SelectionGroup::Unknown);
        ASSERT_EQ(1, unknownGroups.size()) << "The correct number of selectables was not found.";

        auto shared3 = unknownGroups.at(0).lock();
        ASSERT_TRUE(shared3) << "Pointer to selection did not exist.";
        ASSERT_EQ(givenSelection2->m_guid, shared3->GetGuid()) << "Guids did not match. ";
    }

#pragma endregion

#pragma region RemoveFromSelection-Multiple

    TEST_F(SelectionManagerTests, RemoveFromSelectionMutliple_RemovesTheItemsGiven_WhenGivenMultiple)
    {
        // Arrange
        SelectionGroup givenGroup = SelectionGroup::Inspectable;
        auto inSelection = std::make_shared<SelectableStub>(SelectionGroup::Inspectable);
        auto inSelection2 = std::make_shared<SelectableStub>(SelectionGroup::Inspectable);

        auto toBeRemoved = std::make_shared<SelectableStub>(SelectionGroup::Inspectable);
        auto toBeRemoved2 = std::make_shared<SelectableStub>(SelectionGroup::Inspectable);

        std::vector<std::weak_ptr<Selectable>> selectionFromTheStart;
        selectionFromTheStart.emplace_back(inSelection);
        selectionFromTheStart.emplace_back(inSelection2);
        selectionFromTheStart.emplace_back(toBeRemoved);
        selectionFromTheStart.emplace_back(toBeRemoved2);
        m_selectionManager->SetSelection(selectionFromTheStart);

        std::vector<std::weak_ptr<Selectable>> givenToRemove;
        givenToRemove.emplace_back(toBeRemoved);
        givenToRemove.emplace_back(toBeRemoved2);

        // Act
        m_selectionManager->RemoveFromSelection(givenToRemove);

        // Assert
        std::vector<std::weak_ptr<Selectable>> actual = m_selectionManager->GetSelection(givenGroup);
        ASSERT_EQ(2, actual.size()) << "The correct number of selectables was not found.";

        auto shared = actual.at(0).lock();
        ASSERT_TRUE(shared) << "Pointer to selection did not exist.";
        ASSERT_EQ(inSelection->m_guid, shared->GetGuid()) << "Guids did not match. ";

        auto shared2 = actual.at(1).lock();
        ASSERT_TRUE(shared2) << "Pointer to selection did not exist.";
        ASSERT_EQ(inSelection2->m_guid, shared2->GetGuid()) << "Guids did not match. ";
    }

    TEST_F(SelectionManagerTests, RemoveFromSelectionMutliple_DoesNotRemove_IfThereIsNoGuid)
    {
        // Arrange
        SelectionGroup givenGroup = SelectionGroup::Inspectable;
        auto inSelection = std::make_shared<SelectableStub>(SelectionGroup::Inspectable);
        auto inSelection2 = std::make_shared<SelectableStub>(SelectionGroup::Inspectable);

        auto toBeRemoved = std::make_shared<SelectableStub>(SelectionGroup::Inspectable);
        auto toBeRemoved2 = std::make_shared<SelectableStub>(SelectionGroup::Inspectable);

        std::vector<std::weak_ptr<Selectable>> selectionFromTheStart;
        selectionFromTheStart.emplace_back(inSelection);
        selectionFromTheStart.emplace_back(inSelection2);
        selectionFromTheStart.emplace_back(toBeRemoved);
        selectionFromTheStart.emplace_back(toBeRemoved2);
        m_selectionManager->SetSelection(selectionFromTheStart);

        std::vector<std::weak_ptr<Selectable>> givenToRemove;
        givenToRemove.emplace_back(toBeRemoved);
        givenToRemove.emplace_back(toBeRemoved2);

        // Expect this to still exist.
        toBeRemoved2->m_guid = {};

        // Act
        m_selectionManager->RemoveFromSelection(givenToRemove);

        // Assert
        std::vector<std::weak_ptr<Selectable>> actual = m_selectionManager->GetSelection(givenGroup);
        ASSERT_EQ(3, actual.size()) << "The correct number of selectables was not found.";

        bool containsSelection1 = SelectionContains(actual, inSelection);
        ASSERT_TRUE(containsSelection1) << "Could not find first in Selection";

        bool containsSelection2 = SelectionContains(actual, inSelection2);
        ASSERT_TRUE(containsSelection2) << "Could not find second in Selection";

        bool containsToBeRemoved2 = SelectionContains(actual, toBeRemoved2);
        ASSERT_TRUE(containsToBeRemoved2) << "Could not find the selection without a GUID";
    }

    TEST_F(SelectionManagerTests, RemoveFromSelectionMutliple_ContinuesToRemove_WhenTheSelectableWithoutAGuidIsFirst)
    {
        // Arrange
        SelectionGroup givenGroup = SelectionGroup::Inspectable;
        auto inSelection = std::make_shared<SelectableStub>(SelectionGroup::Inspectable);
        auto inSelection2 = std::make_shared<SelectableStub>(SelectionGroup::Inspectable);

        auto toBeRemoved = std::make_shared<SelectableStub>(SelectionGroup::Inspectable);
        auto toBeRemoved2 = std::make_shared<SelectableStub>(SelectionGroup::Inspectable);

        std::vector<std::weak_ptr<Selectable>> selectionFromTheStart;
        selectionFromTheStart.emplace_back(inSelection);
        selectionFromTheStart.emplace_back(inSelection2);
        selectionFromTheStart.emplace_back(toBeRemoved);
        selectionFromTheStart.emplace_back(toBeRemoved2);
        m_selectionManager->SetSelection(selectionFromTheStart);

        std::vector<std::weak_ptr<Selectable>> givenToRemove;
        givenToRemove.emplace_back(toBeRemoved);
        givenToRemove.emplace_back(toBeRemoved2);

        // Expect this to still exist.
        toBeRemoved->m_guid = {};

        // Act
        m_selectionManager->RemoveFromSelection(givenToRemove);

        // Assert
        std::vector<std::weak_ptr<Selectable>> actual = m_selectionManager->GetSelection(givenGroup);
        ASSERT_EQ(3, actual.size()) << "The correct number of selectables was not found.";

        bool containsSelection1 = SelectionContains(actual, inSelection);
        ASSERT_TRUE(containsSelection1) << "Could not find first in Selection";

        bool containsSelection2 = SelectionContains(actual, inSelection2);
        ASSERT_TRUE(containsSelection2) << "Could not find second in Selection";

        bool containsSelection3 = SelectionContains(actual, toBeRemoved);
        ASSERT_TRUE(containsSelection3) << "Could not find third in Selection";
    }

#pragma endregion
}
