#include "CollisionDectection.h"
#include "../../../Structural/Components/Colliders/Collider.h"
#include "Collision.h"
#include "CollisionAnswer.h"
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

std::shared_ptr<FList<CollisionAnswer>> CollisionDectection::QueryCollisionForGameObject(Guid& gameObjectGuid) const
{
    std::shared_ptr<FList<CollisionAnswer>> returnAnswer = 
        std::make_shared<FList<CollisionAnswer>>();

    std::shared_ptr<FDictionary<uint64_t, std::shared_ptr<FDictionary<uint64_t, bool>>>> 
        collisionInteractions =
        CopyCollisionInteractions(m_colliderCollisionHistory);

    for (std::weak_ptr<Collider> weakPointer : *m_colliders)
    {
        if (std::shared_ptr<Collider> sharedPointer = weakPointer.lock())
        {
            if (sharedPointer->GetParentObject()->GetGuid()->AsNumber()
                != gameObjectGuid.AsNumber())
            {
                continue;
            }

            EnsureActiveColliderInteractionExists(
                sharedPointer->GetColliderGuid()->AsNumber(), 
                collisionInteractions);

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

                        CollisionAnswer answer;
                        answer.Collision = collision;

                        bool didCollide = false;
                        if (!didCollideLastFrame && areCurrentlyColliding)
                        {
                            answer.Answer = CollisionAnswerState::OnCollisionBegin;
                            didCollide = true;
                        }
                        else if (didCollideLastFrame && areCurrentlyColliding)
                        {
                            answer.Answer = CollisionAnswerState::OnCollisionOccuring;
                            didCollide = true;
                        }
                        else if (didCollideLastFrame && !areCurrentlyColliding)
                        {
                            answer.Answer = CollisionAnswerState::OnCollisionEnd;
                            didCollide = true;
                        }
                        else
                        {
                            // Do Nothing
                            // This would be, no collision last frame nor this frame.
                        }

                        if (didCollide)
                        {
                            returnAnswer->Add(answer);

                            // Re-implement this maybe with a copy.
                            //SetUnactiveColliderValue(
                            //    activeColliderCollection,
                            //    innerSharedPointer->GetColliderGuid()->AsNumber(),
                            //    areCurrentlyColliding);
                        }
                    }
                }
            }
        }
    }

    return returnAnswer;
}

void CollisionDectection::EnsureActiveColliderInteractionExists(uint64_t guid)
{
    if (!m_colliderCollisionHistory->KeyExists(guid))
    {
        std::shared_ptr<FDictionary<uint64_t, bool>> empty = std::make_shared<FDictionary<uint64_t, bool>>();
        m_colliderCollisionHistory->SetValue(guid, empty);
    }
}

void CollisionDectection::EnsureActiveColliderInteractionExists(
    uint64_t guid, 
    std::shared_ptr<FDictionary<uint64_t, std::shared_ptr<FDictionary<uint64_t, bool>>>> collisionHistory) const
{
    if (!collisionHistory->KeyExists(guid))
    {
        std::shared_ptr<FDictionary<uint64_t, bool>> empty = std::make_shared<FDictionary<uint64_t, bool>>();
        collisionHistory->SetValue(guid, empty);
    }
}

std::shared_ptr<FDictionary<uint64_t, std::shared_ptr<FDictionary<uint64_t, bool>>>> 
    CollisionDectection::CopyCollisionInteractions(
        std::shared_ptr<FDictionary<uint64_t, std::shared_ptr<FDictionary<uint64_t, bool>>>> toCopy) const
{
    std::shared_ptr<FDictionary<uint64_t, std::shared_ptr<FDictionary<uint64_t, bool>>>> returnNewList
        = std::make_shared<FDictionary<uint64_t, std::shared_ptr<FDictionary<uint64_t, bool>>>>();
    for (const auto& outter : *toCopy)
    {
        auto valueDictionary = std::make_shared<FDictionary<uint64_t, bool>>();
        returnNewList->SetValue(outter.first, valueDictionary);
        for (const auto& inner : *(outter.second))
        {
            bool secondValue = inner.second;
            valueDictionary->SetValue(inner.first, secondValue);
        }
    }

    return returnNewList;
}

std::shared_ptr<FDictionary<uint64_t, bool>> CollisionDectection::GetActiveColliderInteraction(uint64_t guid) const
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

std::shared_ptr<FDictionary<uint64_t, bool>> 
    CollisionDectection::GetActiveColliderInteraction(
        uint64_t guid,
        std::shared_ptr<FDictionary<uint64_t, std::shared_ptr<FDictionary<uint64_t, bool>>>> collisionHistory) const
{
    std::shared_ptr<FDictionary<uint64_t, bool>> innerCollection;
    if (!collisionHistory->TryGetValue(guid, innerCollection))
    {
        Logger::Error(
            FString("CollisionDectection::GetActiveColliderInteraction:")
                + "With custom collisionHistory sent in)" +
                  "Could not find an entry we just made?");
    }

    return innerCollection;
}

void CollisionDectection::EnsureUnactiveColliderInteractionExists(
    std::shared_ptr<FDictionary<uint64_t, bool>>& activeCollection,
    uint64_t guid) const
{
    if (!activeCollection->KeyExists(guid))
    {
        bool defaultValue = false;
        activeCollection->SetValue(guid, defaultValue);
    }
}

bool CollisionDectection::GetUnactiveColliderValue(std::shared_ptr<FDictionary<uint64_t, bool>>& activeCollection, uint64_t guid) const
{
    bool didCollideLastFrame = false;
    activeCollection->TryGetValue(guid, didCollideLastFrame);
    return didCollideLastFrame;
}

void CollisionDectection::SetUnactiveColliderValue(std::shared_ptr<FDictionary<uint64_t, bool>>& activeCollection, uint64_t guid, bool newValue)
{
    activeCollection->SetValue(guid, newValue);
}

Collision CollisionDectection::CreateCollision(GameObject* parent, Collider* other) const
{
    return Collision(parent, other);
}
