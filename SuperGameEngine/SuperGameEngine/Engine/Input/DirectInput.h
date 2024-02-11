#pragma once
#include "../../LibraryIncludes.h"
#include "DirectKeyInput.h"
#include <SDL.h>

namespace SuperGameEngine
{
    /// <summary>
    /// Access to direct input from the User.
    /// </summary>
    class DirectInput : public Object
    {
    public:
        DirectInput();
        virtual ~DirectInput();

        /// <summary>
        /// Updates all the objects which require knowleadge from an SDL level.
        /// This would be Key Input for instance.
        /// This is sent directly before the GrandScene Update.
        /// </summary>
        /// <param name="e">Event last sent from the update loop. </param>
        void EventUpdate(SDL_Event& e);

        /// <summary>
        /// Gives access to the current state of Key Inputs.
        /// </summary>
        /// <returns>Instance of DirectKeyInput. </returns>
        const DirectKeyInput* GetDirectKeyInput() const;

    private:
        /// <summary>
        /// Gives access to the current state of Key Inputs.
        /// </summary>
        DirectKeyInput* m_directKeyInput;
    };
}

