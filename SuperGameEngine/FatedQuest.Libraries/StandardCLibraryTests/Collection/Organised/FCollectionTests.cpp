#include "../../LibraryIncludes.h"
#include "../../../StandardCLibrary/Collection/Organised/FCollection.hpp"
#include "FCollectionSharedTestHelpers.hpp"

using namespace StandardCLibraryTests_Collection_Organised;
using namespace StandardCLibrary;
namespace StandardCLibraryTests_Collection_Organised_CollectionTests
{
#pragma region OnConstruction
    TEST(FCollectionTests, OnConstruction_ReturnsEmptyCollection_WhenGivenNoEntries)
    {
        FCollection<int> collection = FCollection<int>();

        int count = CountCollection<int>(collection);
        ASSERT_EQ(0, count);
    }

    TEST(FCollectionTests, OnConstruction_ReturnsCollectionWithItem_WhenGivenEntry)
    {
        int given = 42;

        FCollection<int> collection = FCollection<int>(given);

        int count = CountCollection(collection);
        ASSERT_EQ(1, count);
        ASSERT_EQ(given, ReturnItemInCollection<int>(collection, 0));
    }

    TEST(FCollectionTests, OnConstruction_ReturnsCollectionWithPointItem_WhenGivenPointer)
    {
        int* given = new int(42);

        FCollection<int*> collection = FCollection<int*>(given);

        // Values we will test against. Dereferenced because we clean up.
        int count = CountCollection(collection);
        int* actual = ReturnItemInCollectionPointers<int>(collection, 0);
        bool actualFound = actual != NULL;
        int actualDereferenced = *given;
        int givenDereferenced = *given;

        delete given;
        ASSERT_EQ(1, count);
        ASSERT_TRUE(actualFound) << "Actual was not found";
        ASSERT_EQ(givenDereferenced, actualDereferenced);
    }

    TEST(FCollectionTests, OnConstruction_ReturnsAllItemGiven_WhenGivenVectorOfItems)
    {
        std::vector<int> given = { 42, 52, 75, 86 };

        FCollection<int> collection = FCollection<int>(given);

        std::vector<int> actual = ToVector<int>(collection);
        std::string errors = "";
        bool areEqual = Equals(given, actual, errors);
        ASSERT_TRUE(areEqual) << errors;
    }

    TEST(FCollectionTests, OnConstruction_ReturnsAllPointers_WhenGivenVectorOfPointers)
    {
        std::vector<int*> given = { new int(42), new int(52), new int(75), new int(86) };

        FCollection<int*> collection = FCollection<int*>(given);

        std::vector<int*> actual = ToVector<int*>(collection);
        std::string errors = "";
        bool areEqual = Equals(given, actual, errors);
        CleanUp(given);
        ASSERT_TRUE(areEqual) << errors;
    }
#pragma endregion

#pragma region Where
    TEST(FCollectionTests, Where_ExtractsValuesAbove20_WhenGivenPredicateForThisAndValuesThatMatch)
    {
        std::vector<int> given = { 5, 12, 18, 20, 23, 35, 46, 52, 67, 82 };
        std::vector<int> expected = { 23, 35, 46, 52, 67, 82 };
        FCollection<int> collection = FCollection<int>(given);

        FCollection<int> actual = collection.Where([](const int& x) { return x > 20; });

        std::vector<int> actualV = ToVector<int>(actual);
        std::string errors = "";
        bool areEqual = Equals(expected, actualV, errors);
        ASSERT_TRUE(areEqual) << errors;
    }

    TEST(FCollectionTests, Where_ReturnsEmptyCollection_WhenNothingMatches)
    {
        std::vector<int> given = { 5, 12, 18, 20, 23, 35, 46, 52, 67, 82 };
        int expected = 0;
        FCollection<int> collection = FCollection<int>(given);

        FCollection<int> actual = collection.Where([](const int& x) { return x > 100; });

        ASSERT_EQ(expected, CountCollection(actual));
    }

// Pointer method is different code (signature)
#pragma region WithPointers
    TEST(FCollectionTests, Where_ExtractsValuesAbove20FromPointer_WhenGivenPredicateForThisAndValuesThatMatch)
    {
        std::vector<int*> given = { new int(5), new int(12), new int(18), 
            new int(20), new int(23), new int(35), new int(46), 
            new int(52), new int(67), new int(82) };
        std::vector<int*> expected = { new int(23), new int(35), new int(46),
            new int(52), new int(67), new int(82) };;
        FCollection<int*> collection = FCollection<int*>(given);

        FCollection<int*> actual = collection.Where([](const int* x) { return *x > 20; });

        std::vector<int*> actualV = ToVector<int*>(actual);
        std::string errors = "";
        bool areEqual = Equals(expected, actualV, errors);
        CleanUp(collection);
        ASSERT_TRUE(areEqual) << errors;
    }

    TEST(FCollectionTests, Where_ReturnsEmptyCollectionFromPointer_WhenNothingMatches)
    {
        std::vector<int*> given = { new int(5), new int(12), new int(18),
            new int(20), new int(23), new int(35), new int(46),
            new int(52), new int(67), new int(82) };;
        int expected = 0;
        FCollection<int*> collection = FCollection<int*>(given);

        FCollection<int*> actual = collection.Where([](const int* x) { return *x > 100; });

        int count = CountCollection(actual);
        CleanUp(collection);
        ASSERT_EQ(expected, count);
    }
#pragma endregion
#pragma endregion

#pragma region Select
    TEST(FCollectionTests, Select_ExtractsInnerValue_WhenGivenPredicateToExtractInnerInt)
    {
        int given = 7;
        TestClassContainingSomething testClass = TestClassContainingSomething();
        testClass.Value = given;
        FCollection<TestClassContainingSomething> collection(testClass);

        FCollection<int> actual = 
            collection.Select<int>([](const TestClassContainingSomething& x) { return x.Value; });

        ASSERT_EQ(1, CountCollection(actual));
        ASSERT_EQ(given, ReturnItemInCollection(actual,0));
    }

// Pointer method is different code (signature)
#pragma region WithPointers
    TEST(FCollectionTests, Select_ExtractsInnerValueFromPointer_WhenGivenPredicateToExtractInnerInt)
    {
        int given = 12;
        TestClassContainingSomething* testClass = new TestClassContainingSomething();
        testClass->Value = given;
        FCollection<TestClassContainingSomething*> collection(testClass);

        FCollection<int> actual =
            collection.Select<int>([](const TestClassContainingSomething* x) { return x->Value; });
        CleanUp(collection);

        ASSERT_EQ(1, CountCollection(actual));
        ASSERT_EQ(given, ReturnItemInCollection(actual, 0));
    }
#pragma endregion
#pragma endregion

#pragma region Count

    TEST(FCollectionTests, Count_ReturnsZero_WhenConstructingAnEmptyCollection)
    {
        FCollection<int> testClass;
        int expected = CountCollection(testClass);

        size_t actual = testClass.Count();

        ASSERT_EQ(expected, actual);
    }

    TEST(FCollectionTests, Count_ReturnsOne_WhenConstructingACollectionWithOneElement)
    {
        FCollection<int> testClass(42);
        int expected = CountCollection(testClass);

        size_t actual = testClass.Count();

        ASSERT_EQ(expected, actual);
    }

    TEST(FCollectionTests, Count_ReturnsFour_WhenConstructingACollectionWithManyElements)
    {
        std::vector<int> given{ 42, 56, 78, 1 };
        FCollection<int> testClass(given);
        int expected = CountCollection(testClass);

        size_t actual = testClass.Count();

        ASSERT_EQ(expected, actual);
    }
#pragma endregion

#pragma region Any
    TEST(FCollectionTests, Any_ReturnsFalse_WhenConstructedEmpty)
    {
        FCollection<int> testClass;

        bool actual = testClass.Any();

        ASSERT_FALSE(actual);
    }

    TEST(FCollectionTests, Any_ReturnsTrue_WhenConstructedWithEntries)
    {
        FCollection<int> testClass(42);

        bool actual = testClass.Any();

        ASSERT_TRUE(actual);
    }
#pragma endregion
}