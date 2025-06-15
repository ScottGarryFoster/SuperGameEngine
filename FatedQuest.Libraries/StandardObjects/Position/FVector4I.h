#pragma once
#include <string>

namespace FatedQuestLibraries
{
    class FPoint;
    class FVector4D;
    class FVector4F;

    /// <summary>
    /// A point or direction in space.
    /// </summary>
    class FVector4I
    {
    public:
        /// <summary>
        /// Default constructor.
        /// </summary>
        FVector4I();

        /// <summary>
        /// Create an FVector and give it some values.
        /// </summary>
        /// <param name="x">X location. </param>
        /// <param name="y">Y location. </param>
        /// <param name="z">Z location. </param>
        /// <param name="w">W location. </param>
        FVector4I(int x, int y, int z, int w);

        /// <summary>
        /// Use the public data of an FVector to create another one.
        /// </summary>
        /// <param name="other">Other FVector to use.</param>
        FVector4I(const FVector4I& other);

        /// <summary>
        /// Use the public data of an FPoint to create another one.
        /// </summary>
        /// <param name="other">Other FPoint to use.</param>
        FVector4I(const FPoint& other);

        /// <summary>
        /// Creates from a FVector4D.
        /// </summary>
        /// <param name="other">FVector4D to create from. </param>
        FVector4I(const FVector4D& other);

        /// <summary>
        /// Creates from a FVector4F.
        /// </summary>
        /// <param name="other">FVector3I to create from. </param>
        FVector4I(const FVector4F& other);

        virtual ~FVector4I();

        /// <summary>
        /// X coordinate.
        /// </summary>
        /// <returns>X coordinate. </returns>
        [[nodiscard]] int GetX() const;

        /// <summary>
        /// Y coordinate.
        /// </summary>
        /// <returns>Y coordinate. </returns>
        [[nodiscard]] int GetY() const;

        /// <summary>
        /// Z coordinate.
        /// </summary>
        /// <returns>Z coordinate. </returns>
        [[nodiscard]] int GetZ() const;

        /// <summary>
        /// W coordinate.
        /// </summary>
        /// <returns>W coordinate. </returns>
        [[nodiscard]] int GetW() const;

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
        /// Sets the Z Value.
        /// </summary>
        /// <param name="newValue">The new Z value. </param>
        virtual void SetZ(int newValue);

        /// <summary>
        /// Sets the W Value.
        /// </summary>
        /// <param name="newValue">The new W value. </param>
        virtual void SetW(int newValue);

        /// <summary>
        /// Sets both the x and y values.
        /// Z is untouched.
        /// </summary>
        /// <param name="x">New X value. </param>
        /// <param name="y">New Y value. </param>
        virtual void SetXYValue(int x, int y);

        /// <summary>
        /// Sets the X and Y based upon the value of another Vector.
        /// </summary>
        /// <param name="other">Other vector to obtain the value from. </param>
        virtual void SetValue(const FVector4I& other);

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
        virtual void SetXYZValue(int x, int y, int z);

        /// <summary>
        /// Sets the x y z w values.
        /// </summary>
        /// <param name="x">New X value. </param>
        /// <param name="y">New Y value. </param>
        /// <param name="z">New Z value. </param>
        /// <param name="w">New W value. </param>
        virtual void SetXYZWValue(int x, int y, int z, int w);

        /// <summary>
        /// Adds two vectors together.
        /// </summary>
        /// <param name="other">Other vector to add. </param>
        /// <returns>Result of addition. </returns>
        FVector4I operator+(const FVector4I& other) const;

        /// <summary>
        /// Adds two vectors together.
        /// </summary>
        /// <param name="other">Other vector to add. </param>
        /// <returns>Result of addition. </returns>
        FVector4I& operator+=(const FVector4I& other);

        /// <summary>
        /// Subtracts two vectors from one another.
        /// </summary>
        /// <param name="other">Other vector to subtract. </param>
        /// <returns>Result of subtraction. </returns>
        FVector4I operator-(const FVector4I& other) const;

        /// <summary>
        /// Subtracts two vectors from one another.
        /// </summary>
        /// <param name="other">Other vector to subtract. </param>
        /// <returns>Result of subtraction. </returns>
        FVector4I& operator-=(const FVector4I& other);

        /// <summary>
        /// Multiplies the components of this vector by a scalar value.
        /// </summary>
        /// <param name="scalar">Amount to multiply by. </param>
        /// <returns>Vector multiplied. </returns>
        FVector4I operator*(int scalar) const;

        /// <summary>
        /// Multiplies the components of this vector by a scalar value.
        /// </summary>
        /// <param name="scalar">Amount to multiply by. </param>
        /// <returns>Vector multiplied. </returns>
        FVector4I& operator*=(int scalar);

        /// <summary>
        /// Divides the components of this vector by a scalar value.
        /// </summary>
        /// <param name="scalar">Amount to divide by. </param>
        /// <returns>Vector divided. </returns>
        FVector4I operator/(int scalar) const;

        /// <summary>
        /// Divides the components of this vector by a scalar value.
        /// </summary>
        /// <param name="scalar">Amount to divide by. </param>
        /// <returns>Vector divided. </returns>
        FVector4I& operator/=(int scalar);

        /// <summary>
        /// Returns true if two vectors are approximately equal.
        /// Numbers must be equal within 5pts.
        /// 1.000001f == 1 = true but 1.00001f == 1 = false.
        /// See tests for further details.
        /// </summary>
        /// <param name="other">Other vector to test against. </param>
        /// <returns>True means equal. </returns>
        bool operator==(const FVector4I& other) const;

        /// <summary>
        /// A unit vector version of the current vector.
        /// A unit vector retains the direction of the original.
        /// </summary>
        /// <returns>The normalized vector (unit vector). </returns>
        [[nodiscard]] FVector4I Normalize() const;

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
        [[nodiscard]] int DotProduct(const FVector4I& other) const;

        /// <summary>
        /// Calculates the distance between two points.
        /// </summary>
        /// <param name="other">Other point to calculate between. </param>
        /// <returns>The distance between the two points. </returns>
        [[nodiscard]] float DistanceBetween(const FVector4I& other) const;

        /// <summary>
        /// Prints the Point value.
        /// </summary>
        /// <returns>A string version of the point. </returns>
        [[nodiscard]] std::string Print() const;

    private:

        /// <summary>
        /// X coordinate.
        /// </summary>
        int m_x;

        /// <summary>
        /// Y coordinate.
        /// </summary>
        int m_y;

        /// <summary>
        /// Z coordinate.
        /// </summary>
        int m_z;

        /// <summary>
        /// W coordinate.
        /// </summary>
        int m_w;
    };
}