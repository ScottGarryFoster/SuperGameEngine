#include "FontFaceFromText.h"
#include "../../../../../LibraryIncludes.h"
#include "../../../../../Engine/Content/ContentManager.h"

using namespace SuperGameEngine;
using namespace StandardCLibrary;

FontFaceFromText::FontFaceFromText(ContentManager* contentManager)
{
    this->contentManager = contentManager;
}

std::shared_ptr<FontFace> FontFaceFromText::LoadFromFile
    (std::shared_ptr<bool>& answer, const std::shared_ptr<FString> text)
{
    // TODO: Make a better error throw back than this bool.
    // Does not seem to be good enough.
    *answer = false;
    std::shared_ptr<FontFace> fontFace = std::shared_ptr<FontFace>();

    XMLDocument* document = new XMLDocument();
    if (TryParseXMLDocument(text, document))
    {
        std::shared_ptr<FontFaceData> fontFaceData = std::make_shared<FontFaceData>();

        XMLNode* root = document->first_node("AssetMeta");
        if (!root)
        {
            return fontFace;
        }

        bool failedToLoad = false;
        int tagsFound = 0;
        for (XMLNode* child = root->first_node(); child; child = child->next_sibling())
        {
            FString name = FString(child->name());
            name.ConvertToLower();
            if (name == FString("metadata"))
            {
                if (ParseAssetMetadata(fontFaceData, child))
                {
                    ++tagsFound;
                }
                else
                {
                    failedToLoad = true;
                }

            }
            if (name == FString("texture"))
            {
                if (ParseAssetTexture(fontFaceData, child))
                {
                    ++tagsFound;
                }
                else
                {
                    failedToLoad = true;
                }
            }

            if (name == FString("characters"))
            {
                if (ParseCharacters(fontFaceData, child))
                {
                    ++tagsFound;
                }
                else
                {
                    failedToLoad = true;
                }
            }

        }

        if (tagsFound != 3)
        {
            failedToLoad = true;
        }

        if (!failedToLoad)
        {
            fontFace = CreateFontFace(answer, fontFaceData);
        }

    }
    delete document;

    return fontFace;
}

FontFaceFromText::~FontFaceFromText()
{
}

 bool FontFaceFromText::TryParseXMLDocument(const std::shared_ptr<FString> text, XMLDocument* document)
{
    bool loaded = false;
    try
    {
        document->parse<0>(const_cast<char*>(text->AsCharArr()));
        loaded = true;
    }
    catch (rapidxml::parse_error e)
    {
        // Returning false is enough.
    }

    return loaded;
}

bool FontFaceFromText::ParseAssetMetadata
    (std::shared_ptr<FontFaceData>& fontFaceData, XMLNode* node)
{
    bool loaded = false;
    for (XMLAttribute* attr = node->first_attribute(); attr; attr = attr->next_attribute())
    {
        FString name = FString(attr->name());
        FString value = FString(attr->value());
        name.ConvertToLower();

        if (name == FString("name"))
        {
            fontFaceData->MetaDataName = std::make_shared<FText>(value.AsStdString());
            loaded = true;
        }
        else if (name == FString("brand"))
        {
            fontFaceData->MetaDataBrand = std::make_shared<FText>(value.AsStdString());
        }
    }

    return loaded;
}

bool FontFaceFromText::ParseAssetTexture
    (std::shared_ptr<FontFaceData>& fontFaceData, XMLNode* node)
{
    bool loaded = false;
    for (XMLAttribute* attr = node->first_attribute(); attr; attr = attr->next_attribute())
    {
        FString name = FString(attr->name());
        FString value = FString(attr->value());
        name.ConvertToLower();

        if (name == FString("source"))
        {
            fontFaceData->TextureSource = std::make_shared<FText>(value.AsStdString());
            loaded = !fontFaceData->TextureSource->IsEmptyOrWhitespace();
        }
    }

    return loaded;
}

bool FontFaceFromText::ParseCharacters
    (std::shared_ptr<FontFaceData>& fontFaceData, XMLNode* node)
{
    bool loaded = true;
    fontFaceData->Characters = std::make_shared<FList<FontCharacter>>();
    for (XMLNode* child = node->first_node(); child; child = child->next_sibling())
    {
        FString name = FString(child->name());
        FString value = FString(child->value());
        name.ConvertToLower();

        if (name == FString("character"))
        {
            if (!ParseCharacter(fontFaceData, child))
            {
                return false;
            }
        }
    }

    return loaded;
}

bool FontFaceFromText::ParseCharacter
    (std::shared_ptr<FontFaceData>& fontFaceData, XMLNode* node)
{
    bool loaded = false;
    FontFaceFromText::FontCharacter character;
    for (XMLAttribute* attr = node->first_attribute(); attr; attr = attr->next_attribute())
    {
        FString name = FString(attr->name());
        FString value = FString(attr->value());
        int intvalue = -1;
        name.ConvertToLower();
        if (name == FString("top") || name == FString("left") || name == FString("width") || name == FString("height"))
        {
            if(!IntHelpers::TryParse(value, intvalue))
            {
                return false;
            }
        }

        if (name == FString("top"))
        {
            character.TextureRectangle.SetY(intvalue);
        }
        else if(name == FString("left"))
        {
            character.TextureRectangle.SetX(intvalue);
        }
        else if (name == FString("width"))
        {
            character.TextureRectangle.SetWidth(intvalue);
        }
        else if (name == FString("height"))
        {
            character.TextureRectangle.SetHeight(intvalue);
        }
        else if (name == FString("character"))
        {
            FText txt = FText(value.AsStdString());
            if (txt.IsEmptyOrWhitespace())
            {
                // Pointless if there is no character
                return false;
            }

            character.Character = txt.AsCharArr()[0];
            loaded = true;
        }
    }

    fontFaceData->Characters->Add(character);

    return loaded;
}

std::shared_ptr<FontFace> FontFaceFromText::CreateFontFace
    (std::shared_ptr<bool>& answer, std::shared_ptr<FontFaceData>& fontFaceData)
{
    FString textureSource = FString(fontFaceData->TextureSource->AsStdString());
    std::shared_ptr<SuperTexture> texture = this->contentManager->GetTexture(textureSource);

    std::shared_ptr<FontFace> fontFace = std::make_shared<FontFace>(texture);

    for (const FontCharacter fc : *fontFaceData->Characters)
    {
        fontFace->AddCharacter(fc.Character, fc.TextureRectangle);
    }

    *answer = true;
    return fontFace;
}