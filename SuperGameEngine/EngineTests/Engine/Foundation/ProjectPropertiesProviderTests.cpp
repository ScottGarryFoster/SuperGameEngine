#include "../../../Engine/Engine/Foundation/ProjectPropertiesProvider.h"
#include "../../FatedQuest.Libraries/Logger/AllReferences.h"
#include <memory>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Engine/Foundation/ProjectProperties.h"
#include "../../FatedQuest.Libraries/GamePackageTestMocks/GamePackage/GamePackageMock.h"
#include "../../FatedQuest.Libraries/GamePackageTestMocks/GamePackage/FileSystem/PackageFileSystemFileMock.h"
#include "../../FatedQuest.Libraries/GamePackageTestMocks/GamePackage/FileSystem/PackageFileSystemDirectoryMock.h"
#include "FileHandling/Directory.h"

using namespace SuperGameEngine;
using namespace FatedQuestLibraries;
using namespace SuperGameEngineTests_Mocks;

namespace SuperGameEngineTests_Engine_Foundation
{
    class ProjectPropertiesProviderTests : public ::testing::Test
    {
    public:
        ProjectPropertiesProviderTests()
        {
        }

    protected:

        std::shared_ptr<ProjectPropertiesProvider> m_testClass;
        std::shared_ptr<ConsoleLog> m_logger;
        std::shared_ptr<GamePackageMock> m_gamePackageMock;
        std::shared_ptr<PackageFileSystemFileMock> m_packageFileSystemFileMock;
        std::shared_ptr<PackageFileSystemDirectoryMock> m_packageFileSystemDirectoryMock;

        const char* m_propertiesFileName = "ProjectProperties.uod";

        const char* m_validProjectProperties = "<UniversalObjectData>"
            "<Strings>"
            "<String \"Key\"=\"StartScene\" \"Value\"=\"sceneName.scene\" />"
            "<String \"Key\"=\"WindowTitle\" \"Value\"=\"WindowTitle\" />"
            "</Strings>"
            "</UniversalObjectData>";

        void SetUp() override
        {
            m_logger = std::make_shared<ConsoleLog>();
            if (auto event = Log::GetEvent().lock())
            {
                event->Subscribe(m_logger);
            }

            m_testClass = std::make_shared<ProjectPropertiesProvider>();
            m_gamePackageMock = std::make_shared<GamePackageMock>();
            m_packageFileSystemFileMock = std::make_shared<PackageFileSystemFileMock>();
            m_packageFileSystemDirectoryMock = std::make_shared<PackageFileSystemDirectoryMock>();

            ON_CALL(*m_gamePackageMock, File()).WillByDefault(testing::Return(m_packageFileSystemFileMock));
            ON_CALL(*m_gamePackageMock, Directory()).WillByDefault(testing::Return(m_packageFileSystemDirectoryMock));
        }

        void TearDown() override
        {
            if (auto event = Log::GetEvent().lock())
            {
                event->Unsubscribe(m_logger);
            }
        }
    };

#pragma region LoadProjectProperties

    TEST_F(ProjectPropertiesProviderTests, LoadProjectProperties_ReturnsNothing_WhenNoFileCanBeFound)
    {
        // Arrange
        // Nothing to arrange, File will not exist and no directories will exist.

        // Act
        std::shared_ptr<ProjectProperties> actual = m_testClass->LoadProjectProperties(m_gamePackageMock);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(ProjectPropertiesProviderTests, LoadProjectProperties_ReturnsAValidClass_WhenFileIsInRootAndIsReadableAsXML)
    {
        // Arrange
        EXPECT_CALL(*m_packageFileSystemFileMock, Exists(m_propertiesFileName))
            .WillOnce(testing::Return(true));

        EXPECT_CALL(*m_packageFileSystemFileMock, ReadFileContents(m_propertiesFileName))
            .WillOnce(testing::Return(m_validProjectProperties));

        // Act
        std::shared_ptr<ProjectProperties> actual = m_testClass->LoadProjectProperties(m_gamePackageMock);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(ProjectPropertiesProviderTests, LoadProjectProperties_PassesValuesSuccessfullyToProjectProperties_WhenValidValuesAreGiven)
    {
        // Do not update these to add more parsed values, this purely tests to see if the provider did pass the XML
        // to the project properties successful. Use the actual project properties tests to add new values and test those.

        // Arrange
        EXPECT_CALL(*m_packageFileSystemFileMock, Exists(m_propertiesFileName))
            .WillOnce(testing::Return(true));

        EXPECT_CALL(*m_packageFileSystemFileMock, ReadFileContents(m_propertiesFileName))
            .WillOnce(testing::Return(m_validProjectProperties));

        // Act
        std::shared_ptr<ProjectProperties> actual = m_testClass->LoadProjectProperties(m_gamePackageMock);

        // Assert
        ASSERT_EQ("sceneName.scene", actual->GetStartScene());
        ASSERT_EQ("WindowTitle", actual->GetWindowTitle());
    }

    TEST_F(ProjectPropertiesProviderTests, LoadProjectProperties_LoadValueFromDirectory_WhenRootFileDoesNotExist)
    {
        // Do not update these to add more parsed values, this purely tests to see if the provider did pass the XML
        // to the project properties successful. Use the actual project properties tests to add new values and test those.

        // Arrange


        std::string validDirectory = "MyDirectory";
        std::vector<std::string> givenDirectories = { "Directory", validDirectory, "Another" };

        ON_CALL(*m_packageFileSystemDirectoryMock, ListDirectories(""))
            .WillByDefault(testing::Return(givenDirectories));
        ON_CALL(*m_packageFileSystemDirectoryMock, ListDirectoryNames(""))
            .WillByDefault(testing::Return(givenDirectories));

        std::string fullPathToFile = validDirectory + "\\" + m_propertiesFileName;
        ON_CALL(*m_packageFileSystemFileMock, Exists(fullPathToFile))
            .WillByDefault(testing::Return(true));
        EXPECT_CALL(*m_packageFileSystemFileMock, ReadFileContents(fullPathToFile))
            .WillOnce(testing::Return(m_validProjectProperties));

        // Act
        std::shared_ptr<ProjectProperties> actual = m_testClass->LoadProjectProperties(m_gamePackageMock);

        // Assert
        ASSERT_EQ("sceneName.scene", actual->GetStartScene());
        ASSERT_EQ("WindowTitle", actual->GetWindowTitle());
    }

    TEST_F(ProjectPropertiesProviderTests, LoadProjectProperties_PrioritisesOutterFile_WhenOneIsFoundAtTheRootLevel)
    {
        // Do not update these to add more parsed values, this purely tests to see if the provider did pass the XML
        // to the project properties successful. Use the actual project properties tests to add new values and test those.

        // Arrange
        EXPECT_CALL(*m_packageFileSystemFileMock, Exists(m_propertiesFileName))
            .WillOnce(testing::Return(true));

        EXPECT_CALL(*m_packageFileSystemFileMock, ReadFileContents(m_propertiesFileName))
            .WillOnce(testing::Return(m_validProjectProperties));

        std::string validDirectory = "MyDirectory";
        std::vector<std::string> givenDirectories = { "Directory", validDirectory, "Another" };

        ON_CALL(*m_packageFileSystemDirectoryMock, ListDirectories(""))
            .WillByDefault(testing::Return(givenDirectories));
        ON_CALL(*m_packageFileSystemDirectoryMock, ListDirectoryNames(""))
            .WillByDefault(testing::Return(givenDirectories));

        const char* unexpectedFileRead = "<UniversalObjectData>"
            "<Strings>"
            "<String \"Key\"=\"StartScene\" \"Value\"=\"somethingElse\" />"
            "<String \"Key\"=\"WindowTitle\" \"Value\"=\"SomethingElse\" />"
            "</Strings>"
            "</UniversalObjectData>";
        ASSERT_NE(unexpectedFileRead, m_validProjectProperties)
            << "Ensure the given value for the sub directory and the root do not equal so that the assertions make sense.";

        std::string fullPathToFile = validDirectory + "\\" + m_propertiesFileName;
        ON_CALL(*m_packageFileSystemFileMock, Exists(fullPathToFile))
            .WillByDefault(testing::Return(true));
        ON_CALL(*m_packageFileSystemFileMock, ReadFileContents(fullPathToFile))
            .WillByDefault(testing::Return(unexpectedFileRead));

        // Act
        std::shared_ptr<ProjectProperties> actual = m_testClass->LoadProjectProperties(m_gamePackageMock);

        // Assert
        ASSERT_EQ("sceneName.scene", actual->GetStartScene());
        ASSERT_EQ("WindowTitle", actual->GetWindowTitle());
    }

#pragma endregion
#pragma region CanLoadProjectProperties

    TEST_F(ProjectPropertiesProviderTests, CanLoadProjectProperties_ReturnsFalse_WhenTheFileDoesNotExist)
    {
        // Arrange
        // Nothing to arrange, File will not exist and no directories will exist.

        // Act
        bool actual = m_testClass->CanLoadProjectProperties(m_gamePackageMock);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(ProjectPropertiesProviderTests, CanLoadProjectProperties_ReturnsTrue_WhenTheFileExistsInTheRootDirectory)
    {
        // Arrange
        ON_CALL(*m_packageFileSystemFileMock, Exists(m_propertiesFileName))
            .WillByDefault(testing::Return(true));

        ON_CALL(*m_packageFileSystemFileMock, ReadFileContents(m_propertiesFileName))
            .WillByDefault(testing::Return(m_validProjectProperties));

        // Act
        bool actual = m_testClass->CanLoadProjectProperties(m_gamePackageMock);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(ProjectPropertiesProviderTests, CanLoadProjectProperties_ReturnsTrue_WhenTheFileExistsOneDirectoryBelowTheRoot)
    {
        // Arrange
        std::string validDirectory = "MyDirectory";
        std::vector<std::string> givenDirectories = { "Directory", validDirectory, "Another" };

        ON_CALL(*m_packageFileSystemDirectoryMock, ListDirectories(""))
            .WillByDefault(testing::Return(givenDirectories));
        ON_CALL(*m_packageFileSystemDirectoryMock, ListDirectoryNames(""))
            .WillByDefault(testing::Return(givenDirectories));

        std::string fullPathToFile = validDirectory + "\\" + m_propertiesFileName;
        ON_CALL(*m_packageFileSystemFileMock, Exists(fullPathToFile))
            .WillByDefault(testing::Return(true));

        // Act
        bool actual = m_testClass->CanLoadProjectProperties(m_gamePackageMock);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(ProjectPropertiesProviderTests, CanLoadProjectProperties_ReturnsFalse_WhenTheFileDoesNotExistInAnySubdirectory)
    {
        // Arrange
        std::vector<std::string> givenDirectories = { "Directory", "Another" };

        ON_CALL(*m_packageFileSystemDirectoryMock, ListDirectories(""))
            .WillByDefault(testing::Return(givenDirectories));
        ON_CALL(*m_packageFileSystemDirectoryMock, ListDirectoryNames(""))
            .WillByDefault(testing::Return(givenDirectories));

        // Act
        bool actual = m_testClass->CanLoadProjectProperties(m_gamePackageMock);

        // Assert
        ASSERT_FALSE(actual);
    }

#pragma endregion
#pragma region GetProjectPropertiesPath

    TEST_F(ProjectPropertiesProviderTests, GetProjectPropertiesPath_ReturnsEmpty_WhenThereIsNoFileCurrently)
    {
        // Arrange
        // Nothing to arrange, File will not exist and no directories will exist.
        std::string expected = {};

        // Act
        std::string actual = m_testClass->GetProjectPropertiesPath(m_gamePackageMock);

        // Assert
        ASSERT_EQ(expected, actual);
    }

    TEST_F(ProjectPropertiesProviderTests, GetProjectPropertiesPath_ReturnsTheNameOfTheFile_WhenThereIsAProjectPropertiesFileAtTheRoot)
    {
        // Arrange
        ON_CALL(*m_packageFileSystemFileMock, Exists(m_propertiesFileName))
            .WillByDefault(testing::Return(true));

        // Act
        std::string actual = m_testClass->GetProjectPropertiesPath(m_gamePackageMock);

        // Assert
        ASSERT_EQ(m_propertiesFileName, actual);
    }

    TEST_F(ProjectPropertiesProviderTests, GetProjectPropertiesPath_ReturnsThePathWithSubdirectory_WhenTheOnlyFileFoundIsInASubDirectory)
    {
        // Arrange
        std::string validDirectory = "MyDirectory";
        std::vector<std::string> givenDirectories = { "Directory", validDirectory, "Another" };

        ON_CALL(*m_packageFileSystemDirectoryMock, ListDirectories(""))
            .WillByDefault(testing::Return(givenDirectories));
        ON_CALL(*m_packageFileSystemDirectoryMock, ListDirectoryNames(""))
            .WillByDefault(testing::Return(givenDirectories));

        std::string fullPathToFile = validDirectory + "\\" + m_propertiesFileName;
        ON_CALL(*m_packageFileSystemFileMock, Exists(fullPathToFile))
            .WillByDefault(testing::Return(true));

        // Act
        std::string actual = m_testClass->GetProjectPropertiesPath(m_gamePackageMock);

        // Assert
        ASSERT_EQ(fullPathToFile, actual);
    }

#pragma endregion
}