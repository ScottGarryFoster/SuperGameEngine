#pragma once

namespace FatedQuestLibraries
{
    /// <summary>
    /// Sent by all FEvents. Override this with custom event arguments.
    /// </summary>
    class FEventArguments
    {
    public:
        virtual ~FEventArguments() = default;
    };
}