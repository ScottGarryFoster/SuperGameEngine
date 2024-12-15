#pragma once
#include <memory>

namespace SuperGameEngine
{
    class SDLRendererReader;
}

namespace SuperGameTools
{
    class WindowPackage;

    /// <summary>
    /// The basic concept of setup, update and draw.
    /// </summary>
    class UpdateableObject
    {
    public:
        /// <summary>
        /// Called once on setup.
        /// </summary>
        /// <param name="windowPackage">Everything needed to run a window. </param>
        virtual void Setup(std::shared_ptr<WindowPackage> windowPackage) = 0;

        /// <summary>
        /// Called every frame.
        /// </summary>
        virtual void Update() = 0;

        /// <summary>
        /// Called on draw.
        /// </summary>
        virtual void Draw() = 0;

        /// <summary>
        /// Called on destroy.
        /// </summary>
        virtual void TearDown() = 0;
    };
}
