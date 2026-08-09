#include "WindowPackage.h"

using namespace SuperGameTools;

void WindowPackage::SetSDLGameViewportRenderTexture(const std::shared_ptr<SDLTextureChest>& texture)
{
    m_gameViewportTexture = texture;
}

std::shared_ptr<SDLTextureChest> WindowPackage::GetSDLGameViewportRenderTexture() const
{
    return m_gameViewportTexture;
}

void WindowPackage::SetSDLToolsViewportRenderTexture(const std::shared_ptr<SDLTextureChest>& texture)
{
    m_toolsViewportTexture = texture;
}

std::shared_ptr<SDLTextureChest> WindowPackage::GetSDLToolsViewportRenderTexture() const
{
    return m_toolsViewportTexture;
}

void WindowPackage::SetRenderer(std::shared_ptr<SDLRendererReader> sdlRendererReader)
{
    m_renderer = sdlRendererReader;
}

std::shared_ptr<SDLRendererReader> WindowPackage::GetRenderer() const
{
    return m_renderer;
}

std::shared_ptr<ContentManager> WindowPackage::GetContentManager() const
{
    return m_contentManager;
}

void WindowPackage::SetContentManager(const std::shared_ptr<ContentManager>& contentManager)
{
    m_contentManager = contentManager;
}

std::shared_ptr<EngineEntryCommunication> WindowPackage::GetEngineEntryCommunication() const
{
    return m_engineEntryCommunication;
}

void WindowPackage::SetEngineEntryCommunication(const std::shared_ptr<EngineEntryCommunication>& engineEntryCommunication)
{
    m_engineEntryCommunication = engineEntryCommunication;
}

std::shared_ptr<SerializableParser> WindowPackage::GetParser() const
{
    return m_serializableParser;
}

void WindowPackage::SetParser(const std::shared_ptr<SerializableParser>& parser)
{
    m_serializableParser = parser;
}

std::shared_ptr<MenuView> WindowPackage::GetTopMenu() const
{
    return m_menuView;
}

void WindowPackage::SetTopMenu(const std::shared_ptr<MenuView>& menuView)
{
    m_menuView = menuView;
}

std::shared_ptr<FrameworkManager> WindowPackage::GetFrameworkManager() const
{
    return m_frameworkManager;
}

void WindowPackage::SetFrameworkManager(const std::shared_ptr<FrameworkManager>& frameworkManager)
{
    m_frameworkManager = frameworkManager;
}

std::shared_ptr<PackagePaths> WindowPackage::GetPackagePaths() const
{
    return m_packagePaths;
}

void WindowPackage::SetPackagePaths(const std::shared_ptr<PackagePaths>& packagePaths)
{
    m_packagePaths = packagePaths;
}

std::shared_ptr<ColoursAndStyles> WindowPackage::GetColourPalette() const
{
    return m_colorPalette;
}

void WindowPackage::SetColourPalette(const std::shared_ptr<ColoursAndStyles>& colourPalette)
{
    m_colorPalette = colourPalette;
}

std::shared_ptr<AssetTemplateProvider> WindowPackage::GetAssetTemplateProvider() const
{
    return m_assetTemplateProvider;
}

void WindowPackage::SetAssetTemplateProvider(const std::shared_ptr<AssetTemplateProvider>& assetTemplateProvider)
{
    m_assetTemplateProvider = assetTemplateProvider;
}

std::shared_ptr<PanelManager> WindowPackage::GetPanelManager() const
{
    return m_panelManager;
}

void WindowPackage::SetPanelManager(const std::shared_ptr<PanelManager>& panelManager)
{
    m_panelManager = panelManager;
}

std::shared_ptr<UniversalObjectDataTemplateProvider> WindowPackage::GetUniversalObjectDataTemplateProvider() const
{
    return m_universalObjectDataTemplateProvider;
}

void WindowPackage::SetUniversalObjectDataTemplateProvider(
    const std::shared_ptr<UniversalObjectDataTemplateProvider>& newValue)
{
    m_universalObjectDataTemplateProvider = newValue;
}
