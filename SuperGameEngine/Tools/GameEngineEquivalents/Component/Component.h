#pragma once
#include <memory>
#include <string>


namespace FatedQuestLibraries
{
    class Guid;
}

using namespace FatedQuestLibraries;

namespace SuperGameTools
{
    /// <summary>
    /// A component which represents the data of a game component.
    /// </summary>
    class Component
    {
    public:
        virtual ~Component() = default;

        /// <summary>
        /// The type of the component.
        /// </summary>
        /// <returns>The type of the component. </returns>
        virtual std::string GetType() const = 0;

        /// <summary>
        /// Set new type.
        /// </summary>
        /// <param name="type">New type. </param>
        virtual void SetType(const std::string& type) = 0;
    };
}
