#include "../../LibraryIncludes.h"
#include "../../../StandardCLibrary/Collection/Organised/FList.hpp"
#include "FCollectionSharedTestHelpers.hpp"

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
}