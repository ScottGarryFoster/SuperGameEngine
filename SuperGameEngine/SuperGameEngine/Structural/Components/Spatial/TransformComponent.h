#pragma once
#include "../../../LibraryIncludes.h"
#include "../../GameObject/GameComponent.h"
using namespace StandardCLibrary;

namespace SuperGameEngine
{
    /// <summary>
    /// Location and size in space.
    /// </summary>
    class TransformComponent : public GameComponent, public FEventObserver
    {
    public:
        TransformComponent();
        virtual ~TransformComponent();

        /// <summary>
        /// Gets the location of the transform.
        /// This is the center of the GameObject.
        /// </summary>
        /// <returns>The location of the GameObject. </returns>
        FVector2D* GetLocation();

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