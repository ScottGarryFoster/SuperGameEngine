#include "ToolsEngine.h"
#include <SDL.h>

#include "../../../FatedQuest.Libraries/GamePackage/GamePackage/CombinedGamePackage.h"
#include "../../../FatedQuest.Libraries/GamePackage/GamePackage/PackagePaths.h"
#include "../../../FatedQuest.Libraries/GamePackage/GamePackage/SGEPackagePaths.h"
#include "../../Engine/Engine/Content/ContentManager.h"
#include "../../Engine/Engine/Content/SuperContentManager.h"
#include "../ImGuiIncludes.h"
#include "../../Engine/Structural/Serializable/SuperSerializableParser.h"
#include "../Panels/GameViewport/GameViewport.h"
#include "../ToolsEngine/Packages/WindowPackage.h"
#include "../Panels/LoggerOutput/LoggerOutput.h"
#include "../Panels/MainMenuBar/MainMenuBar.h"
#include "../Panels/AssetBrowser/AssetBrowser.h"

#include "../Engine/Content/ImGuiTextureManager.h"
#include "../Panels/DockableContainer/DockableContainer.h"
#include "../Panels/SceneHierarchy/SceneHierarchy.h"
#include "../Panels/InspectorWindow/InspectorWindow.h"
#include "Engine/FileSystem/GamePackage/ToolsGamePackage.h"
#include "Engine/Structural/Asset/AssetTemplateProvider.h"
#include "Engine/Structural/Asset/ToolsAssetTemplateProvider.h"
#include "FrameworkManager/ToolsFrameworkManager.h"
#include "ViewElements/ColoursAndStyles/ToolsColoursAndStyles.h"

// This should be included early in the engine for the inspector.
#include "Engine/Content/ToolsTextureAssetFactory.h"
#include "Engine/Content/ToolsTextureFactory.h"
#include "Engine/Content/ToolsTextureWrapperFactory.h"
#include "Engine/CrossEngineObjects/CrossEngineObjects.h"
#include "Engine/Structural/UniversalObjectData/ToolsUniversalObjectDataTemplateProvider.h"
#include "Panels/PanelManager/SuperPanelManager.h"
#include "Panels/ProjectProperties/ProjectPropertiesPanel.h"
#include "Panels/Viewport/ViewportPanel.h"
#include "Panels/ViewportTools/ViewportTools.h"
#include "Panels/ViewportTools/ViewportToolsPanel.h"
#include "UserInputManagement/EnumFilterFactoryFeeder.h"

using namespace SuperGameTools;

ToolsEngine::ToolsEngine()
{
    m_windowPackage = std::make_shared<WindowPackage>();
    m_haveSetup = false;
    m_superContentManager = std::make_shared<SuperContentManager>();
    m_dockableContainer = std::make_shared<DockableContainer>();

    m_panelManager = std::make_shared<SuperPanelManager>();
    m_panelManager->UpdateDistributedWeakPointer(m_panelManager);
    m_windowPackage->SetPanelManager(m_panelManager);
    m_panelManager->Setup(m_windowPackage);

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
        m_superContentManager->GiveGamePackage(m_gamePackage);

        auto factories = ContentFactories
        {
            .TextureFactory = std::make_shared<ToolsTextureFactory>(),
            .TextureAssetFactory = std::make_shared<ToolsTextureAssetFactory>(),
            .TextureWrapperFactory = std::make_shared<ToolsTextureWrapperFactory>()
        };
        auto textureManager = std::make_shared<ImGuiTextureManager>(renderer, m_gamePackage, factories);
        textureManager->UpdateDistributedWeakPointer(textureManager);
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

void ToolsEngine::GiveGamePackage(const std::shared_ptr<FatedQuestLibraries::GamePackage>& gamePackage)
{
    m_gamePackage = gamePackage;
}

void ToolsEngine::GiveProjectProperties(const std::shared_ptr<ProjectProperties>& projectProperties)
{
    Log::Info("ToolsEngine does not use ProjectProperties.", 
        "ToolsEngine::GiveProjectProperties(const std::shared_ptr<ProjectProperties>)");
}

void ToolsEngine::GiveControls(const std::shared_ptr<EngineControls>& engineControls)
{
    m_engineControls = engineControls;
}

void ToolsEngine::GiveSDLGameEngineTexture(const std::shared_ptr<SDLTextureChest>& sdlRenderTexture)
{
    m_sdlGameViewportRenderTexture = sdlRenderTexture;

    m_windowPackage->SetSDLGameViewportRenderTexture(m_sdlGameViewportRenderTexture);
}

void ToolsEngine::GiveSDLViewportTexture(const std::shared_ptr<SDLTextureChest>& sdlRenderTexture)
{
    m_sdlToolsViewportRenderTexture = sdlRenderTexture;

    m_windowPackage->SetSDLToolsViewportRenderTexture(m_sdlToolsViewportRenderTexture);
}

void ToolsEngine::GiveEnginePlayControls(const std::shared_ptr<EngineEntryCommunication>& engineEntryCommunication)
{
    m_engineEntryCommunication = engineEntryCommunication;
    m_windowPackage->SetEngineEntryCommunication(m_engineEntryCommunication);
}

void ToolsEngine::GiveCrossEngineObjects(const std::shared_ptr<CrossEngineObjects>& crossEngineObjects)
{
    m_crossEngineObjects = crossEngineObjects;
    m_crossEngineObjects->SetWindowPackage(m_windowPackage);
}

void ToolsEngine::GiveViewportEngineAndPanelCommunication(
    const std::shared_ptr<ViewportEngineAndPanelCommunication>& engineAndPanelCommunication)
{
    m_viewportEngineAndPanelCommunication = engineAndPanelCommunication;
}

ApplicationOperationState ToolsEngine::Event(SDL_Event event)
{
    return ApplicationOperationState::Running;
}

ApplicationOperationState ToolsEngine::Update(Uint64 ticks)
{
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

void ToolsEngine::EngineStart()
{
    if (!m_haveSetup)
    {
        Setup();
        m_haveSetup = true;
    }
}

void ToolsEngine::EngineEnd()
{
    m_haveSetup = false;
    m_crossEngineObjects->Reset();
}

void ToolsEngine::Setup()
{
    auto menuBar = std::make_shared<MainMenuBar>();
    menuBar->UpdateDistributedWeakPointer(menuBar);

    std::shared_ptr<SceneHierarchy> sceneHierarchy = std::make_shared<SceneHierarchy>();
    sceneHierarchy->FEventObserver::UpdateDistributedWeakPointer(sceneHierarchy);

    std::shared_ptr<InspectorWindow> inspectorWindow = std::make_shared<InspectorWindow>();
    inspectorWindow->FEventObserver::UpdateDistributedWeakPointer(inspectorWindow);

    m_sharedSceneChangedEvents = std::make_shared<ToolsSharedSceneChangedEvents>(sceneHierarchy, inspectorWindow);
    m_crossEngineObjects->SetSharedSceneChangedEvents(m_sharedSceneChangedEvents);

    std::shared_ptr<LoggerOutput> loggerWindow = std::make_shared<LoggerOutput>();
    loggerWindow->FEventObserver::UpdateDistributedWeakPointer(loggerWindow);

    std::shared_ptr<AssetBrowser> assetBrowserWindow = std::make_shared<AssetBrowser>();
    assetBrowserWindow->FEventObserver::UpdateDistributedWeakPointer(assetBrowserWindow);

    auto projectProperties = std::make_shared<ProjectPropertiesPanel>();
    projectProperties->FEventObserver::UpdateDistributedWeakPointer(projectProperties);

    auto viewportPanel = std::make_shared<ViewportPanel>();
    viewportPanel->GiveViewportEngineAndPanelCommunication(m_viewportEngineAndPanelCommunication);
    viewportPanel->UpdateDistributedWeakPointer(viewportPanel);
    viewportPanel->GiveEngineControls(m_engineControls);

    auto viewportToolsPanel = std::make_shared<ViewportToolsPanel>();
    viewportToolsPanel->UpdateDistributedWeakPointer(viewportToolsPanel);

    m_windowPackage->GetColourPalette()->SetGlobalColoursAndStyles();

    // Must be made first as other things latch on to it.
    menuBar->Setup(m_windowPackage);
    m_windowPackage->SetTopMenu(menuBar->GetTopMenuBar());
    m_updatables.push_back(menuBar);

    // Ensure we listen to logs early.
    loggerWindow->Setup(m_windowPackage);
    if (auto shared = Log::GetEvent().lock())
    {
        std::weak_ptr<FEventObserver> weak = loggerWindow;
        shared->Subscribe(weak);
    }
    m_updatables.push_back(loggerWindow);
    m_windowPackage->GetPanelManager()->RegisterPanel(loggerWindow);

    // Then framework
    auto framework = std::make_shared<ToolsFrameworkManager>(m_windowPackage);
    framework->Setup();
    m_windowPackage->SetFrameworkManager(framework);

    // We are restricted to doing this at the main setup because only here do we 100% know that the
    // game package exists.
    // Load asset templates which must come before Inspector window and Asset Browser Setup.
    auto assetTemplateProvider = std::make_shared<ToolsAssetTemplateProvider>
        (m_windowPackage->GetContentManager()->GamePackage());
    assetTemplateProvider->LoadAllAssetMeta();
    m_windowPackage->SetAssetTemplateProvider(assetTemplateProvider);

    // And general UOD which at the time of writing should be fine before the majority of windows as it is used for properties.
    auto universalObjectTemplateProvider = std::make_shared<ToolsUniversalObjectDataTemplateProvider>
        (m_windowPackage->GetContentManager()->GamePackage());
    universalObjectTemplateProvider->LoadAllTemplateMetaData();
    m_windowPackage->SetUniversalObjectDataTemplateProvider(universalObjectTemplateProvider);
        
    // Everything else should be able to be in any order
    std::shared_ptr<GameViewport> gameViewport = std::make_shared<GameViewport>();
    gameViewport->Setup(m_windowPackage);
    m_updatables.push_back(gameViewport);
    m_windowPackage->GetPanelManager()->RegisterPanel(gameViewport);

    inspectorWindow->Setup(m_windowPackage);
    m_updatables.push_back(inspectorWindow);
    m_windowPackage->GetPanelManager()->RegisterPanel(inspectorWindow);

    sceneHierarchy->Setup(m_windowPackage);
    inspectorWindow->OnMenuDelete()->Subscribe(sceneHierarchy);
    m_updatables.push_back(sceneHierarchy);
    m_windowPackage->GetPanelManager()->RegisterPanel(sceneHierarchy);

    assetBrowserWindow->Setup(m_windowPackage);
    m_updatables.push_back(assetBrowserWindow);
    m_windowPackage->GetPanelManager()->RegisterPanel(assetBrowserWindow);

    projectProperties->Setup(m_windowPackage);
    m_updatables.push_back(projectProperties);
    m_windowPackage->GetPanelManager()->RegisterPanel(projectProperties);

    viewportPanel->Setup(m_windowPackage);
    m_updatables.push_back(viewportPanel);
    m_windowPackage->GetPanelManager()->RegisterPanel(viewportPanel);

    viewportToolsPanel->Setup(m_windowPackage);
    m_updatables.push_back(viewportToolsPanel);
    m_windowPackage->GetPanelManager()->RegisterPanel(viewportToolsPanel);

    // This must occur after setup of these.
    viewportToolsPanel->OnWindowShownOrHidden()->Subscribe(viewportPanel);
    viewportPanel->GiveViewportTools(viewportToolsPanel->GetViewportTools());

    // Run last after all panels have been run.
    menuBar->SetupPostPanels();
}
