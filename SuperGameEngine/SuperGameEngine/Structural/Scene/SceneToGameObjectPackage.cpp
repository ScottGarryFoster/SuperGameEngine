#include "SceneToGameObjectPackage.h"

#include "../../Structural/Spatial/Collision/CollisionDectection.h"

using namespace SuperGameEngine;

SceneToGameObjectPackage::SceneToGameObjectPackage(CollisionDectection* collisionDection)
{
    m_collisionDectection = collisionDection;
}

SceneToGameObjectPackage::~SceneToGameObjectPackage()
{
    delete m_collisionDectection;
}

CollisionDectection* SceneToGameObjectPackage::GetCollisionDectection()
{
    return m_collisionDectection;
}
