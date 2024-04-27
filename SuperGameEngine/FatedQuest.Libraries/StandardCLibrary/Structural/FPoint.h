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
        FPoint(int x, int y);
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
        /// Sets the X Value.
        /// </summary>
        /// <param name="newValue">The new X value. </param>
        virtual void SetX(int newValue);

        /// <summary>
        /// Sets the Y Value.
        /// </summary>
        /// <param name="newValue">The new Y value. </param>
        virtual void SetY(int newValue);

        /// <summary>
        /// Sets both the x and y values.
        /// </summary>
        /// <param name="x">New X value. </param>
        /// <param name="y">New Y value. </param>
        virtual void SetXYValue(int x, int y);

        /// <summary>
        /// Are equal to one another.
        /// </summary>
        /// <param name="other">Other vector to test against. </param>
        /// <returns>True means equal. </returns>
        bool operator==(const FPoint& other) const;

        /// <summary>
        /// Adds two points together.
        /// </summary>
        /// <param name="other">Other vector to add. </param>
        /// <returns>Result of addition. </returns>
        FPoint operator+(const FPoint& other) const;

        /// <summary>
        /// Adds two points together.
        /// </summary>
        /// <param name="other">Other vector to add. </param>
        /// <returns>Result of addition. </returns>
        FPoint& operator+=(const FPoint& other);

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