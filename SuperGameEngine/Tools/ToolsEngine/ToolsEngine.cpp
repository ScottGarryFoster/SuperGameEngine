#include "ToolsEngine.h"
#include <SDL.h>

#include "../../../FatedQuest.Libraries/GamePackage/GamePackage/CombinedGamePackage.h"
#include "../../../FatedQuest.Libraries/GamePackage/GamePackage/PackagePaths.h"
#include "../../../FatedQuest.Libraries/GamePackage/GamePackage/SGEPackagePaths.h"
#include "../../Engine/Engine/Content/ContentManager.h"
#include "../../Engine/Engine/Content/SuperContentManager.h"
#include "../../Engine/Imgui/External/imgui.h"
#include "../Windows/GameViewport/GameViewport.h"
#include "../ToolsEngine/Packages/WindowPackage.h"
#include "../Windows/LoggerOutput/LoggerOutput.h"

using namespace SuperGameTools;

ToolsEngine::ToolsEngine()
{
    m_windowPackage = std::make_shared<WindowPackage>();
    m_haveSetup = false;
    m_superContentManager = std::make_shared<SuperContentManager>();
}

ToolsEngine::~ToolsEngine()
{
}

void ToolsEngine::GiveRenderer(std::shared_ptr<SDLRendererReader> renderer)
{
    m_renderer = renderer;
    
    m_windowPackage->SetRenderer(m_renderer);

    if (!m_superContentManager->GetSuperTextureManager())
    {
        auto paths = std::make_shared<SGEPackagePaths>();
        auto gamePackage = std::make_shared<CombinedGamePackage>();
        gamePackage->Load(paths);
        m_superContentManager->GiveGamePackage(gamePackage);

        auto textureManager = std::make_shared<SuperTextureManager>(renderer, gamePackage);
        m_superContentManager->GiveSuperTextureManager(textureManager);

        m_windowPackage->SetContentManager(m_superContentManager);
    }
}

void ToolsEngine::GiveSDLTexture(std::shared_ptr<ExtremelyWeakWrapper<SDL_Texture>> sdlRenderTexture)
{
    m_sdlRenderTexture = sdlRenderTexture;

    m_windowPackage->SetSDLRenderTexture(m_sdlRenderTexture);
}

ApplicationOperationState ToolsEngine::Event(SDL_Event event)
{
    return ApplicationOperationState::Running;
}

ApplicationOperationState ToolsEngine::Update(Uint64 ticks)
{
    if (!m_haveSetup)
    {
        Setup();
        m_haveSetup = true;
    }

    for (const std::shared_ptr<UpdateableObject>& obj : m_updatables)
    {
        obj->Update();
    }

    return ApplicationOperationState::Running;
}

void ToolsEngine::Draw()
{
    for (const std::shared_ptr<UpdateableObject>& obj : m_updatables)
    {
        obj->Draw();
    }

    ImGui::Begin("Hello, Dear ImGui with SDL2");
    ImGui::TextColored(ImVec4(150, 150, 150, 150), "This is just a basic Hello World!");
    ImGui::End();
}

void ToolsEngine::WindowStart()
{
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
}

void ToolsEngine::WindowTeardown()
{
}

void ToolsEngine::Setup()
{
    std::shared_ptr<UpdateableObject> gameViewport = std::make_shared<GameViewport>();
    gameViewport->Setup(m_windowPackage);
    m_updatables.push_back(gameViewport);

    std::shared_ptr<LoggerOutput> loggerWindow = std::make_shared<LoggerOutput>();
    loggerWindow->Setup(m_windowPackage);
    m_updatables.push_back(loggerWindow);
}
