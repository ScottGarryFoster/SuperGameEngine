#pragma once
#include <string>

namespace PackageFileProvider
{
    /// <summary>
    /// Broadly gives context about locations of the files and folders for
    /// resources.
    /// </summary>
    class TopLevelDirectories
    {
    public:
        /// <summary>
        /// The folder the Exe / application is running in.
        /// CACHE THIS, DO NOT CALL IT EVERY FRAME.
        /// </summary>
        /// <returns>The folder the Exe / application is running in.</returns>
        /// <remark>CACHE THIS, DO NOT CALL IT EVERY FRAME. </remark>
        static std::string GetExeDirectory();

        /// <summary>
        /// The folder the solution files exist in.
        /// CACHE THIS, DO NOT CALL IT EVERY FRAME.
        /// </summary>
        /// <returns>The folder the solution files exist in. </returns>
        /// <remark>CACHE THIS, DO NOT CALL IT EVERY FRAME. </remark>
        static std::string GetWorkingDirectory();

        /// <summary>
        /// The products folder with Engine and game files.
        /// CACHE THIS, DO NOT CALL IT EVERY FRAME.
        /// </summary>
        /// <returns>The products folder with Engine and game files. </returns>
        /// <remarks>CACHE THIS, DO NOT CALL IT EVERY FRAME. </remarks>
        static std::string GetProductsFolder();
    };
}