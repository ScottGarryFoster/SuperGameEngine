#include "FontFace.h"

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
    int numberOfSplits = GetSplits().size();
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
    FVector2D* topLeft = transform->GetLocation();
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
                topLeft->GetX(),
                topLeft->GetY(),
                textureRectangle.GetWidth(),
                textureRectangle.GetHeight());

            Draw(textureRectangleNumber, screenRectangle);

            topLeft->SetX(topLeft->GetX() + textureRectangle.GetWidth());
        }
    }
}