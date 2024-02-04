#include "GameObject.h"
using namespace SuperGameEngine;

GameObject::GameObject()
{

}

GameObject::~GameObject()
{

}

void GameObject::Setup()
{

}

bool GameObject::Update(GameTime gameTime)
{
    return true;
}

void GameObject::Draw()
{

}

template<typename T>
typename std::enable_if<std::is_base_of<GameComponent, T>::value, T*>::type
GameObject::AddComponent()
{
    T* newComponent = new T();
    GameComponent* componentPtr = static_cast<GameComponent*>(newComponent);

    componentPtr->Test();

    return newComponent;
}