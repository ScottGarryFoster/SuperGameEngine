namespace FatedQuestLibraries
{
    /// <summary>
    /// Helper class to grab paths.
    /// </summary>
    public interface IFilePaths
    {
        /// <summary>
        /// Gets the directory the application is running from.
        /// </summary>
        /// <returns>
        /// The directory the application is running from.
        /// </returns>
        string ApplicationDirectory();

        /// <summary>
        /// Gets the Repository directory.
        /// </summary>
        /// <returns>The directory the code lives in. </returns>
        /// <remarks>
        /// This is not cached so cache it locally if calling it a bunch.
        /// This should only be used for tools.
        /// </remarks>
        string RepositoryDirectory();
    }
}