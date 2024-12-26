#include "GameViewport.h"
#include "../../ImGuiIncludes.h"
#include "../../../Engine/Engine/Graphics/Texture/SDLRendererReader.h"
#include "../../ToolsEngine/Communication/EngineEntryCommunication.h"
#include "../../ToolsEngine/Packages/WindowPackage.h"

using namespace SuperGameEngine;
using namespace SuperGameTools;

void GameViewport::Setup(const std::shared_ptr<WindowPackage>& windowPackage)
{
    m_viewport = { 50, 50, 500, 250 };;
    m_renderer = windowPackage->GetRenderer();
    m_windowPackage = windowPackage;
}

void GameViewport::Update()
{

}

void GameViewport::Draw()
{
    ImGui::Begin("My Window");

    if (m_windowPackage->GetEngineEntryCommunication())
    {
        int i = 1;
        ImGui::PushID(i);

        if (m_windowPackage->GetEngineEntryCommunication()->GetPlayControls()->DoRunUpdate())
        {
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(48 / 255.0f, 48 / 255.0f, 48 / 255.0f, 255 / 255.0f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(140 / 255.0f, 140 / 255.0f, 140 / 255.0f, 255 / 255.0f));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(97 / 255.0f, 97 / 255.0f, 97 / 255.0f, 255 / 255.0f));
        }
        else
        {
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(140 / 255.0f, 140 / 255.0f, 140 / 255.0f, 255 / 255.0f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(48 / 255.0f, 48 / 255.0f, 48 / 255.0f, 255 / 255.0f));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(97 / 255.0f, 97 / 255.0f, 97 / 255.0f, 255 / 255.0f));
        }

        if (ImGui::Button("Play"))
        {
            if (m_windowPackage->GetEngineEntryCommunication()->GetPlayControls()->DoRunUpdate())
            {
                m_windowPackage->GetEngineEntryCommunication()->GetPlayControls()->Stop();
            }
            else
            {
                m_windowPackage->GetEngineEntryCommunication()->GetPlayControls()->Play();
            }

        }

        ImGui::PopStyleColor(3);
        ImGui::PopID();
    }


    ImVec2 windowPos = ImGui::GetWindowPos();
    ImVec2 windowTopLeftBelowTitleBar = ImVec2(windowPos.x, windowPos.y + ImGui::GetFrameHeight());
    ImVec2 windowSize = ImGui::GetContentRegionAvail();

    m_viewport.x = static_cast<int>(windowTopLeftBelowTitleBar.x);
    m_viewport.y = static_cast<int>(windowTopLeftBelowTitleBar.y);
    m_viewport.w = static_cast<int>(windowSize.x);
    m_viewport.h = static_cast<int>(windowSize.y);

    if (m_windowPackage->GetSDLRenderTexture())
    {
        if (m_windowPackage->GetSDLRenderTexture()->GetState() == PointerState::Active)
        {
            ImVec2 imageSize = ImVec2((float)1280, (float)720);
            SDL_Texture* texture = m_windowPackage->GetSDLRenderTexture()->Get();
            ImGui::Image(reinterpret_cast<ImTextureID>(static_cast<void*>(texture)), imageSize);
        }
    }



    UpdateTheSDLViewport();
    ImGui::End();
}

void GameViewport::TearDown()
{
}

void GameViewport::UpdateTheSDLViewport()
{
    if (m_renderer->RendererState() == SDLRendererState::Active)
    {
        SDL_RenderSetViewport(m_renderer->GetRenderer(), &m_viewport);
    }
}
