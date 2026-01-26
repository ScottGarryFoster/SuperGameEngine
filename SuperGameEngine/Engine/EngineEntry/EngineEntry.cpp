#include "EngineEntry.h"
#include "Engine.h"

#include <Windows.h>

#include "../../../FatedQuest.Libraries/GamePackage/GamePackage/CombinedGamePackage.h"
#include "../../../FatedQuest.Libraries/GamePackage/GamePackage/SGEPackagePaths.h"
#include "../Engine/Factory/EngineFactory.h"
#include "../Engine/Graphics/Texture/SDLRenderer.h"
#include "../.././../FatedQuest.Libraries/Logger/AllReferences.h"
#include "../../Input/InputManagement/SuperSDLInputManager.h"
#include "Engine/Foundation/ProjectPropertiesProvider.h"
#include "Engine/Window/SDLWindowManager.h"

using namespace SuperGameEngine;
using namespace FatedQuestLibraries;
using namespace SuperGameInput;

EngineEntry::EngineEntry()
{
    m_inputManager = std::make_shared<SuperSDLInputManager>();
    m_engineWindowManager = std::make_shared<SDLWindowManager>();

    // TODO: Consider this reloading when the window restarts.
    auto combinedGamePackage = std::make_shared<CombinedGamePackage>();
    auto paths = std::make_shared<SGEPackagePaths>();
    combinedGamePackage->Load(paths);
    m_gamePackage = combinedGamePackage;
}

int EngineEntry::RunApplication(const std::string& engineType)
{
    ApplicationOperationState windowState = ApplicationOperationState::Restart;
    while (windowState != ApplicationOperationState::Close)
    {
        windowState = RunSDLWindow(engineType);
    }

    return 0;
}

ApplicationOperationState EngineEntry::RunSDLWindow(const std::string& engineType)
{
    if (!InitialiseProjectProperties())
    {
        Log::Error("Could not create Project Properties. Application aborted.");
        return ApplicationOperationState::Close;
    }

    // Initialize SDL. SDL_Init will return -1 if it fails.
    if (SDL_Init(SDL_INIT_EVERYTHING | SDL_INIT_JOYSTICK) < 0)
    {
        std::string sdlError = SDL_GetError();
        Log::Error("Error initializing SDL: " + sdlError);
        return ApplicationOperationState::Close;
    }

    // Set SDL hint to enable VSync
    if (!SDL_SetHint(SDL_HINT_RENDER_VSYNC, "0"))
    {
        Log::Error("Warning: VSync not enabled!");
        return ApplicationOperationState::Close;
    }

    m_engineWindowManager->Setup(m_projectProperties);
    m_engineWindowManager->CreateGameWindow("New", WindowPredefinedPosition::Centered, FPoint(1280, 720));

    // Setup the engine.
    if (!m_engine)
    {
        m_engine = EngineFactory::CreateEngine(engineType);
        if (m_engine == nullptr)
        {
            Log::Error("Could not create Engine from factory: " + engineType);
            return ApplicationOperationState::Close;
        }
    }

    m_engine->GiveGamePackage(m_gamePackage);
    m_engine->GiveRenderer(m_engineWindowManager->GetDefaultRenderer());
    m_engine->GiveInput(m_inputManager);
    m_engine->GiveProjectProperties(m_projectProperties);
    m_engine->WindowStart();
    m_engine->EngineStart();

    // Event handler
    SDL_Event e;

    Uint64 startTime = SDL_GetTicks64();

    // Main loop
    ApplicationOperationState operationState = ApplicationOperationState::Running;
    while (operationState == ApplicationOperationState::Running)
    {
        auto eventAnswer = ApplicationOperationState::Running;

        // Handle events on the queue
        while (SDL_PollEvent(&e) != 0)
        {
            m_inputManager->EventUpdate(e);

            eventAnswer = m_engine->Event(e);
            if (eventAnswer != ApplicationOperationState::Running)
            {
                operationState = eventAnswer;
            }

            if (e.type == SDL_QUIT)
            {
                Log::Info("Engine has indicated from Events it would like to QUIT.");
                operationState = ApplicationOperationState::Close;
            }
        }

        Uint64 currentTime = SDL_GetTicks64();
        Uint64 ticksThisFrame = currentTime - startTime;
        startTime = currentTime;

        ApplicationOperationState updateAnswer = m_engine->Update(ticksThisFrame);
        if (updateAnswer != ApplicationOperationState::Running)
        {
            operationState = updateAnswer;
        }

        // Update the state of inputs. Must be run after anything which uses it.
        m_inputManager->Update();

        // Unlikely to occur but in the situation the event and update loop
        // try to override one another we should log this, in case we get a bug
        // here.
#if defined _DEBUG || defined _TOOLS
        if (eventAnswer != ApplicationOperationState::Running &&
            updateAnswer != ApplicationOperationState::Running &&
            eventAnswer != updateAnswer)
        {
            Log::Warning("The event update and the update loop are both trying to affect the application state but do not agree on what to do."
                      "Event State: " + EApplicationOperationState::ToString(eventAnswer) +
                      "Update State: " + EApplicationOperationState::ToString(updateAnswer));
        }
#endif

        // Clear the renderer
        SDL_SetRenderDrawColor(m_engineWindowManager->GetDefaultRenderer()->GetRenderer(), 103, 235, 229, 255);
        SDL_RenderClear(m_engineWindowManager->GetDefaultRenderer()->GetRenderer());

        m_engine->Draw();

        // Update screen
        SDL_RenderPresent(m_engineWindowManager->GetDefaultRenderer()->GetRenderer());

        // Add a small delay to avoid 100% CPU usage
        SDL_Delay(3);
    }



    // Wait
    //system("pause");

    m_engine->WindowTeardown();
    m_engine->EngineEnd();
    m_engineWindowManager->DestroyWindow();

    // Quit SDL
    SDL_Quit();

#ifdef _DEBUG
    // Close console window in debug mode
    FreeConsole();
#endif

    return operationState;
}

bool EngineEntry::InitialiseProjectProperties()
{
    auto provider = std::make_shared<ProjectPropertiesProvider>();
    m_projectProperties = provider->LoadProjectProperties(m_gamePackage);

    if (m_projectProperties)
    {
        return true;
    }
    
    return false;
}
