#include "ToolsLayoutSettings.h"

#include "SettingsPaths.h"
#include "../../FatedQuestLibraries.h"
#include "../../../../FatedQuest.Libraries/XmlDocument/RapidXMLDocument.h"
#include "../../../Engine/Structural/Spatial/Area/RectangleInt.h"

namespace FatedQuestLibraries
{
    class StoredDocument;
}

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

ToolsLayoutSettings::ToolsLayoutSettings(
    const std::shared_ptr<SettingsPaths>& paths, 
    const std::string& settingsFile,
    const std::shared_ptr<DocumentToXml>& documentToXml)
{
    m_settingsPaths = paths;
    m_thisFilePath = Directory::CombinePath(m_settingsPaths->SettingDirectory(), settingsFile);
    m_thisFilename = settingsFile;
    m_documentToXml = documentToXml;

    m_mainWindow = std::make_shared<RectangleInt>(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720);
    m_isDirty = false;
}

void ToolsLayoutSettings::Event(SDL_Event event)
{
    if (event.type == SDL_WINDOWEVENT)
    {
        switch (event.window.event)
        {
        case SDL_WINDOWEVENT_RESIZED:
            m_mainWindow->SetSize(event.window.data1, event.window.data2);
            m_isDirty = true;
            break;
        case SDL_WINDOWEVENT_MOVED:
            m_mainWindow->SetLocation(event.window.data1, event.window.data2);
            m_isDirty = true;
            break;
        }
    }
}

void ToolsLayoutSettings::WriteSettings()
{
    if (!m_isDirty)
    {
        return;
    }

    // Setup document
    auto document = std::make_shared<ModifiableDocument>();
    auto root = std::make_shared<ModifiableNode>();
    root->SetName("Settings");
    document->SetRootElement(root);

    // Gather all settings
    std::vector<std::shared_ptr<ModifiableNode>> children;
    children.emplace_back(SerialiseSize());
    root->SetAllChildrenNodes(children);

    // Write file
    std::string asFile = m_documentToXml->ConvertToXml(document);
    if (asFile.empty())
    {
        Log::Error("No file data created.", "ToolsLayoutSettings::WriteSettings()");
        return;
    }

    if (!File::WriteLine(m_thisFilePath, asFile))
    {
        Log::Error("Could not write to file. Path: " + m_thisFilePath, "ToolsLayoutSettings::WriteSettings()");
    }

    m_isDirty = false;
}

void ToolsLayoutSettings::ReadSettings()
{
    if (!File::Exists(m_thisFilePath))
    {
        Log::Info("No settings file exists, it should next time you open the application.",
            "ToolsLayoutSettings::ReadSettings");
        m_isDirty = true;
        return;
    }

    auto document = std::make_shared<RapidXMLDocument>();
    if (!document->LoadFromFile(m_thisFilePath))
    {
        Log::Error("Could not load settings file. Path: " + m_thisFilePath,
            "ToolsLayoutSettings::ReadSettings");
        return;
    }

    if (!document->GetRoot())
    {
        Log::Error("No root found.",
            "ToolsLayoutSettings::ReadSettings");
        return;
    }

    for (std::shared_ptr<StoredDocumentNode> child = document->GetRoot()->GetFirstChild(); child; child = child->GetAdjacentNode())
    {
        if (child->Name() == "Size")
        {
            if (!ParseSize(child))
            {
                Log::Error("Could not parse Size, not continuing with the rest", "ToolsLayoutSettings::ReadSettings");
                return;
            }
        }
    }

    m_isDirty = false;
}

int ToolsLayoutSettings::WindowWidth() const
{
    return m_mainWindow->GetWidth();
}

int ToolsLayoutSettings::WindowHeight() const
{
    return m_mainWindow->GetHeight();
}

int ToolsLayoutSettings::WindowX() const
{
    return m_mainWindow->GetLeft();
}

int ToolsLayoutSettings::WindowY() const
{
    return m_mainWindow->GetTop();
}

bool ToolsLayoutSettings::ParseSize(const std::shared_ptr<StoredDocumentNode>& node) const
{
    std::shared_ptr<StoredDocumentAttribute> xAttribute = node->Attribute("X", CaseSensitivity::IgnoreCase);
    if (!xAttribute)
    {
        return false;
    }

    int x = 0;
    if (!IntHelpers::TryParse(xAttribute->Value(), x))
    {
        Log::Error("Could not parse Size X.", "ToolsLayoutSettings::ParseSize");
        return false;
    }

    std::shared_ptr<StoredDocumentAttribute> yAttribute = node->Attribute("Y", CaseSensitivity::IgnoreCase);
    if (!yAttribute)
    {
        return false;
    }

    int y = 0;
    if (!IntHelpers::TryParse(yAttribute->Value(), y))
    {
        Log::Error("Could not parse Size Y.", "ToolsLayoutSettings::ParseSize");
        return false;
    }

    std::shared_ptr<StoredDocumentAttribute> widthAttribute = node->Attribute("Width", CaseSensitivity::IgnoreCase);
    if (!widthAttribute)
    {
        return false;
    }

    int width = 0;
    if (!IntHelpers::TryParse(widthAttribute->Value(), width))
    {
        Log::Error("Could not parse Size Width.", "ToolsLayoutSettings::ParseSize");
        return false;
    }

    std::shared_ptr<StoredDocumentAttribute> heightAttribute = node->Attribute("Height", CaseSensitivity::IgnoreCase);
    if (!heightAttribute)
    {
        return false;
    }

    int height = 0;
    if (!IntHelpers::TryParse(heightAttribute->Value(), height))
    {
        Log::Error("Could not parse Size Height.", "ToolsLayoutSettings::ParseSize");
        return false;
    }

    m_mainWindow->SetLocation(x, y);
    m_mainWindow->SetSize(width, height);
    return true;
}

std::shared_ptr<ModifiableNode> ToolsLayoutSettings::SerialiseSize() const
{
    auto node = std::make_shared<ModifiableNode>();
    node->SetName("Size");

    auto nodeAttributes = std::vector<std::shared_ptr<StoredDocumentAttribute>>();
    {
    auto attribute = std::make_shared<ModifiableAttribute>
        ("X", std::to_string(m_mainWindow->GetLeft()));
    nodeAttributes.emplace_back(attribute);
    }
    {
        auto attribute = std::make_shared<ModifiableAttribute>
            ("Y", std::to_string(m_mainWindow->GetTop()));
        nodeAttributes.emplace_back(attribute);
    }
    {
        auto attribute = std::make_shared<ModifiableAttribute>
            ("Width", std::to_string(m_mainWindow->GetWidth()));
        nodeAttributes.emplace_back(attribute);
    }
    {
        auto attribute = std::make_shared<ModifiableAttribute>
            ("Height", std::to_string(m_mainWindow->GetHeight()));
        nodeAttributes.emplace_back(attribute);
    }

    node->SetAttributes(nodeAttributes);

    return node;
}