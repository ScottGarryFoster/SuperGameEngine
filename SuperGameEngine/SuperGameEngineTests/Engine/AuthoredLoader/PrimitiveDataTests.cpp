#include "../../LibraryIncludes.h"
#include "../../../SuperGameEngine/Engine/AuthoredLoader/XMLPrimitiveDataLoader.h"

using namespace StandardCLibrary;
using namespace SuperGameEngine;

namespace SuperGameEngineTests_Engine_AuthoredLoader
{
    class PrimitiveDataTests : public ::testing::Test
    {
    public:
        PrimitiveDataTests()
        {
        }
    };

    TEST_F(PrimitiveDataTests, PrimitiveData_ReturnsName_WhenConstructedWithName)
    {
        std::string given = "testName";
        std::vector< std::shared_ptr<PrimitiveData>> children;

        std::shared_ptr<PrimitiveData> tested = std::make_shared<PrimitiveData>(given, children);
        std::string actual = tested->GetName();

        ASSERT_EQ(given, actual);
    }

    TEST_F(PrimitiveDataTests, PrimitiveData_ReturnsChild_WhenConstructedWithChildren)
    {
        // Arrange
        std::shared_ptr<PrimitiveData> given = std::make_shared<PrimitiveData>();
        std::vector<std::shared_ptr<PrimitiveData>> children = std::vector<std::shared_ptr<PrimitiveData>>();
        children.push_back(given);

        // Act
        std::shared_ptr<PrimitiveData> tested = std::make_shared<PrimitiveData>(std::string(), children);
        std::vector<std::shared_ptr<const PrimitiveData>> actual = tested->GetChildren();

        // Assert
        ASSERT_EQ(1, actual.size());
        std::shared_ptr<const PrimitiveData> constGiven = std::static_pointer_cast<const PrimitiveData>(given);
        ASSERT_EQ(constGiven, actual[0]);
    }

    TEST_F(PrimitiveDataTests, TryGetProperty_ReturnsFalse_WhenSetPropertyIsNotCalled)
    {
        // Arrange
        std::string given = "testProperty";
        std::shared_ptr<PrimitiveData> testClass = std::make_shared<PrimitiveData>();

        // Act
        std::string propertyValue = std::string();
        bool actual = testClass->TryGetProperty(given, propertyValue);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(PrimitiveDataTests, TryGetProperty_ReturnsProperty_WhenSetPropertyIsCalledButDoesNotMatchTryPropertyValue)
    {
        // Arrange
        std::string given = "testProperty";
        std::string setProperty = "setProperty";
        std::shared_ptr<PrimitiveData> testClass = std::make_shared<PrimitiveData>();

        testClass->SetProperty(setProperty, std::string());

        // Act
        std::string propertyValue = std::string();
        bool actual = testClass->TryGetProperty(given, propertyValue);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(PrimitiveDataTests, TryGetProperty_ReturnsProperty_WhenSetPropertyCalled)
    {
        // Arrange
        std::string given = "testProperty";
        std::shared_ptr<PrimitiveData> testClass = std::make_shared<PrimitiveData>();

        testClass->SetProperty(given, std::string());

        // Act
        std::string propertyValue = std::string();
        bool actual = testClass->TryGetProperty(given, propertyValue);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(PrimitiveDataTests, TryGetProperty_ReturnsValue_WhenPropertyValueGiven)
    {
        // Arrange
        std::string given = "testProperty";
        std::string givenValue = "propertyValue";
        std::shared_ptr<PrimitiveData> testClass = std::make_shared<PrimitiveData>();

        testClass->SetProperty(given, givenValue);

        // Act
        std::string propertyValue = std::string();
        bool actual = testClass->TryGetProperty(given, propertyValue);

        // Assert
        ASSERT_EQ(givenValue, propertyValue);
    }
}