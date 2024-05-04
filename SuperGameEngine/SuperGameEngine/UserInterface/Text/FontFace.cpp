#include "FontFace.h"

using namespace SuperGameEngine_UserInterface;
using namespace SuperGameEngine;

FontFace::FontFace(std::shared_ptr<SuperTexture> superTexture) : FontFaceAsset(superTexture)
{
    storedCharacters = std::make_shared<FList<std::pair<wchar_t, int>>>();
    currentCharacter = 0;
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
            storedCharacters->Add(
        std::pair<wchar_t, int>(character, numberOfSplits));
    }

    return addedSplit;
}

void FontFace::DrawText(
    std::shared_ptr<FText> text, std::shared_ptr<Transform> transform
    )
{
    std::wstring wtext = text->AsStdWstring();
    for (wchar_t charr : wtext)
    {
        FList<std::pair<wchar_t, int>> first =
            storedCharacters->First(
                [charr]
                (const std::pair<wchar_t, int>& c)
                { return c.first == charr; });

        if(first.Any())
        {
            auto r = RectangleInt(0, 0, 1, 1);
            int t = first[0].second;
            Draw(first[0].second, r);
        }
    }
}