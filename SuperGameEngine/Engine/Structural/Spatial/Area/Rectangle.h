#pragma once
#include "../../../FatedQuestReferences.h"

using namespace FatedQuestLibraries;

namespace SuperGameEngine
{
    class Circle;

    /// <summary>
    /// Describes a rectangle shape in 2D Space.
    /// </summary>
    class Rectangle
    {
    public:
        /// <summary>
        /// Constructs a rectangle.
        /// </summary>
        /// <param name="x">X location. </param>
        /// <param name="y">Y Location. </param>
        /// <param name="width">Width of the Rectangle. </param>
        /// <param name="height">Height of the Rectangle. </param>
        Rectangle(float x, float y, float width, float height);

        /// <summary>
        /// Constructs a rectangle.
        /// </summary>
        /// <param name="xy">X Y position of the rectangle. </param>
        /// <param name="widthHeight">Width and Height of the Rectangle. </param>
        Rectangle(float xy, float widthHeight);

        /// <summary>
        /// Does this shape equal the other functionally.
        /// </summary>
        /// <param name="other">Other shape to compare to. </param>
        /// <returns>True means functionally equal but not pointer equal. </returns>
        bool operator==(const Rectangle& other) const;

        /// <summary>
        /// The left X of the Rectangle.
        /// </summary>
        /// <returns>The Left X coordinate of the Rectangle. </returns>
        [[nodiscard]] float GetLeft() const;

        /// <summary>
        /// The right X of the Rectangle. 
        /// </summary>
        /// <returns>The Right X coordinate of the Rectangle. </returns>
        [[nodiscard]] float GetRight() const;

        /// <summary>
        /// The top Y of the Rectangle. 
        /// </summary>
        /// <returns>The Top Y coordinate of the Rectangle. </returns>
        [[nodiscard]] float GetTop() const;

        /// <summary>
        /// The bottom Y of the Rectangle.
        /// </summary>
        /// <returns>The bottom Y coordinate of the Rectangle. </returns>
        [[nodiscard]] float GetBottom() const;

        /// <summary>
        /// The width of the rectangle.
        /// </summary>
        /// <returns>The width of the rectangle. </returns>
        [[nodiscard]] float GetWidth() const;

        /// <summary>
        /// The Height of the rectangle.
        /// </summary>
        /// <returns>The Height of the rectangle. </returns>
        [[nodiscard]] float GetHeight() const;

        /// <summary>
        /// The top left X and Y point of the Rectangle.
        /// </summary>
        /// <returns>The top left X and Y point of the Rectangle. </returns>
        [[nodiscard]] FVector2D GetTopLeft() const;

        /// <summary>
        /// The bottom Left X Y point of the Rectangle.
        /// </summary>
        /// <returns>The bottom Left X Y point of the Rectangle. </returns>
        [[nodiscard]] FVector2D GetBottomRight() const;

        /// <summary>
        /// Sets the location of the Rectangle.
        /// </summary>
        /// <param name="x">X location to update. </param>
        /// <param name="y">Y location to update. </param>
        void SetLocation(float x, float y);

        /// <summary>
        /// Updates the X location.
        /// </summary>
        /// <param name="x">New X value. </param>
        void SetX(float x);

        /// <summary>
        /// Updates the Y location.
        /// </summary>
        /// <param name="y">New Y value. </param>
        void SetY(float y);

        /// <summary>
        /// Updates the size of the rectangle.
        /// </summary>
        /// <param name="width">The new width of the rectangle. </param>
        /// <param name="height">The new height of the rectangle. </param>
        void SetSize(float width, float height);

        /// <summary>
        /// Updates the width of the Rectangle.
        /// </summary>
        /// <param name="width">The new Width of the Rectangle. </param>
        void SetWidth(float width);

        /// <summary>
        /// Updates the height of the Rectangle.
        /// </summary>
        /// <param name="height">The new Height of the Rectangle. </param>
        void SetHeight(float height);

        /// <summary>
        /// Moves the shape the given distance.
        /// </summary>
        /// <param name="amount">Amount to move. </param>
        void MoveShape(const FVector2D& amount);

        /// <summary>
        /// Checks to see if the other rectangle overlaps with this rectangle.
        /// TOUCHES DO NOT COUNT.
        /// </summary>
        /// <param name="other">Other to check against. </param>
        /// <returns>True means does overlap. </returns>
        [[nodiscard]] bool Overlaps(const Rectangle& other) const;

        /// <summary>
        /// Checks to see if the other area overlaps with this rectangle.
        /// TOUCHES DO NOT COUNT.
        /// </summary>
        /// <param name="other">Other to check against. </param>
        /// <returns>True means does overlap. </returns>
        [[nodiscard]] bool Overlaps(const Circle& other) const;

        /// <summary>
        /// Checks to see if the other rectangle overlaps with this rectangle.
        /// </summary>
        /// <param name="other">Other to check against. </param>
        /// <returns>True means does overlap. </returns>
        [[nodiscard]] bool OverlapsOrIsTouching(const Rectangle& other) const;

        /// <summary>
        /// Determines if the given point is within the area.
        /// </summary>
        /// <param name="location">Location to test. </param>
        /// <returns>True means is within area. </returns>
        [[nodiscard]] bool PointIsWithin(FVector2D& location) const;

        /// <summary>
        /// Calculates the overlap amount between two shapes.
        /// This is the amount the shape you call from is 
        /// overlapping the shape passed in.
        /// This will always be a number 0 or above and therefore
        /// will not tell you direction to move to no longer overlap.
        /// </summary>
        /// <param name="other">Other shape to use. </param>
        /// <returns>The overlap amount. </returns>
        [[nodiscard]] FVector2D OverlapAmount(const Rectangle& other) const;

        /// <summary>
        /// Calculates the overlap amount between two shapes.
        /// This will always be in the direction of the previous location
        /// such that it is the amount overlapped in the direction given.
        /// This will always be a number 0 or above and therefore
        /// will not tell you direction to move to no longer overlap.
        /// </summary>
        /// <param name="other">Other shape to use. </param>
        /// <param name="previousLocation">
        /// Previous location to this overlap - used as a direction.
        /// </param>
        /// <returns>The overlap amount. </returns>
        [[nodiscard]] FVector2D OverlapAmount(const Rectangle& other, const FVector2D& previousLocation) const;

        /// <summary>
        /// Moves rectangle out of range of other Rectangle.
        /// Will use the position of least resistance.
        /// </summary>
        /// <param name="other">Other to move out of range of. </param>
        void MoveOutOfOverlapRangeOf(const Rectangle& other);

        /// <summary>
        /// Moves rectangle out of range of other Rectangle.
        /// Will go in the direction of previous location.
        /// </summary>
        /// <param name="other">Other to move out of range of. </param>
        /// <param name="previousLocation">Direction to move in. </param>
        void MoveOutOfOverlapRangeOf(const Rectangle& other, const FVector2D& previousLocation);

        /// <summary>
        /// Returns the location required to no overlap the shape.
        /// Will use the position of least resistance.
        /// </summary>
        /// <param name="other">Other to move out of range of. </param>
        /// <returns>Location required. </returns>
        [[nodiscard]] FVector2D GetNewLocationToNotOverlap(const Rectangle& other) const;

        /// <summary>
        /// Returns the location required to no overlap the shape.
        /// Will go in the direction of previous location.
        /// </summary>
        /// <param name="other">Other to move out of range of. </param>
        /// <param name="previousLocation">Direction to move in.</param>
        /// <returns>Location required. </returns>
        [[nodiscard]] FVector2D GetNewLocationToNotOverlap(const Rectangle& other, const FVector2D& previousLocation) const;

        /// <summary>
        /// Returns the location required to no overlap the shape.
        /// Will use the position of least resistance.
        /// </summary>
        /// <param name="other">Other to move out of range of. </param>
        /// <returns>Location required. </returns>
        [[nodiscard]] FVector2D GetNewLocationToNotOverlap(const Circle& other) const;

        /// <summary>
        /// Returns the closest point on the Shape to the given point.
        /// Will return the point given when point is in shape.
        /// </summary>
        /// <param name="other">Point to test. </param>
        /// <returns>Closest point on shape to point.</returns>
        [[nodiscard]] FVector2D ClosestPointTo(const FVector2D& other) const;
    private:
        /// <summary>
        /// Stores the location, top left of the rectangle.
        /// </summary>
        FVector2D m_location;

        /// <summary>
        /// Stores the width and height, X width, Y height.
        /// </summary>
        FVector2D m_size;

        /// <summary>
        /// The center of the shape.
        /// </summary>
        FVector2D m_center;

        /// <summary>
        /// Checks to see if the other rectangle is touching.
        /// Uses the 'close enough' float math to ensure the value is acurate.
        /// These are touches from the outside in.
        /// So imagine you are two rectangles from the outside touching one another's sides
        /// have you actually touched?
        /// </summary>
        /// <param name="other">Other rectangle to test. </param>
        /// <returns>True means are touching. </returns>
        [[nodiscard]] bool IsTouching(const Rectangle& other) const;

        /// <summary>
        /// Returns the center of the shape.
        /// </summary>
        /// <returns>Finds the center of the shape. </returns>
        [[nodiscard]] FVector2D GetCenter() const;
    };
}