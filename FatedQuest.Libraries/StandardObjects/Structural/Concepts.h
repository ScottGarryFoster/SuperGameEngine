#pragma once
namespace FatedQuestLibraries
{
    // <summary>
    // Concepts are used to restrict templated code.
    // They are easier to use and more readable than other templated code.
    // To use:
    // requires CONCEPT TEMPLATE
    // for example:
    // requires Erasable<ValueType>
    // </summary>

    template <typename T>
    concept Erasable = requires(T t, typename T::iterator it)
    {
        t.erase(it);
    };
}