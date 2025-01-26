#include "SuperInputManager.h"

#include <iostream>

#include "../../../FatedQuest.Libraries/Logger/AllReferences.h"

using namespace SuperGameInput;

void SuperInputManager::Setup(const std::shared_ptr<GamePackage>& gamePackage)
{
}

void SuperInputManager::EventUpdate(SDL_Event e)
{
    if (e.type == SDL_KEYUP)
    {
        SDL_Keycode key = e.key.keysym.sym;
        std::string name = SDL_GetKeyName(key);
        Log::Info("Key released: " + name);
    }
}
