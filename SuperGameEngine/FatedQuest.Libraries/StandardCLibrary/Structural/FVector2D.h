#pragma once
#include "../Text/FString.h"

namespace StandardCLibrary
{
    /// <summary>
    /// A point or direction in space.
    /// </summary>
    class FVector2D
    {
    public:
        FVector2D();
        virtual ~FVector2D();

        /// <summary>
        /// X cordinate.
        /// </summary>
        /// <returns>X cordinate. </returns>
        const float GetX() const;

        /// <summary>
        /// Y cordinate.
        /// </summary>
        /// <returns>Y cordinate. </returns>
        const float GetY() const;

        /// <summary>
        /// Prints the Point value.
        /// </summary>
        /// <returns>A string version of the point. </returns>
        const FString Print() const;

    private:

        /// <summary>
        /// X cordinate.
        /// </summary>
        float m_x;

        /// <summary>
        /// Y cordinate.
        /// </summary>
        float m_y;
    };
}
