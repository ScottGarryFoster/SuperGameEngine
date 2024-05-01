#include "FontFace.h"

using namespace SuperGameEngine_UserInterface;
using namespace SuperGameEngine;

FontFace::FontFace(std::shared_ptr<SuperTexture> superTexture) : FontFaceAsset(superTexture)
{
    storedCharacters = std::make_shared<FList<std::pair<wchar_t, RectangleInt>>>();
}

FontFace::~FontFace()
{

}

bool FontFace::AddCharacter(wchar_t character, RectangleInt location)
{
    bool addedSplit = AddSplit(location);
    if (addedSplit)
    {
        storedCharacters->Add(
            std::pair<wchar_t, RectangleInt>(character, location));
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
        if (storedCharacters->Any(
            [charr]
            (const std::pair<wchar_t, RectangleInt>& c) 
            { return c.first == charr; }))
        {
            auto r = RectangleInt(0, 0, 1, 1);
            AddSplit(r);
            Draw(0, r);
            return;
        }
    }
}
