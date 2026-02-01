#pragma once
#include "ViewportToolsType.h"
#include <unordered_map>

namespace SuperGameTools
{
    /// <summary>
    /// Defines all the viewport button information in a raw format.
    /// </summary>
    struct ViewportButtonInfo
    {
    public:

        /// <summary>
        /// Defines the textures to use for each tool.
        /// </summary>
        std::unordered_map<ViewportToolsType, std::string> Textures =
            {
                {ViewportToolsType::Select, R"(Tools\Icons\Select\Select-25.png)" },
                {ViewportToolsType::Move, R"(Tools\Icons\Move\Move-25.png)" },
            };
    };
}
