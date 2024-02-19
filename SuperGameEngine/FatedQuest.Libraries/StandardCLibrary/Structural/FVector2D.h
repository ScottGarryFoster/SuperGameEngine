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
        FVector2D(float x, float y);
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
        /// Sets the X Value.
        /// </summary>
        /// <param name="newValue">The new X value. </param>
        virtual void SetX(float newValue);

        /// <summary>
        /// Sets the Y Value.
        /// </summary>
        /// <param name="newValue">The new Y value. </param>
        virtual void SetY(float newValue);

        /// <summary>
        /// Sets both the x and y values.
        /// </summary>
        /// <param name="x">New X value. </param>
        /// <param name="y">New Y value. </param>
        virtual void SetXYValue(float x, float y);

        /// <summary>
        /// Adds two vectors together.
        /// </summary>
        /// <param name="other">Other vector to add. </param>
        /// <returns>Result of addition. </returns>
        FVector2D operator+(const FVector2D& other) const;

        /// <summary>
        /// Subtracts two vectors from one another.
        /// </summary>
        /// <param name="other">Other vector to subtract. </param>
        /// <returns>Result of subtraction. </returns>
        FVector2D operator-(const FVector2D& other) const;

        /// <summary>
        /// Multiplies the components of this vector by a scalar value.
        /// </summary>
        /// <param name="scalar">Amount to multiply by. </param>
        /// <returns>Vector multiplied. </returns>
        FVector2D operator*(float scalar) const;

        /// <summary>
        /// Divides the components of this vector by a scalar value.
        /// </summary>
        /// <param name="scalar">Amount to divide by. </param>
        /// <returns>Vector divided. </returns>
        FVector2D operator/(float scalar) const;

        /// <summary>
        /// Returns true if two vectors are approximately equal.
        /// Numbers must be equal within 5pts.
        /// 1.000001f == 1 = true but 1.00001f == 1 = false.
        /// See tests for further details.
        /// </summary>
        /// <param name="other">Other vector to test against. </param>
        /// <returns>True means equal. </returns>
        bool operator==(const FVector2D& other) const;

        /// <summary>
        /// A unit vector version of the current vector.
        /// A unit vector retains the direction of the original.
        /// </summary>
        /// <returns>The normalized vector (unit vector). </returns>
        FVector2D Normalize() const;

        /// <summary>
        /// The length of this vector.
        /// </summary>
        /// <returns>The magnitude of the vector. </returns>
        float Magnitude() const;

        /// <summary>
        /// The dot product between two vectors.
        /// </summary>
        /// <param name="other">Other vector to find the dot product. </param>
        /// <returns>The dot product. </returns>
        float DotProduct(const FVector2D& other) const;

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
