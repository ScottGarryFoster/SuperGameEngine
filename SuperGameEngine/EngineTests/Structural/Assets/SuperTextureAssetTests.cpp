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

        void AddString(std::shared_ptr<ModifiableNode>& strings, const std::string& key, const std::string& value)
        {
            auto newString = std::make_shared<ModifiableNode>();
            newString->SetName("String");
            std::vector<std::shared_ptr<StoredDocumentAttribute>> attributes;
            AddAttribute(attributes, "Key", key);
            AddAttribute(attributes, "Value", value);
            newString->SetAttributes(attributes);


            std::shared_ptr<StoredDocumentNode> lastChild = strings->GetLastChild();
            if (!lastChild)
            {
                lastChild = strings->GetFirstChild();
            }

            if (lastChild)
            {
                if (std::shared_ptr<ModifiableNode> modifiableChild = std::dynamic_pointer_cast<ModifiableNode>(lastChild))
                {
                    modifiableChild->SetAdjacentNode(newString);
                    strings->SetLastChild(newString);
                }
            }
            else
            {
                std::vector<std::shared_ptr<ModifiableNode>> children;
                children.emplace_back(newString);
                strings->SetAllChildrenNodes(children);
            }

        }

        void AddVector4I(std::shared_ptr<ModifiableNode>& vector4is, const std::string& key, int x, int y, int z, int w)
        {
            auto newString = std::make_shared<ModifiableNode>();
            newString->SetName("Vector4I");
            std::vector<std::shared_ptr<StoredDocumentAttribute>> attributes;
            AddAttribute(attributes, "Key", key);
            AddAttribute(attributes, "X", std::to_string(x));
            AddAttribute(attributes, "Y", std::to_string(y));
            AddAttribute(attributes, "Z", std::to_string(z));
            AddAttribute(attributes, "W", std::to_string(w));
            newString->SetAttributes(attributes);


            std::shared_ptr<StoredDocumentNode> lastChild = vector4is->GetLastChild();
            if (!lastChild)
            {
                lastChild = vector4is->GetFirstChild();
            }

            if (lastChild)
            {
                if (std::shared_ptr<ModifiableNode> modifiableChild = std::dynamic_pointer_cast<ModifiableNode>(lastChild))
                {
                    modifiableChild->SetAdjacentNode(newString);
                    vector4is->SetLastChild(newString);
                }
            }
            else
            {
                std::vector<std::shared_ptr<ModifiableNode>> children;
                children.emplace_back(newString);
                vector4is->SetAllChildrenNodes(children);
            }
        }
    };


#pragma region Default Draw
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

#pragma endregion

#pragma region Segement Draw Predefined

    TEST_F(SuperTextureAssetTests, Draw_ReturnsFirstSegement_WhenGivenDocumentDefiningASegementInPositionZero)
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
        auto root = std::make_shared<ModifiableNode>();
        auto strings = std::make_shared<ModifiableNode>();
        strings->SetName("Strings");

        auto vector4is = std::make_shared<ModifiableNode>();
        vector4is->SetName("Vector4Is");

        std::vector<std::shared_ptr<ModifiableNode>> children;
        children.emplace_back(strings);
        children.emplace_back(vector4is);
        root->SetAllChildrenNodes(children);
        givenDocument->SetRootElement(root);

        AddString(strings, "TextureUVMethod", "Predefined");
        AddVector4I(vector4is, "TextureUV0", 1, 2, 3, 4);

        auto testClass = std::make_shared<SuperTextureAsset>(givenDocument, givenPath, givenTextureManager);

        // Act
        testClass->Draw(0);

        // Assert
        ASSERT_EQ(1, givenTexture->GetTheNumberOfTimesDrawn());

        std::shared_ptr<SuperGameEngine::RectangleInt> lastTextureLocation = givenTexture->LastDrawnTextureLocation();
        ASSERT_EQ(1, lastTextureLocation->GetLeft()) << "Left location was incorrect";
        ASSERT_EQ(2, lastTextureLocation->GetTop()) << "Top location was incorrect";
        ASSERT_EQ(3, lastTextureLocation->GetWidth()) << "Width was incorrect";
        ASSERT_EQ(4, lastTextureLocation->GetHeight()) << "Height was incorrect";
    }

    TEST_F(SuperTextureAssetTests, Draw_ReturnsSecondSegement_WhenGivenDocumentDefiningASegementInPositionZero)
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
        auto root = std::make_shared<ModifiableNode>();
        auto strings = std::make_shared<ModifiableNode>();
        strings->SetName("Strings");

        auto vector4is = std::make_shared<ModifiableNode>();
        vector4is->SetName("Vector4Is");

        std::vector<std::shared_ptr<ModifiableNode>> children;
        children.emplace_back(strings);
        children.emplace_back(vector4is);
        root->SetAllChildrenNodes(children);
        givenDocument->SetRootElement(root);

        AddString(strings, "TextureUVMethod", "Predefined");
        AddVector4I(vector4is, "TextureUV0", 1, 2, 3, 4);
        AddVector4I(vector4is, "TextureUV1", 5, 6, 7, 8);

        auto testClass = std::make_shared<SuperTextureAsset>(givenDocument, givenPath, givenTextureManager);

        // Act
        testClass->Draw(1);

        // Assert
        ASSERT_EQ(1, givenTexture->GetTheNumberOfTimesDrawn());

        std::shared_ptr<SuperGameEngine::RectangleInt> lastTextureLocation = givenTexture->LastDrawnTextureLocation();
        ASSERT_EQ(5, lastTextureLocation->GetLeft()) << "Left location was incorrect";
        ASSERT_EQ(6, lastTextureLocation->GetTop()) << "Top location was incorrect";
        ASSERT_EQ(7, lastTextureLocation->GetWidth()) << "Width was incorrect";
        ASSERT_EQ(8, lastTextureLocation->GetHeight()) << "Height was incorrect";
    }

    TEST_F(SuperTextureAssetTests, Draw_DrawsNothing_WhenGivenMinusOne)
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
        auto root = std::make_shared<ModifiableNode>();
        auto strings = std::make_shared<ModifiableNode>();
        strings->SetName("Strings");

        auto vector4is = std::make_shared<ModifiableNode>();
        vector4is->SetName("Vector4Is");

        std::vector<std::shared_ptr<ModifiableNode>> children;
        children.emplace_back(strings);
        children.emplace_back(vector4is);
        root->SetAllChildrenNodes(children);
        givenDocument->SetRootElement(root);

        AddString(strings, "TextureUVMethod", "Predefined");
        AddVector4I(vector4is, "TextureUV0", 1, 2, 3, 4);

        auto testClass = std::make_shared<SuperTextureAsset>(givenDocument, givenPath, givenTextureManager);

        // Act
        testClass->Draw(-1);

        // Assert
        ASSERT_EQ(0, givenTexture->GetTheNumberOfTimesDrawn());

        std::shared_ptr<SuperGameEngine::RectangleInt> lastTextureLocation = givenTexture->LastDrawnTextureLocation();
        ASSERT_EQ(0, lastTextureLocation->GetLeft()) << "Left location was incorrect";
        ASSERT_EQ(0, lastTextureLocation->GetTop()) << "Top location was incorrect";
        ASSERT_EQ(0, lastTextureLocation->GetWidth()) << "Width was incorrect";
        ASSERT_EQ(0, lastTextureLocation->GetHeight()) << "Height was incorrect";
    }

    TEST_F(SuperTextureAssetTests, Draw_DrawsNothing_WhenGivenASegementAboveTheNumberOfSegments)
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
        auto root = std::make_shared<ModifiableNode>();
        auto strings = std::make_shared<ModifiableNode>();
        strings->SetName("Strings");

        auto vector4is = std::make_shared<ModifiableNode>();
        vector4is->SetName("Vector4Is");

        std::vector<std::shared_ptr<ModifiableNode>> children;
        children.emplace_back(strings);
        children.emplace_back(vector4is);
        root->SetAllChildrenNodes(children);
        givenDocument->SetRootElement(root);

        AddString(strings, "TextureUVMethod", "Predefined");
        AddVector4I(vector4is, "TextureUV0", 1, 2, 3, 4);

        auto testClass = std::make_shared<SuperTextureAsset>(givenDocument, givenPath, givenTextureManager);

        // Act
        testClass->Draw(1);

        // Assert
        ASSERT_EQ(0, givenTexture->GetTheNumberOfTimesDrawn());

        std::shared_ptr<SuperGameEngine::RectangleInt> lastTextureLocation = givenTexture->LastDrawnTextureLocation();
        ASSERT_EQ(0, lastTextureLocation->GetLeft()) << "Left location was incorrect";
        ASSERT_EQ(0, lastTextureLocation->GetTop()) << "Top location was incorrect";
        ASSERT_EQ(0, lastTextureLocation->GetWidth()) << "Width was incorrect";
        ASSERT_EQ(0, lastTextureLocation->GetHeight()) << "Height was incorrect";
    }

#pragma endregion
}