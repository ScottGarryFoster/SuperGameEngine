#include "ToolsEngineEntry.h"

#include <Windows.h>
#ifdef _DEBUG
#include <iostream>
#endif

#include "../ImGuiIncludes.h"
#include "../../../FatedQuest.Libraries/StoredDocument/Converters/SimpleDocumentToXml.h"
#include "../../Input/InputManagement/SuperSDLInputManager.h"
#include "Communication/ToolsEngineEntryCommunication.h"
#include "Communication/EngineFlowPlayControl.h"
#include "Communication/ToolsEngineControl.h"
#include "Engine/Basic/SuperEngineControls.h"
#include "Engine/Basic/ViewportSizeChangedEventArguments.h"
#include "Engine/FileSystem/GamePackage/ToolsGamePackage.h"
#include "Engine/Foundation/ProjectPropertiesProvider.h"
#include "Panels/Viewport/ViewportEngine.h"
#include "Settings/ToolsLayoutSettings.h"
#include "Settings/ToolsSettingsPaths.h"

using namespace SuperGameTools;

ToolsEngineEntry::ToolsEngineEntry()
{
    auto toolsEngineEntry = std::make_shared<ToolsEngineEntryCommunication>();
    m_engineEntryCommunication = toolsEngineEntry;

    m_engineFlow = std::make_shared<ToolsEngineControl>();
    toolsEngineEntry->SetPlayControls(m_engineFlow);

    m_layoutSettings = std::make_shared<ToolsLayoutSettings>(
        std::make_shared<ToolsSettingsPaths>(),
        "layoutSettings.xml",
        std::make_shared<SimpleDocumentToXml>());

    m_inputManager = std::make_shared<SuperGameInput::SuperSDLInputManager>();

    // TODO: Consider this reloading when the window restarts.
    auto combinedGamePackage = std::make_shared<ToolsGamePackage>();
    auto paths = std::make_shared<SGEPackagePaths>();
    combinedGamePackage->Load(paths);
    m_gamePackage = combinedGamePackage;
}

int ToolsEngineEntry::RunApplication(const std::string& engineType)
{
    m_imgui = std::make_shared<ImGuiContainer>();
    m_toolsEngine = std::make_shared<ToolsEngine>();
    m_toolsEngine->GiveEnginePlayControls(m_engineEntryCommunication);

    m_sdlGameViewportTexture = std::make_shared<ExtremelyWeakWrapper<SDL_Texture>>(nullptr);
    m_toolsEngine->GiveSDLGameEngineTexture(m_sdlGameViewportTexture);

    m_sdlToolsViewportTexture = std::make_shared<ExtremelyWeakWrapper<SDL_Texture>>(nullptr);
    m_toolsEngine->GiveSDLViewportTexture(m_sdlToolsViewportTexture);

    m_gameRenderer = std::make_shared<SDLRenderer>();
    m_toolsViewportRenderer = std::make_shared<SDLRenderer>();
    m_Toolsrenderer = std::make_shared<SDLRenderer>();
    ApplicationOperationState windowState = ApplicationOperationState::Restart;
    while (windowState != ApplicationOperationState::Close)
    {
        windowState = RunSDLWindow(engineType);
    }

    return 0;
}

void ToolsEngineEntry::Invoke(std::shared_ptr<FEventArguments> arguments)
{
    if (auto viewportArgs = std::dynamic_pointer_cast<ViewportSizeChangedEventArguments>(arguments))
    {
        SDL_Renderer* renderer = nullptr;
        if (viewportArgs->GetName() == "ToolsMainViewport")
        {
            renderer = m_toolsViewportRenderer->GetRenderer();
            SDL_DestroyTexture(m_sdlToolsViewportTexture->Get());
        }
        else if (viewportArgs->GetName() == "GameEngine")
        {
            renderer = m_gameRenderer->GetRenderer();
            SDL_DestroyTexture(m_sdlGameViewportTexture->Get());
        }

        if (renderer == nullptr)
        {
            Log::Error("No valid viewport name when requesting a change. Name: " + viewportArgs->GetName(),
                "ToolsEngineEntry::Invoke(std::shared_ptr<FEventArguments>)");
            return;
        }

        // Make texture to render the SDL Viewport
        SDL_Texture* sdlTexture = SDL_CreateTexture(
            renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 
            viewportArgs->GetNewWidth(), viewportArgs->GetNewHeight());
        if (sdlTexture == nullptr)
        {
            std::string sdlError = SDL_GetError();
            Log::Error("Could not create Viewport texture: " + sdlError,
                "ToolsEngineEntry::Invoke(std::shared_ptr<FEventArguments>)");
            return;
        }

        if (viewportArgs->GetName() == "ToolsMainViewport")
        {
            m_sdlToolsViewportTexture->Set(sdlTexture);
        }
        else if (viewportArgs->GetName() == "GameEngine")
        {
            m_sdlGameViewportTexture->Set(sdlTexture);
        }
    }
}

ApplicationOperationState ToolsEngineEntry::RunSDLWindow(const std::string& engineType)
{
    // Pointers to our window and surface
    SDL_Window* window = nullptr;

    // Read latest settings.
    m_layoutSettings->ReadSettings();

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

    // Create our window
    window = SDL_CreateWindow("Example", m_layoutSettings->WindowX(), m_layoutSettings->WindowY(), m_layoutSettings->WindowWidth(), m_layoutSettings->WindowHeight(), SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    // Make sure creating the window succeeded
    if (!window)
    {
        std::string sdlError = SDL_GetError();
        Log::Error("Error creating window: " + sdlError);
        return ApplicationOperationState::Close;
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
    {
        std::string sdlError = SDL_GetError();
        Log::Error("Could not create Renderer: " + sdlError);

        // Handle renderer creation failure
        SDL_DestroyWindow(window);
        SDL_Quit();

        return ApplicationOperationState::Close;
    }

    // Initialise IMGUI
    m_imgui->Initialise(renderer, window);

    // Event handler
    SDL_Event e;

    std::shared_ptr<Engine> engine = {};
    auto provider = std::make_shared<ProjectPropertiesProvider>();
    auto engineControlsGameViewport = std::make_shared<SuperEngineControls>("GameEngine");
    auto engineControlsToolsViewport = std::make_shared<SuperEngineControls>("ToolsMainViewport");
    engineControlsGameViewport->OnViewportSizeChanged()->Subscribe(FEventObserver::shared_from_this());
    engineControlsToolsViewport->OnViewportSizeChanged()->Subscribe(FEventObserver::shared_from_this());

    // Setup the Tools Engine
    if (m_toolsEngine)
    {
        m_Toolsrenderer->SetRenderer(renderer);
        m_toolsEngine->GiveGamePackage(m_gamePackage);
        m_toolsEngine->GiveRenderer(m_Toolsrenderer);
        m_toolsEngine->GiveInput(m_inputManager);
        m_toolsEngine->GiveControls(engineControlsToolsViewport);
        m_toolsEngine->WindowStart();
        m_toolsEngine->EngineStart();
    }

    Uint64 startTime = SDL_GetTicks64();

    std::shared_ptr<Engine> toolsViewport = std::make_shared<ViewportEngine>();
    m_toolsViewportRenderer->SetRenderer(renderer);
    toolsViewport->GiveRenderer(m_toolsViewportRenderer);
    toolsViewport->GiveInput(m_inputManager);
    toolsViewport->GiveGamePackage(m_gamePackage);
    toolsViewport->WindowStart();
    toolsViewport->GiveControls(engineControlsToolsViewport);


    // Main loop
    ApplicationOperationState operationState = ApplicationOperationState::Running;
    while (operationState == ApplicationOperationState::Running)
    {
        auto eventAnswer = ApplicationOperationState::Running;

        if (m_engineFlow->DoRecreate())
        {
            engine = EngineFactory::CreateEngine(engineType);
            if (!engine)
            {
                Log::Error("Could not create Engine from factory, mid flow: " + engineType);
                return ApplicationOperationState::Close;
            }

            std::shared_ptr<ProjectProperties> projectProperties = provider->LoadProjectProperties(m_gamePackage);

            if (engine)
            {
                m_gameRenderer->SetRenderer(renderer);
                engine->GiveRenderer(m_gameRenderer);
                engine->GiveInput(m_inputManager);
                engine->GiveGamePackage(m_gamePackage);
                engine->GiveProjectProperties(projectProperties);
                engine->GiveControls(engineControlsGameViewport);
                engine->WindowStart();
                engine->EngineStart();
            }
        }

        // Handle events on the queue
        while (SDL_PollEvent(&e) != 0)
        {
            m_inputManager->EventUpdate(e);

            if (engine && m_engineFlow->DoRunEvents())
            {
                eventAnswer = engine->Event(e);
                if (eventAnswer != ApplicationOperationState::Running)
                {
                    operationState = eventAnswer;
                }
            }

            if (toolsViewport)
            {
                eventAnswer = toolsViewport->Event(e);
                if (eventAnswer != ApplicationOperationState::Running)
                {
                    operationState = eventAnswer;
                }
            }

            // Tools Engine should also take events
            if (m_toolsEngine)
            {
                eventAnswer = m_toolsEngine->Event(e);
                if (eventAnswer != ApplicationOperationState::Running)
                {
                    operationState = eventAnswer;
                }
            }

            // IMGui also needs events:
            m_imgui->EventCall(e);
            m_layoutSettings->Event(e);

            if (e.type == SDL_QUIT)
            {
                Log::Info("Engine has indicated from Events it would like to QUIT.");
                operationState = ApplicationOperationState::Close;
            }
        }

        // Will only write if it needs to.
        m_layoutSettings->WriteSettings();

        // Let the flow know this occured.
        if (engine && m_engineFlow->DoRunEvents())
        {
            m_engineFlow->RanEvents();
        }


        Uint64 currentTime = SDL_GetTicks64();
        Uint64 ticksThisFrame = currentTime - startTime;
        startTime = currentTime;

        ApplicationOperationState updateAnswer = ApplicationOperationState::Running;

        if (engine && m_engineFlow->DoRunUpdate())
        {
            updateAnswer = engine->Update(ticksThisFrame);
            if (updateAnswer != ApplicationOperationState::Running)
            {
                operationState = updateAnswer;
            }

            m_engineFlow->RanUpdate();
        }

        if (toolsViewport)
        {
            updateAnswer = toolsViewport->Update(ticksThisFrame);
            if (updateAnswer != ApplicationOperationState::Running)
            {
                operationState = updateAnswer;
            }
        }

        // Predraw update for Tools.
        if (m_toolsEngine)
        {
            updateAnswer = m_toolsEngine->Update(ticksThisFrame);
            if (updateAnswer != ApplicationOperationState::Running)
            {
                operationState = updateAnswer;
            }
        }

        // Update the state of inputs. Must be run after anything which uses it.
        m_inputManager->Update();

        // Unlikely to occur but in the situation the event and update loop
        // try to override one another we should log this, incase we get a bug
        // here.
#ifdef _DEBUG
        if (eventAnswer != ApplicationOperationState::Running &&
            updateAnswer != ApplicationOperationState::Running &&
            eventAnswer != updateAnswer)
        {
            Log::Warning("The event update and the update loop are both trying to affect the application state but do not agree on what to do."
                "Event State: " + EApplicationOperationState::ToString(eventAnswer) +
                "Update State: " + EApplicationOperationState::ToString(updateAnswer));
        }
#endif

        // Game Engine Color
        SDL_SetRenderDrawColor(renderer, 103, 125, 106, 255);

        if (engine && m_engineFlow->DoRunDraw())
        {
            // We only want to refresh this if we have a new frame.
            // This is so we can move one frame at a time.
            if (m_sdlGameViewportTexture->GetState() != PointerState::Active)
            {
                // Make texture to render the SDL Viewport
                SDL_Texture* sdlTexture = SDL_CreateTexture(
                    renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1280, 720);
                if (sdlTexture == nullptr)
                {
                    std::string sdlError = SDL_GetError();
                    Log::Error("Could not create Viewport texture: " + sdlError);
                    return ApplicationOperationState::Close;
                }

                // Give the texture the tools
                m_sdlGameViewportTexture->Set(sdlTexture);
            }

            SDL_SetRenderTarget(renderer, m_sdlGameViewportTexture->Get());
            SDL_RenderClear(renderer);

            // Render the game itself
            engine->Draw();
            SDL_SetRenderTarget(renderer, nullptr);

            m_engineFlow->RanDraw();
        }

        // ImGui Background Colour
        SDL_SetRenderDrawColor(renderer, 30, 33, 36, 255);

        if (toolsViewport)
        {
            // We only want to refresh this if we have a new frame and there is no texture.
            // This is so we can move one frame at a time.
            if (m_sdlToolsViewportTexture->GetState() != PointerState::Active)
            {
                // Make texture to render the SDL Viewport
                SDL_Texture* sdlTexture = SDL_CreateTexture(
                    renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1280, 720);
                if (sdlTexture == nullptr)
                {
                    std::string sdlError = SDL_GetError();
                    Log::Error("Could not create Viewport texture: " + sdlError);
                    return ApplicationOperationState::Close;
                }

                m_sdlToolsViewportTexture->Set(sdlTexture);
            }

            SDL_SetRenderTarget(renderer, m_sdlToolsViewportTexture->Get());
            SDL_RenderClear(renderer);

            // Render the game itself
            toolsViewport->Draw();
            SDL_SetRenderTarget(renderer, nullptr);

            // Give the texture the tools
            //m_sdlToolsViewportTexture->Set(sdlTexture);
        }

        // ImGui Background Colour
        SDL_SetRenderDrawColor(renderer, 30, 33, 36, 255);

        // Clear the renderer
        SDL_RenderClear(renderer);

        // Start Tools Draw
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        // Actual draw for Tools
        if (m_toolsEngine)
        {
            m_toolsEngine->Draw();
        }

        // Ensure ImGUI Draws are in buffer
        m_imgui->FinishCreatingDraw();

        // Actually render to the screen.
        m_imgui->Render();

        // Update screen
        SDL_RenderPresent(renderer);

        if (engine && m_engineFlow->DoDestroy())
        {
            /*if (m_sdlGameViewportTexture->GetState() == PointerState::Active)
            {
                SDL_DestroyTexture(m_sdlGameViewportTexture->Get());
                m_sdlGameViewportTexture->Set(nullptr);
            }*/

            m_gameRenderer->SetRenderer(nullptr);
            engine->WindowTeardown();
            engine->EngineEnd();
            engine = {};
        }

        // Add a small delay to avoid 100% CPU usage
        SDL_Delay(3);
    }

    // Ensure we no longer listen to these.
    engineControlsGameViewport->OnViewportSizeChanged()->Unsubscribe(FEventObserver::shared_from_this());
    engineControlsToolsViewport->OnViewportSizeChanged()->Unsubscribe(FEventObserver::shared_from_this());

    // Cleanup Imgui
    m_imgui->Teardown();

    // Ensure the engine knows we no longer have a window
    // Note: Tools and Game renderers are the same.
    SDL_DestroyRenderer(m_gameRenderer->GetRenderer());
    m_gameRenderer->SetRenderer(nullptr);
    m_toolsViewportRenderer->SetRenderer(nullptr);



    if (engine)
    {
        engine->WindowTeardown();
    }


    // Cleanup Tools
    if (m_toolsEngine)
    {
        m_toolsEngine->WindowTeardown();
        m_toolsEngine->EngineEnd();

        // There should be nothing here.
        m_Toolsrenderer->SetRenderer(nullptr);
        if (engine)
        {
            engine->WindowTeardown();
            engine->EngineEnd();
        }
    }

    // Destroy the window. This will also destroy the surface
    SDL_DestroyWindow(window);

    // Quit SDL
    SDL_Quit();

#ifdef _DEBUG
    // Close console window in debug mode
    FreeConsole();
#endif

    return operationState;
}
