#include "LibraryIncludes.h"
#include "../PackageFileProvider/FilepathCollectionFromExternalSource.h"
#include <chrono>
using namespace std::chrono;

using namespace StandardCLibrary;
using namespace PackageFileProvider;

namespace PackageFileProviderTests
{
    class FilepathCollectionTests : public ::testing::Test
    {
    public:
        FilepathCollectionTests()
        {

        }

    protected:

        void SetUp() override
        {
        }

        void TearDown() override
        {
        }

        std::shared_ptr<FilepathCollection> ConstructNew(const std::vector<std::string>& paths)
        {
            // This method exists so that the implementation could be switched out in future.
            std::shared_ptr<FilepathCollection> filepaths =
                std::make_shared<FilepathCollectionFromExternalSource>(paths);

            return filepaths;
        }
    };

    TEST_F(FilepathCollectionTests, GetAllFiles_ReturnsFilepaths_WhenGivenPathsOnConstruction)
    {
        std::vector<std::string> given = std::vector<std::string>();
        given.push_back("MyFolder/MyFilepath.txt");
        given.push_back("MyFolder/MyFilepath2.txt");
        std::shared_ptr<FilepathCollection> testClass = ConstructNew(given);

        const std::vector<std::string>& actual = testClass->GetAllFiles();

        ASSERT_EQ(given, actual);
    }

#pragma region Exists

    TEST_F(FilepathCollectionTests, Exists_ReturnsTrue_WhenPathIsInTopDirectory)
    {
        // Arrange
        std::string expected = "MyFilepath3.txt";

        std::vector<std::string> given = std::vector<std::string>();
        given.push_back("MyFilepath.txt");
        given.push_back("InAFolder/" + expected);
        given.push_back(expected);

        std::shared_ptr<FilepathCollection> testClass = ConstructNew(given);

        // Act
        bool actual = testClass->Exists(expected);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(FilepathCollectionTests, Exists_ReturnsTrue_WhenPathMatchesGiven)
    {
        // Arrange
        std::string expected = "MyFolder/MyFilepath3.txt";

        std::vector<std::string> given = std::vector<std::string>();
        given.push_back("MyFolder/MyFilepath.txt");
        given.push_back("MyFolder/MyFilepath2.txt");
        given.push_back(expected);

        std::shared_ptr<FilepathCollection> testClass = ConstructNew(given);

        // Act
        bool actual = testClass->Exists(expected);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(FilepathCollectionTests, Exists_ReturnsTrue_WhenDirectoryCaseDoesNotMatch)
    {
        // Arrange
        std::string givenDirectory = "MyFoLdEr";
        std::string givenPath = givenDirectory + "/MyFilepath3.txt";
        std::string constrctedDirectory = "MyFolder";
        std::string constructedFilePath = constrctedDirectory + "/MyFilepath3.txt";

        std::vector<std::string> given = std::vector<std::string>();
        given.push_back("MyFolder/MyFilepath.txt");
        given.push_back("MyFolder/MyFilepath2.txt");
        given.push_back(constructedFilePath);

        std::shared_ptr<FilepathCollection> testClass = ConstructNew(given);

        // Act
        bool actual = testClass->Exists(givenPath);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(FilepathCollectionTests, Exists_ReturnsTrue_WhenFilepathCaseDoesNotMatch)
    {
        // Arrange
        std::string givenFilePath = "MyFiLePaTh3.txt";
        std::string givenFullPath = "MyFolder/" + givenFilePath;
        std::string constructedFilePath = "MyFilepath3.txt";
        std::string constructedFullPath = "MyFolder/" + constructedFilePath;

        std::vector<std::string> given = std::vector<std::string>();
        given.push_back("MyFolder/MyFilepath.txt");
        given.push_back("MyFolder/MyFilepath2.txt");
        given.push_back(constructedFullPath);

        std::shared_ptr<FilepathCollection> testClass = ConstructNew(given);

        // Act
        bool actual = testClass->Exists(givenFullPath);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(FilepathCollectionTests, Exists_ReturnsFalse_WhenPathIsNotInList)
    {
        // Arrange
        std::string testPath = "MyFolder/MyFilepath3.txt";

        std::vector<std::string> given = std::vector<std::string>();
        given.push_back("MyFolder/MyFilepath.txt");
        given.push_back("MyFolder/MyFilepath2.txt");

        std::shared_ptr<FilepathCollection> testClass = ConstructNew(given);

        // Act
        bool actual = testClass->Exists(testPath);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(FilepathCollectionTests, Exists_ReturnsFalse_WhenFilepathIsInAnotherDirectoryThanGiven)
    {
        // Arrange
        std::string pathGiven = "MyFolder/MyFilepath3.txt";
        std::string pathFound = "InAFolder/MyFilepath3.txt";

        std::vector<std::string> given = std::vector<std::string>();
        given.push_back("MyFilepath.txt");
        given.push_back(pathFound);

        std::shared_ptr<FilepathCollection> testClass = ConstructNew(given);

        // Act
        bool actual = testClass->Exists(pathGiven);

        // Assert
        ASSERT_FALSE(actual);
    }

#ifdef _PERFORMANCETESTS
    TEST_F(FilepathCollectionTests, Exists_ExecutesExistsQuickly_WhenGivenMillionsOfEntries)
    {
        // Arrange
        std::string expected = "MyFolder/MyFilepath3.txt";

        std::vector<std::string> given = std::vector<std::string>();
        given.push_back("MyFolder/MyFilepath2.txt");
        given.push_back("MyFolder/MyFilepath.txt");

        for (size_t i = 0; i < 1000; ++i)
        {
            for (size_t j = 0; j < 1000; ++j)
            {
                given.push_back(
                    "MyOtherFolder/MyFilepath_" + 
                    std::to_string(i) + "_" + 
                    std::to_string(j) + ".txt");
            }

            // Mix the one we are trying to find in the list.
            if (i == 753)
            {
                given.push_back(expected);
            }
        }

        std::shared_ptr<FilepathCollection> testClass = ConstructNew(given);

        // Act
        auto start = high_resolution_clock::now();
        bool actual = testClass->Exists(expected);
        auto stop = high_resolution_clock::now();

        // Assert
        auto duration = duration_cast<microseconds>(stop - start);
        // Expected > Actual
        ASSERT_GT(25, duration.count());
    }
#endif // _PERFORMANCETESTS

#pragma endregion

#pragma region GetAllFilesInDirectory

    TEST_F(FilepathCollectionTests, GetAllFilesInDirectory_ReturnsFilesInDirectory_WhenGivenFilesInDirectory)
    {
        // Arrange
        std::string testPath = "MyFolder";

        std::vector<std::string> given = std::vector<std::string>();
        given.push_back("MyFolder/MyFilepath.txt");
        given.push_back("MyOtherFolder/MyFilepath3.txt");
        given.push_back("MyFolder/MyFilepath2.txt");
        given.push_back("MyOtherFolder/MyFilepath4.txt");

        std::vector<std::string> expected = std::vector<std::string>();
        expected.push_back("MyFilepath.txt");
        expected.push_back("MyFilepath2.txt");

        std::shared_ptr<FilepathCollection> testClass = ConstructNew(given);

        // Act
        const std::vector<std::string> actual = testClass->GetAllFilesInDirectory(testPath);

        // Assert
        ASSERT_EQ(2, actual.size());
        ASSERT_EQ(expected, actual);
    }

    TEST_F(FilepathCollectionTests, GetAllFilesInDirectory_ReturnsFilesInDirectory_WhenGivenASubdirectoryOfASubdirectory)
    {
        // Arrange
        std::string testPath = "MyOtherFolder/MySubFolder/MySubSubFolder";

        std::vector<std::string> expected = std::vector<std::string>();
        expected.push_back("MyExpectedPath1.txt");
        expected.push_back("MyExpectedPath2.txt");

        std::vector<std::string> given = std::vector<std::string>();
        given.push_back("MyFolder/MyFilepath.txt");
        given.push_back("MyOtherFolder/MyFilepath3.txt");
        given.push_back("MyFolder/MyFilepath2.txt");
        given.push_back("MyOtherFolder/MySubFolder/NotTheCorrectDirectory/MyFilepath8.txt");
        given.push_back(testPath + "/" + expected.at(0));
        given.push_back("MyOtherFolder/MyFilepath4.txt");
        given.push_back("MyFolder/MySubFolder/NotTheCorrectDirectory/MyFilepath7.txt");
        given.push_back("MyFolder/MySubFolder/MyFilepath5.txt");
        given.push_back("MyOtherFolder/MySubFolder/MyFilepath6.txt");
        given.push_back(testPath + "/" + expected.at(1));


        std::shared_ptr<FilepathCollection> testClass = ConstructNew(given);

        // Act
        const std::vector<std::string> actual = testClass->GetAllFilesInDirectory(testPath);

        // Assert
        ASSERT_EQ(2, actual.size());
        ASSERT_EQ(expected, actual);
    }

    TEST_F(FilepathCollectionTests, GetAllFilesInDirectory_ReturnsFilesInDirectory_WhenGivenEndsInAForwardSlash)
    {
        // Arrange
        std::string testPath = "MyFolder/";

        std::vector<std::string> given = std::vector<std::string>();
        given.push_back("MyFolder/MyFilepath.txt");
        given.push_back("MyOtherFolder/MyFilepath3.txt");
        given.push_back("MyFolder/MyFilepath2.txt");
        given.push_back("MyOtherFolder/MyFilepath4.txt");

        std::vector<std::string> expected = std::vector<std::string>();
        expected.push_back("MyFilepath.txt");
        expected.push_back("MyFilepath2.txt");

        std::shared_ptr<FilepathCollection> testClass = ConstructNew(given);

        // Act
        const std::vector<std::string> actual = testClass->GetAllFilesInDirectory(testPath);

        // Assert
        ASSERT_EQ(2, actual.size());
        ASSERT_EQ(expected, actual);
    }

    TEST_F(FilepathCollectionTests, GetAllFilesInDirectory_ReturnsFilesInDirectory_WhenCaseOfDirectoryDoesNotMatch)
    {
        // Arrange
        std::string testPath = "MYFOLDeR";
        std::string givenDirectory = "MyFolder";
        ASSERT_NE(testPath, givenDirectory);

        std::vector<std::string> given = std::vector<std::string>();
        given.push_back(givenDirectory + "/MyFilepath.txt");
        given.push_back("MyOtherFolder/MyFilepath3.txt");
        given.push_back(givenDirectory + "/MyFilepath2.txt");
        given.push_back("MyOtherFolder/MyFilepath4.txt");

        std::vector<std::string> expected = std::vector<std::string>();
        expected.push_back("MyFilepath.txt");
        expected.push_back("MyFilepath2.txt");

        std::shared_ptr<FilepathCollection> testClass = ConstructNew(given);

        // Act
        const std::vector<std::string> actual = testClass->GetAllFilesInDirectory(testPath);

        // Assert
        ASSERT_EQ(2, actual.size());
        ASSERT_EQ(expected, actual);
    }

#pragma endregion
}