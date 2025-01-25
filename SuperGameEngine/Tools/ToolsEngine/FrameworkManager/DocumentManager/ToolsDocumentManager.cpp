#include "ToolsDocumentManager.h"

#include "Document.h"
#include "DocumentCriteria.h"
#include "DocumentFactory.h"
#include "DocumentMatcher.h"
#include "../../../FatedQuestLibraries.h"
#include "../../../../../FatedQuest.Libraries/GamePackage/GamePackage/PackagePaths.h"
#include "../../../../Engine/Engine/Content/ContentManager.h"
#include "../../../SystemActions/FileDialog/FileDialogProvider.h"
#include "../../Packages/WindowPackage.h"
#include "../../ViewElements/Menu/MenuItemView.h"
#include "../../ViewElements/Menu/MenuItemViewEventArguments.h"
#include "../../ViewElements/Menu/MenuView.h"
#include "DocumentEvent/DocumentActionEventArguments.h"
#include "DocumentEvent/DocumentEventOpenLevel.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

ToolsDocumentManager::ToolsDocumentManager(const std::weak_ptr<WindowPackage>& windowsPackage)
{
    m_onDocumentAction = std::make_shared<FEvent>();
    m_lastPathOpenedTo = {};


    if (auto sharedWindowsPackage = windowsPackage.lock())
    {
        m_windowsPackage = windowsPackage;
    }
    else
    {
        Log::Error("Windows package not given as a real reference to Document Manager.",
            "ToolsDocumentManager::ToolsDocumentManager(std::weak_ptr<WindowPackage>)");
        return;
    }

    auto fileDialogProvider = std::make_shared<FileDialogProvider>();
    m_fileDialog = fileDialogProvider->GetFileDialog();
    if (!m_fileDialog)
    {
        Log::Error("Could not obtain a method of opening file dialogs.",
            "ToolsDocumentManager::ToolsDocumentManager(std::weak_ptr<WindowPackage>)");
    }
}

void ToolsDocumentManager::Setup()
{
    if (auto windowsPackage = m_windowsPackage.lock())
    {
        // Do not load straight from this, instead
        // there needs to be a framework package which opens a dialogue window
        // then I listen to it here.
        std::weak_ptr<FEventObserver> me = shared_from_this();
        windowsPackage->GetTopMenu()->GetMenuItem("FileOpen")->OnSelected()->Subscribe(me);
        windowsPackage->GetTopMenu()->GetMenuItem("FileSave")->OnSelected()->Subscribe(me);
        windowsPackage->GetTopMenu()->GetMenuItem("FileNew")->OnSelected()->Subscribe(me);

        
        std::string productsDirectory = windowsPackage->GetPackagePaths()->ProductsDirectory();
        std::string productsDirectoryName = windowsPackage->GetPackagePaths()->ProductsDirectoryName();
        m_productsPath = Directory::CombinePath(productsDirectory, productsDirectoryName);
    }
    else
    {
        Log::Error("Windows package not given as a real reference to Document Manager.",
            "void ToolsDocumentManager::Setup()");
    }
}

std::shared_ptr<FEventSubscriptions> ToolsDocumentManager::OnDocumentAction() const
{
    return m_onDocumentAction;
}

void ToolsDocumentManager::Invoke(std::shared_ptr<FEventArguments> arguments)
{
    if (auto menuItemSelected = std::dynamic_pointer_cast<MenuItemViewEventArguments>(arguments))
    {
        if (auto menuItem = menuItemSelected->GetMenuItem().lock())
        {
            if (menuItem->GetKey() == "FileNew")
            {
                NewFile();
            }
            else if (menuItem->GetKey() == "FileOpen")
            {
                OpenFile(DocumentEventOpenLevel::Exclusive);
            }
            else if (menuItem->GetKey() == "FileSave")
            {
                SaveFile(DocumentEventSaveContext::Everything);
            }
        }
    }
}

void ToolsDocumentManager::OpenFile(DocumentEventOpenLevel level)
{
    std::vector<std::string> sceneFileExtensions;
    sceneFileExtensions.emplace_back("*.scene");
    std::string openTo = GetFilepathToOpenTo();

    std::string path = m_fileDialog->OpenFile(
        "Open Scene",
        openTo,
        sceneFileExtensions,
        "Scene");
    if (path.empty())
    {
        return;
    }

    std::string gamePackagePath = File::MakeRelative(m_productsPath, path);
    if (gamePackagePath.empty())
    {
        // TODO: Create an error / general message box for the user. #114
        Log::Error("Path was not within Game Package",
            "ToolsDocumentManager::OpenFile(DocumentEventOpenLevel)");
        return;
    }

    // Save the last path for convenience
    m_lastPathOpenedTo = path;

    // Ensure the file exists.
    if (!File::Exists(path))
    {
        // TODO: Create an error / general message box for the user. #114
        Log::Error("Filepath does not exist.",
            "ToolsDocumentManager::OpenFile(DocumentEventOpenLevel)");
        return;
    }

    // It might exist but it might not exist in the GamePackage.
    // Ensure it does.
    if (auto windowsPackage = m_windowsPackage.lock())
    {
        if (!windowsPackage->GetContentManager()->GamePackage()->File()->Exists(gamePackagePath))
        {
            windowsPackage->GetContentManager()->GamePackage()->Reload();
        }
    }
    else
    {
        Log::Error("Windows package is no longer alive. Cannot create/open document.",
            "ToolsDocumentManager::OpenFile(DocumentEventOpenLevel)");
        return;
    }

    // See if this is a valid document for us to open.
    auto matcher = DocumentCriteria();
    matcher.FilePath = gamePackagePath;

    std::shared_ptr<Document> document = DocumentFactory::CreateDocument(matcher);
    if (!document)
    {
        // TODO: Create an error / general message box for the user. #114
        Log::Error("The file opened could not be loaded because it was not registered as a valid type."
                     " Filepath: " + gamePackagePath,
            "ToolsDocumentManager::OpenFile(DocumentEventOpenLevel)");
        return;
    }

    // We need to set this up.
    // This needs to occur now because Windows Package is not static,
    // and we do not want it to be.
    if (auto windowsPackage = m_windowsPackage.lock())
    {
        document->Setup(gamePackagePath, 
            windowsPackage->GetContentManager()->GamePackage(), 
            windowsPackage->GetPackagePaths());
    }
    else
    {
        Log::Error("Windows package is no longer alive. Cannot create/open document.",
            "ToolsDocumentManager::OpenFile(DocumentEventOpenLevel)");
        return;
    }

    if (!document->Load())
    {
        Log::Error("Could not load document. Filepath: " + gamePackagePath,
            "ToolsDocumentManager::OpenFile(DocumentEventOpenLevel)");
        return;
    }

    auto args = std::make_shared<DocumentActionEventArguments>(
        document, DocumentEventAction::Open, level);
    m_onDocumentAction->Invoke(args);
}

void ToolsDocumentManager::SaveFile(DocumentEventSaveContext saveContext)
{
    if (saveContext != DocumentEventSaveContext::Everything)
    {
        Log::Error("Only " + EDocumentEventSaveContext::ToString(DocumentEventSaveContext::Everything) + ""
            " is implemented for saving.", "ToolsDocumentManager::SaveFile(DocumentEventSaveContext)");
        return;
    }

    auto args = std::make_shared<DocumentActionEventArguments>(
        nullptr, DocumentEventAction::Save, saveContext);
    m_onDocumentAction->Invoke(args);
}

void ToolsDocumentManager::NewFile()
{
    std::vector<std::string> sceneFileExtensions;
    sceneFileExtensions.emplace_back("*.scene");
    std::string openTo = GetFilepathToOpenTo();

    std::string path = m_fileDialog->SaveFile(
        "Save scene", 
        openTo,
        sceneFileExtensions, 
        "Scene File");
    if (path.empty())
    {
        return;
    }

    std::string gamePackagePath = File::MakeRelative(m_productsPath, path);
    if (gamePackagePath.empty())
    {
        // TODO: Create an error / general message box for the user. #114
        Log::Error("Path was not within Game Package",
            "ToolsDocumentManager::OpenFile(DocumentEventOpenLevel)");
        return;
    }

    // Save the last path for convenience
    m_lastPathOpenedTo = path;

    if (File::Exists(path))
    {
        if (!File::WriteLine(path, ""))
        {
            // TODO: Create an error / general message box for the user. [#114]
            Log::Error("Could not override old path."
                "ToolsDocumentManager::OpenFile(DocumentEventOpenLevel)");
            return;
        }
    }
    else if (!File::WriteLine(path, ""))
    {
        // TODO: Create an error / general message box for the user. #114
        Log::Error("Could not create file."
            "ToolsDocumentManager::OpenFile(DocumentEventOpenLevel)");
        return;
    }

    // We need to set this up.
    // This needs to occur now because Windows Package is not static,
    // and we do not want it to be.
    if (auto windowsPackage = m_windowsPackage.lock())
    {
        windowsPackage->GetContentManager()->GamePackage()->Reload();
    }
    else
    {
        Log::Error("Windows package is no longer alive. Cannot create/open document.",
            "ToolsDocumentManager::OpenFile(DocumentEventOpenLevel)");
        return;
    }

    auto matcher = DocumentCriteria();
    matcher.FilePath = gamePackagePath;

    std::shared_ptr<Document> document = DocumentFactory::CreateDocument(matcher);
    if (!document)
    {
        // TODO: Create an error / general message box for the user. #114
        Log::Error("The file opened could not be loaded because it was not registered as a valid type."
            " Filepath: " + gamePackagePath,
            "ToolsDocumentManager::OpenFile(DocumentEventOpenLevel)");
        return;
    }

    if (!document->Create())
    {
        // TODO: Create an error / general message box for the user. #114
        Log::Error("Could not create an empty version of the file."
            " Filepath: " + gamePackagePath,
            "ToolsDocumentManager::OpenFile(DocumentEventOpenLevel)");
        return;
    }

    // We need to set this up.
    // This needs to occur now because Windows Package is not static,
    // and we do not want it to be.
    if (auto windowsPackage = m_windowsPackage.lock())
    {
        document->Setup(gamePackagePath,
            windowsPackage->GetContentManager()->GamePackage(),
            windowsPackage->GetPackagePaths());
    }
    else
    {
        Log::Error("Windows package is no longer alive. Cannot create/open document.",
            "ToolsDocumentManager::OpenFile(DocumentEventOpenLevel)");
        return;
    }

    auto args = std::make_shared<DocumentActionEventArguments>(
        document, DocumentEventAction::Create);
    m_onDocumentAction->Invoke(args);
}

std::string ToolsDocumentManager::GetFilepathToOpenTo()
{
    std::string gamePackagePath = File::MakeRelative(m_productsPath, m_lastPathOpenedTo);
    if (gamePackagePath.empty())
    {
        m_lastPathOpenedTo = m_productsPath;
    }
    else
    {
        if (!Directory::IsDirectory(m_lastPathOpenedTo))
        {
            m_lastPathOpenedTo = Directory::GetParent(m_lastPathOpenedTo);
        }
    }

    if (m_lastPathOpenedTo.back() != '\\' && m_lastPathOpenedTo.back() != '/')
    {
        m_lastPathOpenedTo += '\\';
    }

    return m_lastPathOpenedTo;
}
