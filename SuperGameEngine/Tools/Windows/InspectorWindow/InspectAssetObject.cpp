#include "InspectAssetObject.h"

#include "../../../../FatedQuest.Libraries/StandardObjects/UniversalObjectData/ExplicitDocumentModifiableUniversalObjectData.h"
#include "../../../../FatedQuest.Libraries/XmlDocument/RapidXMLDocument.h"
#include "../../ToolsEngine/Packages/WindowPackage.h"
#include "../../ToolsEngine/FrameworkManager/FrameworkManager.h"
#include "../../ToolsEngine/FrameworkManager/SelectionManager/SelectionChangedEventArguments.h"
#include "../../ToolsEngine/FrameworkManager/SelectionManager/SelectionGroup.h"
#include "../../ToolsEngine/FrameworkManager/SelectionManager/SelectionManager.h"
#include "Engine/Structural/Asset/Template/AssetLayout.h"
#include "Engine/Structural/Asset/Template/AssetMetaData.h"
#include "Windows/AssetBrowser/FileManagement/AssetFile.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

InspectAssetObject::InspectAssetObject()
{
    m_isSetup = false;
    m_assetFileCurrentlyEdited = {};
}

void InspectAssetObject::Setup(const std::shared_ptr<WindowPackage>& windowPackage)
{
    m_windowPackage = windowPackage;

    if (!m_windowPackage->GetFrameworkManager())
    {
        Log::Error("No framework manager found, "
            "this means we do not know what is selected.",
            "InspectorWindow::Setup(std::shared_ptr<WindowPackage>)");
        return;
    }

    if (!m_windowPackage->GetFrameworkManager()->GetSelectionManager())
    {
        Log::Error("No selection manager found, "
            "this means we do not know what is selected.",
            "InspectorWindow::Setup(std::shared_ptr<WindowPackage>)");
        return;
    }

    std::weak_ptr<FEventObserver> observer = shared_from_this();
    m_windowPackage->GetFrameworkManager()->GetSelectionManager()->OnSelectionChanged()->Subscribe(observer);

    if (!m_windowPackage->GetContentManager())
    {
        Log::Error("No content manager found, "
            "this means we cannot create a tree for the components.",
            "InspectorWindow::Setup(std::shared_ptr<WindowPackage>)");
        return;
    }

    m_isSetup = true;
}

void InspectAssetObject::Update()
{
    if (!m_assetFileCurrentlyEdited)
    {
        return;
    }

    m_assetFileCurrentlyEdited->GetMetaData()->GetLayout()->Update(m_currentlyEditedDocument);
}

void InspectAssetObject::Draw()
{
    if (!m_assetFileCurrentlyEdited)
    {
        return;
    }

    m_assetFileCurrentlyEdited->GetMetaData()->GetLayout()->Draw(m_currentlyEditedDocument);
}

void InspectAssetObject::TearDown()
{
    if (!m_windowPackage->GetFrameworkManager())
    {
        return;
    }

    if (!m_windowPackage->GetFrameworkManager()->GetSelectionManager())
    {
        return;
    }

    std::weak_ptr<FEventObserver> observer = shared_from_this();
    m_windowPackage->GetFrameworkManager()->GetSelectionManager()->OnSelectionChanged()->Unsubscribe(observer);
}

void InspectAssetObject::Invoke(std::shared_ptr<FEventArguments> arguments)
{
    if (auto selectableArguments = std::dynamic_pointer_cast<SelectionChangedEventArguments>(arguments))
    {
        m_assetFileCurrentlyEdited = {};
        m_currentlyEditedDocument = {};

        std::shared_ptr<SelectionManager> selectionManager = m_windowPackage->GetFrameworkManager()->GetSelectionManager();
        std::vector<std::weak_ptr<Selectable>> selectables = selectionManager->GetSelection(SelectionGroup::Inspectable);
        if (selectables.empty() || selectables.size() != 1)
        {
            return;
        }

        if (auto sharedSelectable = selectables.at(0).lock())
        {
            if (auto assetFile = std::dynamic_pointer_cast<AssetFile>(sharedSelectable))
            {
                m_assetFileCurrentlyEdited = assetFile;
                std::shared_ptr<PackagePaths> paths = m_windowPackage->GetPackagePaths();
                std::string fullPath = Directory::CombinePath(paths->ProductsDirectory(), paths->ProductsDirectoryName(), assetFile->GetPackagePath());

                auto document = std::make_shared<RapidXMLDocument>();
                if (!document->LoadFromFile(fullPath))
                {
                    Log::Error("Could not read the .ast when getting it in the inspector window. "
                               "Something weird must be happening. Report this as an issue. "
                               "Path: " + fullPath,
                        "InspectAssetObject::Invoke(std::shared_ptr<FEventArguments>)");
                    return;
                }

                auto documentModifiableUniversalObjectData = std::make_shared<ExplicitDocumentModifiableUniversalObjectData>();
                if (!documentModifiableUniversalObjectData->ImportAsDocument(document))
                {
                    Log::Error("Could not parse asset file into a universal asset when getting the asset into"
                               "the inspector window. This is unexpected. Report this as an issue. "
                        "Path: " + fullPath,
                        "InspectAssetObject::Invoke(std::shared_ptr<FEventArguments>)");
                    return;
                }

                m_currentlyEditedDocument = documentModifiableUniversalObjectData;
            }
        }
    }
}
