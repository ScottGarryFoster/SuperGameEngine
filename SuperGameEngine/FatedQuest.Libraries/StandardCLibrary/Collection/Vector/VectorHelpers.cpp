#include "VectorHelpers.h"
using namespace StandardCLibrary;

template<typename T>
bool VectorHelpers::RemoveValue(std::vector<T>& vector, const T& valueToRemove)
{
    auto it = std::find(vector.begin(), vector.end(), valueToRemove);
    if (it != vector.end())
    {
        vector.erase(it);
        return true;
    }
    
    return false;
}

template<typename T>
bool VectorHelpers::RemoveAt(std::vector<T>& vector, size_t index)
{
    if (index < vector.size())
    {
        vector.erase(vector.begin() + index);
        return true;
    }

    return false;
}