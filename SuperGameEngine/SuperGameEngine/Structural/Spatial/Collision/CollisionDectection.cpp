#include "CollisionDectection.h"
#include "../../../Structural/Components/Colliders/Collider.h"
#include "Collision.h"
#include "../../../Structural/GameObject/GameObject.h"

using namespace StandardCLibrary;
using namespace SuperGameEngine;
CollisionDectection::CollisionDectection()
{
    m_colliders = new FList<std::weak_ptr<Collider>>();
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
    //for (Collider* outer : *m_colliders)
    //{
    //    for (Collider* inner : *m_colliders)
    //    {
    //        if (outer == inner)
    //        {
    //            continue;
    //        }

    //        if (outer->Overlaps(*inner))
    //        {
    //            Collision collision = 
    //                Collision(inner->GetParentObject(),inner);

    //            outer->GetParentObject()->OnCollisionOccuring(collision);
    //        }
    //    }
    //}


    // TODO: Start using Shared and Weak pointers in GameObjects and Components.

    for (std::weak_ptr<Collider> weakPointer : *m_colliders)
    {
        std::shared_ptr<Collider> sharedPointer = weakPointer.lock();
        if (sharedPointer)
        {

            bool didOverlap = false;

            for (std::weak_ptr<Collider> innerWeakPointer : *m_colliders)
            {
                std::shared_ptr<Collider> innerSharedPointer = innerWeakPointer.lock();
                if (innerSharedPointer)
                {
                    if (sharedPointer != innerSharedPointer)
                    {
                        if (sharedPointer->Overlaps(*innerSharedPointer.get()))
                        {
                            Collision collision = 
                                Collision(
                                innerSharedPointer->GetParentObject(), 
                                innerSharedPointer.get());

                            sharedPointer->GetParentObject()->OnCollisionOccuring(collision);
                            didOverlap = true;
                        }
                    }
                }
            }
        }
    }
}
