#pragma once
#include <string>
#include <vector>

namespace BinaryOperations
{
    /// <summary>
    /// Methods to zip and unzip binary files.
    /// </summary>
    class BinaryZip
    {
    public:
        /// <summary>
        /// Takes a single file and makes it binary.
        /// </summary>
        /// <param name="input">Filepath in a Raw non-binary form. </param>
        /// <param name="output">The Filepath to the store the binary file. </param>
        /// <param name="errors">If not created successfully this contains the errors. </param>
        /// <returns>True means created. </returns>
        virtual bool FileToBinary(const std::string& inputFilepath, const std::string& outputFilepath, std::vector<std::string>& errors) = 0;

        /// <summary>
        /// Takes a binary file and outputs the raw data.
        /// </summary>
        /// <param name="input">A binary filepath. </param>
        /// <param name="output">The destination file path.</param>
        /// <param name="errors">If not created successfully this contains the errors. </param>
        /// <returns>True means created.</returns>
        virtual bool BinaryToFile(const std::string& inputFilepath, const std::string& outputFilepath, std::vector<std::string>& errors) = 0;

        /// <summary>
        /// Takes all the files in a directory and makes them binary.
        /// </summary>
        /// <param name="input">A directory path with files. </param>
        /// <param name="output">Where to store the directory with Binary Files as a path. </param>
        /// <param name="errors">If not created successfully this contains the errors. </param>
        /// <returns>True means created successfully. </returns>
        virtual bool DirectoryToBinary(const std::string& inputPath, const std::string& outputPath, std::vector<std::string>& errors) = 0;

        /// <summary>
        /// Takes a directory with Binary files and provides the raw data.
        /// </summary>
        /// <param name="input">A directory path with Binary data. </param>
        /// <param name="output">A directory path to store the raw files. </param>
        /// <param name="errors">If not created successfully this contains the errors. </param>
        /// <returns>True means created succesfully. </returns>
        virtual bool BinaryDirectoryToDirectory(const std::string& inputPath, const std::string& outputPath, std::vector<std::string>& errors) = 0;

        /// <summary>
        /// Takes a directory of files and stores them in a Zip.
        /// </summary>
        /// <param name="input">Directory path to store in zip. </param>
        /// <param name="output">A location and filename for the zip. </param>
        /// <param name="errors">If not created successfully this contains the errors. </param>
        /// <returns>True means created sucessfully. </returns>
        virtual bool DirectoryToZip(const std::string& inputPath, const std::string& outputFilepath, std::vector<std::string>& errors) = 0;

        /// <summary>
        /// Takes a zip and outputs a directory containing all the contents of the zip.
        /// </summary>
        /// <param name="input">A zip file. </param>
        /// <param name="output">A location to store the contents of the zip. </param>
        /// <param name="errors">If not created successfully this contains the errors. </param>
        /// <returns>True means created successfully. </returns>
        virtual bool ZipToDirectory(const std::string& inputFilepath, const std::string& outputPath, std::vector<std::string>& errors) = 0;

        /// <summary>
        /// Takes a directory of files, converts them to binary and then adds them to a zip file.
        /// </summary>
        /// <param name="input">Directory of files. </param>
        /// <param name="output">A location and filename for a zip file. </param>
        /// <param name="errors">If not created successfully this contains the errors. </param>
        /// <returns>True means created successfully. </returns>
        virtual bool DirectoryToZipWithFileToBinary(const std::string& inputPath, const std::string& outputFilepath, std::vector<std::string>& errors) = 0;

        /// <summary>
        /// Takes a zip with binary files, converts the files to raw format and stores them in the output directory.
        /// </summary>
        /// <param name="inputFilepath">A filename for a zip file. </param>
        /// <param name="outputPath">The location to store the files in the zip. </param>
        /// <param name="errors">If not created successfully this contains the errors. </param>
        /// <returns>True means created successfully. </returns>
        virtual bool ZipWithBinaryToDirectoryToFile(const std::string& inputFilepath, const std::string& outputPath, std::vector<std::string>& errors) = 0;
    };
}
