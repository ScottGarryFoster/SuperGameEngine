#include "ToolsEngine.h"
#include <SDL.h>

#include "../../../FatedQuest.Libraries/GamePackage/GamePackage/CombinedGamePackage.h"
#include "../../../FatedQuest.Libraries/GamePackage/GamePackage/PackagePaths.h"
#include "../../../FatedQuest.Libraries/GamePackage/GamePackage/SGEPackagePaths.h"
#include "../../Engine/Engine/Content/ContentManager.h"
#include "../../Engine/Engine/Content/SuperContentManager.h"
#include "../ImGuiIncludes.h"
#include "../../Engine/Structural/Serializable/SuperSerializableParser.h"
#include "../Windows/GameViewport/GameViewport.h"
#include "../ToolsEngine/Packages/WindowPackage.h"
#include "../Windows/LoggerOutput/LoggerOutput.h"
#include "../Windows/MainMenuBar/MainMenuBar.h"

#include "../Engine/Content/ImGuiTextureManager.h"
#include "../Windows/DockableContainer/DockableContainer.h"
#include "../Windows/SceneHierarchy/SceneHierarchy.h"
#include "../Windows/InspectorWindow/InspectorWindow.h"
#include "FrameworkManager/ToolsFrameworkManager.h"
#include "ViewElements/ColoursAndStyles/ToolsColoursAndStyles.h"

using namespace SuperGameTools;

ToolsEngine::ToolsEngine()
{
    m_windowPackage = std::make_shared<WindowPackage>();
    m_haveSetup = false;
    m_superContentManager = std::make_shared<SuperContentManager>();
    m_dockableContainer = std::make_shared<DockableContainer>();
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
        m_windowPackage->SetColourPalette(std::make_shared<ToolsColoursAndStyles>(paths));
        auto gamePackage = std::make_shared<CombinedGamePackage>();
        gamePackage->Load(paths);
        m_superContentManager->GiveGamePackage(gamePackage);

        auto textureManager = std::make_shared<ImGuiTextureManager>(renderer, gamePackage);
        m_superContentManager->GiveSuperTextureManager(textureManager);

        m_windowPackage->SetContentManager(m_superContentManager);
        m_windowPackage->SetParser(std::make_shared<SuperSerializableParser>());
        m_windowPackage->SetPackagePaths(paths);
    }
}

void ToolsEngine::GiveInput(const std::shared_ptr<SuperGameInput::SDLInputManager>& inputManager)
{
    m_inputManager = inputManager;
}

void ToolsEngine::GiveSDLTexture(std::shared_ptr<ExtremelyWeakWrapper<SDL_Texture>> sdlRenderTexture)
{
    m_sdlRenderTexture = sdlRenderTexture;

    m_windowPackage->SetSDLRenderTexture(m_sdlRenderTexture);
}

void ToolsEngine::GiveEnginePlayControls(const std::shared_ptr<EngineEntryCommunication>& engineEntryCommunication)
{
    m_engineEntryCommunication = engineEntryCommunication;
    m_windowPackage->SetEngineEntryCommunication(m_engineEntryCommunication);
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
    m_dockableContainer->DrawDockableContainer();

    ImGui::ShowDemoWindow();
    for (const std::shared_ptr<UpdateableObject>& obj : m_updatables)
    {
        obj->Draw();
    }

    // Stop drawing the dockable container.
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
    auto menuBar = std::make_shared<MainMenuBar>();
    std::shared_ptr<UpdateableObject> gameViewport = std::make_shared<GameViewport>();

    std::shared_ptr<SceneHierarchy> sceneHierarchy = std::make_shared<SceneHierarchy>();
    sceneHierarchy->UpdateDistributedWeakPointer(sceneHierarchy);

    std::shared_ptr<InspectorWindow> inspectorWindow = std::make_shared<InspectorWindow>();
    inspectorWindow->UpdateDistributedWeakPointer(inspectorWindow);

    std::shared_ptr<LoggerOutput> loggerWindow = std::make_shared<LoggerOutput>();
    loggerWindow->UpdateDistributedWeakPointer(loggerWindow);

    m_windowPackage->GetColourPalette()->SetGlobalColoursAndStyles();

    // Ensure we listen to logs early.
    loggerWindow->Setup(m_windowPackage);
    if (auto shared = Log::GetEvent().lock())
    {
        std::weak_ptr<FEventObserver> weak = loggerWindow;
        shared->Subscribe(weak);
    }
    m_updatables.push_back(loggerWindow);

    // Must be made first as other things latch on to it.
    menuBar->Setup(m_windowPackage);
    m_windowPackage->SetTopMenu(menuBar->GetTopMenuBar());
    m_updatables.push_back(menuBar);

    // Then framework
    auto framework = std::make_shared<ToolsFrameworkManager>(m_windowPackage);
    framework->Setup();
    m_windowPackage->SetFrameworkManager(framework);

    // Everything else should be able to be in any order
    gameViewport->Setup(m_windowPackage);
    m_updatables.push_back(gameViewport);

    inspectorWindow->Setup(m_windowPackage);
    m_updatables.push_back(inspectorWindow);

    sceneHierarchy->Setup(m_windowPackage);
    inspectorWindow->OnMenuDelete()->Subscribe(sceneHierarchy);
    m_updatables.push_back(sceneHierarchy);
}
