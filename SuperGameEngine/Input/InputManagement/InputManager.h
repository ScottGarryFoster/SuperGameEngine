#pragma once
#include <memory>

#include "InputHandler.h"
#include "Event/WindowEvent.h"

namespace FatedQuestLibraries
{
    class GamePackage;
}

using namespace FatedQuestLibraries;

namespace SuperGameInput
{
    /// <summary>
    /// Handles and updates user input.
    /// </summary>
    class InputManager : public InputHandler
    {
    public:
        virtual ~InputManager() = default;

        /// <summary>
        /// Called once on setup.
        /// </summary>
        /// <param name="gamePackage">Game Package, used to load controller inputs. </param>
        virtual void Setup(const std::shared_ptr<GamePackage>& gamePackage) = 0;

        /// <summary>
        /// Called once after Tools or Game to reset states of keys.
        /// </summary>
        virtual void Update() = 0;

        /// <summary>
        /// Called upon every event to handle key and controller changes.
        /// </summary>
        /// <param name="event">Event to inspect. </param>
        virtual void EventUpdate(WindowEvent event) = 0;
    };
}
