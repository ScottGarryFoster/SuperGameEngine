#include "TextComponent.h"
#include "../../../Engine/Graphics/RenderPacket.h"
#include "../../GameObject/GameObject.h"

#include "../../../UserInterface/Text/FontFace.h"
#include "../../../UserInterface/Text/FontFaceRenderPacketParameters.hpp"
#include "../../Components/Spatial/TransformComponent.h"

using namespace SuperGameEngine;
using namespace SuperGameEngine_UserInterface;
using namespace StandardCLibrary;

TextComponent::TextComponent()
{
    this->componentText = std::make_shared<FText>();
}

TextComponent::~TextComponent()
{
}

void TextComponent::Setup(SceneLoadPackage* loadPackage, GameObject* parent)
{
    GameComponent::Setup(loadPackage, parent);
    SetDoRender(true);

    std::shared_ptr<bool> didFind = std::make_shared<bool>();
    std::shared_ptr<FontFaceAsset> ffa = loadPackage->GetContentManager()->GetFontFace(FString(""), didFind);
    if (*didFind)
    {
        this->fontFace = ffa;
        FontFaceRenderPacketParameters parameters = FontFaceRenderPacketParameters();
        parameters.TextToRender = FText("aabbaa");

        this->textRenderPacket = this->fontFace->SetParametersForRenderPacket(parameters);
    }
}

bool TextComponent::Update(GameTime gameTime)
{
    GameComponent::Update(gameTime);

    return false;
}

void TextComponent::Draw()
{
    GameComponent::Draw();

    if (!this->fontFace)
    {
        return;
    }

    std::shared_ptr<Transform> transform = dynamic_pointer_cast<Transform>(this->GetParent()->GetTransform());

    this->fontFace->DrawPacket(this->textRenderPacket, transform);
}

void TextComponent::SetText(const FText& newValue)
{
    if (!this->fontFace)
    {
        return;
    }

    FontFaceRenderPacketParameters parameters = FontFaceRenderPacketParameters();
    parameters.TextToRender = newValue;

    this->textRenderPacket = this->fontFace->SetParametersForRenderPacket(parameters);

    this->componentText = std::make_shared<FText>(newValue.AsStdWstring());
}

const FText TextComponent::GetText()
{
    return *this->componentText;
}
