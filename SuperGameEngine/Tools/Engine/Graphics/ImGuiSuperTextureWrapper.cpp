#include "ImGuiSuperTextureWrapper.h"

#include "ImGuiTexture.h"

using namespace SuperGameTools;
using namespace SuperGameEngine;

ImGuiSuperTextureWrapper::ImGuiSuperTextureWrapper(const std::shared_ptr<ImGuiTexture>& texture)
{
    m_texture = texture;
}

void ImGuiSuperTextureWrapper::Draw() const
{
    ImTextureID textureID = 0;
    if (!m_texture->GetTextureID(textureID))
    {
        return;
    }

    FPoint size = m_texture->Size();
    auto imageSize = ImVec2(
        static_cast<float>(size.GetX()), 
        static_cast<float>(size.GetY()));

    ImGui::Image(textureID, imageSize);
}

void ImGuiSuperTextureWrapper::Draw(const FPoint& location) const
{
    ImVec2 position = ImGui::GetCursorPos();
    ImGui::SetCursorPos(ImVec2(
        static_cast<int>(static_cast<int>(position.x) + location.GetX()),
        static_cast<int>(static_cast<int>(position.y) + location.GetY())));

    ImTextureID textureID = 0;
    if (!m_texture->GetTextureID(textureID))
    {
        return;
    }

    FPoint size = m_texture->Size();
    auto imageSize = ImVec2(
        static_cast<float>(size.GetX()),
        static_cast<float>(size.GetY()));

    ImGui::Image(textureID, imageSize);

    ImGui::SetCursorPos(ImVec2(position.x, position.y));
}

void ImGuiSuperTextureWrapper::Draw(const FPoint& location, const FPoint& size) const
{
    ImVec2 position = ImGui::GetCursorPos();
    ImGui::SetCursorPos(ImVec2(
        static_cast<int>(static_cast<int>(position.x) + location.GetX()),
        static_cast<int>(static_cast<int>(position.y) + location.GetY())));

    ImTextureID textureID = 0;
    if (!m_texture->GetTextureID(textureID))
    {
        return;
    }

    auto imageSize = ImVec2(
        static_cast<float>(size.GetX()),
        static_cast<float>(size.GetY()));

    ImGui::Image(textureID, imageSize);

    ImGui::SetCursorPos(ImVec2(position.x, position.y));
}

void ImGuiSuperTextureWrapper::Draw(const RectangleInt& textureRectangle, const RectangleInt& screenRectangle) const
{
    ImVec2 position = ImGui::GetCursorPos();
    ImGui::SetCursorPos(ImVec2(
        static_cast<int>(static_cast<int>(position.x) + screenRectangle.GetLeft()),
        static_cast<int>(static_cast<int>(position.y) + screenRectangle.GetTop())));

    ImTextureID textureID = 0;
    if (!m_texture->GetTextureID(textureID))
    {
        return;
    }

    FPoint size = m_texture->Size();
    auto imageSize = ImVec2(
        static_cast<float>(screenRectangle.GetRight()),
        static_cast<float>(screenRectangle.GetBottom()));

    ImGui::Image(textureID, imageSize);

    ImGui::SetCursorPos(ImVec2(position.x, position.y));
}

bool ImGuiSuperTextureWrapper::RepresentSameImage(std::shared_ptr<SuperTexture> texture) const
{
    return false;
}

bool ImGuiSuperTextureWrapper::RepresentSameImage(std::string filePath) const
{
    return false;
}

FPoint ImGuiSuperTextureWrapper::Size() const
{
    return {};
}
