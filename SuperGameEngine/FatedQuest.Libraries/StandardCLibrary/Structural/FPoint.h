#pragma once

#include "../Text/FString.h"
#include "../Events/FEvent.h"

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
        void SetX(int newValue);

        /// <summary>
        /// Sets the Y Value.
        /// </summary>
        /// <param name="newValue">The new Y value. </param>
        void SetY(int newValue);

        /// <summary>
        /// Sets both the x and y values.
        /// </summary>
        /// <param name="x">New X value. </param>
        /// <param name="y">New Y value. </param>
        void SetXYValue(int x, int y);

        /// <summary>
        /// Prints the Point value.
        /// </summary>
        /// <returns>A string version of the point. </returns>
        const FString Print() const;

        /// <summary>
        /// Invokes when value has changed.
        /// </summary>
        //FEventSubscriptions* GetOnValueChanged();

    private:

        /// <summary>
        /// X cordinate.
        /// </summary>
        int m_x;

        /// <summary>
        /// Y cordinate.
        /// </summary>
        int m_y;

        /// <summary>
        /// Event subject for OnValueChanged.
        /// </summary>
        FEvent* m_onValueChangedEvent;

        /// <summary>
        /// Invokes changed for all observers.
        /// </summary>
        void InvokeOnValueChanged();
    };
}