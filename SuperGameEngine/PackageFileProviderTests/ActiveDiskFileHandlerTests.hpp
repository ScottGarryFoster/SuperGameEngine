#include "LibraryIncludes.h"
#include "../PackageFileProvider/LibraryIncludes.h"
#include "../PackageFileProvider/ActiveDiskFileHandler.h"
#include <chrono>
using namespace std::chrono;

using namespace StandardCLibrary;
using namespace PackageFileProvider;

namespace PackageFileProviderTests
{
    class ActiveDiskFileHandlerTests : public ::testing::Test
    {
    public:
        ActiveDiskFileHandlerTests()
        {

        }

    protected:

        std::string m_topLevelPath;
        std::shared_ptr<FileHandler> m_testClass;

        void SetUp() override
        {
            std::string productsPath = TopLevelDirectories::GetProductsFolder();

            // Test folder is a few levels deeper than regular debug.
            // This allows these tests to work in VS with the exe remaining where it is.
            std::vector<std::string> splitPath = StringHelpers::Split("\\", productsPath);
            splitPath.pop_back();
            splitPath.pop_back();
            splitPath.pop_back();
            splitPath.pop_back();
            std::string newProductsPath = StringHelpers::Join("\\", splitPath);

            m_topLevelPath = newProductsPath + "\\Products\\Engine\\_CodeTestFiles\\PackageFileProviderTests";
            m_testClass = std::make_shared<ActiveDiskFileHandler>(m_topLevelPath);
        }

        void TearDown() override
        {
            m_testClass.reset();
        }

        /// <summary>
        /// Returns True if the two vectors contain the same thing.
        /// Does not care about order.
        /// </summary>
        template<typename T>
        bool AreEquivalent(const std::vector<T>& left, const std::vector<T>& right)
        {
            if (left.size() != right.size())
            {
                return false;
            }

            for (const T& item : left)
            {
                if (!VectorHelpers::Contains(right, item))
                {
                    return false;
                }
            }
        }
    };

    /// <summary>
    /// Ensures test files are in place for other tests,
    /// if this test fails all others will likely fail.
    /// </summary>
    TEST_F(ActiveDiskFileHandlerTests, FileExists_ReturnsTrue_WhenGivenTestFolderAndTestFile)
    {
        std::string given = "BasicTextFile.txt";
        std::shared_ptr<const FilepathCollection> filePathCollection =
            m_testClass->GetFilePathInfo();
        ASSERT_TRUE(filePathCollection) << "FilepathCollection is not set.";

        bool actual = filePathCollection->Exists(given);

        ASSERT_TRUE(actual);
    }

#pragma region GetAllFiles
    TEST_F(ActiveDiskFileHandlerTests, GetAllFiles_ReturnsAllTestFiles_WhenACollectionOfTestFilesExist)
    {
        // Arrange
        std::shared_ptr<const FilepathCollection> filePathCollection =
            m_testClass->GetFilePathInfo();
        ASSERT_TRUE(filePathCollection) << "FilepathCollection is not set.";

        std::vector<std::string> expected;
        expected.push_back("BasicTextFile.txt");
        expected.push_back("ComplexFile.txt");
        expected.push_back("TestDirectory1\\WithinTestDirectory.txt");
        expected.push_back("TestDirectory1\\InnerDirectory1\\WithinInnerDirectory1.txt");
        expected.push_back("TestDirectory1\\InnerDirectory2\\WithinInnerDirectory2.txt");

        // Act
        std::vector<std::string> actual = filePathCollection->GetAllFiles();

        // Assert
        ASSERT_EQ(expected.size(), actual.size());
        for (const std::string& path : actual)
        {
            ASSERT_TRUE(VectorHelpers::ContainsString(expected, path)) 
                << "Actual path not found in expected: " + path;
        }
    }

    TEST_F(ActiveDiskFileHandlerTests, GetAllFiles_ReturnsNewFile_WhenNewFileIsCreated)
    {
        // Arrange
        std::shared_ptr<const FilepathCollection> filePathCollection =
            m_testClass->GetFilePathInfo();
        ASSERT_TRUE(filePathCollection) << "FilepathCollection is not set.";

        std::vector<std::string> prepared;
        prepared.push_back("BasicTextFile.txt");
        prepared.push_back("ComplexFile.txt");
        prepared.push_back("TestDirectory1\\WithinTestDirectory.txt");
        prepared.push_back("TestDirectory1\\InnerDirectory1\\WithinInnerDirectory1.txt");
        prepared.push_back("TestDirectory1\\InnerDirectory2\\WithinInnerDirectory2.txt");

        ASSERT_TRUE(AreEquivalent(Directory::GetFilesOnlyStd(m_topLevelPath, true), prepared)) <<
            "Did not find the same files on disk as expected. Ensure these match";

        ASSERT_TRUE(
            File::CopyFileToDirectory(m_topLevelPath + "\\BasicTextFile.txt",
            m_topLevelPath + "\\TestDirectory1",
            CopyFileOptions::OverwriteExistingFile))
            << "Could not copy file.";

        // Act
        std::vector<std::string> actual = filePathCollection->GetAllFiles();

        // Assert
        prepared.push_back("TestDirectory1\\BasicTextFile.txt");
        bool answer = AreEquivalent(prepared, actual);
        ASSERT_TRUE(File::Delete(m_topLevelPath + "\\TestDirectory1\\BasicTextFile.txt"))
            << "Could not Delete new file.";
        ASSERT_TRUE(answer) <<
            "Did not find the new copied file";
    }

#pragma endregion

#pragma region GetAllFilesInDirectory

    TEST_F(ActiveDiskFileHandlerTests, GetAllFilesInDirectory_ReturnsAllTestFiles_WhenACollectionOfTestFilesExist)
    {
        // Arrange
        std::shared_ptr<const FilepathCollection> filePathCollection =
            m_testClass->GetFilePathInfo();
        ASSERT_TRUE(filePathCollection) << "FilepathCollection is not set.";

        std::vector<std::string> expected;
        expected.push_back("WithinTestDirectory.txt");
        expected.push_back("InnerDirectory1\\WithinInnerDirectory1.txt");
        expected.push_back("InnerDirectory2\\WithinInnerDirectory2.txt");

        // Act
        std::vector<std::string> actual = filePathCollection->GetAllFilesInDirectory("TestDirectory1");

        // Assert
        ASSERT_EQ(expected.size(), actual.size());
        for (const std::string& path : actual)
        {
            ASSERT_TRUE(VectorHelpers::ContainsString(expected, path))
                << "Actual path not found in expected: " + path;
        }
    }

    TEST_F(ActiveDiskFileHandlerTests, GetAllFilesInDirectory_ReturnsNewFile_WhenNewFileIsCreated)
    {
        // Arrange
        std::shared_ptr<const FilepathCollection> filePathCollection =
            m_testClass->GetFilePathInfo();
        ASSERT_TRUE(filePathCollection) << "FilepathCollection is not set.";

        std::vector<std::string> prepared;
        prepared.push_back("WithinTestDirectory.txt");
        prepared.push_back("InnerDirectory1\\WithinInnerDirectory1.txt");
        prepared.push_back("InnerDirectory2\\WithinInnerDirectory2.txt");

        ASSERT_TRUE(AreEquivalent(
            Directory::GetFilesOnlyStd(m_topLevelPath + "\\TestDirectory1", true), prepared)) <<
            "Did not find the same files on disk as expected. Ensure these match";

        ASSERT_TRUE(
            File::CopyFileToDirectory(m_topLevelPath + "\\BasicTextFile.txt",
                m_topLevelPath + "\\TestDirectory1\\InnerDirectory1",
                CopyFileOptions::OverwriteExistingFile))
            << "Could not copy file.";

        // Act
        std::vector<std::string> actual = filePathCollection->GetAllFilesInDirectory("TestDirectory1");

        // Assert
        prepared.push_back("InnerDirectory1\\BasicTextFile.txt");
        bool answer = AreEquivalent(prepared, actual);
        ASSERT_TRUE(File::Delete(m_topLevelPath + "\\TestDirectory1\\InnerDirectory1\\BasicTextFile.txt"))
            << "Could not Delete new file.";
        ASSERT_TRUE(answer) <<
            "Did not find the new copied file";
    }

#pragma endregion

#pragma region Exists

    TEST_F(ActiveDiskFileHandlerTests, FileExists_ReturnsTrue_WhenFileExistsOnDisk)
    {
        // Arrange
        std::string given = "BasicTextFile.txt";
        std::shared_ptr<const FilepathCollection> filePathCollection =
            m_testClass->GetFilePathInfo();
        ASSERT_TRUE(filePathCollection) << "FilepathCollection is not set.";

        ASSERT_TRUE(File::Exists(m_topLevelPath + "\\" + given))
            << "File does not exist on disk";

        // Act
        bool actual = filePathCollection->Exists(given);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(ActiveDiskFileHandlerTests, FileExists_ReturnsFalse_WhenFileDoesNotExistOnDisk)
    {
        // Arrange
        std::string given = "DOESNOTEXIST.txt";
        std::shared_ptr<const FilepathCollection> filePathCollection =
            m_testClass->GetFilePathInfo();
        ASSERT_TRUE(filePathCollection) << "FilepathCollection is not set.";

        ASSERT_FALSE(File::Exists(m_topLevelPath + "\\" + given))
            << "File exists on disk";

        ASSERT_TRUE(
            File::CopyFileToPath(
                m_topLevelPath + "\\BasicTextFile.txt",
                m_topLevelPath + "\\DOESNOTEXIST.txt",
                CopyFileOptions::OverwriteExistingFile))
            << "Could not copy file.";

        // Act
        bool actual = filePathCollection->Exists(given);

        // Assert
        ASSERT_TRUE(File::Delete(m_topLevelPath + "\\DOESNOTEXIST.txt"))
            << "Could not Delete new file.";
        ASSERT_TRUE(actual);
    }

#pragma endregion
}