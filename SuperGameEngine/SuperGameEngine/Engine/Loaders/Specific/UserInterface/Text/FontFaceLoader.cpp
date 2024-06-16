#include "FontFaceLoader.h"
#include "../../../../../Engine/Graphics/TextureWrapper.h"
#include "../../../../../Engine/Content/ContentManager.h"
#include "../../../../../UserInterface/Text/FontFace.h"

using namespace SuperGameEngine;
using namespace StandardCLibrary;

FontFaceLoader::FontFaceLoader(ContentManager* contentManager)
{
    this->contentManager = contentManager;
    this->fromText = std::make_shared<FontFaceFromText>(this->contentManager);

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

    if (!File::Exists(key))
    {
        Logger::Assert(FileOpenException(), FString("FontFaceLoader"), FString("LoadAsset"),
            FString("File does not exist: ") + key);
        return false;
    }

    std::shared_ptr<FString> fileContents = std::make_shared<FString>(File::ReadFileContents(key));

    std::shared_ptr<bool> loaded = std::make_shared<bool>();
    std::shared_ptr<FontFace> ff = this->fromText->LoadFromFile(loaded, fileContents);
    if (loaded)
    {
        subject = ff;
    }
    else
    {
        Logger::Assert(FileOpenException(), FString("FontFaceLoader"), FString("LoadAsset"),
            FString("Could not load font from file. ") + key);
        return false;
    }

    return true;
}

bool FontFaceLoader::LoadAssetFromData(std::shared_ptr<Object>& subject, std::vector<unsigned char>& data)
{
    std::shared_ptr<FontFace> fontFace = dynamic_pointer_cast<FontFace>(subject);
    if (!fontFace)
    {
        Logger::Assert(NotImplementedException(), FString("FontFaceLoader"), FString("LoadAssetFromData"),
            FString("You must pass in a Font face to load. (Shared Pointer Version) "));
        return false;
    }

    if (data.empty())
    {
        Logger::Assert(NotImplementedException(), FString("FontFaceLoader"), FString("LoadAssetFromData"),
            FString("No data to load font. "));
        return false;
    }

    std::shared_ptr<FString> fileContents = std::make_shared<FString>(data);
    std::shared_ptr<bool> loaded = std::make_shared<bool>();
    std::shared_ptr<FontFace> ff = this->fromText->LoadFromFile(loaded, fileContents);
    if (loaded)
    {
        subject = ff;
    }
    else
    {
        Logger::Assert(FileOpenException(), FString("FontFaceLoader"), FString("LoadAssetFromData"),
            FString("Could not load font from data. "));
        return false;
    }

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

    Logger::Assert(NotImplementedException(), FString("FontFaceLoader"), FString("LoadAsset"),
                FString("Loading assets via Raw Point is not supported yet."));

    return false;
}
