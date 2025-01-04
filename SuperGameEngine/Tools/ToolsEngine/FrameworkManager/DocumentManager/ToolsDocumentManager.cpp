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
            if (menuItem->GetKey() == "FileOpen")
            {
                OpenFile(DocumentEventOpenLevel::Exclusive);
            }
        }
    }
}

void ToolsDocumentManager::OpenFile(DocumentEventOpenLevel level)
{
    std::string path = m_fileDialog->OpenFile();
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
