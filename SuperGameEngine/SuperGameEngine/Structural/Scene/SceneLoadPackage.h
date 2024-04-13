#pragma once
#include "../../Engine/Content/ContentManager.h"
#include "../../Engine/Input/DirectInput.h"
#include "../../Engine/Graphics/Technique/TechniqueRenderer.h"
#include "FrameTiming.h"
#include "../Spatial/Collision/CollisionQuery.h"

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
        /// <param name="contentManager">Access to resources. </param>
        /// <param name="directInput">Access to direct input from the User. ></param>
        /// <param name="techniqueRenderer">Renders techniques which for the most part are primitives. </param>
        /// <param name="frameTimings">Controls when Loops occur. </param>
        SceneLoadPackage(
            ContentManager* contentManager, 
            const DirectInput* directInput,
            TechniqueRenderer* techniqueRenderer,
            FrameTiming* frameTimings,
            CollisionQuery* m_collisionQuery);
        virtual ~SceneLoadPackage();

        /// <summary>
        /// Allows you to gain access to textures.
        /// </summary>
        /// <returns>Gives you a reference to the content manager. </returns>
        ContentManager* GetContentManager() const;

        /// <summary>
        /// Access to direct input from the User.
        /// </summary>
        const DirectInput* GetDirectInput() const;

        /// <summary>
        /// Renders techniques which for the most part are primitives.
        /// </summary>
        TechniqueRenderer* GetTechniqueRender();

        /// <summary>
        /// Controls when Loops occur.
        /// </summary>
        /// <returns>Allows you to control when an update loop occurs. </returns>
        FrameTiming* GetFrameTiming() const;

        /// <summary>
        /// Queries for the colliders in the scene.
        /// </summary>
        /// <remark>
        /// These are expensive commands so use them wisely!
        /// </remark>
        CollisionQuery* GetCollisionQuery() const;
    private:
        /// <summary>
        /// Allows you to gain access to textures.
        /// </summary>
        ContentManager* m_contentManager;

        /// <summary>
        /// Access to direct input from the User.
        /// </summary>
        const DirectInput* m_directInput;

        /// <summary>
        /// Renders techniques which for the most part are primitives.
        /// </summary>
        TechniqueRenderer* m_techniqueRenderer;

        /// <summary>
        /// Controls when Loops occur.
        /// </summary>
        FrameTiming* m_frameTiming;

        /// <summary>
        /// Queries for the colliders in the scene.
        /// </summary>
        /// <remark>
        /// These are expensive commands so use them wisely!
        /// </remark>
        CollisionQuery* m_collisionQuery;
    };
}
