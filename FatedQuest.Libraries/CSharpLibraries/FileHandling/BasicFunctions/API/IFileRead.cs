using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FileHandling
{
    public interface IFileRead
    {
        /// <summary>
        /// True means file exists.
        /// </summary>
        /// <param name="path">Full path to the file. </param>
        /// <returns>True means file exists. </returns>
        bool Exists(string path);

        /// <summary>
        /// Reads all the lines from a given file.
        /// </summary>
        /// <param name="path">Full path to the file. </param>
        /// <returns>Contents of the file if it exists, exception otherwise. </returns>
        /// <exception cref="Exception">
        /// If the file is not found or not readable.
        /// </exception>
        string[] ReadAllLines(string path);
    }
}
