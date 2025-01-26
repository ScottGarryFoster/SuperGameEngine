#pragma once
#include <memory>
#include <SDL.h>

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
    class InputManager
    {
    public:
        virtual ~InputManager() = default;

        virtual void Setup(const std::shared_ptr<GamePackage>& gamePackage) = 0;

        virtual void EventUpdate(SDL_Event e) = 0;
    };
}
