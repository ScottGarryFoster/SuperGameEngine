#pragma once
#include "../../Engine/Content/ContentManager.h"
#include "../../Engine/Input/DirectInput.h"
#include "../../Engine/Graphics/Technique/TechniqueRenderer.h"

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
        SceneLoadPackage(
            ContentManager* contentManager, 
            const DirectInput* directInput,
            TechniqueRenderer* techniqueRenderer);

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
    };
}
