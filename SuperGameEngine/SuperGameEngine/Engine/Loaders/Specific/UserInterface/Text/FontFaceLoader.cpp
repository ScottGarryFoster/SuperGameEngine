#include "FontFaceLoader.h"
#include "../../../../../Engine/Graphics/TextureWrapper.h"
#include "../../../../../Engine/Content/ContentManager.h"

using namespace SuperGameEngine;
using namespace StandardCLibrary;

FontFaceLoader::FontFaceLoader(ContentManager* contentManager)
{
    this->contentManager = contentManager;

}

bool FontFaceLoader::LoadAsset(std::shared_ptr<Object>& subject, FString key)
{
    std::shared_ptr<FontFace> fontFace = dynamic_pointer_cast<FontFace>(subject);
    if (!fontFace)
    {
        Logger::Assert(NotImplementedException(), FString("FontFaceLoader"), FString("LoadAsset"),
            FString("You must pass in a Font face to load. (Shared Point Version) "));
        return false;
    }

    std::shared_ptr<SuperTexture> sp = this->contentManager->GetTexture(FString("Engine\\Assets\\Fonts\\Direct-Message.png"));
    if (!sp)
    {
        Logger::Assert(FileOpenException(), FString("FontFaceLoader"), FString("LoadAsset"),
            FString("Super Texture not found / could not load. "));
        return false;
    }

    fontFace = std::make_shared<FontFace>(sp);
    subject = fontFace;

    RectangleInt r = RectangleInt(0, 0, 32, 32);
    fontFace->AddCharacter(L'a', r);

    RectangleInt r2 = RectangleInt(32, 32, 32, 32);
    fontFace->AddCharacter(L'b', r2);

    return true;
}

bool FontFaceLoader::LoadAsset(Object* subject, FString key)
{
    //FontFace* fontFace = dynamic_cast<FontFace*>(subject);
    //if (!fontFace)
    //{
    //    Logger::Assert(NotImplementedException(), FString("FontFaceLoader"), FString("LoadAsset"),
    //        FString("You must pass in a Font face to load. (Raw Pointer Version) "));
    //    return false;
    //}

    //RectangleInt r = RectangleInt(0, 0, 32, 32);
    //fontFace->AddCharacter(L'a', r);

    //RectangleInt r2 = RectangleInt(32, 32, 32, 32);
    //fontFace->AddCharacter(L'b', r2);

    return true;
}
