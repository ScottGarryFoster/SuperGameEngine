#pragma once
#include <memory>

#include "GrandScenePackage.h"

namespace SuperGameEngine
{
    class ContentManager;

    /// <summary>
    /// Everything a grand scene needs to run.
    /// This contains services run by the engine.
    /// </summary>
    class SuperGrandScenePackage : public GrandScenePackage
    {
    public:
        /// <summary>
        /// Provides and manages all shared resources.
        /// </summary>
        /// <returns>Provides and manages all shared resources. </returns>
        [[nodiscard]] virtual std::shared_ptr<ContentManager> GetContentManager() const override;

        /// <summary>
        /// Set the content manager for the package.
        /// </summary>
        /// <param name="contentManager">Provides and manages all shared resources. </param>
        virtual void SetContentManager(std::shared_ptr<ContentManager> contentManager);

    private:
        /// <summary>
        /// Provides and manages all shared resources.
        /// </summary>
        std::shared_ptr<ContentManager> m_contentManager;
    };
}


