#pragma once
#include "../../../LibraryIncludes.h"

namespace SuperGameEngine
{
    using namespace StandardCLibrary;

    class Transform : public FEventObserver
    {
    public:
        Transform();
        virtual ~Transform();

        /// <summary>
        /// Gets the location of the transform.
        /// This is the center of the GameObject.
        /// </summary>
        /// <returns>The location of the GameObject. </returns>
        /// <remarks>
        /// Do not store this location as a pointer.
        /// It is to only be used as a reference and to get the
        /// location out without using multiple methods.
        /// </remarks>
        const FVector2D* GetLocation() const;

        /// <summary>
        /// Set the location
        /// </summary>
        /// <param name="x">X locaiton. </param>
        /// <param name="y">Y locaiton. </param>
        void SetLocation(const float x, const float y);

        /// <summary>
        /// Set the location
        /// </summary>
        /// <param name="x">XY locaiton. </param>
        void SetLocation(const float xy);

        /// <summary>
        /// Set the location
        /// </summary>
        /// <param name="value">X and Y values. </param>
        void SetLocation(const FVector2D& value);

        /// <summary>
        /// Sets the scale.
        /// </summary>
        /// <param name="xy">Sets both X and Y values.</param>
        void SetScale(const float xy);

        /// <summary>
        /// Set the Scale.
        /// </summary>
        /// <param name="x">X scale. </param>
        /// <param name="y">Y scale. </param>
        void SetScale(const float x, const float y);

        /// <summary>
        /// Set scale. 
        /// </summary>
        /// <param name="value">X and Y values. </param>
        void SetScale(const FVector2D& value);

        /// <summary>
        /// Get the scale value.
        /// </summary>
        /// <returns>Both the X and Y value. </returns>
        /// <remarks>
        /// Do not store this location as a pointer.
        /// It is to only be used as a reference and to get the
        /// location out without using multiple methods.
        /// </remarks>
        const FVector2D* GetScale() const;

        /// <summary>
        /// Sets the rotation.
        /// </summary>
        /// <param name="xy">Sets both X and Y values.</param>
        void SetRotation(const float xy);

        /// <summary>
        /// Set the rotation.
        /// </summary>
        /// <param name="x">X scale. </param>
        /// <param name="y">Y scale. </param>
        void SetRotation(const float x, const float y);

        /// <summary>
        /// Set rotation. 
        /// </summary>
        /// <param name="value">X and Y values. </param>
        void SetRotation(const FVector2D& value);

        /// <summary>
        /// Get the rotation value.
        /// </summary>
        /// <returns>Both the X and Y value. </returns>
        /// <remarks>
        /// Do not store this location as a pointer.
        /// It is to only be used as a reference and to get the
        /// location out without using multiple methods.
        /// </remarks>
        const FVector2D* GetRotation() const;

        /// <summary>
        /// Invoked when location has changed.
        /// </summary>
        /// <returns>Subscribe to this to gain access to this event. </returns>
        FEventSubscriptions* OnLocationChanged();

        /// <summary>
        /// Called when observations have been made and now we should react.
        /// </summary>
        /// <param name="arguments">Arguments to react to. </param>
        virtual void Invoke(FEventArguments* arguments) override;
    private:

        /// <summary>
        /// Location of the transform.
        /// </summary>
        std::unique_ptr<FObservableVector2D> m_location;

        /// <summary>
        /// Invokes on location changed.
        /// </summary>
        FEvent* m_onLocationChanged;

        /// <summary>
        /// Scale value.
        /// </summary>
        std::unique_ptr<FObservableVector2D> m_scale;

        /// <summary>
        /// Rotation value.
        /// </summary>
        std::unique_ptr<FObservableVector2D> m_rotation;
    };
}