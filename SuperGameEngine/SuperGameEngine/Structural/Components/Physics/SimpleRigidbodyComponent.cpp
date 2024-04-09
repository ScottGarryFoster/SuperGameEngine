#include "SimpleRigidbodyComponent.h"
#include "../../GameObject/GameObject.h"
#include "../../Spatial/Collision/Collision.h"
#include "../Spatial/TransformComponent.h"

using namespace SuperGameEngine;
using namespace StandardCLibrary;
SimpleRigidbodyComponent::SimpleRigidbodyComponent()
{
    m_previousLocation = new FVector2D();
    m_numberOfCollisions = 0;
    m_numberOfCollisionsLastFixedUpdate = 0;

    m_canRunPhysics = false;
    m_haveEverUpdated = false;
    m_currentVelocity = new FVector2D();

    m_didMoveLastFrame = false;
}

SimpleRigidbodyComponent::~SimpleRigidbodyComponent()
{
    delete m_previousLocation;
    delete m_currentVelocity;
}

void SimpleRigidbodyComponent::Setup(SceneLoadPackage* loadPackage, GameObject* parent)
{
    GameComponent::Setup(loadPackage, parent);
}

void SimpleRigidbodyComponent::FixedUpdate(GameTime gameTime)
{
    m_didMoveLastFrame = false;
    DetirmineIfCanRunPhysics();

    if (m_canRunPhysics)
    {
        RunPhysicsLoop();
    }
}

void SimpleRigidbodyComponent::OnCollisionBegin(Collision& collision)
{
    ++m_numberOfCollisions;
    //if (m_didMoveLastFrame && m_haveEverUpdated)
    //{
    //    GameComponent::GetParent()->GetTransform()->SetLocation(
    //        m_previousLocation->GetX(), m_previousLocation->GetY());
    //}
}

void SimpleRigidbodyComponent::OnCollisionEnd(Collision& collision)
{
    --m_numberOfCollisions;
}

void SimpleRigidbodyComponent::AddVelocity(float x, float y)
{
    float vX = m_currentVelocity->GetX();
    m_currentVelocity->SetX(vX + x);

    float vY = m_currentVelocity->GetY();
    m_currentVelocity->SetY(vY + y);

}

void SimpleRigidbodyComponent::SetVelocity(float x, float y)
{
    float newX = x;
    float newY = y;
    m_currentVelocity->SetXYValue(newX, newY);
}

void SimpleRigidbodyComponent::DetirmineIfCanRunPhysics()
{
    m_canRunPhysics = false;
    if (m_numberOfCollisions > m_numberOfCollisionsLastFixedUpdate)
    {
        if (!m_haveEverUpdated)
        {
            FVector2D* currentLocation = GameComponent::GetParent()->GetTransform()->GetLocation();
            m_previousLocation->SetXYValue(currentLocation->GetX(), currentLocation->GetY());
            m_haveEverUpdated = true;
        }
        else
        {
            GameComponent::GetParent()->GetTransform()->SetLocation(
                m_previousLocation->GetX(), m_previousLocation->GetY());
        }
    }
    else if (m_numberOfCollisions == 0)
    {
        m_canRunPhysics = true;
        if (m_numberOfCollisionsLastFixedUpdate >= 0)
        {
            FVector2D* currentLocation = GameComponent::GetParent()->GetTransform()->GetLocation();
            m_previousLocation->SetXYValue(currentLocation->GetX(), currentLocation->GetY());
            m_haveEverUpdated = true;
        }

    }

    m_numberOfCollisionsLastFixedUpdate = m_numberOfCollisions;
}

void SimpleRigidbodyComponent::RunPhysicsLoop()
{
    std::shared_ptr<TransformComponent> transform = GetParent()->GetTransform();

    FrameTiming* timing = GetLoadPackage()->GetFrameTiming();
    FVector2D* location = transform->GetLocation();

    bool setX = false;
    float newX = location->GetX();
    if (m_currentVelocity->GetX() != 0)
    {
        newX = location->GetX() + (m_currentVelocity->GetX() * timing->GetFixedUpdateLoopTimingAsSecond());
        setX = true;
    }

    bool setY = false;
    float newY = location->GetY();
    if (m_currentVelocity->GetY() != 0)
    {
        newY = location->GetY() + (m_currentVelocity->GetY() * timing->GetFixedUpdateLoopTimingAsSecond());
        setY = true;
    }

    if (setX || setY)
    {
        transform->SetLocation(newX, newY);
        m_didMoveLastFrame = true;
    }

    std::shared_ptr<FList<CollisionAnswer>> collisionAnswer = 
        GetLoadPackage()->GetCollisionQuery()->QueryCollisionForGameObject(*GetParent()->GetGuid());
    if (collisionAnswer->Any([](const CollisionAnswer& c) { return c.Answer != CollisionAnswerState::OnCollisionEnd; }))
    {
        GameComponent::GetParent()->GetTransform()->SetLocation(
            m_previousLocation->GetX(), m_previousLocation->GetY());
    }
}
