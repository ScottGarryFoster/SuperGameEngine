#pragma once
#include "../UpdateableObject/UpdateableObject.h"

namespace SuperGameTools
{
    class TreeView;
    class SceneLoader;

    /// <summary>
    /// Contains the scenes and game objects.
    /// </summary>
    class SceneHierarchy : public UpdateableObject
    {
    public:
        SceneHierarchy();
        virtual ~SceneHierarchy() override = default;

        /// <summary>
        /// Called once on setup.
        /// </summary>
        /// <param name="windowPackage">Everything needed to run a window. </param>
        virtual void Setup(const std::shared_ptr<WindowPackage>& windowPackage) override;

        /// <summary>
        /// Called every frame.
        /// </summary>
        virtual void Update() override {}

        /// <summary>
        /// Called on draw.
        /// </summary>
        virtual void Draw() override;

        /// <summary>
        /// Called on destroy.
        /// </summary>
        virtual void TearDown() override {}

    private:
        /// <summary>
        /// The tree.
        /// </summary>
        std::shared_ptr<TreeView> m_tree;

        /// <summary>
        /// Loads scene for the Tools.
        /// </summary>
        std::shared_ptr<SceneLoader> m_sceneLoader;
    };
}


