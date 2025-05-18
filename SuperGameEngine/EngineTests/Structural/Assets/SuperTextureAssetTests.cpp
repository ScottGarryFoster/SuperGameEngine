#include "../../../Engine/Structural/Assets/Texture/SuperTextureAsset.h"
#include "../../../../FatedQuest.Libraries/Logger/Console/ConsoleLog.h"
#include "../../../../FatedQuest.Libraries/StoredDocument/AllReferences.h"
#include <memory>
#include <gtest/gtest.h>
#include "Stubs/Engine/Content/TextureManagerStub.h"
#include "Stubs/Engine/Graphics/SuperTextureStub.h"

using namespace SuperGameEngine;
using namespace FatedQuestLibraries;
using namespace SuperGameEngineTests_Stubs;
namespace SuperGameEngineTests_Structural_Assets
{
    class SuperTextureAssetTests : public ::testing::Test
    {
    public:
        SuperTextureAssetTests()
        {
        }

    protected:
        std::shared_ptr<ConsoleLog> m_logger;

        void SetUp() override
        {
            m_logger = std::make_shared<ConsoleLog>();
            if (auto event = Log::GetEvent().lock())
            {
                event->Subscribe(m_logger);
            }


        }

        void TearDown() override
        {
            if (auto event = Log::GetEvent().lock())
            {
                event->Unsubscribe(m_logger);
            }
        }

        /// <summary>
        /// For a TextureAsset get a valid document with the minimum in.
        /// </summary>
        /// <returns></returns>
        std::shared_ptr<ModifiableDocument> GetValidDocument()
        {
            return std::make_shared<ModifiableDocument>();
        }

        void AddAttribute(std::vector<std::shared_ptr<StoredDocumentAttribute>>& list, const std::string& name, const std::string& value)
        {
            list.emplace_back(std::make_shared<ModifiableAttribute>(name, value));
        }
    };

    TEST_F(SuperTextureAssetTests, Draw_FindsTheTextureGivenAtConstructionAndCallsDraw_WhenGivenAValidPath)
    {
        // Arrange
        std::string givenPath = "myPath.png";
        FatedQuestLibraries::FPoint givenSize = FPoint(10, 20);
        auto givenTexture = std::make_shared<SuperTextureStub>(givenPath, givenSize);
        ASSERT_EQ(0, givenTexture->GetTheNumberOfTimesDrawn()) << "Times drawn must begin at zero to mean something to the test.";

        // Ensure the texture is acquirable.
        auto givenTextureManager = std::make_shared<TextureManagerStub>();
        givenTextureManager->GiveTexture(givenTexture, givenPath);

        std::shared_ptr<ModifiableDocument> givenDocument = GetValidDocument();
        auto testClass = std::make_shared<SuperTextureAsset>(givenDocument, givenPath, givenTextureManager);

        // Act
        testClass->Draw();

        // Assert
        ASSERT_EQ(1, givenTexture->GetTheNumberOfTimesDrawn());
    }

    TEST_F(SuperTextureAssetTests, Draw_DoesNothing_WhenTexturePathNotFound)
    {
        // Arrange
        std::string givenPath = "notAdded.png";
        std::string addedPath = "myPath.png";
        FatedQuestLibraries::FPoint givenSize = FPoint(10, 20);
        auto givenTexture = std::make_shared<SuperTextureStub>(addedPath, givenSize);
        ASSERT_EQ(0, givenTexture->GetTheNumberOfTimesDrawn()) << "Times drawn must begin at zero to mean something to the test.";

        // Ensure the texture is acquirable.
        auto givenTextureManager = std::make_shared<TextureManagerStub>();
        givenTextureManager->GiveTexture(givenTexture, addedPath);

        std::shared_ptr<ModifiableDocument> givenDocument = GetValidDocument();
        auto testClass = std::make_shared<SuperTextureAsset>(givenDocument, givenPath, givenTextureManager);

        // Act
        testClass->Draw();

        // Assert
        ASSERT_EQ(0, givenTexture->GetTheNumberOfTimesDrawn());
    }

    TEST_F(SuperTextureAssetTests, Draw_DoesNothing_WhenPathContainsNothing)
    {
        // Arrange
        std::string givenPath = "  ";
        std::string addedPath = "myPath.png";
        FatedQuestLibraries::FPoint givenSize = FPoint(10, 20);
        auto givenTexture = std::make_shared<SuperTextureStub>(addedPath, givenSize);
        ASSERT_EQ(0, givenTexture->GetTheNumberOfTimesDrawn()) << "Times drawn must begin at zero to mean something to the test.";

        // Ensure the texture is acquirable.
        auto givenTextureManager = std::make_shared<TextureManagerStub>();
        givenTextureManager->GiveTexture(givenTexture, addedPath);

        std::shared_ptr<ModifiableDocument> givenDocument = GetValidDocument();
        auto testClass = std::make_shared<SuperTextureAsset>(givenDocument, givenPath, givenTextureManager);

        // Act
        testClass->Draw();

        // Assert
        ASSERT_EQ(0, givenTexture->GetTheNumberOfTimesDrawn());
    }
}