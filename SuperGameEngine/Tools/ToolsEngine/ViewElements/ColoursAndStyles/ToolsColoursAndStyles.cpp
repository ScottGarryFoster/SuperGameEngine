#include "ToolsColoursAndStyles.h"
#include <unordered_map>

#include "EmbeddedFont.h"
#include "../../../FatedQuestLibraries.h"

#include "../../../../../FatedQuest.Libraries/GamePackage/GamePackage/PackagePaths.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

ToolsColoursAndStyles::ToolsColoursAndStyles(const std::shared_ptr<PackagePaths>& paths)
{
    m_packagePaths = paths;

    auto dark_p0 = std::unordered_map<ColourIdentity, ImVec4>();
    dark_p0.insert_or_assign(ColourIdentity::Background, FromColour(6, 6, 13, 255));
    dark_p0.insert_or_assign(ColourIdentity::Primary, FromColour(134, 80, 211, 255));
    dark_p0.insert_or_assign(ColourIdentity::Highlight, FromColour(138, 202, 47, 255));
    dark_p0.insert_or_assign(ColourIdentity::Secondary, FromColour(86,98,222, 255));
    dark_p0.insert_or_assign(ColourIdentity::Error, FromColour(190,47,202, 255));
    dark_p0.insert_or_assign(ColourIdentity::Warning, FromColour(202,112,47, 255));

    auto dark_p1 = std::unordered_map<ColourIdentity, ImVec4>();
    dark_p1.insert_or_assign(ColourIdentity::Background, FromColour(17,16,35, 255));
    dark_p1.insert_or_assign(ColourIdentity::Primary, FromColour(134, 80, 211, 255));
    dark_p1.insert_or_assign(ColourIdentity::Highlight, FromColour(138, 202, 47, 255));
    dark_p1.insert_or_assign(ColourIdentity::Secondary, FromColour(86, 98, 222, 255));
    dark_p1.insert_or_assign(ColourIdentity::Error, FromColour(190, 47, 202, 255));
    dark_p1.insert_or_assign(ColourIdentity::Warning, FromColour(202, 112, 47, 255));

    auto dark_p2 = std::unordered_map<ColourIdentity, ImVec4>();
    dark_p2.insert_or_assign(ColourIdentity::Background, FromColour(48, 48, 68, 255));
    dark_p2.insert_or_assign(ColourIdentity::Primary, FromColour(134, 80, 211, 255));
    dark_p2.insert_or_assign(ColourIdentity::Highlight, FromColour(156, 211, 83, 255));
    dark_p2.insert_or_assign(ColourIdentity::Secondary, FromColour(86, 98, 222, 255));
    dark_p2.insert_or_assign(ColourIdentity::Error, FromColour(245, 50, 152, 255));
    dark_p2.insert_or_assign(ColourIdentity::Warning, FromColour(210, 125, 50, 255));

    auto dark_p3 = std::unordered_map<ColourIdentity, ImVec4>();
    dark_p3.insert_or_assign(ColourIdentity::Background, FromColour(79, 78, 99, 255));
    dark_p3.insert_or_assign(ColourIdentity::Primary, FromColour(156, 113, 219, 255));
    dark_p3.insert_or_assign(ColourIdentity::Highlight, FromColour(175, 219, 116, 255));
    dark_p3.insert_or_assign(ColourIdentity::Secondary, FromColour(118, 127, 228, 255));
    dark_p3.insert_or_assign(ColourIdentity::Error, FromColour(242, 81, 171, 255));
    dark_p3.insert_or_assign(ColourIdentity::Warning, FromColour(222, 148, 59, 255));

    auto dark_p4 = std::unordered_map<ColourIdentity, ImVec4>();
    dark_p4.insert_or_assign(ColourIdentity::Background, FromColour(98, 96, 119, 255));
    dark_p4.insert_or_assign(ColourIdentity::Primary, FromColour(87, 33, 118, 255));
    dark_p4.insert_or_assign(ColourIdentity::Highlight, FromColour(138, 202, 47, 255));
    dark_p4.insert_or_assign(ColourIdentity::Secondary, FromColour(0, 7, 161, 255));
    dark_p4.insert_or_assign(ColourIdentity::Error, FromColour(226, 49, 146, 255));
    dark_p4.insert_or_assign(ColourIdentity::Warning, FromColour(222, 148, 59, 255));

    auto dark_p5 = std::unordered_map<ColourIdentity, ImVec4>();
    dark_p5.insert_or_assign(ColourIdentity::Background, FromColour(137, 136, 160, 255));
    dark_p5.insert_or_assign(ColourIdentity::Primary, FromColour(87, 33, 188, 255));
    dark_p5.insert_or_assign(ColourIdentity::Highlight, FromColour(138, 202, 47, 255));
    dark_p5.insert_or_assign(ColourIdentity::Secondary, FromColour(0, 7, 161, 255));
    dark_p5.insert_or_assign(ColourIdentity::Error, FromColour(180, 44, 130, 255));
    dark_p5.insert_or_assign(ColourIdentity::Warning, FromColour(232, 178, 99, 255));

    auto darkInorder = std::unordered_map<int, std::unordered_map<ColourIdentity, ImVec4>>();
    darkInorder.insert_or_assign(0, dark_p0);
    darkInorder.insert_or_assign(1, dark_p1);
    darkInorder.insert_or_assign(2, dark_p2);
    darkInorder.insert_or_assign(3, dark_p3);
    darkInorder.insert_or_assign(4, dark_p4);
    darkInorder.insert_or_assign(5, dark_p5);

    m_colorMap.insert_or_assign(ColourPalette::Dark, darkInorder);
    m_currentPalette = ColourPalette::Dark;

    //dark_p0.insert_or_assign(ColourIdentity::Background, FromColour(, , , 255));
    //dark_p0.insert_or_assign(ColourIdentity::Primary, FromColour(, , , 255));
    //dark_p0.insert_or_assign(ColourIdentity::Highlight, FromColour(, , , 255));
    //dark_p0.insert_or_assign(ColourIdentity::Secondary, FromColour(, , , 255));
    //dark_p0.insert_or_assign(ColourIdentity::Error, FromColour(, , , 255));
    //dark_p0.insert_or_assign(ColourIdentity::Warning, FromColour(, , , 255));

    const std::string productPath = m_packagePaths->ProductsDirectory();
    const std::string productFolder = m_packagePaths->ProductsDirectoryName();
    const std::string fullProductsPath = Directory::CombinePath(productPath, productFolder);

    m_fontPaths.insert_or_assign(
        EmbeddedFont::NotoSansVariableFont, 
        Directory::CombinePath(fullProductsPath, 
            "Tools\\Fonts\\NotoSans-VariableFont_wdth,wght.ttf"));
    CreateFontImGui(EmbeddedFont::NotoSansVariableFont, 18);
}

void ToolsColoursAndStyles::SetGlobalColoursAndStyles() const
{
    ImGuiStyle& style = ImGui::GetStyle();
    style.Colors[ImGuiCol_Tab] = m_colorMap.at(m_currentPalette).at(0).at(ColourIdentity::Background);
    style.Colors[ImGuiCol_TabSelected] = m_colorMap.at(m_currentPalette).at(1).at(ColourIdentity::Background);
    style.Colors[ImGuiCol_TabSelectedOverline] = m_colorMap.at(m_currentPalette).at(1).at(ColourIdentity::Background);
    style.Colors[ImGuiCol_TabDimmed] = m_colorMap.at(m_currentPalette).at(0).at(ColourIdentity::Background);
    style.Colors[ImGuiCol_TabDimmedSelected] = m_colorMap.at(m_currentPalette).at(1).at(ColourIdentity::Background);
    style.Colors[ImGuiCol_TabDimmedSelectedOverline] = m_colorMap.at(m_currentPalette).at(1).at(ColourIdentity::Background);
    style.Colors[ImGuiCol_DockingEmptyBg] = m_colorMap.at(m_currentPalette).at(0).at(ColourIdentity::Background);
    style.Colors[ImGuiCol_WindowBg] = m_colorMap.at(m_currentPalette).at(1).at(ColourIdentity::Background);
    style.Colors[ImGuiCol_TitleBg] = m_colorMap.at(m_currentPalette).at(0).at(ColourIdentity::Background);
    style.Colors[ImGuiCol_TitleBgActive] = m_colorMap.at(m_currentPalette).at(0).at(ColourIdentity::Background);
    style.Colors[ImGuiCol_Border] = m_colorMap.at(m_currentPalette).at(0).at(ColourIdentity::Background);
    style.Colors[ImGuiCol_TabHovered] = m_colorMap.at(m_currentPalette).at(1).at(ColourIdentity::Secondary);


}

void ToolsColoursAndStyles::SetTopMenuColoursAndStyles() const
{
    PushFont(EmbeddedFont::NotoSansVariableFont, 18);
    ImGui::PushStyleColor(ImGuiCol_MenuBarBg, m_colorMap.at(m_currentPalette).at(0).at(ColourIdentity::Background));
    ImGui::PushStyleColor(ImGuiCol_Text, m_colorMap.at(m_currentPalette).at(0).at(ColourIdentity::Primary));
    ImGui::PushStyleColor(ImGuiCol_Header, m_colorMap.at(m_currentPalette).at(1).at(ColourIdentity::Background));
    ImGui::PushStyleColor(ImGuiCol_HeaderHovered, m_colorMap.at(m_currentPalette).at(2).at(ColourIdentity::Background));
    ImGui::PushStyleColor(ImGuiCol_HeaderActive, m_colorMap.at(m_currentPalette).at(2).at(ColourIdentity::Background));
}

void ToolsColoursAndStyles::PopTopMenuColoursAndStyles() const
{
    ImGui::PopStyleColor(5);
    PopFont(EmbeddedFont::NotoSansVariableFont, 18);
}

void ToolsColoursAndStyles::SetMenuColoursAndStyles(bool isOpen, bool isHovered) const
{
    if (isOpen)
    {
        ImGui::PushStyleColor(ImGuiCol_Text, m_colorMap.at(m_currentPalette).at(2).at(ColourIdentity::Highlight));
    }
    else if (isHovered)
    {
        ImGui::PushStyleColor(ImGuiCol_Text, m_colorMap.at(m_currentPalette).at(2).at(ColourIdentity::Highlight));
    }
    else
    {
        ImGui::PushStyleColor(ImGuiCol_Text, m_colorMap.at(m_currentPalette).at(0).at(ColourIdentity::Primary));
    }
}

void ToolsColoursAndStyles::PopMenuColoursAndStyles() const
{
    ImGui::PopStyleColor(1);
}

void ToolsColoursAndStyles::SetWindowTabColoursAndStyles(const bool isOpen, const bool isHovered) const
{
    if (isOpen)
    {
        ImGui::PushStyleColor(ImGuiCol_Text, m_colorMap.at(m_currentPalette).at(1).at(ColourIdentity::Highlight));
        ImGui::PushStyleColor(ImGuiCol_TextDisabled, m_colorMap.at(m_currentPalette).at(1).at(ColourIdentity::Highlight));
        ImGui::PushStyleColor(ImGuiCol_TabHovered, m_colorMap.at(m_currentPalette).at(1).at(ColourIdentity::Background));
    }
    else
    {
        if (isHovered)
        {
            ImGui::PushStyleColor(ImGuiCol_Text, m_colorMap.at(m_currentPalette).at(2).at(ColourIdentity::Secondary));
            ImGui::PushStyleColor(ImGuiCol_TextDisabled, m_colorMap.at(m_currentPalette).at(2).at(ColourIdentity::Secondary));
        }
        else
        {
            ImGui::PushStyleColor(ImGuiCol_Text, m_colorMap.at(m_currentPalette).at(0).at(ColourIdentity::Secondary));
            ImGui::PushStyleColor(ImGuiCol_TextDisabled, m_colorMap.at(m_currentPalette).at(0).at(ColourIdentity::Secondary));
        }

        ImGui::PushStyleColor(ImGuiCol_TabHovered, m_colorMap.at(m_currentPalette).at(2).at(ColourIdentity::Background));
    }
}

void ToolsColoursAndStyles::PopWindowTabColoursAndStyles() const
{
    ImGui::PopStyleColor(3);
}

void ToolsColoursAndStyles::CreateFontImGui(EmbeddedFont font, float size)
{
    ImGuiIO& io = ImGui::GetIO();

    const char* path = m_fontPaths.at(font).c_str();
    ImFont* newFont = io.Fonts->AddFontFromFileTTF(path, size);
    if (newFont == nullptr)
    {
        Log::Error("Could not load font: " + EEmbeddedFont::ToString(font),
            "ToolsColoursAndStyles::CreateFontImGui(EmbeddedFont,float)");
        return;
    }

    std::unordered_map<float, ImFont*> newDictionary = {};
    if (!m_actualFonts.contains(font))
    {
        m_actualFonts.insert_or_assign(font, std::unordered_map<float, ImFont*>());
    }

    newDictionary = m_actualFonts.at(font);
    newDictionary.insert_or_assign(size, newFont);
    m_actualFonts.insert_or_assign(font, newDictionary);
}

void ToolsColoursAndStyles::PushFont(EmbeddedFont font, float size) const
{
    if (!m_fontPaths.contains(font))
    {
        return;
    }

    if (!m_actualFonts.contains(font))
    {
        return;
    }

    if (!m_actualFonts.at(font).contains(size))
    {
        return;
    }

    ImGui::PushFont(m_actualFonts.at(font).at(size));
}

void ToolsColoursAndStyles::PopFont(EmbeddedFont font, float size) const
{
    if (!m_fontPaths.contains(font))
    {
        return;
    }

    if (!m_actualFonts.contains(font))
    {
        return;
    }

    if (!m_actualFonts.at(font).contains(size))
    {
        return;
    }

    ImGui::PopFont();
}

ImVec4 ToolsColoursAndStyles::FromColour(int r, int g, int b, int a) const
{
    ImU32 col32 = IM_COL32(r, g, b, a);
    ImVec4 color_float = ImVec4(
        ((col32 >> IM_COL32_R_SHIFT) & 0xFF) / 255.0f,
        ((col32 >> IM_COL32_G_SHIFT) & 0xFF) / 255.0f,
        ((col32 >> IM_COL32_B_SHIFT) & 0xFF) / 255.0f,
        ((col32 >> IM_COL32_A_SHIFT) & 0xFF) / 255.0f
    );

    return color_float;
}
