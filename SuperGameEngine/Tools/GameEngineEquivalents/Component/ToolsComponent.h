#pragma once
#include "Component.h"

using namespace FatedQuestLibraries;

namespace SuperGameTools
{
    /// <summary>
    /// A component which represents the data of a game component.
    /// </summary>
    class ToolsComponent : public Component
    {
    public:
        virtual ~ToolsComponent() override = default;

        /// <summary>
        /// The type of the component.
        /// </summary>
        /// <returns>The type of the component. </returns>
        virtual std::string GetType() const override;

        /// <summary>
        /// Set new type.
        /// </summary>
        /// <param name="type">New type. </param>
        virtual void SetType(const std::string& type) override;

    private:
        /// <summary>
        /// The type of the component.
        /// </summary>
        std::string m_type;
    };
}
