#pragma once
#include "../Text/FString.h"

namespace StandardCLibrary
{
    /// <summary>
    /// Defines a point in space.
    /// </summary>
    class FPoint
    {
    public:
        FPoint();
        virtual ~FPoint();

        /// <summary>
        /// X cordinate.
        /// </summary>
        /// <returns>X cordinate. </returns>
        const int GetX() const;

        /// <summary>
        /// Y cordinate.
        /// </summary>
        /// <returns>Y cordinate. </returns>
        const int GetY() const;

        /// <summary>
        /// Prints the Point value.
        /// </summary>
        /// <returns>A string version of the point. </returns>
        const FString Print() const;

    private:

        /// <summary>
        /// X cordinate.
        /// </summary>
        int m_x;

        /// <summary>
        /// Y cordinate.
        /// </summary>
        int m_y;
    };
}