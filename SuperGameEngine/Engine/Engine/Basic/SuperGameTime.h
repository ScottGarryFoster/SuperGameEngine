#pragma once
#include "GameTime.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Stores and updates GameTime.
    /// </summary>
    class SuperGameTime : public GameTime
    {
    public:
        SuperGameTime();
        virtual ~SuperGameTime();

        /// <summary>
        /// The ticks since the last non-physics based updated loop.
        /// </summary>
        [[nodiscard]] virtual std::uint64_t TimeDelta() const override;

        /// <summary>
        /// Time the application has been running.
        /// </summary>
        /// <returns>Ticks the application has been running. </returns>
        [[nodiscard]] virtual std::uint64_t AllTime() const override;

        /// <summary>
        /// Time the current window/renderer has been running.
        /// </summary>
        /// <returns>Ticks the current window/renderer has been running. </returns>
        [[nodiscard]] virtual std::uint64_t WindowTime() const override;

        /// <summary>
        /// Set the ticks since last frame.
        /// Will update the above.
        /// </summary>
        /// <param name="ticks">Ticks since last frame. </param>
        void SetTicksSinceLastFrame(uint64_t ticks);

        /// <summary>
        /// Reset window time.
        /// </summary>
        void ResetWindowTime();

    private:
        /// <summary>
        /// Time since last frame, including the amount of time the last frame took.
        /// This is a prediction of how much you need to factor in when adjusting in
        /// the update loop.
        /// </summary>
        uint64_t m_timeDelta;

        /// <summary>
        /// Uptime for the entire application.
        /// </summary>
        uint64_t m_allTime;

        /// <summary>
        /// Window uptime.
        /// </summary>
        uint64_t m_windowUpTime;
    };
}

