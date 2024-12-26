#include "WindowPackage.h"}

using namespace SuperGameTools;

void WindowPackage::SetSDLRenderTexture(std::shared_ptr<ExtremelyWeakWrapper<SDL_Texture>> texture)
{
    m_texture = texture;
}

std::shared_ptr<ExtremelyWeakWrapper<SDL_Texture>> WindowPackage::GetSDLRenderTexture() const
{
    return m_texture;
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