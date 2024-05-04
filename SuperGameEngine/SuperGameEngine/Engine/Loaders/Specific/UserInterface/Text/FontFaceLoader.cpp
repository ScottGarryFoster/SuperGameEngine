#include "FontFaceLoader.h"
using namespace SuperGameEngine;
using namespace StandardCLibrary;

bool FontFaceLoader::LoadAsset(Object* subject, FString key)
{
    FontFace* fontFace = dynamic_cast<FontFace*>(subject);
    if (!fontFace)
    {
        Logger::Assert(NotImplementedException(), FString("FontFaceLoader"), FString("LoadAsset"),
            FString("You must pass in a Font face to load."));
        return false;
    }

    RectangleInt r = RectangleInt(0, 0, 32, 32);
    fontFace->AddCharacter(L'a', r);

    RectangleInt r2 = RectangleInt(32, 32, 32, 32);
    fontFace->AddCharacter(L'b', r2);

    return true;
}
