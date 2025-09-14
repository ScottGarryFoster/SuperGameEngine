using System;
using System.Collections.Generic;
using System.IO;

namespace FatedQuestLibraries
{
    /// <summary>
    /// Helper class to grab paths.
    /// </summary>
    public class FilePaths : IFilePaths
    {
        private static readonly string[] FoldersAtRepoRoot = { "FatedQuest.Libraries", "SuperGameEngine", "Tools" };

        /// <summary>
        /// Gets the directory the application is running from.
        /// </summary>
        /// <returns>
        /// The directory the application is running from.
        /// </returns>
        public string ApplicationDirectory()
        {
            return System.Reflection.Assembly.GetExecutingAssembly().Location;
        }

        /// <summary>
        /// Gets the Repository directory.
        /// </summary>
        /// <returns>The directory the code lives in. </returns>
        /// <remarks>
        /// This is not cached so cache it locally if calling it a bunch.
        /// This should only be used for tools.
        /// </remarks>
        public string RepositoryDirectory()
        {
            Func<string, List<string>> MakeFullPaths = folder =>
            {
                var newList = new List<string>();
                foreach (string directory in FoldersAtRepoRoot)
                {
                    newList.Add($"{Path.Combine(folder, directory)}");
                }

                return newList;
            };

            string currentDirectory = ApplicationDirectory();
            List<string> foldersAsFullPaths = MakeFullPaths(currentDirectory);
            for (int i = 0; i < 10; i++)
            {
                int foldersFound = 0;
                foreach(string directory in foldersAsFullPaths)
                {
                    if(Directory.Exists(directory))
                    {
                        ++foldersFound;
                    }
                }

                if(foldersFound == FoldersAtRepoRoot.Length)
                {
                    return currentDirectory;
                }

                currentDirectory = Directory.GetParent(currentDirectory).FullName;
                foldersAsFullPaths = MakeFullPaths(currentDirectory);
            }

            return currentDirectory;
        }
    }
}