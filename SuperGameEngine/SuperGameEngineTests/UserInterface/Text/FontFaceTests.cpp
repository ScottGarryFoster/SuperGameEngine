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

        FontFace* fontFace;
        std::shared_ptr<MockSuperTexture> mockSuperTexture;

        void SetUp() override
        {
            mockSuperTexture = std::make_shared<MockSuperTexture>();

            FPoint validSize = FPoint(100, 100);
            EXPECT_CALL(*this->mockSuperTexture, Size())
                .WillRepeatedly(Return(validSize));

            this->fontFace = new FontFace(mockSuperTexture);
        }

        void TearDown() override
        {
            mockSuperTexture.reset();
            if (this->fontFace != nullptr)
            {
                delete this->fontFace;
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

        // We have to utilise the == operator of Rectangle to get this working
        // this dose mean a little bit of logic which should be replaced with a
        // custom matcher.
        int seq = 0;
        bool inOrder = true;
        EXPECT_CALL(*this->mockSuperTexture, Draw(_, _))
            .WillRepeatedly(testing::Invoke(
                [&seq, &inOrder, &valid, &validSecond]
                (const RectangleInt& x, const RectangleInt& y)
                { 
                    if (seq == 0 && x == valid)
                    {
                        ++seq;
                    }
                    else if (seq == 1 && x == validSecond)
                    {
                        ++seq;
                    }
                    else
                    {
                        inOrder = false;
                    }
                }));
        std::shared_ptr<FText> givenText = std::make_shared<FText>(L"ab");

        // Act
        this->fontFace->DrawText(givenText, givenTransform);

        // Assert
        ASSERT_TRUE(seq == 2 && inOrder) << "Seq: " << seq << " In Order: " << inOrder;
    }
#pragma endregion
}