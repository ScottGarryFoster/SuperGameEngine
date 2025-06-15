#pragma once
#include <string>

namespace FatedQuestLibraries
{
    class FPoint;
    class FVector4F;
    class FVector4I;

    /// <summary>
    /// A point or direction in space.
    /// </summary>
    class FVector4D
    {
    public:
        /// <summary>
        /// Default constructor.
        /// </summary>
        FVector4D();

        /// <summary>
        /// Create an FVector and give it some values.
        /// </summary>
        /// <param name="x">X location. </param>
        /// <param name="y">Y location. </param>
        /// <param name="z">Z location. </param>
        /// <param name="w">W location. </param>
        FVector4D(double x, double y, double z, double w);

        /// <summary>
        /// Use the public data of an FVector to create another one.
        /// </summary>
        /// <param name="other">Other FVector to use.</param>
        FVector4D(const FVector4D& other);

        /// <summary>
        /// Use the public data of an FPoint to create another one.
        /// </summary>
        /// <param name="other">Other FPoint to use.</param>
        FVector4D(const FPoint& other);

        /// <summary>
        /// Creates from a FVector4F.
        /// </summary>
        /// <param name="other">FVector4F to create from. </param>
        FVector4D(const FVector4F& other);

        /// <summary>
        /// Creates from a FVector3I.
        /// </summary>
        /// <param name="other">FVector3I to create from. </param>
        FVector4D(const FVector4I& other);

        virtual ~FVector4D();

        /// <summary>
        /// X coordinate.
        /// </summary>
        /// <returns>X coordinate. </returns>
        [[nodiscard]] double GetX() const;

        /// <summary>
        /// Y coordinate.
        /// </summary>
        /// <returns>Y coordinate. </returns>
        [[nodiscard]] double GetY() const;

        /// <summary>
        /// Z coordinate.
        /// </summary>
        /// <returns>Z coordinate. </returns>
        [[nodiscard]] double GetZ() const;

        /// <summary>
        /// W coordinate.
        /// </summary>
        /// <returns>W coordinate. </returns>
        [[nodiscard]] double GetW() const;

        /// <summary>
        /// Sets the X Value.
        /// </summary>
        /// <param name="newValue">The new X value. </param>
        virtual void SetX(double newValue);

        /// <summary>
        /// Sets the Y Value.
        /// </summary>
        /// <param name="newValue">The new Y value. </param>
        virtual void SetY(double newValue);

        /// <summary>
        /// Sets the Z Value.
        /// </summary>
        /// <param name="newValue">The new Z value. </param>
        virtual void SetZ(double newValue);

        /// <summary>
        /// Sets the W Value.
        /// </summary>
        /// <param name="newValue">The new W value. </param>
        virtual void SetW(double newValue);

        /// <summary>
        /// Sets both the x and y values.
        /// Z is untouched.
        /// </summary>
        /// <param name="x">New X value. </param>
        /// <param name="y">New Y value. </param>
        virtual void SetXYValue(double x, double y);

        /// <summary>
        /// Sets the X and Y based upon the value of another Vector.
        /// </summary>
        /// <param name="other">Other vector to obtain the value from. </param>
        virtual void SetValue(const FVector4D& other);

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
        virtual void SetXYZValue(double x, double y, double z);

        /// <summary>
        /// Sets the x y z w values.
        /// </summary>
        /// <param name="x">New X value. </param>
        /// <param name="y">New Y value. </param>
        /// <param name="z">New Z value. </param>
        /// <param name="w">New W value. </param>
        virtual void SetXYZWValue(double x, double y, double z, double w);

        /// <summary>
        /// Adds two vectors together.
        /// </summary>
        /// <param name="other">Other vector to add. </param>
        /// <returns>Result of addition. </returns>
        FVector4D operator+(const FVector4D& other) const;

        /// <summary>
        /// Adds two vectors together.
        /// </summary>
        /// <param name="other">Other vector to add. </param>
        /// <returns>Result of addition. </returns>
        FVector4D& operator+=(const FVector4D& other);

        /// <summary>
        /// Subtracts two vectors from one another.
        /// </summary>
        /// <param name="other">Other vector to subtract. </param>
        /// <returns>Result of subtraction. </returns>
        FVector4D operator-(const FVector4D& other) const;

        /// <summary>
        /// Subtracts two vectors from one another.
        /// </summary>
        /// <param name="other">Other vector to subtract. </param>
        /// <returns>Result of subtraction. </returns>
        FVector4D& operator-=(const FVector4D& other);

        /// <summary>
        /// Multiplies the components of this vector by a scalar value.
        /// </summary>
        /// <param name="scalar">Amount to multiply by. </param>
        /// <returns>Vector multiplied. </returns>
        FVector4D operator*(double scalar) const;

        /// <summary>
        /// Multiplies the components of this vector by a scalar value.
        /// </summary>
        /// <param name="scalar">Amount to multiply by. </param>
        /// <returns>Vector multiplied. </returns>
        FVector4D& operator*=(double scalar);

        /// <summary>
        /// Divides the components of this vector by a scalar value.
        /// </summary>
        /// <param name="scalar">Amount to divide by. </param>
        /// <returns>Vector divided. </returns>
        FVector4D operator/(double scalar) const;

        /// <summary>
        /// Divides the components of this vector by a scalar value.
        /// </summary>
        /// <param name="scalar">Amount to divide by. </param>
        /// <returns>Vector divided. </returns>
        FVector4D& operator/=(double scalar);

        /// <summary>
        /// Returns true if two vectors are approximately equal.
        /// Numbers must be equal within 5pts.
        /// 1.000001f == 1 = true but 1.00001f == 1 = false.
        /// See tests for further details.
        /// </summary>
        /// <param name="other">Other vector to test against. </param>
        /// <returns>True means equal. </returns>
        bool operator==(const FVector4D& other) const;

        /// <summary>
        /// A unit vector version of the current vector.
        /// A unit vector retains the direction of the original.
        /// </summary>
        /// <returns>The normalized vector (unit vector). </returns>
        [[nodiscard]] FVector4D Normalize() const;

        /// <summary>
        /// The length of this vector.
        /// </summary>
        /// <returns>The magnitude of the vector. </returns>
        [[nodiscard]] double Magnitude() const;

        /// <summary>
        /// The dot product between two vectors.
        /// </summary>
        /// <param name="other">Other vector to find the dot product. </param>
        /// <returns>The dot product. </returns>
        [[nodiscard]] double DotProduct(const FVector4D& other) const;

        /// <summary>
        /// Calculates the distance between two points.
        /// </summary>
        /// <param name="other">Other point to calculate between. </param>
        /// <returns>The distance between the two points. </returns>
        [[nodiscard]] double DistanceBetween(const FVector4D& other) const;

        /// <summary>
        /// Prints the Point value.
        /// </summary>
        /// <returns>A string version of the point. </returns>
        [[nodiscard]] std::string Print() const;

    private:

        /// <summary>
        /// X coordinate.
        /// </summary>
        double m_x;

        /// <summary>
        /// Y coordinate.
        /// </summary>
        double m_y;

        /// <summary>
        /// Z coordinate.
        /// </summary>
        double m_z;

        /// <summary>
        /// W coordinate.
        /// </summary>
        double m_w;
    };
}
