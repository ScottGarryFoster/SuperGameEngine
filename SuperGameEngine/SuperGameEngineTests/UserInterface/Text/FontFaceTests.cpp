#include "../../LibraryIncludes.h"
#include "../../../SuperGameEngine/UserInterface/Text/FontFace.h"
#include "../../Engine/Graphics/MockSuperTexture.h"

using namespace StandardCLibrary;
using namespace SuperGameEngine_UserInterface;
using namespace SuperGameEngine;
using namespace SuperGameEngineTests;

namespace SuperGameEngineTests_UserInterface_Text
{
    class FontFaceTests : public ::testing::Test
    {
    public:
        FontFaceTests()
        {
            fontFace = nullptr;
        }

    protected:

        std::shared_ptr<FontFace> fontFace;
        std::shared_ptr<MockSuperTexture> mockSuperTexture;

        void SetUp() override
        {
            mockSuperTexture = std::make_shared<MockSuperTexture>();

            FPoint validSize = FPoint(100, 100);
            EXPECT_CALL(*this->mockSuperTexture, Size())
                .WillRepeatedly(Return(validSize));

            this->fontFace = std::make_shared<FontFace>(mockSuperTexture);
        }

        void TearDown() override
        {
            this->mockSuperTexture.reset();
            this->fontFace.reset();
        }

        void SetUpFontWithAlphabet(std::shared_ptr<FontFace> fontface)
        {
            std::wstring alphabet = L"abcdefghijklmnopqrstuvwxyz";
            RectangleInt textureLocation = RectangleInt(0, 0, 1, 1);
            for (wchar_t charr : alphabet)
            {
                fontFace->AddCharacter(charr, textureLocation);
            }

        }
    };

#pragma region DrawText mixed with AddCharacter

    TEST_F(FontFaceTests, DrawText_DoesNotCallSuperTexture_WhenNoCharacterAdded)
    {
        // Arrange
        std::shared_ptr<FText> givenText = std::make_shared<FText>(L"a");
        std::shared_ptr<Transform> givenTransform = std::make_shared<Transform>();
        EXPECT_CALL(*this->mockSuperTexture, Draw(_, _)).Times(0);

        // Act
        this->fontFace->DrawText(givenText, givenTransform);
    }

    TEST_F(FontFaceTests, DrawText_DoesNotCallSuperTexture_WhenCharacterIsAddedButItIsNotGiven)
    {
        // Arrange
        wchar_t given = 'a';
        wchar_t added = 'b';

        RectangleInt valid = RectangleInt(0, 0, 1, 1);
        this->fontFace->AddCharacter(added, valid);

        std::shared_ptr<FText> givenText = std::make_shared<FText>(L""+ given);
        std::shared_ptr<Transform> givenTransform = std::make_shared<Transform>();
        EXPECT_CALL(*this->mockSuperTexture, Draw(_, _)).Times(0);

        // Act
        this->fontFace->DrawText(givenText, givenTransform);
    }

#pragma endregion

#pragma region AddCharacter

    TEST_F(FontFaceTests, AddCharacter_DrawIsCalled_WhenGivenTextContainsCharacterAdded)
    {
        // Arrange
        wchar_t given = L'a';

        RectangleInt valid = RectangleInt(0, 0, 1, 1);
        this->fontFace->AddCharacter(given, valid);

        std::shared_ptr<FText> givenText = std::make_shared<FText>(L"a");
        std::shared_ptr<Transform> givenTransform = std::make_shared<Transform>();
        EXPECT_CALL(*this->mockSuperTexture, Draw(_, _)).Times(1);

        // Act
        this->fontFace->DrawText(givenText, givenTransform);
    }

    TEST_F(FontFaceTests, AddCharacter_DrawIsCalled_WhenGivenACharacterAddedSeveralCharactersBefore)
    {
        // Arrange
        wchar_t givenFirst = L'a';
        RectangleInt valid = RectangleInt(0, 0, 1, 1);
        this->fontFace->AddCharacter(givenFirst, valid);

        wchar_t givenSecond = L'b';
        this->fontFace->AddCharacter(givenSecond, valid);

        // First is expected
        std::shared_ptr<FText> givenText = std::make_shared<FText>(L"a");
        std::shared_ptr<Transform> givenTransform = std::make_shared<Transform>();
        EXPECT_CALL(*this->mockSuperTexture, Draw(_, _)).Times(1);

        // Act
        this->fontFace->DrawText(givenText, givenTransform);
    }

    TEST_F(FontFaceTests, AddCharacter_ReturnsTrue_WhenRectanglesIsOnTexture)
    {
        wchar_t givenFirst = L'a';
        RectangleInt valid = RectangleInt(0, 0, 1, 1);

        bool actual = this->fontFace->AddCharacter(givenFirst, valid);

        ASSERT_TRUE(actual);
    }

    TEST_F(FontFaceTests, AddCharacter_ReturnsFalse_WhenRectanglesIsNotOnTexture)
    {
        wchar_t givenFirst = L'a';
        RectangleInt valid = RectangleInt(-1, -1, 1, 1);

        bool actual = this->fontFace->AddCharacter(givenFirst, valid);

        ASSERT_FALSE(actual);
    }

    TEST_F(FontFaceTests, AddCharacter_DrawIsNotCalled_IfAddCharacterWasFalse)
    {
        // Arrange
        wchar_t givenFirst = L'a';
        RectangleInt valid = RectangleInt(-1, -1, 1, 1);
        bool addCharacterResult = this->fontFace->AddCharacter(givenFirst, valid);
        ASSERT_FALSE(addCharacterResult) << 
            "Could add character. This needs to fail for this test.";

        std::shared_ptr<FText> givenText = std::make_shared<FText>(L"a");
        std::shared_ptr<Transform> givenTransform = std::make_shared<Transform>();
        EXPECT_CALL(*this->mockSuperTexture, Draw(_, _)).Times(0);

        // Act
        this->fontFace->DrawText(givenText, givenTransform);
    }

#pragma endregion

#pragma region DrawText

#pragma region WhichCharacterIsDrawn
    TEST_F(FontFaceTests, DrawText_DrawsFirstCharacterFromTheCorrectTextureLocation)
    {
        // Arrange
        wchar_t givenFirst = L'a';
        RectangleInt valid = RectangleInt(0, 0, 1, 1);
        this->fontFace->AddCharacter(givenFirst, valid);

        std::shared_ptr<FText> givenText = std::make_shared<FText>(L"a");
        std::shared_ptr<Transform> givenTransform = std::make_shared<Transform>();
        EXPECT_CALL(*this->mockSuperTexture, Draw(valid, _)).Times(1);

        // Act
        this->fontFace->DrawText(givenText, givenTransform);
    }

    TEST_F(FontFaceTests, DrawText_DrawsFirstCharacterFromTheCorrectTextureLocation_WhenGivenTwoLocations)
    {
        // Arrange
        wchar_t givenFirst = L'a';
        RectangleInt valid = RectangleInt(4, 3, 2, 1);
        this->fontFace->AddCharacter(givenFirst, valid);

        wchar_t givenSecond = L'b';
        RectangleInt validSecond = RectangleInt(1, 2, 3, 4);
        this->fontFace->AddCharacter(givenSecond, validSecond);

        std::shared_ptr<Transform> givenTransform = std::make_shared<Transform>();

        Sequence sequence;
        EXPECT_CALL(*this->mockSuperTexture, Draw(valid, _))
            .InSequence(sequence);
        EXPECT_CALL(*this->mockSuperTexture, Draw(validSecond, _))
            .InSequence(sequence);

        std::shared_ptr<FText> givenText = std::make_shared<FText>(L"ab");

        // Act
        this->fontFace->DrawText(givenText, givenTransform);
    }

    TEST_F(FontFaceTests, DrawText_DrawsFirstCharacterFromTheCorrectTextureLocation_WhenAddSplitIsCalled)
    {
        // Arrange
        wchar_t givenFirst = L'a';
        RectangleInt valid = RectangleInt(4, 3, 2, 1);
        this->fontFace->AddCharacter(givenFirst, valid);

        this->fontFace->AddSplit(valid);

        wchar_t givenSecond = L'b';
        RectangleInt validSecond = RectangleInt(1, 2, 3, 4);
        this->fontFace->AddCharacter(givenSecond, validSecond);

        std::shared_ptr<Transform> givenTransform = std::make_shared<Transform>();

        Sequence sequence;
        EXPECT_CALL(*this->mockSuperTexture, Draw(valid, _))
            .InSequence(sequence);
        EXPECT_CALL(*this->mockSuperTexture, Draw(validSecond, _))
            .InSequence(sequence);

        std::shared_ptr<FText> givenText = std::make_shared<FText>(L"ab");

        // Act
        this->fontFace->DrawText(givenText, givenTransform);
    }
#pragma endregion

#pragma region WhereThCharacterIsDrawn
    TEST_F(FontFaceTests, DrawText_DrawsCharacterInLocation_WhenTransformGiven)
    {
        // Arrange
        SetUpFontWithAlphabet(fontFace);
        std::shared_ptr<FText> givenText = std::make_shared<FText>(L"a");
        float givenX = 1;
        float givenY = 2;

        std::shared_ptr<Transform> givenTransform = std::make_shared<Transform>();
        givenTransform->SetLocation(givenX, givenY);
        RectangleInt expectedScreenLocation = RectangleInt(givenX, givenY, 1, 1);

        EXPECT_CALL(*this->mockSuperTexture, Draw(_, expectedScreenLocation)).Times(1);

        // Act
        this->fontFace->DrawText(givenText, givenTransform);
    }

    TEST_F(FontFaceTests, DrawText_DrawsSecondCharacterNextToFirst_WhenTwoCharactersGiven)
    {
        // Arrange
        SetUpFontWithAlphabet(fontFace);
        std::shared_ptr<FText> givenText = std::make_shared<FText>(L"ab");
        float givenX = 1;
        float givenY = 2;

        std::shared_ptr<Transform> givenTransform = std::make_shared<Transform>();
        givenTransform->SetLocation(givenX, givenY);
        RectangleInt expectedScreenLocation = RectangleInt(givenX, givenY, 1, 1);
        RectangleInt expectedScreenLocationSecond = RectangleInt(givenX + 1, givenY, 1, 1);

        Sequence sequence;
        EXPECT_CALL(*this->mockSuperTexture, Draw(_, expectedScreenLocation))
            .InSequence(sequence);
        EXPECT_CALL(*this->mockSuperTexture, Draw(_, expectedScreenLocationSecond))
            .InSequence(sequence);

        // Act
        this->fontFace->DrawText(givenText, givenTransform);
    }
#pragma endregion
#pragma endregion
}