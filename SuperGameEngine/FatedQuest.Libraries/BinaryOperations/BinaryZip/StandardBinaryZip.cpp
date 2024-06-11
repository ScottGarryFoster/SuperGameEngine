#include "StandardBinaryZip.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <string>
#include "minizip/zip.h"
#include "minizip/mztools.h"
#include "minizip/unzip.h"
#include <minizip/ioapi.h>
#include "../../Logging/Logger.h"
#include "../../StandardCLibrary/LibraryIncludes.h"

using namespace BinaryOperations;
using namespace StandardCLibrary;
namespace FileSystem = std::filesystem;

bool StandardBinaryZip::FileToBinary(const std::string& input, const std::string& output, std::vector<std::string>& errors)
{
    // Do not allow methods to do anything if there are existing errors.
    if (errors.size() > 0)
    {
        return false;
    }

    std::ifstream readFile = ReadFileContentsToBinaryStream(input, errors);
    if (errors.size() > 0)
    {
        return false;
    }

    std::vector<char> buffer((std::istreambuf_iterator<char>(readFile)), std::istreambuf_iterator<char>());
    uLong sourceLength = buffer.size();
    uLong destinationLength = compressBound(sourceLength);

    std::vector<unsigned char> compressedData(destinationLength);

    int result = compress(compressedData.data(), &destinationLength, reinterpret_cast<unsigned char*>(buffer.data()), sourceLength);
    if (result != Z_OK)
    {
        errors.push_back("Compression failed!");
        return false;
    }

    std::ofstream outFile(output, std::ios::binary);
    if (!outFile)
    {
        errors.push_back("Error opening destination file!");
        return false;
    }

    outFile.write(reinterpret_cast<char*>(compressedData.data()), destinationLength);
    outFile.close();

    return true;
}

bool StandardBinaryZip::BinaryToFile(const std::string& input, const std::string& output, std::vector<std::string>& errors)
{
    // Do not allow methods to do anything if there are existing errors.
    if (errors.size() > 0)
    {
        return false;
    }

    std::ifstream readFile = ReadFileContentsToBinaryStream(input, errors);
    if (errors.size() > 0)
    {
        return false;
    }

    std::vector<char> buffer((std::istreambuf_iterator<char>(readFile)), std::istreambuf_iterator<char>());
    uLong sourceLength = buffer.size();

    // This is unknown at this stage, we perform a loop below to figure this out.
    uLong destinationLength = sourceLength * 2;

    std::vector<unsigned char> decompressedData(destinationLength);

    // Keep increasing the buffer until it is big enough.
    int result;
    while ((result = uncompress(decompressedData.data(), &destinationLength, reinterpret_cast<unsigned char*>(buffer.data()), sourceLength)) == Z_BUF_ERROR)
    {
        destinationLength *= 2;
        decompressedData.resize(destinationLength);

        if (result != Z_BUF_ERROR && result != Z_OK)
        {
            break;
        }
    }
    
    // The last loop above we might not have increased this.
    decompressedData.resize(destinationLength);

    // We catch the buffer size in the loop.
    if (result != Z_OK)
    {
        errors.push_back("Decompression failed!");
        return false;
    }

    std::ofstream outFile(output, std::ios::binary);
    if (!outFile)
    {
        errors.push_back("Error opening destination file!");
        return false;
    }

    outFile.write(reinterpret_cast<char*>(decompressedData.data()), destinationLength);
    outFile.close();

    return true;
}

bool StandardBinaryZip::DirectoryToBinary(const std::string& input, const std::string& output, std::vector<std::string>& errors)
{
    // Do not allow methods to do anything if there are existing errors.
    if (errors.size() > 0)
    {
        return false;
    }

    if (!File::Exists(input) || !Directory::Exists(input))
    {
        errors.push_back("Source directory does not exist or is not a directory.");
        return false;
    }

    Directory::CreateDirectories(output);

    std::vector<std::string> filenames;
    std::vector<std::string> filenamesRelativeToDirectory;
    for (const auto& entry : FileSystem::recursive_directory_iterator(input)) 
    {
        if (FileSystem::is_regular_file(entry.path()))
        {
            FileSystem::path relativePath = FileSystem::relative(entry.path(), input);
            FileSystem::path destPath = output / relativePath;
            FileSystem::create_directories(destPath.parent_path());

            std::string filepath = destPath.string() + ".gz";
            std::string relativeFilepath = relativePath.string() + ".gz";
            if (FileToBinary(entry.path().string(), destPath.string() + ".gz", errors))
            {
                filenames.push_back(filepath);
                filenamesRelativeToDirectory.push_back(relativeFilepath);
            }
            else
            {
                return false;
            }
        }
    }

    std::string zipPath = output + ".zip";
    CreateZip(zipPath.c_str(), filenames, filenamesRelativeToDirectory, errors);

    return true;
}

bool BinaryOperations::StandardBinaryZip::BinaryDirectoryToDirectory(const std::string& input, const std::string& output, std::vector<std::string>& errors)
{
    // Do not allow methods to do anything if there are existing errors.
    if (errors.size() > 0)
    {
        return false;
    }

    if (!File::Exists(input) || !Directory::Exists(input))
    {
        errors.push_back("Source directory does not exist or is not a directory.");
        return false;
    }

    Directory::CreateDirectories(output);

    for (const auto& entry : FileSystem::recursive_directory_iterator(input))
    {
        if (FileSystem::is_regular_file(entry.path()) && entry.path().extension() == ".gz")
        {
            FileSystem::path relativePath = FileSystem::relative(entry.path(), input);
            FileSystem::path destPath = output / relativePath;

            // Remove .gz extension
            destPath.replace_extension("");

            FileSystem::create_directories(destPath.parent_path());
            if (!BinaryToFile(entry.path().string(), destPath.string(), errors))
            {
                return false;
            }
        }
    }


    return true;
}

bool StandardBinaryZip::DirectoryToZip(const std::string& input, const std::string& output, std::vector<std::string>& errors)
{
    // Do not allow methods to do anything if there are existing errors.
    if (errors.size() > 0)
    {
        return false;
    }

    if (!File::Exists(input) || !Directory::Exists(input))
    {
        errors.push_back("Source directory does not exist or is not a directory.");
        return false;
    }

    std::string zipname = output + ".zip";
    zipFile zf = zipOpen(zipname.c_str(), APPEND_STATUS_CREATE);
    if (zf == NULL) 
    {
        errors.push_back("Could not create zip file " + zipname);
        return false;
    }

    std::vector<std::string> filenames;
    std::vector<std::string> filenamesRelativeToDirectory;
    for (const auto& entry : FileSystem::recursive_directory_iterator(input)) {
        if (FileSystem::is_regular_file(entry.path())) {
            FileSystem::path relativePath = FileSystem::relative(entry.path(), input);
            FileSystem::path destPath = output / relativePath;


            std::string filepath = entry.path().string();
            filenames.push_back(filepath);
            filenamesRelativeToDirectory.push_back(relativePath.string());
            AddFileToZip(zf, filepath, relativePath.string(), errors);
        }
    }

    zipClose(zf, NULL);

    return true;
}

bool StandardBinaryZip::ZipToDirectory(const std::string& input, const std::string& output, std::vector<std::string>& errors)
{
    // Do not allow methods to do anything if there are existing errors.
    if (errors.size() > 0)
    {
        return false;
    }

    const char* zipname = input.c_str();
    unzFile uf = unzOpen(zipname);
    if (uf == NULL)
    {
        errors.push_back("Could not open zip file " + *zipname);
        return false;
    }

    std::string dirname = output.c_str();
    if(!Directory::CreateDirectories(dirname))
    {
        errors.push_back("Could not create directory " + dirname);
        unzClose(uf);
        return false;
    }

    if (unzGoToFirstFile(uf) != UNZ_OK)
    {
        errors.push_back("Could not find files in zip archive " + *zipname);
        unzClose(uf);
        return false;
    }

    do
    {
        char filename_inzip[256];
        unz_file_info file_info;
        if (unzGetCurrentFileInfo(uf, &file_info, filename_inzip, sizeof(filename_inzip), NULL, 0, NULL, 0) != UNZ_OK)
        {
            errors.push_back("Could not read file info");
            unzClose(uf);
            return false;
        }

        // Create full path for the output file
        char filepath[512];
        snprintf(filepath, sizeof(filepath), "%s/%s", dirname, filename_inzip);

        std::string filepathAsString = dirname + "\\" + filename_inzip;

        // Create directories for nested files
        std::string directoryPath = filepathAsString.substr(0, filepathAsString.find_last_of("/\\"));
        Directory::CreateDirectories(directoryPath);

        if (!ExtractFileFromZip(uf, filepathAsString, errors))
        {
            errors.push_back("Could not extract file " + *filepath);
            unzClose(uf);
            return false;
        }

    } while (unzGoToNextFile(uf) == UNZ_OK);

    unzClose(uf);
    return false;
}

bool BinaryOperations::StandardBinaryZip::DirectoryToZipWithFileToBinary(const std::string& input, const std::string& output, std::vector<std::string>& errors)
{
    // Do not allow methods to do anything if there are existing errors.
    if (errors.size() > 0)
    {
        return false;
    }

    if (!File::Exists(input) || !Directory::Exists(input))
    {
        errors.push_back("Source directory does not exist or is not a directory.");
        return false;
    }

    if (!Directory::CreateDirectories(output))
    {
        errors.push_back("Could not create directory " + output);
        return false;
    }

    std::string zipname = output + ".zip";
    zipFile zf = zipOpen(zipname.c_str(), APPEND_STATUS_CREATE);
    if (zf == NULL)
    {
        errors.push_back("Could not create zip file " + zipname);
        return false;
    }

    std::vector<std::string> filenames;
    std::vector<std::string> filenamesRelativeToDirectory;
    for (const auto& entry : FileSystem::recursive_directory_iterator(input))
    {
        if (File::IsFile(entry.path().string()))
        {
            FileSystem::path relativePath = FileSystem::relative(entry.path(), input);
            FileSystem::path destPath = output / relativePath;

            std::string directory = destPath.parent_path().string();
            if (!Directory::CreateDirectories(directory))
            {
                errors.push_back("Could not create directory " + directory);
                zipClose(zf, NULL);
                return false;
            }

            std::string filepath = destPath.string() + ".gz";
            if (FileToBinary(entry.path().string(), destPath.string() + ".gz", errors))
            {
                filenames.push_back(filepath);
                filenamesRelativeToDirectory.push_back(relativePath.string() + ".gz");
                AddFileToZip(zf, filepath, relativePath.string() + ".gz", errors);
            }
            else
            {
                errors.push_back("Could not convert file to binary: " + entry.path().string());
                return false;
            }
        }
    }

    zipClose(zf, NULL);
    if (!Directory::RemoveAll(output))
    {
        errors.push_back("Could not delete directory after zipping.");
        return false;
    }

    return true;
}

bool StandardBinaryZip::ZipWithBinaryToDirectoryToFile(const std::string& input, const std::string& output, std::vector<std::string>& errors)
{
    // Do not allow methods to do anything if there are existing errors.
    if (errors.size() > 0)
    {
        return false;
    }

    const char* zipname = input.c_str();
    unzFile uf = unzOpen(zipname);
    if (uf == NULL)
    {
        errors.push_back("Could not open zip file " + *zipname);
        return false;
    }

    std::string dirname = output.c_str();
    if (!Directory::CreateDirectories(dirname) != 0)
    {
        errors.push_back("Could not create directory " + dirname);
        unzClose(uf);
        return -1;
    }

    if (unzGoToFirstFile(uf) != UNZ_OK)
    {
        errors.push_back("Could not find files in zip archive " + *zipname);
        unzClose(uf);
        return -1;
    }

    do
    {
        char filename_inzip[256];
        unz_file_info file_info;
        if (unzGetCurrentFileInfo(uf, &file_info, filename_inzip, sizeof(filename_inzip), NULL, 0, NULL, 0) != UNZ_OK)
        {
            errors.push_back("Could not read file info");
            unzClose(uf);
            return false;
        }

        // Create full path for the output file
        char filepath[512];
        snprintf(filepath, sizeof(filepath), "%s/%s", dirname, filename_inzip);
        std::string outFilename = dirname + "\\" + filename_inzip;

        // Create directories for nested files
        std::string directoryPath = outFilename.substr(0, outFilename.find_last_of("/\\"));
        if (!Directory::CreateDirectories(directoryPath) != 0)
        {
            errors.push_back("Could not create directory " + directoryPath);
            unzClose(uf);
            return false;
        }

        if (!ExtractFileFromZip(uf, outFilename, errors))
        {
            errors.push_back("Could not extract file " + outFilename);
            unzClose(uf);
            return false;
        }

        std::string finalFileName = outFilename.substr(0, outFilename.find_last_of(".gz") - 2);
        if (BinaryToFile(outFilename, finalFileName, errors))
        {
            if (!File::Delete(outFilename))
            {
                errors.push_back("Could not delete file " + outFilename);
                unzClose(uf);
                return false;
            }
        }
        else
        {
            errors.push_back("Could not deconvert file from binary " + outFilename);
            unzClose(uf);
            return false;
        }

    } while (unzGoToNextFile(uf) == UNZ_OK);

    unzClose(uf);
    return false;
}

std::ifstream StandardBinaryZip::ReadFileContentsToBinaryStream(const std::string& input, std::vector<std::string>& errors)
{
    std::ifstream inFileStream;
    if (!File::Exists(input) && !File::IsFile(input))
    {
        errors.push_back("File does not exist: " + input);
        return inFileStream;
    }

    inFileStream = std::ifstream(input, std::ios::binary);
    if (!inFileStream)
    {
        errors.push_back("Could not open file location: " + input);
        return inFileStream;
    }
    return inFileStream;
}

bool StandardBinaryZip::ExtractFileFromZip(unzFile uf, std::string filename, std::vector<std::string>& errors)
{
    char buffer[4096];
    int err;

    if (unzOpenCurrentFile(uf) != UNZ_OK)
    {
        errors.push_back("Could not open zip");
        return false;
    }

    FILE* file;
    errno_t error = fopen_s(&file, filename.c_str(), "wb");
    if (error != 0)
    {
        errors.push_back("Could not open file in zip " + filename);
        return false;
    }


    do {
        err = unzReadCurrentFile(uf, buffer, sizeof(buffer));
        if (err < 0)
        {
            errors.push_back("Error " + std::to_string(err) + " reading file " + filename);
            fclose(file);
            unzCloseCurrentFile(uf);
            return false;
        }

        if (err > 0)
        {
            fwrite(buffer, err, 1, file);
        }
    } while (err > 0);

    fclose(file);
    unzCloseCurrentFile(uf);

    return true;
}



bool BinaryOperations::StandardBinaryZip::AddFileToZip(zipFile zipFile, std::string filename, std::string entryname, std::vector<std::string>& errors)
{
    FILE* file;
    errno_t err = fopen_s(&file, filename.c_str(), "rb");
    if (err != 0)
    {
        errors.push_back("Could not open zip " + filename);
        return false;
    }


    zip_fileinfo zi = { 0 };
    zipOpenNewFileInZip(zipFile, entryname.c_str(), &zi, NULL, 0, NULL, 0, NULL, Z_DEFLATED, Z_DEFAULT_COMPRESSION);

    char buffer[4096];
    size_t bytes_read;
    size_t element = 1;
    while ((bytes_read = fread(buffer, element, sizeof(buffer), file)) > 0)
    {
        unsigned int size = (unsigned int)bytes_read;
        zipWriteInFileInZip(zipFile, buffer, size);
    }

    zipCloseFileInZip(zipFile);
    fclose(file);

    return true;
}

bool StandardBinaryZip::CreateZip(
    std::string zipname, 
    const std::vector<std::string>& filenames,
    const std::vector<std::string>& filenamesRelativeToDirectory,
    std::vector<std::string>& errors)
{
    zipFile zf = zipOpen(zipname.c_str(), APPEND_STATUS_CREATE);
    if (zf == NULL)
    {
        errors.push_back("Could not create zip file " + zipname);
        return false;
    }

    for (size_t i = 0; i < filenames.size(); i++)
    {
        if (!AddFileToZip(zf, filenames[i], filenamesRelativeToDirectory[i], errors))
        {
            errors.push_back("Failed to add file %s to zip " + filenames[i]);
            zipClose(zf, NULL);
            return false;
        }
    }

    zipClose(zf, NULL);
    return true;
}