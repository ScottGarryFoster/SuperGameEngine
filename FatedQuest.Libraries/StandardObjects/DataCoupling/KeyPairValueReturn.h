#pragma once

namespace FatedQuestLibraries
{
    /// <summary>
    /// Stores two values next to one another and uses the names Key and Value.
    /// </summary>
    /// <typeparam name="KeyType">The key type. </typeparam>
    /// <typeparam name="ValueType">The value type. </typeparam>
    template <typename KeyType, typename ValueType>
    struct KeyPairValueReturn
    {
    public:
        KeyType Key;
        ValueType Value;
        bool WasError = false;

        /// <summary>
        /// Returns a <see cref="KeyPairValueReturn"/> in an error state.
        /// </summary>
        /// <returns>Returns a <see cref="KeyPairValueReturn"/> in an error state. </returns>
        static KeyPairValueReturn Error()
        {
            return { .WasError = true };
        }

        /// <summary>
        /// True when there was an error.
        /// </summary>
        /// <returns>True when there was an error. </returns>
        [[nodiscard]] bool HasAnError() const
        {
            return WasError;
        }
    };
}