#include "ImGuiContainer.h"

#include "../External/imgui.h"
#include "../External/imgui_impl_sdl2.h"
#include "../External/imgui_impl_sdlrenderer2.h"

using namespace SuperGameEngine;

ImGuiContainer::ImGuiContainer()
{

}

ImGuiContainer::~ImGuiContainer()
{

}

void ImGuiContainer::Initialise(SDL_Renderer* renderer, SDL_Window* window)
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    m_context = ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);

    m_renderer = renderer;
}

void ImGuiContainer::EventCall(const SDL_Event& e)
{
    ImGui_ImplSDL2_ProcessEvent(&e);
}

void ImGuiContainer::FinishCreatingDraw()
{
    ImGui::Render();
}

void ImGuiContainer::Render()
{
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), m_renderer);
}

void ImGuiContainer::Teardown()
{
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext(m_context);
}
