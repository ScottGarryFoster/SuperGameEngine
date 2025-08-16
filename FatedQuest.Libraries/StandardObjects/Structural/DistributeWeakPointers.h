#pragma once
#include <memory>

namespace FatedQuestLibraries
{
    /// <summary>
    /// Allows an object to own a weak pointer to the given type.
    /// </summary>
    /// <typeparam name="T">Type to store.</typeparam>
    template <typename T>
    class DistributeWeakPointers
    {
    public:
        /// <summary>
        /// Get the weak pointer for this object.
        /// </summary>
        /// <returns>Get the weak pointer for this object. </returns>
        inline std::weak_ptr<T> GetWeakDistributed()
        {
            return m_weakPtr;
        }

        /// <summary>
        /// Get the weak pointer for this object.
        /// </summary>
        /// <returns>Get the weak pointer for this object. </returns>
        inline std::weak_ptr<T> GetWeakDistributed() const
        {
            return m_weakPtr;
        }

        /// <summary>
        /// Update the weak pointer for this object.
        /// </summary>
        /// <param name="pointer">New weak pointer. </param>
        inline void UpdateDistributedWeakPointer(const std::weak_ptr<T>& pointer)
        {
            m_weakPtr = pointer;
        }

    private:
        /// <summary>
        /// Pointer stored.
        /// </summary>
        std::weak_ptr<T> m_weakPtr;
    };
}
