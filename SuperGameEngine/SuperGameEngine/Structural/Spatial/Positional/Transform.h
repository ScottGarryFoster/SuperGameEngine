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
        const FVector2D* GetLocation() const;

        /// <summary>
        /// Gets the location of the transform.
        /// This is the center of the GameObject.
        /// </summary>
        /// <returns>The location of the GameObject. </returns>
        void SetLocation(float x, float y);

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
        FObservableVector2D* m_location;

        /// <summary>
        /// Invokes on location changed.
        /// </summary>
        FEvent* m_onLocationChanged;
    };
}