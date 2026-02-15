#pragma once
#include <memory>

#include "../../../../FatedQuest.Libraries/Observer/FEventArguments.h"

namespace SuperGameTools
{
    class ToolsSerializableProperty;

    /// <summary>
    /// Occurs on Tools Property Changed.
    /// </summary>
    class ToolsPropertyChangedArguments : public FatedQuestLibraries::FEventArguments
    {
    public:
        ToolsPropertyChangedArguments(const std::shared_ptr<const ToolsSerializableProperty>& property)
        {
            m_property = property;
        }

        /// <summary>
        /// The property which changed.
        /// </summary>
        /// <returns>The property which changed. </returns>
        std::shared_ptr<const ToolsSerializableProperty> GetPropertyChanged() const;

    private:

        /// <summary>
        /// The property which changed.
        /// </summary>
        std::shared_ptr<const ToolsSerializableProperty> m_property;
    };
}
