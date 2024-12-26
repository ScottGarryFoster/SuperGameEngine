#pragma once
#include "../UpdateableObject/UpdateableObject.h"

namespace SuperGameTools
{
    /// <summary>
    /// Property and metadata inspector window.
    /// </summary>
    class InspectorWindow : public UpdateableObject
    {
    public:
        /// <summary>
        /// Called once on setup.
        /// </summary>
        /// <param name="windowPackage">Everything needed to run a window. </param>
        virtual void Setup(const std::shared_ptr<WindowPackage>& windowPackage) override {};

        /// <summary>
        /// Called every frame.
        /// </summary>
        virtual void Update() override {};

        /// <summary>
        /// Called on draw.
        /// </summary>
        virtual void Draw() override;

        /// <summary>
        /// Called on destroy.
        /// </summary>
        virtual void TearDown() override {};
    };
}


