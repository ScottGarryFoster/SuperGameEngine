#include "TextComponent.h"
#include "../../../Engine/Graphics/RenderPacket.h"
#include "../../GameObject/GameObject.h"

#include "../../../UserInterface/Text/FontFace.h"
#include "../../../UserInterface/Text/FontFaceRenderPacketParameters.hpp"
#include "../../Components/Spatial/TransformComponent.h"

using namespace SuperGameEngine;
using namespace StandardCLibrary;

TextComponent::TextComponent()
{
    m_componentText = std::make_shared<FText>(L"");
}

TextComponent::~TextComponent()
{
}

void TextComponent::Setup(SceneLoadPackage* loadPackage, GameObject* parent)
{
    GameComponent::Setup(loadPackage, parent);
    SetDoRender(true);

    std::shared_ptr<bool> didFind = std::make_shared<bool>();
    std::shared_ptr<FontFaceAsset> ffa = loadPackage->GetContentManager()->GetFontFace(FString("Engine\\Assets\\Fonts\\Direct-Message.assetmeta"), didFind);
    //if (*didFind)
    //{
    //    this->m_fontFace = ffa;

    //    FontFaceRenderPacketParameters parameters = FontFaceRenderPacketParameters();
    //    parameters.TextToRender = *m_componentText;

    //    m_textRenderPacket = m_fontFace->SetParametersForRenderPacket(parameters);
    //}

    //GetParent()->GetTransform()->SetScale(3);
}

bool TextComponent::Update(const GameTime gameTime)
{
    GameComponent::Update(gameTime);
    return false;
}

void TextComponent::Draw()
{
    GameComponent::Draw();

    if (!this->m_fontFace)
    {
        return;
    }

    this->m_fontFace->DrawPacket(this->m_textRenderPacket, GetParent()->GetTransform());
}

void TextComponent::SetText(const FText& newValue)
{
    m_componentText.reset();
    m_componentText = std::make_shared<FText>(newValue);
    if (!this->m_fontFace)
    {
        return;
    }

    FontFaceRenderPacketParameters parameters = FontFaceRenderPacketParameters();
    parameters.TextToRender = newValue;

    this->m_textRenderPacket = this->m_fontFace->SetParametersForRenderPacket(parameters);
}

const FText TextComponent::GetText()
{
    return *this->m_componentText;
}
