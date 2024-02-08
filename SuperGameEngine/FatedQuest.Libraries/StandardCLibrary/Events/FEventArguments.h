#pragma once

namespace StandardCLibrary
{
    /// <summary>
    /// Sent by all FEvents. Override this with custom event arguments.
    /// </summary>
    class FEventArguments
    {
    public:
        FEventArguments(){}
        virtual ~FEventArguments() {}
    };
}