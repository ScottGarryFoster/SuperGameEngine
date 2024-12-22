#pragma once
#include <string>
#include <vector>

#include "../../../BinaryOperations/BinaryZip/BinaryZip.h"

using namespace FatedQuestLibraries;

namespace FatedQuestLibraries_GamePackage
{
    /// <summary>
    /// A file within a game package.
    /// </summary>
    class StubBinaryZip : public BinaryZip
    {
    public:
        
        virtual bool FileToBinary(
            const std::string& inputFilepath,
            const std::string& outputFilepath,
            std::vector<std::string>& errors) const override { return false; }

        virtual bool BinaryToFile(
            const std::string& inputFilepath,
            const std::string& outputFilepath,
            std::vector<std::string>& errors) const override { return false; }

        virtual bool BinaryToData(
            const std::string& inputFilepath,
            std::vector<unsigned char>& data,
            std::vector<std::string>& errors) const override  { return false; }

        virtual bool DirectoryToBinary(
            const std::string& inputPath,
            const std::string& outputPath,
            std::vector<std::string>& errors) const override { return false; }

        virtual bool BinaryDirectoryToDirectory(
            const std::string& inputPath,
            const std::string& outputPath,
            std::vector<std::string>& errors) const override { return false; }

        virtual bool DirectoryToZip(
            const std::string& inputPath,
            const std::string& outputFilepath,
            std::vector<std::string>& errors) const override { return false; }

        virtual bool ZipToDirectory(
            const std::string& inputFilepath,
            const std::string& outputPath,
            std::vector<std::string>& errors) const override { return false; }

        virtual bool DirectoryToZipWithFileToBinary(
            const std::string& inputPath,
            const std::string& outputFilepath,
            std::vector<std::string>& errors) const override { return false; }

        virtual bool ZipWithBinaryToDirectoryToFile(
            const std::string& inputFilepath,
            const std::string& outputPath,
            std::vector<std::string>& errors) const override { return false; }

        virtual bool ExtractSingleFileToData(
            const std::string& zipFilePath,
            const std::string& innerFilepath,
            std::vector<unsigned char>& data,
            std::vector<std::string>& errors) const override { return false; }

        virtual bool ExtractSingleBinaryFileToData(
            const std::string& zipFilePath,
            const std::string& innerFilepath,
            std::vector<unsigned char>& data,
            std::vector<std::string>& errors) const override { return false; }

        virtual std::vector<std::string> ListFilesInArchive(
            const std::string& filepath,
            std::vector<std::string>& errors) const override { return {}; }
    };
}