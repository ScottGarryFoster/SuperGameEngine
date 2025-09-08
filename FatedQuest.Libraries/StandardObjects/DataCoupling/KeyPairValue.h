#pragma once

/// <summary>
/// Stores two values next to one another and uses the names Key and Value.
/// </summary>
/// <typeparam name="KeyType">The key type. </typeparam>
/// <typeparam name="ValueType">The value type. </typeparam>
template <typename KeyType, typename ValueType>
struct KeyPairValue
{
    KeyType Key;
    ValueType Value;
};