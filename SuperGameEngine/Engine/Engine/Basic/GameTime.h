#pragma once
#include <cstdint>

namespace SuperGameEngine
{
    /// <summary>
    /// Stores and updates GameTime.
    /// </summary>
    class GameTime
    {
    public:
        /// <summary>
        /// The ticks since the last non-physics based updated loop.
        /// </summary>
        [[nodiscard]] virtual std::uint64_t TimeDelta() const = 0;

        /// <summary>
        /// Time the application has been running.
        /// </summary>
        /// <returns>Ticks the application has been running. </returns>
        [[nodiscard]] virtual std::uint64_t AllTime() const = 0;

        /// <summary>
        /// Time the current window/renderer has been running.
        /// </summary>
        /// <returns>Ticks the current window/renderer has been running. </returns>
        [[nodiscard]] virtual std::uint64_t WindowTime() const = 0;
    };
}

