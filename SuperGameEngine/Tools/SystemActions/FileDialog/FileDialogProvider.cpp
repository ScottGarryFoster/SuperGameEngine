#include "FileDialogProvider.h"

#include "TinyFileDialogs.h"

using namespace SuperGameTools;

FileDialogProvider::FileDialogProvider()
{
    // This should work on all platforms, although I might need to include
    // other things later for linux or mac.
    m_fileDialog = std::make_shared<TinyFileDialogs>();
}

std::shared_ptr<FileDialog> FileDialogProvider::GetFileDialog() const
{
    return m_fileDialog;
}
