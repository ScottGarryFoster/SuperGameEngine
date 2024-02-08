#include "SpriteComponent.h"
#include "../../../LibraryIncludes.h"

using namespace StandardCLibrary;
using namespace SuperGameEngine;

void SpriteComponent::Setup(SceneLoadPackage* loadPackage, GameObject* parent)
{
    GameComponent::Setup(loadPackage, parent);

    if (!loadPackage)
    {
        Logger::Exception(ArgumentNullException(), GetTypeName(), FString("Setup"), FString("loadPackage is null"));
        return;
    }

    m_loadPackage = loadPackage;

    m_superTexture = m_loadPackage->GetContentManager()->GetTexture(FString("E:/Development/SuperGameEngine-SDL/collideCircle.png"));
    if (!m_superTexture)
    {
        Logger::Exception(SystemNullReference(), GetTypeName(), FString("Setup"), FString("m_superTexture is null"));
        return;
    }
}

bool SpriteComponent::Update(GameTime gameTime)
{
    GameComponent::Update(gameTime);

    return false;
}

void SpriteComponent::Draw()
{
    GameComponent::Draw();

    if (m_superTexture)
    {
        m_superTexture->Draw();
    }

}
