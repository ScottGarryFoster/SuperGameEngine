#pragma once
#include "CopyFileOptions.h"
#include <filesystem>

namespace FileSystem = std::filesystem;

using namespace FatedQuestLibraries;

namespace CopyFileOptionsHelper
{
    /// <summary>
    /// Converts CopyOptions to the FileSystem version.
    /// Not included in the main libraries to avoid FileSystem includes.
    /// </summary>
    /// <param name="options">Option to convert. </param>
    /// <returns>Converted option. </returns>
    static FileSystem::copy_options Convert(CopyFileOptions options)
    {
        FileSystem::copy_options returnOptions;
        bool haveAtLeastOneOption = false;
        if (ECopyOptions::HasOption(options, CopyFileOptions::None))
        {
            returnOptions |= FileSystem::copy_options::none;
            haveAtLeastOneOption = true;
        }
        if (ECopyOptions::HasOption(options, CopyFileOptions::SkipExistingFile))
        {
            returnOptions |= FileSystem::copy_options::skip_existing;
            haveAtLeastOneOption = true;
        }
        if (ECopyOptions::HasOption(options, CopyFileOptions::OverwriteExistingFile))
        {
            returnOptions |= FileSystem::copy_options::overwrite_existing;
            haveAtLeastOneOption = true;
        }
        if (FatedQuestLibraries::ECopyOptions::HasOption(options, CopyFileOptions::UpdateExistingFile))
        {
            returnOptions |= FileSystem::copy_options::update_existing;
            haveAtLeastOneOption = true;
        }

        if (FatedQuestLibraries::ECopyOptions::HasOption(options, CopyFileOptions::RecursiveDirectories))
        {
            returnOptions |= FileSystem::copy_options::recursive;
            haveAtLeastOneOption = true;
        }

        if (FatedQuestLibraries::ECopyOptions::HasOption(options, CopyFileOptions::CopySymlinks))
        {
            returnOptions |= FileSystem::copy_options::copy_symlinks;
            haveAtLeastOneOption = true;
        }

        if (FatedQuestLibraries::ECopyOptions::HasOption(options, CopyFileOptions::SkipSymlinks))
        {
            returnOptions |= FileSystem::copy_options::skip_symlinks;
            haveAtLeastOneOption = true;
        }

        if (FatedQuestLibraries::ECopyOptions::HasOption(options, CopyFileOptions::DirectoriesOnly))
        {
            returnOptions |= FileSystem::copy_options::directories_only;
            haveAtLeastOneOption = true;
        }
        if (FatedQuestLibraries::ECopyOptions::HasOption(options, CopyFileOptions::CreateSymlinks))
        {
            returnOptions |= FileSystem::copy_options::create_symlinks;
            haveAtLeastOneOption = true;
        }
        if (FatedQuestLibraries::ECopyOptions::HasOption(options, CopyFileOptions::CreateHardLinks))
        {
            returnOptions |= FileSystem::copy_options::create_hard_links;
            haveAtLeastOneOption = true;
        }

        if (haveAtLeastOneOption)
        {
            return returnOptions;
        }

        return FileSystem::copy_options::none;
    }
}