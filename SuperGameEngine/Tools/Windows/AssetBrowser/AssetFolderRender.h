#pragma once

namespace SuperGameTools
{
    /// <summary>
    /// Renders the Asset Browser buttons representing Files and Folders and the controls to move back up to the root folder.
    /// </summary>
    class AssetFolderRender
    {
    public:
        /// <summary>
        /// An update loop ran before the draw.
        /// </summary>
        virtual void Update() = 0;

        /// <summary>
        /// Render the asset tiles.
        /// </summary>
        virtual void Draw() = 0;
    };
}