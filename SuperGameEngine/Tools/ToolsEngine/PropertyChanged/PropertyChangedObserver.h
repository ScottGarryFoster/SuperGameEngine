#pragma once
#include <string>

namespace SuperGameTools
{
    /// <summary>
    /// Any class which is able to observe events.
    /// </summary>
    class PropertyChangedObserver
    {
    public:
        virtual ~PropertyChangedObserver() = default;

        /// <summary>
        /// Property has changed.
        /// </summary>
        /// <param name="name">Property which has changed. </param>
        virtual void OnPropertyChanged(const std::string& name) = 0;
    };
}