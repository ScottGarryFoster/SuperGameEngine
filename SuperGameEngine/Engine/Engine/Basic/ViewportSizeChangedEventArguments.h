#pragma once
#include <string>

#include "../../../../FatedQuest.Libraries/Observer/FEventArguments.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Used to store changes to the viewport.
    /// </summary>
    class ViewportSizeChangedEventArguments : public FatedQuestLibraries::FEventArguments
    {
    public:

        ViewportSizeChangedEventArguments(const std::string& name, int newWidth, int newHeight)
        {
            m_name = name;
            m_newWidth = newWidth;
            m_newHeight = newHeight;
        }

        /// <summary>
        /// The name of the viewport attempting to change size.
        /// </summary>
        /// <returns>The name of the viewport attempting to change size. </returns>
        std::string GetName() const
        {
            return m_name;
        }

        /// <summary>
        /// The new width which has now changed.
        /// </summary>
        /// <returns>The new width which has now changed. </returns>
        int GetNewWidth() const
        {
            return m_newWidth;
        }

        /// <summary>
        /// The new height which has now changed.
        /// </summary>
        /// <returns>The new height which has now changed. </returns>
        int GetNewHeight() const
        {
            return m_newHeight;
        }

    private:

        /// <summary>
        /// The name of the engine which sent the request.
        /// </summary>
        std::string m_name;

        /// <summary>
        /// The width this event is giving as the new width for the viewport.
        /// </summary>
        int m_newWidth;

        /// <summary>
        /// The height this event is giving as the new height for the viewport.
        /// </summary>
        int m_newHeight;
    };
}
