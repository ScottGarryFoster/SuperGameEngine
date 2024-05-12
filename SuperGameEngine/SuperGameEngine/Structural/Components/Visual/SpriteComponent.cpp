#include "SpriteComponent.h"
#include "../../../LibraryIncludes.h"
#include "../Spatial/TransformComponent.h"
#include "../../GameObject/GameObject.h"
#include "../../../Engine/Graphics/SimpleRenderPacket.h"

using namespace StandardCLibrary;
using namespace SuperGameEngine;

SpriteComponent::SpriteComponent() : GameComponent()
{
    m_superTexture = nullptr;
    m_renderPacket = std::shared_ptr<RenderPacket>();
}

void SpriteComponent::Setup(SceneLoadPackage* loadPackage, GameObject* parent)
{
    GameComponent::Setup(loadPackage, parent);

    FString filePath = FString("Engine\\TestImages\\Text-Character-SpriteSheet.png");
    m_superTexture = GetLoadPackage()->GetContentManager()->GetTexture(filePath);
    if (!m_superTexture)
    {
        Logger::Assert(SystemNullReference(), GetTypeName(), FString("Setup"), FString("m_superTexture is null"));
        return;
    }

    m_splitTexture = std::make_shared <SplitTexture>(m_superTexture);
    for (int x = 0; x < 8; ++x)
    {
        for (int y = 0; y < 9; ++y)
        {
            m_splitTexture->AddSplit(RectangleInt(x * 16, y * 32, 16, 32));
        }
    }
    m_currentSplit = 0;
    m_currentTime = 0;

    GetParent()->GetTransform()->SetScale(4, 4);

    UpdateCurrentSprite();

    SetDoRender(true);
}

bool SpriteComponent::Update(GameTime gameTime)
{
    GameComponent::Update(gameTime);

    m_currentTime += gameTime.TicksSinceLastFrame;
    if (m_currentTime >= 100)
    {
        ++m_currentSplit;
        if (m_currentSplit > (8 * 9) - 1)
        {
            m_currentSplit = 0;
        }

        UpdateCurrentSprite();

        m_currentTime -= 100;
    }

    return false;
}

void SpriteComponent::Draw()
{
    GameComponent::Draw();

    if (m_splitTexture && m_renderPacket)
    {
        m_splitTexture->DrawPacket(m_renderPacket, GetParent()->GetTransform());
    }

}

void SpriteComponent::UpdateCurrentSprite()
{
    SplitTextureRenderPacketParameters parameters;
    parameters.Split = m_currentSplit;
    m_renderPacket = m_splitTexture->SetParametersForRenderPacket(parameters);
}
