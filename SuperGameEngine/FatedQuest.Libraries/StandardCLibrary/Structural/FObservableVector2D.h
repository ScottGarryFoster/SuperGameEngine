#pragma once
#include "FVector2D.h"
#include "../Events/FEvent.h"

namespace StandardCLibrary
{
    class FObservableVector2D : public FVector2D
    {
    public:
        FObservableVector2D();
        virtual ~FObservableVector2D();

        /// <summary>
        /// Sets the X Value.
        /// </summary>
        /// <param name="newValue">The new X value. </param>
        virtual void SetX(float newValue) override;

        /// <summary>
        /// Sets the Y Value.
        /// </summary>
        /// <param name="newValue">The new Y value. </param>
        virtual void SetY(float newValue) override;

        /// <summary>
        /// Sets both the x and y values.
        /// </summary>
        /// <param name="x">New X value. </param>
        /// <param name="y">New Y value. </param>
        virtual void SetXYValue(float x, float y) override;

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