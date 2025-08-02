#include "ToolsAssetFile.h"
#include "../../../FatedQuestLibraries.h"
#include "../../../../../FatedQuest.Libraries/XmlDocument/RapidXMLDocument.h"
#include "../../../../Engine/Structural/Assets/SuperGameAsset.h"
#include "../../../../Engine/Engine/Content/TextureManager.h"
#include "Engine/Graphics/Texture/SuperTexture.h"


using namespace SuperGameTools;
using namespace SuperGameEngine;
using namespace FatedQuestLibraries;

ToolsAssetFile::ToolsAssetFile(
    const std::weak_ptr<GamePackage>& package,
    const std::weak_ptr<SuperGameEngine::TextureManager>& texture,
    const std::string& packagePath, 
    const std::weak_ptr<AssetFolder>& parent)
{
    m_parent = parent;
    m_guid = GUIDHelpers::CreateGUID();
    m_selectionGroups.insert(SelectionGroup::Inspectable);
    m_selected = false;

    if (std::shared_ptr<GamePackage> gamePackage = package.lock())
    {
        std::string originalFilePath = File::RemoveLastExtension(packagePath);
        if (!gamePackage->File()->Exists(originalFilePath))
        {
            throw std::exception("ToolsAssetFile::ToolsAssetFile: Original file asset refers to not found.");
        }

        if (gamePackage->File()->Exists(packagePath))
        {
            std::string contents = gamePackage->File()->ReadFileContents(packagePath);
            auto document = std::make_shared<RapidXMLDocument>();
            if (document->Load(contents))
            {
                m_gameAsset = std::make_shared<SuperGameAsset>(document, packagePath);
            }
            else
            {
                Log::Error("Could not load Stored document from XML. Path: " + packagePath, "ToolsAssetFile::ToolsAssetFile");
            }
        }
        else
        {
            Log::Error("Asset file does not exist. Path: " + packagePath, "ToolsAssetFile::ToolsAssetFile");
        }

        // Setup the image.
        if (std::shared_ptr<TextureManager> textureManager = texture.lock())
        {
            std::string fileType = File::GetExtension(originalFilePath);
            if (StringHelpers::ToLower(fileType) == ".png")
            {
                m_largeTilePreview = textureManager->GetTexture(originalFilePath);
                if (!m_largeTilePreview)
                {
                    Log::Error("Could not load large tile preview from Texture Manager. Path: " + packagePath, "ToolsAssetFile::ToolsAssetFile");
                }
            }
        }
        else
        {
            Log::Error("Texture Manager is not given. Path: " + packagePath, "ToolsAssetFile::ToolsAssetFile");
        }
    }
    else
    {
        Log::Error("Package manager is not given, asset not loaded. Path: " + packagePath, "ToolsAssetFile::ToolsAssetFile");
    }

}

std::weak_ptr<AssetFolder> ToolsAssetFile::GetParent() const
{
    return m_parent;
}

std::string ToolsAssetFile::GetDisplayName() const
{
    if (m_gameAsset)
    {
        std::string name = m_gameAsset->GetName();
        if (!name.empty())
        {
            return name;
        }

        return File::GetFilename(m_gameAsset->GetPath());
    }

    return "Unknown";
}

std::string ToolsAssetFile::GetPackagePath() const
{
    if (m_gameAsset)
    {
        return m_gameAsset->GetPath();
    }

    return "Unknown";
}

void ToolsAssetFile::DrawLargeTile(const RectangleInt& screenRectangle) const
{
    if (m_largeTilePreview)
    {
        // TODO: Cache this.
        RectangleInt uv = RectangleInt(0, 0, m_largeTilePreview->Size().GetX(), m_largeTilePreview->Size().GetY());
        m_largeTilePreview->Draw(uv, screenRectangle);
    }
}

void ToolsAssetFile::SelectFile()
{
    m_selected = true;
}

void ToolsAssetFile::UnselectFile()
{
    m_selected = false;
}

bool ToolsAssetFile::IsSelected() const
{
    return m_selected;
}

std::unordered_set<SelectionGroup> ToolsAssetFile::GetSelectionGroup() const
{
    return m_selectionGroups;
}

std::shared_ptr<Guid> ToolsAssetFile::GetGuid() const
{
    return m_guid;
}
