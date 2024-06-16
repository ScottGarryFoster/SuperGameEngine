#pragma once
#include <string>
#include <vector>
#include "minizip/zip.h"
#include <minizip/unzip.h>

#include "BinaryZip.h"

namespace BinaryOperations
{
    /// <summary>
    /// Standard implementation of Binary Zip.
    /// </summary>
    class StandardBinaryZip : public BinaryZip
    {
    public:
        /// <summary>
        /// Takes a single file and makes it binary.
        /// </summary>
        /// <param name="inputFilepath">Filepath in a Raw non-binary form. </param>
        /// <param name="outputFilepath">The Filepath to the store the binary file. </param>
        /// <param name="errors">If not created successfully this contains the errors. </param>
        /// <returns>True means created. </returns>
        virtual bool FileToBinary(const std::string& inputFilepath, const std::string& outputFilepath, std::vector<std::string>& errors);

        /// <summary>
        /// Takes a binary file and outputs the raw data.
        /// </summary>
        /// <param name="inputFilepath">A binary filepath. </param>
        /// <param name="outputFilepath">The destination file path.</param>
        /// <param name="errors">If not created successfully this contains the errors. </param>
        /// <returns>True means created.</returns>
        virtual bool BinaryToFile(const std::string& inputFilepath, const std::string& outputFilepath, std::vector<std::string>& errors);

        /// <summary>
        /// Takes all the files in a directory and makes them binary.
        /// </summary>
        /// <param name="inputPath">A directory path with files. </param>
        /// <param name="outputPath">Where to store the directory with Binary Files as a path. </param>
        /// <param name="errors">If not created successfully this contains the errors. </param>
        /// <returns>True means created successfully. </returns>
        virtual bool DirectoryToBinary(const std::string& inputPath, const std::string& outputPath, std::vector<std::string>& errors);

        /// <summary>
        /// Takes a directory with Binary files and provides the raw data.
        /// </summary>
        /// <param name="inputPath">A directory path with Binary data. </param>
        /// <param name="outputPath">A directory path to store the raw files. </param>
        /// <param name="errors">If not created successfully this contains the errors. </param>
        /// <returns>True means created succesfully. </returns>
        virtual bool BinaryDirectoryToDirectory(const std::string& inputPath, const std::string& outputPath, std::vector<std::string>& errors);

        /// <summary>
        /// Takes a directory of files and stores them in a Zip.
        /// </summary>
        /// <param name="inputPath">Directory path to store in zip. </param>
        /// <param name="outputFilepath">A location and filename for the zip. </param>
        /// <param name="errors">If not created successfully this contains the errors. </param>
        /// <returns>True means created sucessfully. </returns>
        virtual bool DirectoryToZip(const std::string& inputPath, const std::string& outputFilepath, std::vector<std::string>& errors);

        /// <summary>
        /// Takes a zip and outputs a directory containing all the contents of the zip.
        /// </summary>
        /// <param name="inputFilepath">A zip file. </param>
        /// <param name="outputPath">A location to store the contents of the zip. </param>
        /// <param name="errors">If not created successfully this contains the errors. </param>
        /// <returns>True means created successfully. </returns>
        virtual bool ZipToDirectory(const std::string& inputFilepath, const std::string& outputPath, std::vector<std::string>& errors);

        /// <summary>
        /// Takes a directory of files, converts them to binary and then adds them to a zip file.
        /// </summary>
        /// <param name="inputPath">Directory of files. </param>
        /// <param name="outputFilepath">A location and filename for a zip file. </param>
        /// <param name="errors">If not created successfully this contains the errors. </param>
        /// <returns>True means created successfully. </returns>
        virtual bool DirectoryToZipWithFileToBinary(const std::string& inputPath, const std::string& outputFilepath, std::vector<std::string>& errors);

        /// <summary>
        /// Takes a zip with binary files, converts the files to raw format and stores them in the output directory.
        /// </summary>
        /// <param name="inputFilepath">A filename for a zip file. </param>
        /// <param name="outputPath">The location to store the files in the zip. </param>
        /// <param name="errors">If not created successfully this contains the errors. </param>
        /// <returns>True means created successfully. </returns>
        virtual bool ZipWithBinaryToDirectoryToFile(const std::string& inputFilepath, const std::string& outputPath, std::vector<std::string>& errors);

        /// <summary>
        /// Extracts a single file and reads it back in memory (directly from file).
        /// This is a non-binary version so it will just read the file back as is.
        /// </summary>
        /// <param name="zipFilePath">Location of the zip file. </param>
        /// <param name="innerFilepath">Location of the file with the zip. Case-Sensitive! </param>
        /// <param name="data">If found and loaded this is the data. </param>
        /// <param name="errors">If not loaded this will be the reason why. </param>
        /// <returns>True means loaded successfully. </returns>
        virtual bool ExtractSingleFileToData(const std::string& zipFilePath, const std::string innerFilepath, std::vector<unsigned char>& data, std::vector<std::string>& errors);

        /// <summary>
        /// Extracts a single file and reads it back in memory (directly from file).
        /// This is a binary version and gives back the uncompressed version.
        /// By binary version this will be the default binary version not for particular data types.
        /// </summary>
        /// <param name="zipFilePath">Location of the zip file. </param>
        /// <param name="innerFilepath">Location of the file with the zip. Case-Sensitive! </param>
        /// <param name="data">If found and loaded this is the data. </param>
        /// <param name="errors">If not loaded this will be the reason why. </param>
        /// <returns>True means loaded successfully. </returns>
        virtual bool ExtractSingleBinaryFileToData(const std::string& zipFilePath, const std::string innerFilepath, std::vector<unsigned char>& data, std::vector<std::string>& errors);
    private:
        /// <summary>
        /// Reads file contents into Stream.
        /// </summary>
        /// <param name="inputFilepath">File path.</param>
        /// <param name="errors">Errors if any. </param>
        /// <returns>Stream of data. </returns>
        std::ifstream ReadFileContentsToBinaryStream(const std::string& inputFilepath, std::vector<std::string>& errors);

        /// <summary>
        /// Add file to a given zip.
        /// </summary>
        /// <param name="zipFile">Zip file to add to. </param>
        /// <param name="filename">Filename of the file to add. </param>
        /// <param name="entryname">Where to add the file in the zip. </param>
        /// <param name="errors">Errors if any. </param>
        /// <returns>True means added. </returns>
        bool AddFileToZip(zipFile zipFile, std::string filename, std::string entryname, std::vector<std::string>& errors);

        /// <summary>
        /// Create new zip.
        /// </summary>
        /// <param name="zipname">Zip file name. Will always be .zip. </param>
        /// <param name="filenames">Filenames to add to the zip.</param>
        /// <param name="filenamesRelativeToDirectory">Where to place the files in the zip (one to one with the filenames). </param>
        /// <param name="errors">Errors if any. </param>
        /// <returns>True means created. </returns>
        bool CreateZip(std::string zipname, const std::vector<std::string>& filenames, const std::vector<std::string>& filenamesRelativeToDirectory, std::vector<std::string>& errors);

        /// <summary>
        /// Extract file from zip.
        /// </summary>
        /// <param name="zip">File to extract. </param>
        /// <param name="destination">Where to extract. </param>
        /// <param name="errors">Errors if any. </param>
        /// <returns>True means success. </returns>
        bool ExtractFileFromZip(unzFile zip, std::string destination, std::vector<std::string>& errors);
    };
}
