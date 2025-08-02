#include "AssetBrowser.h"
#include "../../../Engine/Imgui/External/imgui_internal.h"
#include "../../Engine/Graphics/ImGuiSuperTexture.h"
#include "../../ToolsEngine/Packages/WindowPackage.h"
#include "Engine/Content/ContentManager.h"
#include "FileManagement/ToolsAssetFileProvider.h"
#include <algorithm>
#include "../../FatedQuestLibraries.h"

#include "AssetTileRender.h"
#include "FileManagement/AssetFile.h"
#include "FileManagement/AssetFolder.h"

using namespace SuperGameTools;

AssetBrowser::AssetBrowser()
{
}

AssetBrowser::~AssetBrowser()
{
}

void AssetBrowser::Setup(const std::shared_ptr<WindowPackage>& windowPackage)
{
    m_windowPackage = windowPackage;
    WindowElement::Setup(m_windowPackage->GetColourPalette());

    // Setup Selection Manager or Document Manager if you're going to in the future.

    auto assetFileProvider = std::make_shared<ToolsAssetFileProvider>(
        m_windowPackage->GetContentManager()->GamePackage(), 
        m_windowPackage->GetContentManager()->Texture(),
        m_windowPackage->GetPackagePaths(),
        m_windowPackage->GetAssetTemplateProvider());
    m_assetFileProvider = assetFileProvider;

   auto tileFolderRenderer = std::make_shared<AssetTileRender>(
        m_assetFileProvider->GetRootFolder(), 
        m_windowPackage->GetContentManager()->Texture());
    m_tileFolderRenderer = tileFolderRenderer;

    if (auto subscription = assetFileProvider->OnFileSystemUpdated().lock())
    {
        subscription->Subscribe(tileFolderRenderer);
    }
}

void AssetBrowser::Update()
{
    m_assetFileProvider->Update();
    m_tileFolderRenderer->Update();
}

void AssetBrowser::Draw()
{
    const char* windowName = "Asset Browser";
    RenderWindow(windowName);

    ImGuiWindow* window = ImGui::FindWindowByName(windowName);
    if (window->Size.x < 50 || window->Size.y < 50)
    {
        ImGui::SetWindowPos(window, ImVec2(0, 100));
        ImGui::SetWindowSize(window, ImVec2(50, 50));
    }

    m_tileFolderRenderer->Draw();

    EndWindowRender(windowName);
}

void AssetBrowser::TearDown()
{
}

void AssetBrowser::Invoke(std::shared_ptr<FatedQuestLibraries::FEventArguments> arguments)
{
}
