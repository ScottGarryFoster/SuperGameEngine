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

        SceneLoadPackage(ContentManager* contentManager);


        ContentManager* GetContentManager() const;

    private:

        ContentManager* m_contentManager;
    };
}
