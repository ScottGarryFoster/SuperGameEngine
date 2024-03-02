#pragma once
#include "../../../LibraryIncludes.h"
#include "../../GameObject/GameComponent.h"
#include "Collider.h"

namespace SuperGameEngine
{
    class ColliderComponent : public GameComponent, public Collider
    {
    public:
        ColliderComponent();
        virtual ~ColliderComponent();

        /// <summary>
        /// Gets the parent gameobject.
        /// </summary>
        /// <returns>The gameobject the collider belongs to. </returns>
        virtual GameObject* GetParentObject() override;
    };
}