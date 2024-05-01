#pragma once
#include "../../../LibraryIncludes.h"
#include "../../GameObject/GameComponent.h"
#include "../../Spatial/Positional/Transform.h"
using namespace StandardCLibrary;

namespace SuperGameEngine
{
    /// <summary>
    /// Location and size in space.
    /// </summary>
    class TransformComponent : public GameComponent, public Transform
    {
    };
}