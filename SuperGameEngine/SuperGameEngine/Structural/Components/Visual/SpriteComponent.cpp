#include "SpriteComponent.h"
#include "../../../LibraryIncludes.h"
#include "../Spatial/TransformComponent.h"
#include "../../GameObject/GameObject.h"

using namespace StandardCLibrary;
using namespace SuperGameEngine;

SpriteComponent::SpriteComponent() : GameComponent()
{
    m_superTexture = nullptr;
}

void SpriteComponent::Setup(SceneLoadPackage* loadPackage, GameObject* parent)
{
    GameComponent::Setup(loadPackage, parent);

    FString filePath = FString("Engine\\TestImages\\collideCircle.png");
    m_superTexture = m_loadPackage->GetContentManager()->GetTexture(filePath);
    if (!m_superTexture)
    {
        Logger::Assert(SystemNullReference(), GetTypeName(), FString("Setup"), FString("m_superTexture is null"));
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
        FPoint textureSize = m_superTexture->Size();
        TransformComponent* transform = GetParent()->GetTransform();
        FPoint drawLocation = FPoint(
            (int)transform->GetLocation()->GetX() - (textureSize.GetX() / 2),
            (int)transform->GetLocation()->GetY() - (textureSize.GetY() / 2));

        m_superTexture->Draw(drawLocation);
    }

}
