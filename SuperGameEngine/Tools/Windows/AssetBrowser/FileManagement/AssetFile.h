#pragma once
#include <memory>
#include <string>
#include <vector>

namespace SuperGameEngine
{
    class RectangleInt;
}

namespace SuperGameTools
{
    class AssetFolder;

    /// <summary>
    /// Represents a single Asset File.
    /// </summary>
    class AssetFile
    {
    public:

        /// <summary>
        /// Gets the parent folder.
        /// </summary>
        /// <returns>The parent of the given file. </returns>
        virtual std::weak_ptr<AssetFolder> GetParent() const = 0;

        /// <summary>
        /// Get the name to display in a browser.
        /// </summary>
        /// <returns>The display name. </returns>
        virtual std::string GetDisplayName() const = 0;

        /// <summary>
        /// Get the path to this file in relation to the package.
        /// </summary>
        /// <returns>The path relative to the products folder. </returns>
        virtual std::string GetPackagePath() const = 0;

        /// <summary>
        /// Draws an image representing the file with the given size.
        /// </summary>
        /// <param name="screenRectangle">Location and size on the screen to draw. </param>
        virtual void DrawLargeTile(const SuperGameEngine::RectangleInt& screenRectangle) const = 0;
    };
}
