#pragma once
#include "ToolsGizmoAction.h"
#include "../../../../FatedQuest.Libraries/Observer/FEventArguments.h"
#include "../../../../FatedQuest.Libraries/Logger/AllReferences.h"

namespace SuperGameTools
{
    /// <summary>
    /// Holds information upon the move gizmo being interacted with.
    /// </summary>
    class MoveInteractionChangedEvent : public FatedQuestLibraries::FEventArguments
    {
    public:

        MoveInteractionChangedEvent(ToolsGizmoAction action)
        {
            m_gizmoAction = action;
            m_x = 0;
            m_y = 0;

            if (action == ToolsGizmoAction::MoveBy)
            {
                FatedQuestLibraries::Log::Error("No X or Y given but action was " + EToolsGizmoAction::ToString(action),
                    "MoveInteractionChangedEvent(ToolsGizmoAction)");
            }
        }

        MoveInteractionChangedEvent(ToolsGizmoAction action, int x, int y)
        {
            m_gizmoAction = action;
            m_x = x;
            m_y = y;
        }

        [[nodiscard]] ToolsGizmoAction GetAction() const
        {
            return m_gizmoAction;
        }

        [[nodiscard]] int GetX() const
        {
            return m_x;
        }

        [[nodiscard]] int GetY() const
        {
            return m_y;
        }

    private:

        /// <summary>
        /// Describes the action to take when reacting to a Gizmo event
        /// </summary>
        ToolsGizmoAction m_gizmoAction;

        /// <summary>
        /// In a move by or move to, this is the X cord.
        /// </summary>
        int m_x;

        /// <summary>
        /// In a move by or move to, this is the Y cord.
        /// </summary>
        int m_y;
    };
}
