#include "FilepathCollectionFromExternalSource.h"
#include "LibraryIncludes.h"

using namespace PackageFileProvider;
using namespace StandardCLibrary;

FilepathCollectionFromExternalSource::FilepathCollectionFromExternalSource
    (const std::vector<std::string>& paths)
{

    m_filePathsAsDirectories = std::make_shared<DirectoryInfo>();
    m_filePathsAsDirectories->Name = m_topDirectoryName;

    for (std::string path : paths)
    {
        m_filepaths.push_back(path);
        std::vector<std::string> pathSplit = SplitPathIntoParts(path);
        AddPathToDirectoryTree(pathSplit, m_filePathsAsDirectories);
    }
}

const std::vector<std::string> FilepathCollectionFromExternalSource::GetAllFiles() const
{
    return m_filepaths;
}

bool FilepathCollectionFromExternalSource::Exists(const std::string& filePath) const
{
    std::vector<std::string> pathSplit = SplitPathIntoParts(filePath);

    std::vector<std::string> files;
    if (pathSplit.size() > 1)
    {
        // If this is a directory path, find the exact directory and extract the files.
        std::vector<std::string> restOfPath = 
            VectorHelpers::ReturnVectorWithElementRemovedAtIndex(pathSplit, pathSplit.size() - 1);
        std::string directoryPath = StringHelpers::Join("/", restOfPath);

        files = GetAllFilesInDirectory(directoryPath);
    }
    else
    {
        files = m_filePathsAsDirectories->Files;
    }

    return VectorHelpers::ContainsString(files, pathSplit.back(), false);
}

const std::vector<std::string> FilepathCollectionFromExternalSource::GetAllFilesInDirectory
    (const std::string& directoryPath) const
{
    std::shared_ptr<DirectoryInfo> directory = 
        GetDirectory(directoryPath, m_filePathsAsDirectories);
    if (!directory)
    {
        // If directory does not exist then return no files.
        return std::vector<std::string>();
    }

    return directory->Files;
}

void FilepathCollectionFromExternalSource::AddPathToDirectoryTree
    (const std::vector<std::string>& pathSplit, std::shared_ptr<DirectoryInfo> current)
{
    if (pathSplit.empty())
    {
        // Cannot continue without a path.
        return;
    }

    std::string currentElement = pathSplit[0];
    std::vector<std::string> restOfPath = VectorHelpers::ReturnVectorWithElementRemovedAtIndex(pathSplit, 0);

    // If rest of path is empty then the current element is the filename.
    if (restOfPath.empty())
    {
        current->Files.push_back(currentElement);
    }
    else
    {
        std::shared_ptr<DirectoryInfo> newDirectory;
        for (size_t i = 0; i < current->ChildDirectory.size(); ++i)
        {
            if (current->ChildDirectory[i]->Name == currentElement)
            {
                newDirectory = current->ChildDirectory[i];

                // Here is be more performant if there are a lot of directories.
                // This should not be an issue I imagine there would not be thousands of them but
                // you never know? For instance a directory per chunk in a world?
                break;
            }
        }

        if (!newDirectory)
        {
            newDirectory = std::make_shared<DirectoryInfo>();
            newDirectory->Name = currentElement;
            current->ChildDirectory.push_back(newDirectory);
        }

        AddPathToDirectoryTree(restOfPath, newDirectory);
    }
}

const std::vector<std::string> FilepathCollectionFromExternalSource::SplitPathIntoParts
    (const std::string& path) const
{
    std::vector<std::string> pathSplit = StringHelpers::Split("/", path);
    if (!pathSplit.empty())
    {
        // Ensure that if the input had a blank directory at the end this is not counted.
        if (StringHelpers::IsEmptyOrWhitespace(pathSplit.back()))
        {
            pathSplit.pop_back();
        }
    }

    return pathSplit;
}

std::shared_ptr<FilepathCollectionFromExternalSource::DirectoryInfo> 
    FilepathCollectionFromExternalSource::GetDirectory
        (const std::string& path, std::shared_ptr<DirectoryInfo> current) const
{
    std::vector<std::string> pathSplit = SplitPathIntoParts(path);
    return GetDirectory(pathSplit, current);
}

std::shared_ptr<FilepathCollectionFromExternalSource::DirectoryInfo> 
    FilepathCollectionFromExternalSource::GetDirectory
        (const std::vector<std::string>& pathSplit, std::shared_ptr<DirectoryInfo> current) const
{
    if (pathSplit.empty())
    {
        // Cannot continue without a path.
        return std::shared_ptr<FilepathCollectionFromExternalSource::DirectoryInfo>();
    }

    std::string currentElement = pathSplit[0];
    std::vector<std::string> restOfPath = VectorHelpers::ReturnVectorWithElementRemovedAtIndex(pathSplit, 0);
    
    // Find the directory we are currently looking for:
    std::shared_ptr<DirectoryInfo> foundDirectory;
    for (size_t i = 0; i < current->ChildDirectory.size(); ++i)
    {
        if (StringHelpers::Equals(current->ChildDirectory[i]->Name, currentElement, true))
        {
            foundDirectory = current->ChildDirectory[i];

            // Here is be more performant if there are a lot of directories.
            // This should not be an issue I imagine there would not be thousands of them but
            // you never know? For instance a directory per chunk in a world?
            break;
        }
    }

    // We found a directory
    if (foundDirectory)
    {
        // and there is more to find.
        if (!restOfPath.empty())
        {
            return GetDirectory(restOfPath, foundDirectory);
        }
    }

    return foundDirectory;
}
