#pragma once

namespace StandardCLibrary
{
    /// <summary>
    /// Defines a length of time.
    /// Note: Finish this and make it work when you have the time.
    /// </summary>
    class Timespan
    {
    public:
        Timespan();

        void SetTimeByTick(int newTick);

        void SetTimeByTick(long int newTick);

        void SetTimeByTick(unsigned long int newTick);

        void SetTimeByMilliseconds(int newValue);

        void SetTimeBySeconds(int newValue);

        void SetTimeByMinutes(int newValue);

        void SetTimeByHours(int newValue);

        void SetTimeByDays(int newValue);

        void AddTicks(int addValue);

        void AddTicks(long int addValue);

        void AddTicks(unsigned long int addValue);

        void AddMilliseconds(int addValue);

        void AddSeconds(int addValue);

        void AddMinutes(int addValue);

        void AddHours(int addMinutes);

        void AddDays(int addValue);


        /// <summary>
        /// As a complete time statement, how many ticks are on the clock before
        /// counting the tick as a millisecond?
        /// </summary>
        /// <returns>The number of ticks on the clock. </returns>
        int GetTicks();

        /// <summary>
        /// As a complete time statement, how many milliseconds are on the clock before
        /// counting the milliseconds as a second?
        /// </summary>
        /// <returns>The number of milliseconds on the clock. </returns>
        int GetMilliseconds();

        /// <summary>
        /// As a complete time statement, how many seconds are on the clock before
        /// counting the seconds as a minute?
        /// </summary>
        /// <returns>The number of seconds on the clock. </returns>
        int GetSeconds();

        /// <summary>
        /// As a complete time statement, how many minutes are on the clock before
        /// counting the seconds as an hour?
        /// </summary>
        /// <returns>The number of minutes on the clock. </returns>
        int GetMinutes();

        /// <summary>
        /// As a complete time statement, how many hours are on the clock before
        /// counting the hours as a day?
        /// </summary>
        /// <returns>The number of hours on the clock. </returns>
        int GetHours();

        /// <summary>
        /// As a complete time statement, how many days are on the clock.
        /// </summary>
        /// <returns>The number of days on the clock. </returns>
        int GetDays();

        /// <summary>
        /// In total the number of ticks.
        /// </summary>
        /// <returns>In total on the clock the number of ticks. </returns>
        /// <remark>Roughly 49 days in this will overflow. </remark>
        unsigned long long int GetTotalTicks();

        /// <summary>
        /// In total the number of milliseconds.
        /// </summary>
        /// <returns>In total on the clock the number of milliseconds. </returns>
        unsigned long long int GetTotalMilliseconds();

    private:
        /// <summary>
        /// The total ticks for the entire timespan.
        /// A tick is 1000 milliseconds.
        /// </summary>
        unsigned long long int m_totalTicks;
    };
}