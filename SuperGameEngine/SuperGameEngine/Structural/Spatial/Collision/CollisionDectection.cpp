#include "CollisionDectection.h"
#include "../../../Structural/Components/Colliders/Collider.h"
#include "Collision.h"
#include "../../../Structural/GameObject/GameObject.h"

using namespace StandardCLibrary;
using namespace SuperGameEngine;
CollisionDectection::CollisionDectection()
{
    m_colliders = new FList<std::weak_ptr<Collider>>();
    m_colliderCollisionHistory = 
        std::make_shared<
        FDictionary<uint64_t, 
        std::shared_ptr<FDictionary<uint64_t, bool>>>>();
}

CollisionDectection::~CollisionDectection()
{
    delete m_colliders;
}

void CollisionDectection::GiveActiveCollider(std::weak_ptr<Collider> collider)
{
    m_colliders->Add(collider);
}

void CollisionDectection::RunCollisionUpdate()
{
    for (std::weak_ptr<Collider> weakPointer : *m_colliders)
    {
        if (std::shared_ptr<Collider> sharedPointer = weakPointer.lock())
        {
            EnsureActiveColliderInteractionExists(sharedPointer->GetColliderGuid()->AsNumber());

            std::shared_ptr<FDictionary<uint64_t, bool>> activeColliderCollection = 
                GetActiveColliderInteraction(sharedPointer->GetColliderGuid()->AsNumber());

            for (std::weak_ptr<Collider> innerWeakPointer : *m_colliders)
            {
                if (std::shared_ptr<Collider> innerSharedPointer = innerWeakPointer.lock())
                {
                    if (sharedPointer != innerSharedPointer)
                    {
                        EnsureUnactiveColliderInteractionExists(
                            activeColliderCollection, innerSharedPointer->GetColliderGuid()->AsNumber());

                        bool didCollideLastFrame = GetUnactiveColliderValue(
                            activeColliderCollection, innerSharedPointer->GetColliderGuid()->AsNumber());
                        
                        bool areCurrentlyColliding = false;
                        if (sharedPointer->Overlaps(*innerSharedPointer.get()))
                        {
                            areCurrentlyColliding = true;
                        }
                        
                        Collision collision = CreateCollision(
                            innerSharedPointer->GetParentObject(), 
                            innerSharedPointer.get());

                        bool didCollide = false;
                        if (!didCollideLastFrame && areCurrentlyColliding)
                        {
                            sharedPointer->GetParentObject()->OnCollisionBegin(collision);
                            didCollide = true;
                        }
                        else if (didCollideLastFrame && areCurrentlyColliding)
                        {
                            sharedPointer->GetParentObject()->OnCollisionOccuring(collision);
                            didCollide = true;
                        }
                        else if (didCollideLastFrame && !areCurrentlyColliding)
                        {
                            sharedPointer->GetParentObject()->OnCollisionEnd(collision);
                            didCollide = true;
                        }
                        else
                        {
                            // Do Nothing
                            // This would be, no collision last frame nor this frame.
                        }

                        if (didCollide)
                        {
                            SetUnactiveColliderValue(
                                activeColliderCollection, 
                                innerSharedPointer->GetColliderGuid()->AsNumber(), 
                                areCurrentlyColliding);
                        }
                    }
                }
            }
        }
    }
}

void CollisionDectection::EnsureActiveColliderInteractionExists(uint64_t guid)
{
    if (!m_colliderCollisionHistory->KeyExists(guid))
    {
        std::shared_ptr<FDictionary<uint64_t, bool>> empty = std::make_shared<FDictionary<uint64_t, bool>>();
        m_colliderCollisionHistory->SetValue(guid, empty);
    }
}

std::shared_ptr<FDictionary<uint64_t, bool>> CollisionDectection::GetActiveColliderInteraction(uint64_t guid)
{
    std::shared_ptr<FDictionary<uint64_t, bool>> innerCollection;
    if (!m_colliderCollisionHistory->TryGetValue(guid, innerCollection))
    {
        Logger::Error(
            FString("CollisionDectection::GetActiveColliderInteraction:") + 
            "Could not find an entry we just made?");
    }

    return innerCollection;
}

void CollisionDectection::EnsureUnactiveColliderInteractionExists(std::shared_ptr<FDictionary<uint64_t, bool>>& activeCollection, uint64_t guid)
{
    if (!activeCollection->KeyExists(guid))
    {
        bool defaultValue = false;
        activeCollection->SetValue(guid, defaultValue);
    }
}

bool CollisionDectection::GetUnactiveColliderValue(std::shared_ptr<FDictionary<uint64_t, bool>>& activeCollection, uint64_t guid)
{
    bool didCollideLastFrame = false;
    activeCollection->TryGetValue(guid, didCollideLastFrame);
    return didCollideLastFrame;
}

void CollisionDectection::SetUnactiveColliderValue(std::shared_ptr<FDictionary<uint64_t, bool>>& activeCollection, uint64_t guid, bool newValue)
{
    activeCollection->SetValue(guid, newValue);
}

Collision CollisionDectection::CreateCollision(GameObject* parent, Collider* other)
{
    return Collision(parent, other);
}
