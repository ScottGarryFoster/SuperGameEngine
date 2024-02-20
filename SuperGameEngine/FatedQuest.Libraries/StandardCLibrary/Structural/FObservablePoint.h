#pragma once
#include "FPoint.h"
#include "../Events/FEvent.h"

namespace StandardCLibrary
{
    /// <summary>
    /// A point you can passively observe changes to.
    /// </summary>
    class FObservablePoint : FPoint
    {
    public:
        FObservablePoint();
        FObservablePoint(int x, int y);
        virtual ~FObservablePoint();

        /// <summary>
        /// Sets the X Value.
        /// </summary>
        /// <param name="newValue">The new X value. </param>
        virtual void SetX(int newValue) override;

        /// <summary>
        /// Sets the Y Value.
        /// </summary>
        /// <param name="newValue">The new Y value. </param>
        virtual void SetY(int newValue) override;

        /// <summary>
        /// Sets both the x and y values.
        /// </summary>
        /// <param name="x">New X value. </param>
        /// <param name="y">New Y value. </param>
        virtual void SetXYValue(int x, int y) override;

        /// <summary>
        /// Invokes when value has changed.
        /// </summary>
        FEventSubscriptions* GetOnValueChanged();

    private:
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