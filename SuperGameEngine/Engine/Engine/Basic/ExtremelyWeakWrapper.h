#pragma once
#include <memory>

#include "PointerState.h"

namespace SuperGameEngine
{
    /// <summary>
    /// A weak pointer wrapper which is so weak that it never has any garbage collection
    /// ties to the original.
    /// Used for situations where you might want to connect a child to its parent.
    /// In these cases, **never** refer to the raw pointer and always refer to this type using
    /// the safe elements to ensure you access actual memory which is cleaned up.
    /// </summary>
    /// <typeparam name="T">Type to wrap. </typeparam>
    template <typename T>
    class ExtremelyWeakWrapper
    {
    public:
        ExtremelyWeakWrapper(T* object)
        {
            m_pointer = object;
            UpdatePointerState(object);
        }

        [[nodiscard]] PointerState GetState() const
        {
            return m_pointerState;
        }

        T* Get() const
        {
            return m_pointer;
        }

        void Set(T* object)
        {
            m_pointer = object;
            UpdatePointerState(object);
        }

    private:

        /// <summary>
        /// Actual pointer.
        /// </summary>
        T* m_pointer;

        /// <summary>
        /// The current state of the pointer.
        /// </summary>
        PointerState m_pointerState;

        /// <summary>
        /// Updates the state of the pointer.
        /// </summary>
        /// <param name="object">Current object pointer. </param>
        void UpdatePointerState(const T* object)
        {
            if (object)
            {
                m_pointerState = PointerState::Active;
            }
            else
            {
                m_pointerState = PointerState::Destroyed;
            }
        }
    };
}
