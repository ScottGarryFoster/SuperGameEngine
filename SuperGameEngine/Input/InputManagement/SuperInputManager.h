#pragma once
#include "InputManager.h"

namespace SuperGameInput
{
    /// <summary>
    /// Handles and updates user input.
    /// </summary>
    class SuperInputManager : public InputManager
    {
    public:
        virtual ~SuperInputManager() override = default;

        virtual void Setup(const std::shared_ptr<GamePackage>& gamePackage) override;

        virtual void EventUpdate(SDL_Event e) override;
    };
}
