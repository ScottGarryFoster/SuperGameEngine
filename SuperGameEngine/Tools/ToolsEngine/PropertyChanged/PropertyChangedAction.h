#pragma once
#include <string>

namespace SuperGameTools
{
    /// <summary>
    /// The action portion of the event.
    /// </summary>
    class PropertyChangedAction
    {
    public:
        virtual ~PropertyChangedAction() = default;

        /// <summary>
        /// Property has changed.
        /// </summary>
        /// <param name="name">Property which has changed. </param>
        virtual void PropertyChanged(const std::string& name) = 0;
    };
}