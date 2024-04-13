#pragma once
#include "../../LibraryIncludes.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Controls when Loops occur.
    /// </summary>
    class FrameTiming : Object
    {
    public:
        FrameTiming();
        virtual ~FrameTiming();

        /// <summary>
        /// Number of ticks required until the fixed update loop occurs.
        /// Zero means it will never happen.
        /// </summary>
        /// <returns>Number of ticks update loop will occur. </returns>
        int GetFixedUpdateLoopTiming() const;

        /// <summary>
        /// Number of ticks required until the fixed update loop occurs.
        /// Zero means it will never happen.
        /// </summary>
        /// <returns>How often fixed update is called with 1 meaning 1 second. </returns>
        float GetFixedUpdateLoopTimingAsSecond() const;

        /// <summary>
        /// Number of ticks between fixed update loop calls.
        /// </summary>
        /// <param name="newValue">New value for this timing. </param>
        void SetFixedUpdateLoopTiming(int newValue);
    private:

        /// <summary>
        /// Number of ticks required until the fixed update loop occurs.
        /// Zero means it will never happen.
        /// </summary>
        int m_fixedUpdateLoopTicks;

        /// <summary>
        /// Cached version of the Fixed update loop as seconds.
        /// 1 meaning 1 second.
        /// </summary>
        float m_fixedUpdateAsSecond;
    };
}