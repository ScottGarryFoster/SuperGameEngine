#include "DebugEngine.h"

#include "../Engine/Content/SuperContentManager.h"
#include "../Structural/GameObject/SuperGameObject.h"
#include "../Structural/Packages/SuperGrandScenePackage.h"
#include "../Engine/Basic/SuperGameTime.h"

// TODO: Reference all Components
#include "DebugLogger.h"
#include "../Structural/InternalComponents/TestComponent/TestComponent.h"
#include "../Structural/InternalComponents/SpriteComponent/SpriteComponent.h"
#include "../Structural/Scene/GrandScene.h"
#include "../Structural/Scene/Scene.h"
#include "../Structural/Scene/SuperGrandScene.h"

#include "../../../FatedQuest.Libraries/GamePackage/GamePackage/CombinedGamePackage.h"
#include "../../../FatedQuest.Libraries/GamePackage/GamePackage/SGEPackagePaths.h"
#include "../../../FatedQuest.Libraries/GamePackage/GamePackage/FileSystem/PackageFileSystemFile.h"

#include "../FatedQuestReferences.h"
#include "../../../FatedQuest.Libraries/Logger/Logger/Log.h"
#include "../Engine/Content/SuperSceneStorageCache.h"
#include "../Structural/Loaders/SuperSceneLoader.h"

using namespace SuperGameEngine;
using namespace FatedQuestLibraries;

void DebugEngine::GiveRenderer(std::shared_ptr<SDLRendererReader> renderer)
{
    m_renderer = renderer;
    if (!m_textureManager)
    {
        m_grandSceneLoadPackage = std::make_shared<SuperGrandScenePackage>();

        auto m_contentManager = std::make_shared<SuperContentManager>();

        m_combinedGamePackage = std::make_shared<CombinedGamePackage>();
        std::shared_ptr<PackagePaths> paths = std::make_shared<SGEPackagePaths>();
        m_combinedGamePackage->Load(paths);
        m_contentManager->GiveGamePackage(m_combinedGamePackage);

        m_textureManager = std::make_shared<SuperTextureManager>(renderer, m_combinedGamePackage);
        m_contentManager->GiveSuperTextureManager(m_textureManager);

        m_grandSceneLoadPackage->SetContentManager(m_contentManager);

        std::shared_ptr<SceneLoadPackage> sceneLoadPackage = m_grandSceneLoadPackage->GetSceneLoadPackage();
        auto sceneLoader = std::make_shared<SuperSceneLoader>(sceneLoadPackage);
        auto sceneLoadCache = std::make_shared<SuperSceneStorageCache>();
        sceneLoadCache->Setup(sceneLoader, m_combinedGamePackage);
        m_contentManager->GiveSceneCache(sceneLoadCache);

        m_gameTime = std::make_shared<SuperGameTime>();
        curr = m_gameTime->AllTime() + 5000;

        t = 0;
    }
    else
    {
        // TODO: Create a way to update the Renderer.
    }
}

ApplicationOperationState DebugEngine::Event(SDL_Event event)
{
    return ApplicationOperationState::Running;
}

ApplicationOperationState DebugEngine::Update(Uint64 ticks)
{
    if (m_haveLoaded && !m_haveSavedScene)
    {
        
        //m_haveSavedScene = true;
    }

    if (!m_haveLoaded)
    {
        m_haveLoaded = true;

        curr = ticks;

        m_grandScene = std::make_shared<SuperGrandScene>();
        m_grandScene->Setup(m_grandSceneLoadPackage);

        //m_scene = m_grandScene->CreateAndAddNewScene("TestScene.txt");
        m_scene = m_grandScene->CreateAndAddNewScene("savedOut.txt");

        // Keep in mind in the current setup TestComponent spawns Sprite so this is recursive if we send the same object.
        m_grandSceneLoadPackage->GetContentManager()->Scene()->SaveScene(m_scene, "E:\\Development\\SuperGameEngine-Myriad\\Products\\savedOut2.txt");
        

        //m_scene = m_grandScene->CreateAndAddNewScene();
        //m_go = m_scene->CreateAndAddNewGameObject();
        //m_go->AddComponent("TestComponent");

        //std::optional<std::shared_ptr<void>> fromFactory = ClassTypes::GetInstance().Create("SuperGameObject");
        //if (fromFactory.has_value())
        //{
        //    std::shared_ptr<void> sgov = fromFactory.value();
        //    std::shared_ptr<SuperGameObject> sgo = std::static_pointer_cast<SuperGameObject>(fromFactory.value());
        //    if (1 == 1)
        //    {
        //        
        //    }
        //}

        //std::string testPath = R"(Engine\Input\ControllerMappings\NintendoN64Controller.xml)";
        //if (m_combinedGamePackage->File()->Exists(testPath))
        //{
        //    std::string contents = m_combinedGamePackage->File()->ReadFileContents(testPath);
        //    if (contents[0] == '<')
        //    {
        //        auto sprite = std::static_pointer_cast<SpriteComponent>(m_go->AddComponent("SpriteComponent"));
        //        sprite->Move(400, 400);
        //    }
        //}

#ifdef defined(_DEBUG) && !defined(_TOOLS)
        m_logger = std::make_shared<DebugLogger>();
        if (auto shared = Log::GetEvent().lock())
        {
            shared->Subscribe(m_logger);
        }
#endif

    }

    m_gameTime->SetTicksSinceLastFrame(ticks);
    m_grandScene->Update(m_gameTime);


    if (m_gameTime->AllTime() > curr)
    {
        curr = m_gameTime->AllTime() + 5000;

        if (t == 0)
        {
            Log::Info("Test 1");
        }
        else if (t == 1)
        {
            Log::Warning("Warning Message");
        }
        else if (t == 2)
        {
            Log::Error("Error Message");
        }
        else if (t == 3)
        {
            Log::Exception("Exception Message");
            t = -1;
        }
        ++t;

        //if (m_scene)
        //{
        //    m_scene->Destroy();
        //    m_scene = std::shared_ptr<Scene>();
        //}

    }

    /*m_gameTime->SetTicksSinceLastFrame(ticks);
    if (m_go)
    {
        
        m_go = std::shared_ptr<SuperGameObject>();
    }
    else
    {
        m_go = std::make_shared<SuperGameObject>();
        m_go->Setup(m_loadPackage);
        m_go->AddComponent("TestComponent");
        m_go->Update(m_gameTime);
    }

    curr += ticks;
    if (curr > 10000)
    {
        m_haveRestartedWindow = true;
        curr = 0;
        std::cout << "Restart" << std::endl;
        return ApplicationOperationState::Restart;
    }*/

    return ApplicationOperationState::Running;
}

void DebugEngine::Draw()
{
    if (m_grandScene)
    {
        m_grandScene->Draw();
    }

}

void DebugEngine::WindowStart()
{
    if (m_haveLoaded)
    {
        std::vector<std::string> errors;
        m_textureManager->RemakeAllTextures(errors);
    }
}

void DebugEngine::WindowTeardown()
{
}
