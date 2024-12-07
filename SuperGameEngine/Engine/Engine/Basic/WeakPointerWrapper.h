#pragma once
#include <memory>

namespace SuperGameEngine
{
    /// <summary>
    /// Wraps a weak pointer.
    /// </summary>
    /// <typeparam name="T">Type to wrap. </typeparam>
    template <typename T>
    class WeakPointerWrapper
    {
    public:
        // Default constructor
        WeakPointerWrapper() = default;

        /// <summary>
        /// Constructor with a pointer.
        /// </summary>
        /// <param name="weakPointer">Weak pointer to add. </param>
        explicit WeakPointerWrapper(const std::weak_ptr<T>& weakPointer)
            : m_weakPointer(weakPointer) {}

        /// <summary>
        /// Constructor with a pointer.
        /// </summary>
        /// <param name="sharedPointer">Shared pointer to add. Will be stored weak. </param>
        explicit WeakPointerWrapper(const std::shared_ptr<T>& sharedPointer)
            : m_weakPointer(sharedPointer) {}

        /// <summary>
        /// Set the weak pointer.
        /// </summary>
        /// <param name="weakPointer">New weak pointer. </param>
        void Set(const std::weak_ptr<T>& weakPointer)
        {
            m_weakPointer = weakPointer;
        }

        /// <summary>
        /// Reset the pointer.
        /// </summary>
        void Reset()
        {
            m_weakPointer.reset();
        }

        /// <summary>
        /// Get pointer.
        /// </summary>
        /// <returns>Pointer in a usable form.</returns>
        std::shared_ptr<T> Get() const
        {
            return m_weakPointer.lock();
        }

        /// <summary>
        /// Is the pointer valid.
        /// </summary>
        /// <returns>True means the pointer points to something. </returns>
        bool IsValid() const
        {
            return !m_weakPointer.expired();
        }

    private:

        /// <summary>
        /// Actual pointer.
        /// </summary>
        std::weak_ptr<T> m_weakPointer;
    };
}
