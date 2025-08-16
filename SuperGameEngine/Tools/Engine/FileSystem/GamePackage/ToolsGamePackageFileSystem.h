#pragma once
#include "../../../../../FatedQuest.Libraries/GamePackage/GamePackage/FileSystem/GamePackageFileSystem.h"

namespace SuperGameTools
{
    /// <summary>
    /// Contains tools differences to the game package.
    /// </summary>
    /// <remarks>
    /// Note that the game package is always the literal file version within tools.
    /// </remarks>
    class ToolsGamePackageFileSystem : public FatedQuestLibraries::GamePackageFileSystem
    {
    public:
        ToolsGamePackageFileSystem();
    };
}

