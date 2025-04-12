using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FileHandling.BasicFunctions
{
    /// <summary>
    /// Wraps the .NET File methods.
    /// </summary>
    /// <remarks>
    /// This is so that we may pass interfaces for testing and limit classes to what they can do.
    /// </remarks>
    public class FileWrapper : IFile
    {
        /// <summary>
        /// True means file exists.
        /// </summary>
        /// <param name="path">Full path to the file. </param>
        /// <returns>True means file exists. </returns>
        public bool Exists(string path)
        {
            return File.Exists(path);
        }

        /// <summary>
        /// Reads all the lines from a given file.
        /// </summary>
        /// <param name="path">Full path to the file. </param>
        /// <returns>Contents of the file if it exists, exception otherwise. </returns>
        /// <exception cref="Exception">
        /// If the file is not found or not readable.
        /// </exception>
        public string[] ReadAllLines(string path)
        {
            return File.ReadAllLines(path);
        }
    }
}
