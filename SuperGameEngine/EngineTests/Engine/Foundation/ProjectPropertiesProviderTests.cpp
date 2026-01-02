#include "../../../Engine/Engine/Foundation/ProjectPropertiesProvider.h"
#include "../../FatedQuest.Libraries/Logger/AllReferences.h"
#include <memory>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Engine/Foundation/ProjectProperties.h"
#include "../../FatedQuest.Libraries/GamePackageTestMocks/GamePackage/GamePackageMock.h"
#include "../../FatedQuest.Libraries/GamePackageTestMocks/GamePackage/FileSystem/PackageFileSystemFileMock.h"
#include "../../FatedQuest.Libraries/GamePackageTestMocks/GamePackage/FileSystem/PackageFileSystemDirectoryMock.h"

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
        std::string propertyFileName = "ProjectProperties.uod";

        EXPECT_CALL(*m_packageFileSystemFileMock, Exists(propertyFileName))
            .WillOnce(testing::Return(true));

        EXPECT_CALL(*m_packageFileSystemFileMock, ReadFileContents(propertyFileName))
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
        std::string propertyFileName = "ProjectProperties.uod";

        EXPECT_CALL(*m_packageFileSystemFileMock, Exists(propertyFileName))
            .WillOnce(testing::Return(true));

        EXPECT_CALL(*m_packageFileSystemFileMock, ReadFileContents(propertyFileName))
            .WillOnce(testing::Return(m_validProjectProperties));

        // Act
        std::shared_ptr<ProjectProperties> actual = m_testClass->LoadProjectProperties(m_gamePackageMock);

        // Assert
        ASSERT_EQ("sceneName.scene", actual->GetStartScene());
        ASSERT_EQ("WindowTitle", actual->GetWindowTitle());
    }
}