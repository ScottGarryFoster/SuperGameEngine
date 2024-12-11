#pragma once
#include <memory>
#include "ComponentLoadPackage.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Everything a component needs to run.
    /// </summary>
    class SuperComponentLoadPackage : public ComponentLoadPackage
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

