#pragma once
#include "../../Engine/Content/ContentManager.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Contains all the objects a GameObject needs to opperate.
    /// Can be given to other GameObjets freely.
    /// </summary>
    class SceneLoadPackage
    {
    public:
        /// <summary>
        /// Constructs a package.
        /// </summary>
        /// <param name="contentManager"></param>
        SceneLoadPackage(ContentManager* contentManager);

        /// <summary>
        /// Allows you to gain access to textures.
        /// </summary>
        /// <returns>Gives you a reference to the content manager. </returns>
        ContentManager* GetContentManager() const;

    private:
        /// <summary>
        /// Allows you to gain access to textures.
        /// </summary>
        ContentManager* m_contentManager;
    };
}
