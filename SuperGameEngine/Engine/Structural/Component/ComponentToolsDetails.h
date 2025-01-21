#pragma once
#include <string>

namespace SuperGameEngine
{
    /// <summary>
    /// Details about a component which are used in the Tooling.
    /// </summary>
    class ComponentToolsDetails
    {
    public:
        /// <summary>
        /// The name to display when searching for the component.
        /// </summary>
        /// <returns>Display name. </returns>
        std::string GetDisplayName();
    };
}
