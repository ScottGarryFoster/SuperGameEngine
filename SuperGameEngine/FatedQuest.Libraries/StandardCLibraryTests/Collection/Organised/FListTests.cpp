#include "../../LibraryIncludes.h"
#include "../../../StandardCLibrary/Collection/Organised/FList.hpp"
#include "FCollectionSharedTestHelpers.hpp"
#include <string>

using namespace StandardCLibraryTests_Collection_Organised;
using namespace StandardCLibrary;
namespace StandardCLibraryTests_Collection_Organised_ListTests
{
#pragma region Add
    TEST(FListTests, Add_ReturnsACollectionOneBigger_WhenNewEmptyCollectionCreatedWithAddCalled)
    {
        int given = 42;
        FList<int> collection = FList<int>();

        collection.Add(given);

        int count = CountCollection<int>(collection);
        EXPECT_EQ(1, count);
        EXPECT_EQ(given, ReturnItemInCollection(collection, 0));
    }

    TEST(FListTests, Add_PushesItemToEnd_WhenACollectionWithItemWithAddCalled)
    {
        int given = 42;
        int started = 21;
        FList<int> collection = FList<int>(started);

        collection.Add(given);

        int count = CountCollection<int>(collection);
        EXPECT_EQ(2, count);
        EXPECT_EQ(given, ReturnItemInCollection(collection, 1));
    }

    TEST(FListTests, Add_AddsAPointerToList_WhenGivenAPointer)
    {
        int* given = new int(42);
        FList<int*> collection = FList<int*>();

        collection.Add(given);

        // Need to gather results before cleanup
        int count = CountCollection<int>(collection);
        int givenDerefered = *given;
        int actual = *ReturnItemInCollection(collection, 0);
        
        delete given;
        EXPECT_EQ(1, count);
        EXPECT_EQ(givenDerefered, actual);
    }
#pragma endregion

#pragma region Operator[]
    TEST(FListTests, OperatorBrackets_ReturnsElementsInOrderGiven_WhenGivenThreeElementsInOrder)
    {
        std::vector<int> given = { 42, 56, 99 };
        FList<int> collection = FList<int>(given);

        int actualZero = collection[0];
        int actualOne = collection[1];
        int actualTwo = collection[2];

        EXPECT_EQ(given[0], actualZero);
        EXPECT_EQ(given[1], actualOne);
        EXPECT_EQ(given[2], actualTwo);
    }

    TEST(FListTests, OperatorBrackets_ReturnsElementsInOrderGiven_WhenGivenThreeElementsInOrderWithConst)
    {
        std::vector<int> given = { 42, 56, 99 };
        const FList<int> collection = FList<int>(given);

        int actualZero = collection[0];
        int actualOne = collection[1];
        int actualTwo = collection[2];

        EXPECT_EQ(given[0], actualZero);
        EXPECT_EQ(given[1], actualOne);
        EXPECT_EQ(given[2], actualTwo);
    }

    TEST(FListTests, OperatorBrackets_ReturnsElementsInOrderGivenAsPointers_WhenGivenThreeElementsInOrder)
    {
        std::vector<int*> given = { new int(42), new int (56), new int(99) };
        std::vector<int> givenDeref = { 42, 56, 99 };
        FList<int*> collection = FList<int*>(given);

        int actualZero = *collection[0];
        int actualOne = *collection[1];
        int actualTwo = *collection[2];

        CleanUp(given);
        EXPECT_EQ(givenDeref[0], actualZero);
        EXPECT_EQ(givenDeref[1], actualOne);
        EXPECT_EQ(givenDeref[2], actualTwo);
    }
#pragma endregion
}