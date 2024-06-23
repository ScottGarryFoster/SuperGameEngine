#include "../../LibraryIncludes.h"
#include "../../../SuperGameEngine/Engine/AuthoredLoader/ParsedData.h"

using namespace StandardCLibrary;
using namespace SuperGameEngine;

namespace SuperGameEngineTests_Engine_AuthoredLoader
{
    class ParsedDataTests : public ::testing::Test
    {
    public:
        ParsedDataTests()
        {
        }
    };

    TEST_F(ParsedDataTests, ParsedData_ReturnsName_WhenConstructedWithName)
    {
        std::string given = "testName";
        std::vector< std::shared_ptr<ParsedData>> children;

        std::shared_ptr<ParsedData> tested = std::make_shared<ParsedData>(given, children);
        std::string actual = tested->GetName();

        ASSERT_EQ(given, actual);
    }

    TEST_F(ParsedDataTests, ParsedData_ReturnsChild_WhenConstructedWithChildren)
    {
        // Arrange
        std::shared_ptr<ParsedData> given = std::make_shared<ParsedData>();
        std::vector<std::shared_ptr<ParsedData>> children = std::vector<std::shared_ptr<ParsedData>>();
        children.push_back(given);

        // Act
        std::shared_ptr<ParsedData> tested = std::make_shared<ParsedData>(std::string(), children);
        std::vector<std::shared_ptr<const ParsedData>> actual = tested->GetChildren();

        // Assert
        ASSERT_EQ(1, actual.size());
        std::shared_ptr<const ParsedData> constGiven = std::static_pointer_cast<const ParsedData>(given);
        ASSERT_EQ(constGiven, actual[0]);
    }

#pragma region TryGetProperty String
    TEST_F(ParsedDataTests, TryGetProperty_ReturnsFalse_WhenSetPropertyIsNotCalled)
    {
        // Arrange
        std::string given = "testProperty";
        std::shared_ptr<ParsedData> testClass = std::make_shared<ParsedData>();

        // Act
        std::string propertyValue = std::string();
        bool actual = testClass->TryGetProperty(given, propertyValue);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(ParsedDataTests, TryGetProperty_ReturnsProperty_WhenSetPropertyIsCalledButDoesNotMatchTryPropertyValue)
    {
        // Arrange
        std::string given = "testProperty";
        std::string setProperty = "setProperty";
        std::shared_ptr<ParsedData> testClass = std::make_shared<ParsedData>();

        testClass->SetProperty(setProperty, std::string());

        // Act
        std::string propertyValue = std::string();
        bool actual = testClass->TryGetProperty(given, propertyValue);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(ParsedDataTests, TryGetProperty_ReturnsProperty_WhenSetPropertyCalled)
    {
        // Arrange
        std::string given = "testProperty";
        std::shared_ptr<ParsedData> testClass = std::make_shared<ParsedData>();

        testClass->SetProperty(given, std::string());

        // Act
        std::string propertyValue = std::string();
        bool actual = testClass->TryGetProperty(given, propertyValue);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(ParsedDataTests, TryGetProperty_ReturnsValue_WhenPropertyValueGiven)
    {
        // Arrange
        std::string given = "testProperty";
        std::string givenValue = "propertyValue";
        std::shared_ptr<ParsedData> testClass = std::make_shared<ParsedData>();

        testClass->SetProperty(given, givenValue);

        // Act
        std::string propertyValue = std::string();
        bool actual = testClass->TryGetProperty(given, propertyValue);

        // Assert
        ASSERT_EQ(givenValue, propertyValue);
    }

#pragma endregion

#pragma region TryGetProperty Int

    TEST_F(ParsedDataTests, TryGetPropertyInt_ReturnsFalse_WhenSetPropertyIsNotCalled)
    {
        // Arrange
        std::string given = "testProperty";
        std::shared_ptr<ParsedData> testClass = std::make_shared<ParsedData>();

        // Act
        int propertyValue = int();
        bool actual = testClass->TryGetProperty(given, propertyValue);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(ParsedDataTests, TryGetPropertyInt_ReturnsProperty_WhenSetPropertyIsCalledButDoesNotMatchTryPropertyValue)
    {
        // Arrange
        std::string given = "testProperty";
        std::string setProperty = "setProperty";
        std::shared_ptr<ParsedData> testClass = std::make_shared<ParsedData>();

        testClass->SetProperty(setProperty, int());

        // Act
        int propertyValue = int();
        bool actual = testClass->TryGetProperty(given, propertyValue);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(ParsedDataTests, TryGetPropertyInt_ReturnsProperty_WhenSetPropertyCalled)
    {
        // Arrange
        std::string given = "testProperty";
        std::shared_ptr<ParsedData> testClass = std::make_shared<ParsedData>();

        testClass->SetProperty(given, int());

        // Act
        int propertyValue = int();
        bool actual = testClass->TryGetProperty(given, propertyValue);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(ParsedDataTests, TryGetPropertyInt_ReturnsValue_WhenPropertyValueGiven)
    {
        // Arrange
        std::string given = "testProperty";
        int givenValue = 42;
        std::shared_ptr<ParsedData> testClass = std::make_shared<ParsedData>();

        testClass->SetProperty(given, givenValue);

        // Act
        int propertyValue = int();
        bool actual = testClass->TryGetProperty(given, propertyValue);

        // Assert
        ASSERT_EQ(givenValue, propertyValue);
    }

#pragma endregion

#pragma region TryGetProperty Float

    TEST_F(ParsedDataTests, TryGetPropertyFloat_ReturnsFalse_WhenSetPropertyIsNotCalled)
    {
        // Arrange
        std::string given = "testProperty";
        std::shared_ptr<ParsedData> testClass = std::make_shared<ParsedData>();

        // Act
        float propertyValue = float();
        bool actual = testClass->TryGetProperty(given, propertyValue);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(ParsedDataTests, TryGetPropertyFloat_ReturnsProperty_WhenSetPropertyIsCalledButDoesNotMatchTryPropertyValue)
    {
        // Arrange
        std::string given = "testProperty";
        std::string setProperty = "setProperty";
        std::shared_ptr<ParsedData> testClass = std::make_shared<ParsedData>();

        testClass->SetProperty(setProperty, float());

        // Act
        float propertyValue = float();
        bool actual = testClass->TryGetProperty(given, propertyValue);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(ParsedDataTests, TryGetPropertyFloat_ReturnsProperty_WhenSetPropertyCalled)
    {
        // Arrange
        std::string given = "testProperty";
        std::shared_ptr<ParsedData> testClass = std::make_shared<ParsedData>();

        testClass->SetProperty(given, float());

        // Act
        float propertyValue = float();
        bool actual = testClass->TryGetProperty(given, propertyValue);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(ParsedDataTests, TryGetPropertyFloat_ReturnsValue_WhenPropertyValueGiven)
    {
        // Arrange
        std::string given = "testProperty";
        float givenValue = 42.432f;
        std::shared_ptr<ParsedData> testClass = std::make_shared<ParsedData>();

        testClass->SetProperty(given, givenValue);

        // Act
        float propertyValue = float();
        bool actual = testClass->TryGetProperty(given, propertyValue);

        // Assert
        ASSERT_EQ(givenValue, propertyValue);
    }

#pragma endregion
}