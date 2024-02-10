#include <vector>
#include "../../LibraryIncludes.h"
#include "../../../StandardCLibrary/Collection/Organised/FCollection.hpp"

using namespace StandardCLibrary;
namespace StandardCLibraryTests_Collection_Organised
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