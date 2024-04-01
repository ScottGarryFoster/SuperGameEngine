#pragma once
#include "../../../LibraryIncludes.h"

using namespace StandardCLibrary;
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
        FVector2D GetLocation() const;

        /// <summary>
        /// Sets the radius of the circle.
        /// </summary>
        /// <param name="radius">New radius. </param>
        void SetRadius(int radius);

        /// <summary>
        /// Gets the radius of the circle.
        /// </summary>
        /// <returns>Current radius. </returns>
        int GetRadius() const;

        /// <summary>
        /// Checks to see if the other circle overlaps with this circle.
        /// TOUCHES DO NOT COUNT.
        /// </summary>
        /// <param name="other">Other to check against. </param>
        /// <returns>True means does overlap. </returns>
        bool Overlaps(Circle& other) const;

        /// <summary>
        /// Checks to see if the other circle overlaps with this circle.
        /// Touches count.
        /// </summary>
        /// <param name="other">Other to check against. </param>
        /// <returns>True means does overlap. </returns>
        bool OverlapsOrTouches(Circle& other) const;

        /// <summary>
        /// Checks to see if the other Rectangle overlaps with this circle.
        /// TOUCHES DO NOT COUNT.
        /// </summary>
        /// <param name="other">Other to check against. </param>
        /// <returns>True means does overlap. </returns>
        bool Overlaps(Rectangle& other) const;

        /// <summary>
        /// Detirmines if the given point is within the area.
        /// </summary>
        /// <param name="location">Location to test. </param>
        /// <returns>True means is within area. </returns>
        bool PointIsWithin(FVector2D& location) const;
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