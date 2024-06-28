#pragma once
#include "../../LibraryIncludes.h"
#include "DirectKeyInput.h"
#include <SDL.h>
#include "DirectControllerInput.h"
#include "../Content/PackageContents.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Access to direct input from the User.
    /// </summary>
    class DirectInput : public Object
    {
    public:
        DirectInput(std::shared_ptr<PackageContents> packageContents);
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

        /// <summary>
        /// Access to input on a XInput controller.
        /// </summary>
        /// <returns>Instance of DirectXInput. </returns>
        const DirectControllerInput* GetDirectXInput() const;

    private:
        /// <summary>
        /// Gives access to the current state of Key Inputs.
        /// </summary>
        DirectKeyInput* m_directKeyInput;

        /// <summary>
        /// Access to input on a XInput controller.
        /// </summary>
        DirectControllerInput* m_directXInput;

        /// <summary>
        /// 
        /// </summary>
        std::shared_ptr<PackageContents> m_packageContents;
    };
}

