#include "SceneToGameObjectPackage.h"

#include "../../Structural/Spatial/Collision/CollisionDectection.h"

using namespace SuperGameEngine;

SceneToGameObjectPackage::SceneToGameObjectPackage(CollisionDectectionSubscription* collisionDection, GrandScene* scene)
{
    m_collisionDectection = collisionDection;
    m_scene = scene;
}

SceneToGameObjectPackage::~SceneToGameObjectPackage()
{
}

CollisionDectectionSubscription* SceneToGameObjectPackage::GetCollisionDectection()
{
    return m_collisionDectection;
}

GrandScene* SceneToGameObjectPackage::GetScene()
{
    return m_scene;
}
