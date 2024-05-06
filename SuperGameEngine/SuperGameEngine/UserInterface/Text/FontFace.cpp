#include "FontFace.h"
#include "../../Engine/Graphics/SimpleRenderPacket.h"

using namespace SuperGameEngine_UserInterface;
using namespace SuperGameEngine;

FontFace::FontFace(std::shared_ptr<SuperTexture> superTexture) : FontFaceAsset(superTexture)
{
    storedCharacters = std::make_unique<FList<std::pair<wchar_t, int>>>();
}

FontFace::~FontFace()
{
}

bool FontFace::AddCharacter(wchar_t character, RectangleInt location)
{
    int numberOfSplits = (int)GetSplits().size();
    bool addedSplit = AddSplit(location);
    if (addedSplit)
    {
            this->storedCharacters->Add(
        std::pair<wchar_t, int>(character, numberOfSplits));
    }

    return addedSplit;
}

void FontFace::DrawText(
    std::shared_ptr<FText> text, std::shared_ptr<Transform> transform
    )
{
    const FVector2D* topLeft = transform->GetLocation();
    FVector2D* copyTopLeft = new FVector2D(*topLeft);
    std::vector<RectangleInt> splits = GetSplits();

    std::wstring wtext = text->AsStdWstring();
    for (wchar_t charr : wtext)
    {
        FList<std::pair<wchar_t, int>> first =
            this->storedCharacters->First(
                [charr]
                (const std::pair<wchar_t, int>& c)
                { return c.first == charr; });

        if(first.Any())
        {
            int textureRectangleNumber = first[0].second;
            RectangleInt textureRectangle = splits.at(textureRectangleNumber);
            auto screenRectangle = RectangleInt(
                (int)copyTopLeft->GetX(),
                (int)copyTopLeft->GetY(),
                textureRectangle.GetWidth(),
                textureRectangle.GetHeight());

            SplitTexture::Draw(textureRectangleNumber, screenRectangle);

            copyTopLeft->SetX(copyTopLeft->GetX() + textureRectangle.GetWidth());
        }
    }

    delete copyTopLeft;
}

std::shared_ptr<RenderPacket> FontFace::SetParametersForRenderPacket(const FontFaceRenderPacketParameters& parameters)
{
    std::shared_ptr<RenderPacket> returnPacket = std::make_shared<SimpleRenderPacket>();
    this->cachedRenderPacket = returnPacket;

    std::shared_ptr <FVector2D> copyTopLeft = std::make_shared <FVector2D>(0,0);
    std::vector<RectangleInt> splits = GetSplits();

    std::wstring wtext = parameters.TextToRender.AsStdWstring();
    for (wchar_t charr : wtext)
    {
        FList<std::pair<wchar_t, int>> first =
            this->storedCharacters->First(
                [charr]
                (const std::pair<wchar_t, int>& c)
                { return c.first == charr; });

        if (first.Any())
        {
            int textureRectangleNumber = first[0].second;
            RectangleInt textureRectangle = splits.at(textureRectangleNumber);
            auto screenRectangle = RectangleInt(
                (int)copyTopLeft->GetX(),
                (int)copyTopLeft->GetY(),
                textureRectangle.GetWidth(),
                textureRectangle.GetHeight());

            returnPacket->AddDrawPacket(textureRectangle, screenRectangle);

            copyTopLeft->SetX(copyTopLeft->GetX() + textureRectangle.GetWidth());
        }
    }

    return returnPacket;
}