#pragma once
#include "../../../../../FatedQuest.Libraries/GamePackage/GamePackage/CombinedGamePackage.h"

namespace SuperGameTools
{
    /// <summary>
    /// Contains tools differences to the game package.
    /// </summary>
    /// <remarks>
    /// Note that the game package is always the literal file version within tools.
    /// </remarks>
    class ToolsGamePackage : public FatedQuestLibraries::CombinedGamePackage
    {
    public:
        ToolsGamePackage();
    };
}

