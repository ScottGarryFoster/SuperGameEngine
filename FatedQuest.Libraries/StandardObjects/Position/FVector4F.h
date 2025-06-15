#pragma once
#include <string>

namespace FatedQuestLibraries
{
    class FPoint;
    class FVector4D;
    class FVector4I;

    /// <summary>
    /// A point or direction in space.
    /// </summary>
    class FVector4F
    {
    public:
        /// <summary>
        /// Default constructor.
        /// </summary>
        FVector4F();

        /// <summary>
        /// Create an FVector and give it some values.
        /// </summary>
        /// <param name="x">X location. </param>
        /// <param name="y">Y location. </param>
        /// <param name="z">Z location. </param>
        /// <param name="w">W location. </param>
        FVector4F(float x, float y, float z, float w);

        /// <summary>
        /// Use the public data of an FVector to create another one.
        /// </summary>
        /// <param name="other">Other FVector to use.</param>
        FVector4F(const FVector4F& other);

        /// <summary>
        /// Use the public data of an FPoint to create another one.
        /// </summary>
        /// <param name="other">Other FPoint to use.</param>
        FVector4F(const FPoint& other);

        /// <summary>
        /// Creates from a FVector4D.
        /// </summary>
        /// <param name="other">FVector4D to create from. </param>
        FVector4F(const FVector4D& other);

        /// <summary>
        /// Creates from a FVector3I.
        /// </summary>
        /// <param name="other">FVector3I to create from. </param>
        FVector4F(const FVector4I& other);

        virtual ~FVector4F();

        /// <summary>
        /// X coordinate.
        /// </summary>
        /// <returns>X coordinate. </returns>
        [[nodiscard]] float GetX() const;

        /// <summary>
        /// Y coordinate.
        /// </summary>
        /// <returns>Y coordinate. </returns>
        [[nodiscard]] float GetY() const;

        /// <summary>
        /// Z coordinate.
        /// </summary>
        /// <returns>Z coordinate. </returns>
        [[nodiscard]] float GetZ() const;

        /// <summary>
        /// W coordinate.
        /// </summary>
        /// <returns>W coordinate. </returns>
        [[nodiscard]] float GetW() const;

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
        /// Sets the Z Value.
        /// </summary>
        /// <param name="newValue">The new Z value. </param>
        virtual void SetZ(float newValue);

        /// <summary>
        /// Sets the W Value.
        /// </summary>
        /// <param name="newValue">The new W value. </param>
        virtual void SetW(float newValue);

        /// <summary>
        /// Sets both the x and y values.
        /// Z is untouched.
        /// </summary>
        /// <param name="x">New X value. </param>
        /// <param name="y">New Y value. </param>
        virtual void SetXYValue(float x, float y);

        /// <summary>
        /// Sets the X and Y based upon the value of another Vector.
        /// </summary>
        /// <param name="other">Other vector to obtain the value from. </param>
        virtual void SetValue(const FVector4F& other);

        /// <summary>
        /// Sets the X and Y values based on the value in an FPoint.
        /// </summary>
        /// <param name="other">Other FPoint location. </param>
        virtual void SetXYValue(const FPoint& other);

        /// <summary>
        /// Sets the x y z values.
        /// </summary>
        /// <param name="x">New X value. </param>
        /// <param name="y">New Y value. </param>
        /// <param name="z">New Z value. </param>
        virtual void SetXYZValue(float x, float y, float z);

        /// <summary>
        /// Sets the x y z w values.
        /// </summary>
        /// <param name="x">New X value. </param>
        /// <param name="y">New Y value. </param>
        /// <param name="z">New Z value. </param>
        /// <param name="w">New W value. </param>
        virtual void SetXYZWValue(float x, float y, float z, float w);

        /// <summary>
        /// Adds two vectors together.
        /// </summary>
        /// <param name="other">Other vector to add. </param>
        /// <returns>Result of addition. </returns>
        FVector4F operator+(const FVector4F& other) const;

        /// <summary>
        /// Adds two vectors together.
        /// </summary>
        /// <param name="other">Other vector to add. </param>
        /// <returns>Result of addition. </returns>
        FVector4F& operator+=(const FVector4F& other);

        /// <summary>
        /// Subtracts two vectors from one another.
        /// </summary>
        /// <param name="other">Other vector to subtract. </param>
        /// <returns>Result of subtraction. </returns>
        FVector4F operator-(const FVector4F& other) const;

        /// <summary>
        /// Subtracts two vectors from one another.
        /// </summary>
        /// <param name="other">Other vector to subtract. </param>
        /// <returns>Result of subtraction. </returns>
        FVector4F& operator-=(const FVector4F& other);

        /// <summary>
        /// Multiplies the components of this vector by a scalar value.
        /// </summary>
        /// <param name="scalar">Amount to multiply by. </param>
        /// <returns>Vector multiplied. </returns>
        FVector4F operator*(float scalar) const;

        /// <summary>
        /// Multiplies the components of this vector by a scalar value.
        /// </summary>
        /// <param name="scalar">Amount to multiply by. </param>
        /// <returns>Vector multiplied. </returns>
        FVector4F& operator*=(float scalar);

        /// <summary>
        /// Divides the components of this vector by a scalar value.
        /// </summary>
        /// <param name="scalar">Amount to divide by. </param>
        /// <returns>Vector divided. </returns>
        FVector4F operator/(float scalar) const;

        /// <summary>
        /// Divides the components of this vector by a scalar value.
        /// </summary>
        /// <param name="scalar">Amount to divide by. </param>
        /// <returns>Vector divided. </returns>
        FVector4F& operator/=(float scalar);

        /// <summary>
        /// Returns true if two vectors are approximately equal.
        /// Numbers must be equal within 5pts.
        /// 1.000001f == 1 = true but 1.00001f == 1 = false.
        /// See tests for further details.
        /// </summary>
        /// <param name="other">Other vector to test against. </param>
        /// <returns>True means equal. </returns>
        bool operator==(const FVector4F& other) const;

        /// <summary>
        /// A unit vector version of the current vector.
        /// A unit vector retains the direction of the original.
        /// </summary>
        /// <returns>The normalized vector (unit vector). </returns>
        [[nodiscard]] FVector4F Normalize() const;

        /// <summary>
        /// The length of this vector.
        /// </summary>
        /// <returns>The magnitude of the vector. </returns>
        [[nodiscard]] float Magnitude() const;

        /// <summary>
        /// The dot product between two vectors.
        /// </summary>
        /// <param name="other">Other vector to find the dot product. </param>
        /// <returns>The dot product. </returns>
        [[nodiscard]] float DotProduct(const FVector4F& other) const;

        /// <summary>
        /// Calculates the distance between two points.
        /// </summary>
        /// <param name="other">Other point to calculate between. </param>
        /// <returns>The distance between the two points. </returns>
        [[nodiscard]] float DistanceBetween(const FVector4F& other) const;

        /// <summary>
        /// Prints the Point value.
        /// </summary>
        /// <returns>A string version of the point. </returns>
        [[nodiscard]] std::string Print() const;

    private:

        /// <summary>
        /// X coordinate.
        /// </summary>
        float m_x;

        /// <summary>
        /// Y coordinate.
        /// </summary>
        float m_y;

        /// <summary>
        /// Z coordinate.
        /// </summary>
        float m_z;

        /// <summary>
        /// W coordinate.
        /// </summary>
        float m_w;
    };
}