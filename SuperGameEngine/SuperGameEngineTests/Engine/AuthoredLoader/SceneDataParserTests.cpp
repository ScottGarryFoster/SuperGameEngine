#include "../../LibraryIncludes.h"
#include "../../../SuperGameEngine/Engine/AuthoredLoader/SceneDataParser.h"

using namespace StandardCLibrary;
using namespace SuperGameEngine;

namespace SuperGameEngineTests_Engine_AuthoredLoader
{
    class SceneDataParserTests : public ::testing::Test
    {
    public:

        std::shared_ptr<SceneDataParser> testClass;

        void SetUp() override
        {
            testClass = std::make_shared<SceneDataParser>();
        }

        void TearDown() override
        {
            testClass.reset();
        }

        std::shared_ptr<PrimitiveData> ReturnSceneData(
            std::vector<std::shared_ptr<PrimitiveData>> children)
        {
            std::string givenName = "Scene";
            return std::make_shared<PrimitiveData>(givenName, children);
        }

        std::shared_ptr<PrimitiveData> ReturnSceneData(
            std::shared_ptr<PrimitiveData> child)
        {
            std::vector<std::shared_ptr<PrimitiveData>> children;
            children.push_back(child);
            return ReturnSceneData(children);
        }

        std::shared_ptr<PrimitiveData> ReturnGameObjectData(
            std::vector<std::shared_ptr<PrimitiveData>> children)
        {
            std::string givenName = "GameObject";
            return std::make_shared<PrimitiveData>(givenName, children);
        }

        std::shared_ptr<PrimitiveData> ReturnGameObjectData(
            std::shared_ptr<PrimitiveData> child)
        {
            std::vector<std::shared_ptr<PrimitiveData>> children;
            children.push_back(child);
            return ReturnGameObjectData(children);
        }

        std::shared_ptr<PrimitiveData> ReturnGameComponent(
            std::vector<std::shared_ptr<PrimitiveData>> children)
        {
            std::string givenName = "GameComponent";
            std::shared_ptr<PrimitiveData> data = 
                std::make_shared<PrimitiveData>(givenName, children);
            data->SetProperty("type", "fromReturnGameComponent");
            return data;
        }

        std::shared_ptr<PrimitiveData> ReturnGameComponent(
            std::shared_ptr<PrimitiveData> child)
        {
            std::vector<std::shared_ptr<PrimitiveData>> children;
            children.push_back(child);
            return ReturnGameComponent(children);
        }
    };

#pragma region Scene
    TEST_F(SceneDataParserTests, ParseData_ReturnsEmpty_WhenFirstDataIsNotScene)
    {
        std::string givenName = "NotScene";
        std::shared_ptr<PrimitiveData> given = 
            std::make_shared<PrimitiveData>(givenName, std::vector<std::shared_ptr<PrimitiveData>>());

        std::shared_ptr<ParsedData> actual = testClass->ParseData(given);

        ASSERT_FALSE(actual);
    }

    TEST_F(SceneDataParserTests, ParseData_ReturnsParsedData_WhenFirstDataIsCalledScene)
    {
        std::string givenName = "Scene";
        std::shared_ptr<PrimitiveData> given =
            std::make_shared<PrimitiveData>(givenName, std::vector<std::shared_ptr<PrimitiveData>>());

        std::shared_ptr<ParsedData> actual = testClass->ParseData(given);

        ASSERT_TRUE(actual);
    }

#pragma endregion

#pragma region GameObject
    TEST_F(SceneDataParserTests, ParseData_ReturnsEmptyChild_WhenChildIsNotGameObject)
    {
        std::string givenName = "NotGameObject";
        std::shared_ptr<PrimitiveData> given =
            std::make_shared<PrimitiveData>(givenName, std::vector<std::shared_ptr<PrimitiveData>>());
        std::shared_ptr<PrimitiveData> scene = ReturnSceneData(given);

        std::shared_ptr<ParsedData> actual = testClass->ParseData(scene);

        ASSERT_EQ(0, actual->GetChildren().size());
    }

    TEST_F(SceneDataParserTests, ParseData_ReturnsParsedData_WhenFirstDataIsCalledGameObject)
    {
        std::string givenName = "GameObject";
        std::shared_ptr<PrimitiveData> given =
            std::make_shared<PrimitiveData>(givenName, std::vector<std::shared_ptr<PrimitiveData>>());
        std::shared_ptr<PrimitiveData> scene = ReturnSceneData(given);

        std::shared_ptr<ParsedData> actual = testClass->ParseData(scene);

        ASSERT_EQ(1, actual->GetChildren().size());
        ASSERT_TRUE(actual->GetChildren()[0]);
    }

#pragma endregion

#pragma region GameComponent
    TEST_F(SceneDataParserTests, ParseData_ReturnsEmptyChild_WhenChildIsNotGameComponent)
    {
        // Arrange
        std::string givenName = "NotGameComponent";
        std::shared_ptr<PrimitiveData> given =
            std::make_shared<PrimitiveData>(givenName, std::vector<std::shared_ptr<PrimitiveData>>());

        // Needs to be something valid
        given->SetProperty("type", "something");

        std::shared_ptr<PrimitiveData> gameObject = ReturnGameObjectData(given);
        std::shared_ptr<PrimitiveData> scene = ReturnSceneData(gameObject);

        // Act
        std::shared_ptr<ParsedData> actual = testClass->ParseData(scene);

        // Assert
        ASSERT_EQ(0, actual->GetChildren()[0]->GetChildren().size());
    }

    TEST_F(SceneDataParserTests, ParseData_ReturnsParsedData_WhenFirstDataIsCalledGameComponent)
    {
        // Arrange
        std::string givenName = "GameComponent";
        std::shared_ptr<PrimitiveData> given =
            std::make_shared<PrimitiveData>(givenName, std::vector<std::shared_ptr<PrimitiveData>>());

        // Needs to be something valid
        given->SetProperty("type", "something");

        std::shared_ptr<PrimitiveData> gameObject = ReturnGameObjectData(given);
        std::shared_ptr<PrimitiveData> scene = ReturnSceneData(gameObject);

        // Act
        std::shared_ptr<ParsedData> actual = testClass->ParseData(scene);

        // Assert
        ASSERT_EQ(1, actual->GetChildren()[0]->GetChildren().size());
        ASSERT_TRUE(actual->GetChildren()[0]->GetChildren()[0]);
    }

    TEST_F(SceneDataParserTests, ParseData_SetsTypeProperty_WhenTypeFound)
    {
        // Arrange
        std::string expected = "TransformComponent";
        std::string givenName = "GameComponent";
        std::shared_ptr<PrimitiveData> given =
            std::make_shared<PrimitiveData>(givenName, std::vector<std::shared_ptr<PrimitiveData>>());

        given->SetProperty("type", expected);

        std::shared_ptr<PrimitiveData> gameObject = ReturnGameObjectData(given);
        std::shared_ptr<PrimitiveData> scene = ReturnSceneData(gameObject);

        // Act
        std::shared_ptr<ParsedData> actual = testClass->ParseData(scene);

        // Assert
        std::shared_ptr<const ParsedData> actualData = actual->GetChildren()[0]->GetChildren()[0];
        std::string answer = std::string();
        bool found = actualData->TryGetProperty("type", answer);

        ASSERT_TRUE(found);
        ASSERT_EQ(expected, answer);
    }

    TEST_F(SceneDataParserTests, ParseData_ReturnsEmptyChild_WhenNoTypeGiven)
    {
        // Arrange
        std::string givenName = "GameComponent";
        std::shared_ptr<PrimitiveData> given =
            std::make_shared<PrimitiveData>(givenName, std::vector<std::shared_ptr<PrimitiveData>>());

        std::shared_ptr<PrimitiveData> gameObject = ReturnGameObjectData(given);
        std::shared_ptr<PrimitiveData> scene = ReturnSceneData(gameObject);

        // Act
        std::shared_ptr<ParsedData> actual = testClass->ParseData(scene);

        // Assert
        ASSERT_EQ(0, actual->GetChildren()[0]->GetChildren().size());
    }

#pragma endregion

#pragma region Property
    TEST_F(SceneDataParserTests, ParseData_ReturnsEmptyChild_WhenChildIsNotProperty)
    {
        // Arrange
        std::string givenName = "NotProperty";
        std::shared_ptr<PrimitiveData> given =
            std::make_shared<PrimitiveData>(givenName, std::vector<std::shared_ptr<PrimitiveData>>());

        given->SetProperty("type", "string");
        given->SetProperty("name", "valid");
        given->SetProperty("value", "text");

        std::shared_ptr<PrimitiveData> gameComponent = ReturnGameComponent(given);
        std::shared_ptr<PrimitiveData> gameObject = ReturnGameObjectData(gameComponent);
        std::shared_ptr<PrimitiveData> scene = ReturnSceneData(gameObject);

        // Act
        std::shared_ptr<ParsedData> actual = testClass->ParseData(scene);

        // Assert
        std::vector<std::shared_ptr<const ParsedData>> componentChildren =
            actual->GetChildren()[0]->GetChildren()[0]->GetChildren();
        ASSERT_EQ(0, componentChildren.size());
    }

    TEST_F(SceneDataParserTests, ParseData_ReturnsParsedData_WhenFirstDataIsCalledProperty)
    {
        // Arrange
        std::string givenName = "Property";
        std::shared_ptr<PrimitiveData> given =
            std::make_shared<PrimitiveData>(givenName, std::vector<std::shared_ptr<PrimitiveData>>());

        given->SetProperty("type", "string");
        given->SetProperty("name", "valid");
        given->SetProperty("value", "text");

        std::shared_ptr<PrimitiveData> gameComponent = ReturnGameComponent(given);
        std::shared_ptr<PrimitiveData> gameObject = ReturnGameObjectData(gameComponent);
        std::shared_ptr<PrimitiveData> scene = ReturnSceneData(gameObject);

        // Act
        std::shared_ptr<ParsedData> actual = testClass->ParseData(scene);

        // Assert
        std::vector<std::shared_ptr<const ParsedData>> componentChildren =
            actual->GetChildren()[0]->GetChildren()[0]->GetChildren();
        ASSERT_EQ(1, componentChildren.size());
        std::shared_ptr<const ParsedData> property =
            actual->GetChildren()[0]->GetChildren()[0]->GetChildren()[0];
        ASSERT_TRUE(property);
    }

    TEST_F(SceneDataParserTests, ParseData_ReturnsEmptyChild_WhenDoesNotContainATypeAndName)
    {
        // Arrange
        std::string givenName = "Property";
        std::shared_ptr<PrimitiveData> given =
            std::make_shared<PrimitiveData>(givenName, std::vector<std::shared_ptr<PrimitiveData>>());

        // Nothing added

        std::shared_ptr<PrimitiveData> gameComponent = ReturnGameComponent(given);
        std::shared_ptr<PrimitiveData> gameObject = ReturnGameObjectData(gameComponent);
        std::shared_ptr<PrimitiveData> scene = ReturnSceneData(gameObject);

        // Act
        std::shared_ptr<ParsedData> actual = testClass->ParseData(scene);

        // Assert
        std::vector<std::shared_ptr<const ParsedData>> componentChildren =
            actual->GetChildren()[0]->GetChildren()[0]->GetChildren();
        ASSERT_EQ(0, componentChildren.size());
    }

    TEST_F(SceneDataParserTests, ParseData_ReturnsNoProperty_WhenInvalidPropertyTypeFound)
    {
        // Arrange
        std::string givenName = "Property";
        std::shared_ptr<PrimitiveData> given =
            std::make_shared<PrimitiveData>(givenName, std::vector<std::shared_ptr<PrimitiveData>>());

        given->SetProperty("type", "unknownType");
        given->SetProperty("name", "valid");
        given->SetProperty("value", "text");

        std::shared_ptr<PrimitiveData> gameComponent = ReturnGameComponent(given);
        std::shared_ptr<PrimitiveData> gameObject = ReturnGameObjectData(gameComponent);
        std::shared_ptr<PrimitiveData> scene = ReturnSceneData(gameObject);

        // Act
        std::shared_ptr<ParsedData> actual = testClass->ParseData(scene);

        // Assert
        std::vector<std::shared_ptr<const ParsedData>> componentChildren =
            actual->GetChildren()[0]->GetChildren()[0]->GetChildren();
        ASSERT_EQ(0, componentChildren.size());
    }
#pragma endregion

#pragma region String Property
    TEST_F(SceneDataParserTests, ParseData_ReturnsTextProperty_WhenGivenStringProperty)
    {
        // Arrange
        std::string expectedName = "textName";
        std::string expectedValue = "text";

        std::string givenName = "Property";
        std::shared_ptr<PrimitiveData> given =
            std::make_shared<PrimitiveData>(givenName, std::vector<std::shared_ptr<PrimitiveData>>());

        // Property Details
        given->SetProperty("type", "string");
        given->SetProperty("name", expectedName);
        given->SetProperty("value", expectedValue);

        std::shared_ptr<PrimitiveData> gameComponent = ReturnGameComponent(given);
        std::shared_ptr<PrimitiveData> gameObject = ReturnGameObjectData(gameComponent);
        std::shared_ptr<PrimitiveData> scene = ReturnSceneData(gameObject);

        // Act
        std::shared_ptr<ParsedData> actual = testClass->ParseData(scene);

        // Assert
        std::vector<std::shared_ptr<const ParsedData>> componentChildren =
            actual->GetChildren()[0]->GetChildren()[0]->GetChildren();
        ASSERT_EQ(1, componentChildren.size());
        std::shared_ptr<const ParsedData> property =
            actual->GetChildren()[0]->GetChildren()[0]->GetChildren()[0];
        ASSERT_TRUE(property);

        // Type
        std::string actualValue = std::string();
        property->TryGetProperty("type", actualValue);
        ASSERT_EQ("string", actualValue);

        // Name
        property->TryGetProperty("name", actualValue);
        ASSERT_EQ(expectedName, actualValue);

        // Value
        property->TryGetProperty("value", actualValue);
        ASSERT_EQ(expectedValue, actualValue);
    }
#pragma endregion

#pragma region Int Property
    TEST_F(SceneDataParserTests, ParseData_ReturnsIntProperty_WhenGivenIntProperty)
    {
        // Arrange
        std::string expectedName = "textName";
        std::string expectedValue = "23";
        int expectedValueNumber = 23;

        std::string givenName = "Property";
        std::shared_ptr<PrimitiveData> given =
            std::make_shared<PrimitiveData>(givenName, std::vector<std::shared_ptr<PrimitiveData>>());

        // Property Details
        given->SetProperty("type", "int");
        given->SetProperty("name", expectedName);
        given->SetProperty("value", expectedValue);

        std::shared_ptr<PrimitiveData> gameComponent = ReturnGameComponent(given);
        std::shared_ptr<PrimitiveData> gameObject = ReturnGameObjectData(gameComponent);
        std::shared_ptr<PrimitiveData> scene = ReturnSceneData(gameObject);

        // Act
        std::shared_ptr<ParsedData> actual = testClass->ParseData(scene);

        // Assert
        std::vector<std::shared_ptr<const ParsedData>> componentChildren =
            actual->GetChildren()[0]->GetChildren()[0]->GetChildren();
        ASSERT_EQ(1, componentChildren.size());
        std::shared_ptr<const ParsedData> property =
            actual->GetChildren()[0]->GetChildren()[0]->GetChildren()[0];
        ASSERT_TRUE(property);

        // Type
        std::string actualValue = std::string();
        property->TryGetProperty("type", actualValue);
        ASSERT_EQ("int", actualValue);

        // Name
        property->TryGetProperty("name", actualValue);
        ASSERT_EQ(expectedName, actualValue);

        // Value
        property->TryGetProperty("value", actualValue);
        ASSERT_EQ(expectedValue, actualValue);

        // Value as Int
        int actualIntValue = int();
        property->TryGetProperty("value", actualIntValue);
        ASSERT_EQ(expectedValueNumber, actualIntValue);
    }

    TEST_F(SceneDataParserTests, ParseData_ReturnsEmpty_WhenGivenIntValueIsNotAnInt)
    {
        // Arrange
        std::string expectedName = "textName";
        std::string expectedValue = "fdsfds";

        std::string givenName = "Property";
        std::shared_ptr<PrimitiveData> given =
            std::make_shared<PrimitiveData>(givenName, std::vector<std::shared_ptr<PrimitiveData>>());

        // Property Details
        given->SetProperty("type", "int");
        given->SetProperty("name", expectedName);
        given->SetProperty("value", expectedValue);

        std::shared_ptr<PrimitiveData> gameComponent = ReturnGameComponent(given);
        std::shared_ptr<PrimitiveData> gameObject = ReturnGameObjectData(gameComponent);
        std::shared_ptr<PrimitiveData> scene = ReturnSceneData(gameObject);

        // Act
        std::shared_ptr<ParsedData> actual = testClass->ParseData(scene);

        // Assert
        std::vector<std::shared_ptr<const ParsedData>> componentChildren =
            actual->GetChildren()[0]->GetChildren()[0]->GetChildren();
        ASSERT_EQ(0, componentChildren.size());
    }

#pragma endregion

#pragma region Float Property
    TEST_F(SceneDataParserTests, ParseData_ReturnsFloatProperty_WhenGivenFloatProperty)
    {
        // Arrange
        std::string expectedName = "textName";
        std::string expectedValue = "23.67";
        float expectedValueNumber = 23.67f;

        std::string givenName = "Property";
        std::shared_ptr<PrimitiveData> given =
            std::make_shared<PrimitiveData>(givenName, std::vector<std::shared_ptr<PrimitiveData>>());

        // Property Details
        given->SetProperty("type", "float");
        given->SetProperty("name", expectedName);
        given->SetProperty("value", expectedValue);

        std::shared_ptr<PrimitiveData> gameComponent = ReturnGameComponent(given);
        std::shared_ptr<PrimitiveData> gameObject = ReturnGameObjectData(gameComponent);
        std::shared_ptr<PrimitiveData> scene = ReturnSceneData(gameObject);

        // Act
        std::shared_ptr<ParsedData> actual = testClass->ParseData(scene);

        // Assert
        std::vector<std::shared_ptr<const ParsedData>> componentChildren =
            actual->GetChildren()[0]->GetChildren()[0]->GetChildren();
        ASSERT_EQ(1, componentChildren.size());
        std::shared_ptr<const ParsedData> property =
            actual->GetChildren()[0]->GetChildren()[0]->GetChildren()[0];
        ASSERT_TRUE(property);

        // Type
        std::string actualValue = std::string();
        property->TryGetProperty("type", actualValue);
        ASSERT_EQ("float", actualValue);

        // Name
        property->TryGetProperty("name", actualValue);
        ASSERT_EQ(expectedName, actualValue);

        // Value
        property->TryGetProperty("value", actualValue);
        ASSERT_EQ(expectedValue, actualValue);

        // Value as float
        float actualIntValue = float();
        property->TryGetProperty("value", actualIntValue);
        ASSERT_EQ(expectedValueNumber, actualIntValue);
    }

    TEST_F(SceneDataParserTests, ParseData_ReturnsEmpty_WhenGivenFloatValueIsNotAnFloat)
    {
        // Arrange
        std::string expectedName = "textName";
        std::string expectedValue = "fdsfds";

        std::string givenName = "Property";
        std::shared_ptr<PrimitiveData> given =
            std::make_shared<PrimitiveData>(givenName, std::vector<std::shared_ptr<PrimitiveData>>());

        // Property Details
        given->SetProperty("type", "float");
        given->SetProperty("name", expectedName);
        given->SetProperty("value", expectedValue);

        std::shared_ptr<PrimitiveData> gameComponent = ReturnGameComponent(given);
        std::shared_ptr<PrimitiveData> gameObject = ReturnGameObjectData(gameComponent);
        std::shared_ptr<PrimitiveData> scene = ReturnSceneData(gameObject);

        // Act
        std::shared_ptr<ParsedData> actual = testClass->ParseData(scene);

        // Assert
        std::vector<std::shared_ptr<const ParsedData>> componentChildren =
            actual->GetChildren()[0]->GetChildren()[0]->GetChildren();
        ASSERT_EQ(0, componentChildren.size());
    }

#pragma endregion

#pragma region Bool Property
    TEST_F(SceneDataParserTests, ParseData_ReturnsBoolProperty_WhenGivenBoolProperty)
    {
        // Arrange
        std::string expectedName = "textName";
        std::string expectedValue = "true";
        bool expectedValueBool = true;

        std::string givenName = "Property";
        std::shared_ptr<PrimitiveData> given =
            std::make_shared<PrimitiveData>(givenName, std::vector<std::shared_ptr<PrimitiveData>>());

        // Property Details
        given->SetProperty("type", "bool");
        given->SetProperty("name", expectedName);
        given->SetProperty("value", expectedValue);

        std::shared_ptr<PrimitiveData> gameComponent = ReturnGameComponent(given);
        std::shared_ptr<PrimitiveData> gameObject = ReturnGameObjectData(gameComponent);
        std::shared_ptr<PrimitiveData> scene = ReturnSceneData(gameObject);

        // Act
        std::shared_ptr<ParsedData> actual = testClass->ParseData(scene);

        // Assert
        std::vector<std::shared_ptr<const ParsedData>> componentChildren =
            actual->GetChildren()[0]->GetChildren()[0]->GetChildren();
        ASSERT_EQ(1, componentChildren.size());
        std::shared_ptr<const ParsedData> property =
            actual->GetChildren()[0]->GetChildren()[0]->GetChildren()[0];
        ASSERT_TRUE(property);

        // Type
        std::string actualValue = std::string();
        property->TryGetProperty("type", actualValue);
        ASSERT_EQ("bool", actualValue);

        // Name
        property->TryGetProperty("name", actualValue);
        ASSERT_EQ(expectedName, actualValue);

        // Value
        property->TryGetProperty("value", actualValue);
        ASSERT_EQ(expectedValue, actualValue);

        // Value as float
        bool actualIntValue = bool();
        property->TryGetBoolProperty("value", actualIntValue);
        ASSERT_EQ(expectedValueBool, actualIntValue);
    }

    TEST_F(SceneDataParserTests, ParseData_ReturnsEmpty_WhenGivenBoolValueIsNotAnBool)
    {
        // Arrange
        std::string expectedName = "textName";
        std::string expectedValue = "fdsfds";

        std::string givenName = "Property";
        std::shared_ptr<PrimitiveData> given =
            std::make_shared<PrimitiveData>(givenName, std::vector<std::shared_ptr<PrimitiveData>>());

        // Property Details
        given->SetProperty("type", "bool");
        given->SetProperty("name", expectedName);
        given->SetProperty("value", expectedValue);

        std::shared_ptr<PrimitiveData> gameComponent = ReturnGameComponent(given);
        std::shared_ptr<PrimitiveData> gameObject = ReturnGameObjectData(gameComponent);
        std::shared_ptr<PrimitiveData> scene = ReturnSceneData(gameObject);

        // Act
        std::shared_ptr<ParsedData> actual = testClass->ParseData(scene);

        // Assert
        std::vector<std::shared_ptr<const ParsedData>> componentChildren =
            actual->GetChildren()[0]->GetChildren()[0]->GetChildren();
        ASSERT_EQ(0, componentChildren.size());
    }

    TEST_F(SceneDataParserTests, ParseData_ReturnsBoolPropertyInLowercase_WhenGivenIsUppercase)
    {
        // Arrange
        std::string expectedName = "textName";
        std::string givenValue = "TRUE";
        std::string expectedBool = "true";
        bool expectedValueBool = true;

        std::string givenName = "Property";
        std::shared_ptr<PrimitiveData> given =
            std::make_shared<PrimitiveData>(givenName, std::vector<std::shared_ptr<PrimitiveData>>());

        // Property Details
        given->SetProperty("type", "bool");
        given->SetProperty("name", expectedName);
        given->SetProperty("value", givenValue);

        std::shared_ptr<PrimitiveData> gameComponent = ReturnGameComponent(given);
        std::shared_ptr<PrimitiveData> gameObject = ReturnGameObjectData(gameComponent);
        std::shared_ptr<PrimitiveData> scene = ReturnSceneData(gameObject);

        // Act
        std::shared_ptr<ParsedData> actual = testClass->ParseData(scene);

        // Assert
        std::vector<std::shared_ptr<const ParsedData>> componentChildren =
            actual->GetChildren()[0]->GetChildren()[0]->GetChildren();
        ASSERT_EQ(1, componentChildren.size());
        std::shared_ptr<const ParsedData> property =
            actual->GetChildren()[0]->GetChildren()[0]->GetChildren()[0];
        ASSERT_TRUE(property);

        // Type
        std::string actualValue = std::string();
        property->TryGetProperty("type", actualValue);
        ASSERT_EQ("bool", actualValue);

        // Name
        property->TryGetProperty("name", actualValue);
        ASSERT_EQ(expectedName, actualValue);

        // Value
        property->TryGetProperty("value", actualValue);
        ASSERT_EQ(expectedBool, actualValue);

        // Value as float
        bool actualIntValue = bool();
        property->TryGetBoolProperty("value", actualIntValue);
        ASSERT_EQ(expectedValueBool, actualIntValue);
    }

#pragma endregion
}