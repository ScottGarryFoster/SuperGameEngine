#pragma once
#include "../../../LibraryIncludes.h"

using namespace StandardCLibrary;
namespace SuperGameEngine
{
    /// <summary>
    /// Describes a rectange shape in 2D Space.
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
        /// Contructs a rectangle.
        /// </summary>
        /// <param name="xy">X Y position of the rectangle. </param>
        /// <param name="widthHeight">Width and Height of the Rectangle. </param>
        Rectangle(float xy, float widthHeight);

        /// <summary>
        /// The left X of the Rectangle.
        /// </summary>
        /// <returns>The Left X coordinate of the Rectangle. </returns>
        float GetLeft() const;

        /// <summary>
        /// The right X of the Rectangle. 
        /// </summary>
        /// <returns>The Right X coordinate of the Rectangle. </returns>
        float GetRight() const;

        /// <summary>
        /// The top Y of the Rectangle. 
        /// </summary>
        /// <returns>The Top Y coordinate of the Rectangle. </returns>
        float GetTop() const;

        /// <summary>
        /// The bottom Y of the Rectangle.
        /// </summary>
        /// <returns>The bottom Y coordinate of the Rectangle. </returns>
        float GetBottom() const;

        /// <summary>
        /// The width of the rectangle.
        /// </summary>
        /// <returns>The width of the rectangle. </returns>
        float GetWidth() const;

        /// <summary>
        /// The Height of the rectangle.
        /// </summary>
        /// <returns>The Height of the rectangle. </returns>
        float GetHeight() const;

        /// <summary>
        /// The top left X and Y point of the Rectangle.
        /// </summary>
        /// <returns>The top left X and Y point of the Rectangle. </returns>
        FVector2D GetTopLeft() const;

        /// <summary>
        /// The bottom Left X Y point of the Rectangle.
        /// </summary>
        /// <returns>The bottom Left X Y point of the Rectangle. </returns>
        FVector2D GetBottomRight() const;

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
        /// Checks to see if the other rectangle overlaps with this rectangle.
        /// TOUCHES DO NOT COUNT.
        /// </summary>
        /// <param name="other">Other to check against. </param>
        /// <returns>True means does overlap. </returns>
        bool Overlaps(Rectangle& other) const;

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
        /// Checks to see if the other rectangle is touching.
        /// Uses the 'close enough' float math to ensure the value is acurate.
        /// These are touches from the outside in.
        /// So imagine you are two rectangles from the outside touching one another's sides
        /// have you actually touched?
        /// </summary>
        /// <param name="other">Other rectangle to test. </param>
        /// <returns>True means are touching. </returns>
        bool IsTouching(Rectangle& other) const;
    };
}