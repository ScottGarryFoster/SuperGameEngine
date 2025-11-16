#include "MainEngine.h"

#include "../../../FatedQuest.Libraries/GamePackage/GamePackage/CombinedGamePackage.h"
#include "DebugEngine/DebugLogger.h"
#include "../Engine/Structural/Packages/SuperGrandScenePackage.h"
#include "../Input/InputManagement/SDLInputManager.h"
#include "Basic/SuperGameTime.h"
#include "Content/SuperContentManager.h"
#include "Content/SuperSceneStorageCache.h"
#include "Content/SuperTextureManager.h"
#include "Structural/Loaders/SuperSceneLoader.h"
#include "Structural/Scene/GrandScene.h"
#include "Structural/Scene/SuperGrandScene.h"
#include "Structural/Serializable/SuperSerializableParser.h"
#include "../Structural/InternalComponents/InternalComponents.h"
#include "Foundation/ProjectProperties.h"

using namespace SuperGameEngine;

MainEngine::MainEngine()
{
#if defined(_DEBUG) && !defined(_TOOLS)

    m_logger = std::make_shared<DebugLogger>();
    if (auto shared = Log::GetEvent().lock())
    {
        shared->Subscribe(m_logger);
    }
#endif

    m_haveLoaded = false;
}

MainEngine::~MainEngine()
{
#if defined(_DEBUG) && !defined(_TOOLS)
    if (m_logger)
    {
        if (auto shared = Log::GetEvent().lock())
        {
            shared->Unsubscribe(m_logger);
        }
    }
#endif
}

void MainEngine::GiveRenderer(std::shared_ptr<SDLRendererReader> renderer)
{
    m_renderer = renderer;
}

void MainEngine::GiveInput(const std::shared_ptr<SuperGameInput::SDLInputManager>& inputManager)
{
    m_inputManager = inputManager;

    if (auto superGrandScene = std::dynamic_pointer_cast<SuperGrandScenePackage>(m_grandSceneLoadPackage))
    {
        superGrandScene->SetInputHandler(m_inputManager);
    }
}

void MainEngine::GiveGamePackage(const std::shared_ptr<FatedQuestLibraries::GamePackage>& gamePackage)
{
    m_gamePackage = gamePackage;
}

void MainEngine::GiveProjectProperties(const std::shared_ptr<ProjectProperties>& projectProperties)
{
    m_projectProperties = projectProperties;
}

ApplicationOperationState MainEngine::Event(SDL_Event event)
{
    return ApplicationOperationState::Running;
}

ApplicationOperationState MainEngine::Update(Uint64 ticks)
{
    if (!m_haveLoaded)
    {
        Setup();
    }

    m_gameTime->SetTicksSinceLastFrame(ticks);
    m_grandScene->Update(m_gameTime);

    return ApplicationOperationState::Running;
}

void MainEngine::Draw()
{
    if (m_grandScene)
    {
        m_grandScene->Draw();
    }
}

void MainEngine::WindowStart()
{
    if (m_haveLoaded)
    {
        std::vector<std::string> errors;
        m_textureManager->RemakeAllTextures(errors);
    }
}

void MainEngine::WindowTeardown()
{
}

void MainEngine::Setup()
{
    if (m_haveLoaded)
    {
        Log::Warning("Setup called twice.");
        return;
    }

    m_grandScene = std::make_shared<SuperGrandScene>();
    m_grandSceneLoadPackage = CreateGrandScenePackage();
    m_grandScene->Setup(m_grandSceneLoadPackage);

    m_grandScene->CreateAndAddNewScene(m_projectProperties->GetStartScene());

    m_haveLoaded = true;
}

std::shared_ptr<GrandScenePackage> MainEngine::CreateGrandScenePackage()
{
    if (m_haveLoaded)
    {
        Log::Warning("Setup called twice.");
        return {};
    }

    if (!m_inputManager)
    {
        Log::Error("No input package. Cannot load scene.", "MainEngine::CreateGrandScenePackage");
        return {};
    }

    if (!m_renderer)
    {
        Log::Error("No Renderer. Cannot load scene.", "MainEngine::CreateGrandScenePackage");
        return {};
    }

    auto grandSceneLoadPackage = std::make_shared<SuperGrandScenePackage>();
    auto contentManager = std::make_shared<SuperContentManager>();
    contentManager->GiveGamePackage(m_gamePackage);

    // Loads configurations.
    m_inputManager->Setup(m_gamePackage);

    std::shared_ptr<SuperTextureManager> textureManager = 
        std::make_shared<SuperTextureManager>(m_renderer, m_gamePackage);
    m_textureManager = textureManager;
    textureManager->UpdateDistributedWeakPointer(m_textureManager);
    contentManager->GiveSuperTextureManager(textureManager);

    grandSceneLoadPackage->SetContentManager(contentManager);

    grandSceneLoadPackage->SetSerializableParser(
        std::make_shared<SuperSerializableParser>());

    grandSceneLoadPackage->SetInputHandler(m_inputManager);

    std::shared_ptr<SceneLoadPackage> sceneLoadPackage = grandSceneLoadPackage->GetSceneLoadPackage();
    auto sceneLoader = std::make_shared<SuperSceneLoader>(sceneLoadPackage);
    auto sceneLoadCache = std::make_shared<SuperSceneStorageCache>();
    sceneLoadCache->Setup(sceneLoader, m_gamePackage);
    contentManager->GiveSceneCache(sceneLoadCache);

    m_gameTime = std::make_shared<SuperGameTime>();

    return grandSceneLoadPackage;
}
