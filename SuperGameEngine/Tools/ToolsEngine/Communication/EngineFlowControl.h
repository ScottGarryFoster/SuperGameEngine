#pragma once

namespace SuperGameTools
{
    /// <summary>
    /// How the engine entry should treat the engine.
    /// </summary>
    class EngineFlowControl
    {
    public:
        virtual ~EngineFlowControl() = default;

        /// <summary>
        /// Questioned at the start of the game loop.
        /// True means the engine will be re-created.
        /// </summary>
        /// <returns>True means the engine will be re-created. </returns>
        virtual bool DoRecreate() const = 0;

        /// <summary>
        /// Questioned at the end of the loop.
        /// True means the engine pointer will be lost and
        /// the garbage collection will collect it.
        /// </summary>
        /// <returns></returns>
        virtual bool DoDestroy() const = 0;

        /// <summary>
        /// Called after the events have run.
        /// Only is called if the flow mentions that the events should have run.
        /// Will be called if no events occured.
        /// </summary>
        virtual void RanEvents() = 0;

        /// <summary>
        /// Called after the update provided the update ran.
        /// </summary>
        virtual void RanUpdate() = 0;

        /// <summary>
        /// Called after the draw provided the draw ran.
        /// </summary>
        virtual void RanDraw() = 0;
    };
}

