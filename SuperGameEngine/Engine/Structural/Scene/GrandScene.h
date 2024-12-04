#pragma once
#include "../../Engine/Content/ContentManager.h"
#include <memory>

namespace SuperGameEngine
{
    /// <summary>
    /// Holds everything in the entire game and manages the objects.
    /// </summary>
    class GrandScene
    {
    public:
        GrandScene(std::shared_ptr<ContentManager> contentManager);
    };
};