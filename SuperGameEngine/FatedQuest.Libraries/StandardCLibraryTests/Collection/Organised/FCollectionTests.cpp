#include "../../LibraryIncludes.h"
#include "../../../StandardCLibrary/Collection/Organised/FCollection.hpp"

using namespace StandardCLibrary;
namespace StandardCLibraryTests_Collection_Organised_CollectionTests
{
    class TestClassContainingSomething
    {
    public:
        TestClassContainingSomething() { Value = 0; }
        int Value;
    };

    template<typename T>
    int CountCollection(FCollection<T> collection);

    template<typename T>
    int CountCollection(FCollection<T*> collection);

    template<typename T>
    T ReturnItemInCollection(FCollection<T> collection, int index);

    template<typename T>
    T* ReturnItemInCollectionPointers(FCollection<T*> collection, int index);

    template<typename T>
    std::vector<T> ToVector(FCollection<T> collection);

    template<typename T>
    bool Equals(std::vector<T> first, std::vector<T> second, std::string& errors);

    template<typename T>
    bool Equals(std::vector<T*> first, std::vector<T*> second, std::string& errors);

    template<typename T>
    bool CleanUp(std::vector<T*> collection);

    template<typename T>
    bool CleanUp(FCollection<T*> collection);

#pragma region OnConstruction
    TEST(FCollectionTests, OnConstruction_ReturnsEmptyCollection_WhenGivenNoEntries)
    {
        FCollection<int> collection = FCollection<int>();

        int count = CountCollection<int>(collection);
        EXPECT_EQ(0, count);
    }

    TEST(FCollectionTests, OnConstruction_ReturnsCollectionWithItem_WhenGivenEntry)
    {
        int given = 42;

        FCollection<int> collection = FCollection<int>(given);

        int count = CountCollection(collection);
        EXPECT_EQ(1, count);
        EXPECT_EQ(given, ReturnItemInCollection<int>(collection, 0));
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
        EXPECT_EQ(1, count);
        EXPECT_TRUE(actualFound) << "Actual was not found";
        EXPECT_EQ(givenDereferenced, actualDereferenced);
    }

    TEST(FCollectionTests, OnConstruction_ReturnsAllItemGiven_WhenGivenVectorOfItems)
    {
        std::vector<int> given = { 42, 52, 75, 86 };

        FCollection<int> collection = FCollection<int>(given);

        std::vector<int> actual = ToVector<int>(collection);
        std::string errors = "";
        bool areEqual = Equals(given, actual, errors);
        EXPECT_TRUE(areEqual) << errors;
    }

    TEST(FCollectionTests, OnConstruction_ReturnsAllPointers_WhenGivenVectorOfPointers)
    {
        std::vector<int*> given = { new int(42), new int(52), new int(75), new int(86) };

        FCollection<int*> collection = FCollection<int*>(given);

        std::vector<int*> actual = ToVector<int*>(collection);
        std::string errors = "";
        bool areEqual = Equals(given, actual, errors);
        CleanUp(given);
        EXPECT_TRUE(areEqual) << errors;
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
        EXPECT_TRUE(areEqual) << errors;
    }

    TEST(FCollectionTests, Where_ReturnsEmptyCollection_WhenNothingMatches)
    {
        std::vector<int> given = { 5, 12, 18, 20, 23, 35, 46, 52, 67, 82 };
        int expected = 0;
        FCollection<int> collection = FCollection<int>(given);

        FCollection<int> actual = collection.Where([](const int& x) { return x > 100; });

        EXPECT_EQ(expected, CountCollection(actual));
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
        EXPECT_TRUE(areEqual) << errors;
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
        EXPECT_EQ(expected, count);
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

        EXPECT_EQ(1, CountCollection(actual));
        EXPECT_EQ(given, ReturnItemInCollection(actual,0));
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

        EXPECT_EQ(1, CountCollection(actual));
        EXPECT_EQ(given, ReturnItemInCollection(actual, 0));
    }
#pragma endregion
#pragma endregion
#pragma region HelperMethods

    template<typename T>
    int CountCollection(FCollection<T> collection)
    {
        int count = 0;
        for (T value : collection)
        {
            ++count;
        }

        return count;
    }

    template<typename T>
    int CountCollection(FCollection<T*> collection)
    {
        int count = 0;
        for (T* value : collection)
        {
            ++count;
        }

        return count;
    }

    template<typename T>
    T ReturnItemInCollection(FCollection<T> collection, int index)
    {
        int count = 0;
        for (T value : collection)
        {
            if (index == count++)
            {
                return value;
            }
        }

        return NULL;
    }

    template<typename T>
    T* ReturnItemInCollectionPointers(FCollection<T*> collection, int index)
    {
        int count = 0;
        for (T* value : collection)
        {
            if (index == count++)
            {
                return value;
            }
        }

        return NULL;
    }

    template<typename T>
    std::vector<T> ToVector(FCollection<T> collection)
    {
        std::vector<T> extracted;
        for (T value : collection)
        {
            extracted.push_back(value);
        }

        return extracted;
    }

    template<typename T>
    bool Equals(std::vector<T> first, std::vector<T> second, std::string& errors)
    {
        if (first.size() != second.size())
        {
            errors = "Size did not match. 1. " + 
                std::to_string(first.size()) + " | 2. " + 
                std::to_string(second.size());
            return false;
        }

        int i = 0;
        for (T value : first)
        {
            if (value != second[i])
            {
                errors = "Value mismatch. Index:" + 
                    std::to_string(i) + " First: " + 
                    std::to_string(value) + " Second: " + 
                    std::to_string(second[i]);
                return false;
            }
            ++i;
        }

        return true;
    }

    template<typename T>
    bool Equals(std::vector<T*> first, std::vector<T*> second, std::string& errors)
    {
        if (first.size() != second.size())
        {
            errors = "Size did not match. 1. " +
                std::to_string(first.size()) + " | 2. " +
                std::to_string(second.size());
            return false;
        }

        int i = 0;
        for (T* value : first)
        {
            if (*value != *second[i])
            {
                errors = "Value mismatch. Index:" +
                    std::to_string(i) + " First: " +
                    std::to_string(*value) + " Second: " +
                    std::to_string(*second[i]);
                return false;
            }
            ++i;
        }

        return true;
    }

    template<typename T>
    bool CleanUp(std::vector<T*> collection)
    {
        for (T* value : collection)
        {
            delete value;
        }
        return true;
    }

    template<typename T>
    bool CleanUp(FCollection<T*> collection)
    {
        for (T* value : collection)
        {
            delete value;
        }
        return true;
    }

#pragma endregion
}