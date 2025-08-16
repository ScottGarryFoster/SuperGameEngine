#pragma once
#include "../../../FatedQuestReferences.h"

using namespace FatedQuestLibraries;

namespace SuperGameEngine
{
    class Rectangle;

    /// <summary>
    /// Represents the shape circle.
    /// </summary>
    class Circle
    {
    public:
        Circle(int radius);
        Circle(float x, float y, int radius);
        virtual ~Circle();

        /// <summary>
        /// Updates the location of the circle.
        /// </summary>
        /// <param name="location">New location. </param>
        void SetLocation(FVector2D& location);

        /// <summary>
        /// Gets the current location of the circle. 
        /// </summary>
        /// <returns></returns>
        [[nodiscard]] FVector2D GetLocation() const;

        /// <summary>
        /// Sets the radius of the circle.
        /// </summary>
        /// <param name="radius">New radius. </param>
        void SetRadius(int radius);

        /// <summary>
        /// Gets the radius of the circle.
        /// </summary>
        /// <returns>Current radius. </returns>
        [[nodiscard]] int GetRadius() const;

        /// <summary>
        /// Checks to see if the other circle overlaps with this circle.
        /// TOUCHES DO NOT COUNT.
        /// </summary>
        /// <param name="other">Other to check against. </param>
        /// <returns>True means does overlap. </returns>
        [[nodiscard]] bool Overlaps(const Circle& other) const;

        /// <summary>
        /// Checks to see if the other circle overlaps with this circle.
        /// Touches count.
        /// </summary>
        /// <param name="other">Other to check against. </param>
        /// <returns>True means does overlap. </returns>
        [[nodiscard]] bool OverlapsOrTouches(const Circle& other) const;

        /// <summary>
        /// Checks to see if the other Rectangle overlaps with this circle.
        /// TOUCHES DO NOT COUNT.
        /// </summary>
        /// <param name="other">Other to check against. </param>
        /// <returns>True means does overlap. </returns>
        [[nodiscard]] bool Overlaps(const Rectangle& other) const;

        /// <summary>
        /// Determines if the given point is within the area.
        /// </summary>
        /// <param name="location">Location to test. </param>
        /// <returns>True means is within area. </returns>
        [[nodiscard]] bool PointIsWithin(FVector2D& location) const;

        /// <summary>
        /// Calculates the overlap amount between two shapes.
        /// This will always be a number 0 or above and therefore
        /// will not tell you direction to move to no longer overlap.
        /// </summary>
        /// <param name="other">Other shape to use. </param>
        /// <returns>The overlap amount. 0 would mean no overlap. </returns>
        [[nodiscard]] float OverlapAmount(const Circle& other) const;

        /// <summary>
        /// Gets an acceptable location to not overlap.
        /// Will find a location based on the current frame.
        /// </summary>
        /// <param name="other">Other to move out of range of. </param>
        /// <returns>Location required. </returns>
        [[nodiscard]] FVector2D GetNewLocationToNotOverlap(const Circle& other) const;

        /// <summary>
        /// Moves rectangle out of range of other Rectangle.
        /// Will use the position of least resistance.
        /// </summary>
        /// <param name="other">Other to move out of range of. </param>
        void MoveOutOfOverlapRangeOf(const Circle& other);

        /// <summary>
        /// Returns the location required to no overlap the shape.
        /// </summary>
        /// <param name="other">Other to move out of range of. </param>
        /// <returns>Location required. </returns>
        [[nodiscard]] FVector2D GetNewLocationToNotOverlap(const Rectangle& other) const;

        /// <summary>
        /// Returns this object as a debug string.
        /// </summary>
        std::string Print() const;

        /// <summary>
        /// Returns this object as a debug string.
        /// </summary>
        std::string ToString() const;
    private:
        /// <summary>
        /// Location of the circle.
        /// </summary>
        FVector2D m_location;

        /// <summary>
        /// Radius of the circle.
        /// </summary>
        int m_radius;
    };

}