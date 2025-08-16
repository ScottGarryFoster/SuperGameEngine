#include <memory>
#include <gtest/gtest.h>

#include "ModifiableDocument.h"
#include "Collection/Vector/VectorHelpers.h"
#include "Console/ConsoleLog.h"
#include "Logger/Log.h"
#include "Position/FVector4I.h"
#include "Text/StringHelpers.h"
#include "UniversalObjectData/ExplicitDocumentModifiableUniversalObjectData.h"

using namespace FatedQuestLibraries;
namespace StandardObjectsTests
{
    class ExplicitDocumentModifiableUniversalObjectDataTests : public ::testing::Test
    {
    public:
        ExplicitDocumentModifiableUniversalObjectDataTests()
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
    };

#pragma region String

    TEST_F(ExplicitDocumentModifiableUniversalObjectDataTests, GetString_ReturnsEmpty_WhenNothingGiven)
    {
        // Arrange
        std::string expected = {};
        std::string givenKey = "myKey";
        auto document = std::make_shared<ExplicitDocumentModifiableUniversalObjectData>();

        // Act
        std::string actual = document->GetString(givenKey);

        // Assert
        ASSERT_EQ(expected, actual);
    }

    TEST_F(ExplicitDocumentModifiableUniversalObjectDataTests, GetString_ReturnsValue_WhenGivenStringWithSameKey)
    {
        // Arrange
        std::string expected = "MyString";
        std::string givenKey = "myKey";
        auto document = std::make_shared<ExplicitDocumentModifiableUniversalObjectData>();

        document->SetString(givenKey, expected);

        // Act
        std::string actual = document->GetString(givenKey);

        // Assert
        ASSERT_EQ(expected, actual);
    }

    TEST_F(ExplicitDocumentModifiableUniversalObjectDataTests, GetString_ReturnsEmpty_WhenKeyGivenDoesNotMatchKeySet)
    {
        // Arrange
        std::string expected = {};
        std::string givenKey = "myKey";
        std::string setKey = "otherKey";
        auto document = std::make_shared<ExplicitDocumentModifiableUniversalObjectData>();

        document->SetString(setKey, expected);

        // Act
        std::string actual = document->GetString(givenKey);

        // Assert
        ASSERT_EQ(expected, actual);
    }

    TEST_F(ExplicitDocumentModifiableUniversalObjectDataTests, ListStrings_ReturnsEmpty_WhenNothingGiven)
    {
        // Arrange
        auto document = std::make_shared<ExplicitDocumentModifiableUniversalObjectData>();

        // Act
        std::vector<std::string> actual = document->ListStrings();

        // Assert
        ASSERT_EQ(0, actual.size());
    }

    TEST_F(ExplicitDocumentModifiableUniversalObjectDataTests, ListStrings_ReturnsStringValue_WhenGivenString)
    {
        // Arrange
        std::string expected = "MyString";
        std::string givenKey = "myKey";
        auto document = std::make_shared<ExplicitDocumentModifiableUniversalObjectData>();

        document->SetString(givenKey, expected);

        // Act
        std::vector<std::string> actual = document->ListStrings();

        // Assert
        ASSERT_EQ(1, actual.size());

        bool containsKey = VectorHelpers::ContainsString(actual, givenKey);
        ASSERT_TRUE(containsKey) << "Could not find: " << givenKey;
    }

    TEST_F(ExplicitDocumentModifiableUniversalObjectDataTests, ListStrings_ReturnsAllStrings_WhenGivenMany)
    {
        // Arrange
        std::string expected = "MyString";
        std::string givenKey = "myKey";
        std::string givenKey2 = "mySecondKey";
        auto document = std::make_shared<ExplicitDocumentModifiableUniversalObjectData>();

        document->SetString(givenKey, expected);
        document->SetString(givenKey2, expected);

        // Act
        std::vector<std::string> actual = document->ListStrings();

        // Assert
        ASSERT_EQ(2, actual.size());

        ASSERT_TRUE(VectorHelpers::ContainsString(actual, givenKey)) << "Could not find: " << givenKey;
        ASSERT_TRUE(VectorHelpers::ContainsString(actual, givenKey2)) << "Could not find: " << givenKey2;
    }

    TEST_F(ExplicitDocumentModifiableUniversalObjectDataTests, IsStringLoaded_ReturnsFalse_WhenGivenNoStrings)
    {
        // Arrange
        std::string givenKey = "myKey";
        auto document = std::make_shared<ExplicitDocumentModifiableUniversalObjectData>();

        // Act
        bool actual = document->IsStringLoaded(givenKey);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(ExplicitDocumentModifiableUniversalObjectDataTests, IsStringLoaded_ReturnsTrue_WhenStringIsGiven)
    {
        // Arrange
        std::string givenKey = "myKey";
        std::string givenValue = "MyValue";
        auto document = std::make_shared<ExplicitDocumentModifiableUniversalObjectData>();

        document->SetString(givenKey, givenValue);

        // Act
        bool actual = document->IsStringLoaded(givenKey);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(ExplicitDocumentModifiableUniversalObjectDataTests, IsStringLoaded_ReturnsFalse_WhenGivenAStringButKeyDoesNotMatch)
    {
        // Arrange
        std::string givenKey = "myKey";
        std::string givenValue = "MyValue";
        std::string setKey = "otherKey";
        auto document = std::make_shared<ExplicitDocumentModifiableUniversalObjectData>();

        document->SetString(setKey, givenValue);

        // Act
        bool actual = document->IsStringLoaded(givenKey);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(ExplicitDocumentModifiableUniversalObjectDataTests, UnsetString_ReturnsFalse_WhenNothingIsSet)
    {
        // Arrange
        std::string givenKey = "myKey";
        auto document = std::make_shared<ExplicitDocumentModifiableUniversalObjectData>();

        // Act
        bool actual = document->UnsetString(givenKey);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(ExplicitDocumentModifiableUniversalObjectDataTests, UnsetString_ReturnsTrue_WhenTheKeyIsSet)
    {
        // Arrange
        std::string givenKey = "myKey";
        std::string setValue = "MyValue";
        auto document = std::make_shared<ExplicitDocumentModifiableUniversalObjectData>();

        document->SetString(givenKey, setValue);

        // Act
        bool actual = document->UnsetString(givenKey);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(ExplicitDocumentModifiableUniversalObjectDataTests, IsStringLoaded_ReturnsFalse_WhenUnloadedAString)
    {
        // Arrange
        std::string givenKey = "myKey";
        std::string setValue = "MyValue";
        auto document = std::make_shared<ExplicitDocumentModifiableUniversalObjectData>();

        document->SetString(givenKey, setValue);
        document->UnsetString(givenKey);

        // Act
        bool actual = document->IsStringLoaded(givenKey);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(ExplicitDocumentModifiableUniversalObjectDataTests, GetString_ReturnsEmpty_WhenUnloadedAString)
    {
        // Arrange
        std::string givenKey = "myKey";
        std::string setValue = "MyValue";
        std::string expected = {};
        auto document = std::make_shared<ExplicitDocumentModifiableUniversalObjectData>();

        document->SetString(givenKey, setValue);
        document->UnsetString(givenKey);

        // Act
        std::string actual = document->GetString(givenKey);

        // Assert
        ASSERT_EQ(expected, actual);
    }

    TEST_F(ExplicitDocumentModifiableUniversalObjectDataTests, ExportToDocument_HasString_WhenStringIsSet)
    {
        // Arrange
        std::string givenKey = "myKey";
        std::string setValue = "MyValue";
        auto document = std::make_shared<ExplicitDocumentModifiableUniversalObjectData>();

        document->SetString(givenKey, setValue);

        // Act
        std::shared_ptr<ModifiableDocument> actual = document->ExportToDocument();

        // Assert
        std::shared_ptr<StoredDocumentNode> root = actual->GetRoot();
        ASSERT_TRUE(root) << "No root found";

        bool hasStringsNode = false;
        bool hasStringNode = false;
        for (auto child = root->GetFirstChild(); child; child = child->GetAdjacentNode())
        {
            std::string name = StringHelpers::ToLower(child->Name());
            if (name == "strings")
            {
                hasStringsNode = true;
                for (auto stringChild = child->GetFirstChild(); stringChild; stringChild = stringChild->GetAdjacentNode())
                {
                    std::string innerName = StringHelpers::ToLower(stringChild->Name());
                    if (innerName == "string")
                    {
                        hasStringNode = true;
                        std::shared_ptr<StoredDocumentAttribute> attribute = stringChild->Attribute("key", CaseSensitivity::IgnoreCase);
                        ASSERT_TRUE(attribute) << "String node found but it did not have a Key attribute.";
                        ASSERT_EQ(givenKey, attribute->Value()) << "Value of Key did not match.";

                        std::shared_ptr<StoredDocumentAttribute> valueAttribute = stringChild->Attribute("value", CaseSensitivity::IgnoreCase);
                        ASSERT_TRUE(valueAttribute) << "String node found but it did not have a Value attribute.";
                        ASSERT_EQ(setValue, valueAttribute->Value()) << "Value of Key did not match.";
                    }
                }
            }
        }

        ASSERT_TRUE(hasStringsNode) << "No Strings Node found";
        ASSERT_TRUE(hasStringNode) << "No String Node found (singular)";
    }

#pragma endregion

#pragma region Int

    TEST_F(ExplicitDocumentModifiableUniversalObjectDataTests, GetInt_ReturnsMinusOne_WhenNothingGiven)
    {
        // Arrange
        int expected = -1;
        std::string givenKey = "myKey";
        auto document = std::make_shared<ExplicitDocumentModifiableUniversalObjectData>();

        // Act
        int actual = document->GetInt(givenKey);

        // Assert
        ASSERT_EQ(expected, actual);
    }

    TEST_F(ExplicitDocumentModifiableUniversalObjectDataTests, GetInt_ReturnsValue_WhenGivenIntWithSameKey)
    {
        // Arrange
        int expected = 4;
        std::string givenKey = "myKey";
        auto document = std::make_shared<ExplicitDocumentModifiableUniversalObjectData>();

        document->SetInt(givenKey, expected);

        // Act
        int actual = document->GetInt(givenKey);

        // Assert
        ASSERT_EQ(expected, actual);
    }

    TEST_F(ExplicitDocumentModifiableUniversalObjectDataTests, GetInt_ReturnsEmpty_WhenKeyGivenDoesNotMatchKeySet)
    {
        // Arrange
        int expected = -1;
        std::string givenKey = "myKey";
        std::string setKey = "otherKey";
        auto document = std::make_shared<ExplicitDocumentModifiableUniversalObjectData>();

        document->SetInt(setKey, expected);

        // Act
        int actual = document->GetInt(givenKey);

        // Assert
        ASSERT_EQ(expected, actual);
    }

    TEST_F(ExplicitDocumentModifiableUniversalObjectDataTests, ListInts_ReturnsEmpty_WhenNothingGiven)
    {
        // Arrange
        auto document = std::make_shared<ExplicitDocumentModifiableUniversalObjectData>();

        // Act
        std::vector<std::string> actual = document->ListInts();

        // Assert
        ASSERT_EQ(0, actual.size());
    }

    TEST_F(ExplicitDocumentModifiableUniversalObjectDataTests, ListInts_ReturnsKeysValue_WhenGivenKeys)
    {
        // Arrange
        int expected = 54;
        std::string givenKey = "myKey";
        auto document = std::make_shared<ExplicitDocumentModifiableUniversalObjectData>();

        document->SetInt(givenKey, expected);

        // Act
        std::vector<std::string> actual = document->ListInts();

        // Assert
        ASSERT_EQ(1, actual.size());

        bool containsKey = VectorHelpers::ContainsString(actual, givenKey);
        ASSERT_TRUE(containsKey) << "Could not find: " << givenKey;
    }

    TEST_F(ExplicitDocumentModifiableUniversalObjectDataTests, ListInts_ReturnsAllKeys_WhenGivenMany)
    {
        // Arrange
        int expected = 876;
        std::string givenKey = "myKey";
        std::string givenKey2 = "mySecondKey";
        auto document = std::make_shared<ExplicitDocumentModifiableUniversalObjectData>();

        document->SetInt(givenKey, expected);
        document->SetInt(givenKey2, expected);

        // Act
        std::vector<std::string> actual = document->ListInts();

        // Assert
        ASSERT_EQ(2, actual.size());

        ASSERT_TRUE(VectorHelpers::ContainsString(actual, givenKey)) << "Could not find: " << givenKey;
        ASSERT_TRUE(VectorHelpers::ContainsString(actual, givenKey2)) << "Could not find: " << givenKey2;
    }

    TEST_F(ExplicitDocumentModifiableUniversalObjectDataTests, IsIntLoaded_ReturnsFalse_WhenGivenNoKeys)
    {
        // Arrange
        std::string givenKey = "myKey";
        auto document = std::make_shared<ExplicitDocumentModifiableUniversalObjectData>();

        // Act
        bool actual = document->IsIntLoaded(givenKey);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(ExplicitDocumentModifiableUniversalObjectDataTests, IsIntLoaded_ReturnsTrue_WhenKeysIsGiven)
    {
        // Arrange
        std::string givenKey = "myKey";
        int givenValue = 667;
        auto document = std::make_shared<ExplicitDocumentModifiableUniversalObjectData>();

        document->SetInt(givenKey, givenValue);

        // Act
        bool actual = document->IsIntLoaded(givenKey);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(ExplicitDocumentModifiableUniversalObjectDataTests, IsIntLoaded_ReturnsFalse_WhenGivenAStringButKeyDoesNotMatch)
    {
        // Arrange
        std::string givenKey = "myKey";
        std::string givenValue = "MyValue";
        std::string setKey = "otherKey";
        auto document = std::make_shared<ExplicitDocumentModifiableUniversalObjectData>();

        document->SetString(setKey, givenValue);

        // Act
        bool actual = document->IsStringLoaded(givenKey);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(ExplicitDocumentModifiableUniversalObjectDataTests, UnsetInt_ReturnsFalse_WhenNothingIsSet)
    {
        // Arrange
        std::string givenKey = "myKey";
        auto document = std::make_shared<ExplicitDocumentModifiableUniversalObjectData>();

        // Act
        bool actual = document->UnsetInt(givenKey);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(ExplicitDocumentModifiableUniversalObjectDataTests, UnsetInt_ReturnsTrue_WhenTheKeyIsSet)
    {
        // Arrange
        std::string givenKey = "myKey";
        int setValue = 5645;
        auto document = std::make_shared<ExplicitDocumentModifiableUniversalObjectData>();

        document->SetInt(givenKey, setValue);

        // Act
        bool actual = document->UnsetInt(givenKey);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(ExplicitDocumentModifiableUniversalObjectDataTests, IsIntLoaded_ReturnsFalse_WhenUnloadedAnInt)
    {
        // Arrange
        std::string givenKey = "myKey";
        int setValue = 6546;
        auto document = std::make_shared<ExplicitDocumentModifiableUniversalObjectData>();

        document->SetInt(givenKey, setValue);
        document->UnsetInt(givenKey);

        // Act
        bool actual = document->IsIntLoaded(givenKey);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(ExplicitDocumentModifiableUniversalObjectDataTests, GetInt_ReturnsEmpty_WhenUnloadedAnInt)
    {
        // Arrange
        std::string givenKey = "myKey";
        int setValue = 645;
        int expected = -1;
        auto document = std::make_shared<ExplicitDocumentModifiableUniversalObjectData>();

        document->SetInt(givenKey, setValue);
        document->UnsetInt(givenKey);

        // Act
        int actual = document->GetInt(givenKey);

        // Assert
        ASSERT_EQ(expected, actual);
    }

    TEST_F(ExplicitDocumentModifiableUniversalObjectDataTests, ExportToDocument_HasInt_WhenIntIsSet)
    {
        // Arrange
        std::string givenKey = "myKey";
        int setValue = 642;
        auto document = std::make_shared<ExplicitDocumentModifiableUniversalObjectData>();

        document->SetInt(givenKey, setValue);

        // Act
        std::shared_ptr<ModifiableDocument> actual = document->ExportToDocument();

        // Assert
        std::shared_ptr<StoredDocumentNode> root = actual->GetRoot();
        ASSERT_TRUE(root) << "No root found";

        bool hasIntsNode = false;
        bool hasIntNode = false;
        for (auto child = root->GetFirstChild(); child; child = child->GetAdjacentNode())
        {
            std::string name = StringHelpers::ToLower(child->Name());
            if (name == "ints")
            {
                hasIntsNode = true;
                for (auto stringChild = child->GetFirstChild(); stringChild; stringChild = stringChild->GetAdjacentNode())
                {
                    std::string innerName = StringHelpers::ToLower(stringChild->Name());
                    if (innerName == "int")
                    {
                        hasIntNode = true;

                        std::shared_ptr<StoredDocumentAttribute> attribute = stringChild->Attribute("key", CaseSensitivity::IgnoreCase);
                        ASSERT_TRUE(attribute) << "Int node found but it did not have a Key attribute.";
                        ASSERT_EQ(givenKey, attribute->Value()) << "Value of Key did not match.";

                        std::shared_ptr<StoredDocumentAttribute> valueAttribute = stringChild->Attribute("value", CaseSensitivity::IgnoreCase);
                        ASSERT_TRUE(valueAttribute) << "Int node found but it did not have a Value attribute.";
                        ASSERT_EQ(std::to_string(setValue), valueAttribute->Value()) << "Value of Key did not match.";
                    }
                }
            }
        }

        ASSERT_TRUE(hasIntsNode) << "No Ints Node found";
        ASSERT_TRUE(hasIntNode) << "No Int Node found (singular)";
    }

#pragma endregion

#pragma region Vector4I

    TEST_F(ExplicitDocumentModifiableUniversalObjectDataTests, GetVector4I_ReturnsEmpty_WhenNothingGiven)
    {
        // Arrange
        std::shared_ptr<FVector4I> expected = {};
        std::string givenKey = "myKey";
        auto document = std::make_shared<ExplicitDocumentModifiableUniversalObjectData>();

        // Act
        std::shared_ptr<FVector4I> actual = document->GetVector4I(givenKey);

        // Assert
        ASSERT_EQ(expected, actual);
    }

    TEST_F(ExplicitDocumentModifiableUniversalObjectDataTests, GetVector4I_ReturnsValue_WhenGivenVectorWithSameKey)
    {
        // Arrange
        std::shared_ptr<FVector4I> expected = std::make_shared<FVector4I>(1, 2, 3, 4);
        std::string givenKey = "myKey";
        auto document = std::make_shared<ExplicitDocumentModifiableUniversalObjectData>();

        document->SetVector4I(givenKey, *expected);

        // Act
        std::shared_ptr<FVector4I> actual = document->GetVector4I(givenKey);

        // Assert
        ASSERT_EQ(expected->GetX(), actual->GetX()) << "X: " << expected->GetX() << " != " << actual->GetX();
        ASSERT_EQ(expected->GetY(), actual->GetY()) << "Y: " << expected->GetY() << " != " << actual->GetY();
        ASSERT_EQ(expected->GetZ(), actual->GetZ()) << "X: " << expected->GetZ() << " != " << actual->GetZ();
        ASSERT_EQ(expected->GetW(), actual->GetW()) << "W: " << expected->GetW() << " != " << actual->GetW();
    }

    TEST_F(ExplicitDocumentModifiableUniversalObjectDataTests, GetVector4I_ReturnsEmpty_WhenKeyGivenDoesNotMatchKeySet)
    {
        // Arrange
        std::shared_ptr<FVector4I> givenValue = std::make_shared<FVector4I>(1, 2, 3, 4);
        std::string givenKey = "myKey";
        std::string setKey = "otherKey";
        auto document = std::make_shared<ExplicitDocumentModifiableUniversalObjectData>();

        document->SetVector4I(setKey, *givenValue);

        // Act
        std::shared_ptr<FVector4I> actual = document->GetVector4I(givenKey);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(ExplicitDocumentModifiableUniversalObjectDataTests, ListVector4Is_ReturnsEmpty_WhenNothingGiven)
    {
        // Arrange
        auto document = std::make_shared<ExplicitDocumentModifiableUniversalObjectData>();

        // Act
        std::vector<std::string> actual = document->ListVector4Is();

        // Assert
        ASSERT_EQ(0, actual.size());
    }

    TEST_F(ExplicitDocumentModifiableUniversalObjectDataTests, ListVector4Is_ReturnsKeysValue_WhenGivenKeys)
    {
        // Arrange
        std::shared_ptr<FVector4I> givenValue = std::make_shared<FVector4I>(1, 2, 3, 4);
        std::string givenKey = "myKey";
        auto document = std::make_shared<ExplicitDocumentModifiableUniversalObjectData>();

        document->SetVector4I(givenKey, *givenValue);

        // Act
        std::vector<std::string> actual = document->ListVector4Is();

        // Assert
        ASSERT_EQ(1, actual.size());

        bool containsKey = VectorHelpers::ContainsString(actual, givenKey);
        ASSERT_TRUE(containsKey) << "Could not find: " << givenKey;
    }

    TEST_F(ExplicitDocumentModifiableUniversalObjectDataTests, ListVector4Is_ReturnsAllKeys_WhenGivenMany)
    {
        // Arrange
        std::shared_ptr<FVector4I> givenValue = std::make_shared<FVector4I>(1, 2, 3, 4);
        std::string givenKey = "myKey";
        std::string givenKey2 = "mySecondKey";
        auto document = std::make_shared<ExplicitDocumentModifiableUniversalObjectData>();

        document->SetVector4I(givenKey, *givenValue);
        document->SetVector4I(givenKey2, *givenValue);

        // Act
        std::vector<std::string> actual = document->ListVector4Is();

        // Assert
        ASSERT_EQ(2, actual.size());

        ASSERT_TRUE(VectorHelpers::ContainsString(actual, givenKey)) << "Could not find: " << givenKey;
        ASSERT_TRUE(VectorHelpers::ContainsString(actual, givenKey2)) << "Could not find: " << givenKey2;
    }

    TEST_F(ExplicitDocumentModifiableUniversalObjectDataTests, IsVector4ILoaded_ReturnsFalse_WhenGivenNoKeys)
    {
        // Arrange
        std::string givenKey = "myKey";
        auto document = std::make_shared<ExplicitDocumentModifiableUniversalObjectData>();

        // Act
        bool actual = document->IsVector4ILoaded(givenKey);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(ExplicitDocumentModifiableUniversalObjectDataTests, IsVector4ILoaded_ReturnsTrue_WhenKeysIsGiven)
    {
        // Arrange
        std::string givenKey = "myKey";
        std::shared_ptr<FVector4I> givenValue = std::make_shared<FVector4I>(1, 2, 3, 4);
        auto document = std::make_shared<ExplicitDocumentModifiableUniversalObjectData>();

        document->SetVector4I(givenKey, *givenValue);

        // Act
        bool actual = document->IsVector4ILoaded(givenKey);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(ExplicitDocumentModifiableUniversalObjectDataTests, IsVector4ILoaded_ReturnsFalse_WhenGivenAVectorButKeyDoesNotMatch)
    {
        // Arrange
        std::string givenKey = "myKey";
        std::shared_ptr<FVector4I> givenValue = std::make_shared<FVector4I>(1, 2, 3, 4);
        std::string setKey = "otherKey";
        auto document = std::make_shared<ExplicitDocumentModifiableUniversalObjectData>();

        document->SetVector4I(setKey, *givenValue);

        // Act
        bool actual = document->IsVector4ILoaded(givenKey);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(ExplicitDocumentModifiableUniversalObjectDataTests, UnsetVector4I_ReturnsFalse_WhenNothingIsSet)
    {
        // Arrange
        std::string givenKey = "myKey";
        auto document = std::make_shared<ExplicitDocumentModifiableUniversalObjectData>();

        // Act
        bool actual = document->UnsetVector4I(givenKey);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(ExplicitDocumentModifiableUniversalObjectDataTests, UnsetVector4I_ReturnsTrue_WhenTheKeyIsSet)
    {
        // Arrange
        std::string givenKey = "myKey";
        std::shared_ptr<FVector4I> givenValue = std::make_shared<FVector4I>(1, 2, 3, 4);
        auto document = std::make_shared<ExplicitDocumentModifiableUniversalObjectData>();

        document->SetVector4I(givenKey, *givenValue);

        // Act
        bool actual = document->UnsetVector4I(givenKey);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(ExplicitDocumentModifiableUniversalObjectDataTests, IsVector4ILoaded_ReturnsFalse_WhenUnloadedTheKey)
    {
        // Arrange
        std::string givenKey = "myKey";
        std::shared_ptr<FVector4I> givenValue = std::make_shared<FVector4I>(1, 2, 3, 4);
        auto document = std::make_shared<ExplicitDocumentModifiableUniversalObjectData>();

        document->SetVector4I(givenKey, *givenValue);
        document->UnsetVector4I(givenKey);

        // Act
        bool actual = document->IsVector4ILoaded(givenKey);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(ExplicitDocumentModifiableUniversalObjectDataTests, IsVector4ILoaded_ReturnsEmpty_WhenUnloadedTheKey)
    {
        // Arrange
        std::string givenKey = "myKey";
        std::shared_ptr<FVector4I> givenValue = std::make_shared<FVector4I>(1, 2, 3, 4);
        std::shared_ptr<FVector4I> expected = {};
        auto document = std::make_shared<ExplicitDocumentModifiableUniversalObjectData>();

        document->SetVector4I(givenKey, *givenValue);
        document->UnsetVector4I(givenKey);

        // Act
        std::shared_ptr<FVector4I> actual = document->GetVector4I(givenKey);

        // Assert
        ASSERT_EQ(expected, actual);
    }

    TEST_F(ExplicitDocumentModifiableUniversalObjectDataTests, ExportToDocument_HasVector4I_WhenVectorIsSet)
    {
        // Arrange
        std::string givenKey = "myKey";
        std::shared_ptr<FVector4I> setValue = std::make_shared<FVector4I>(1, 2, 3, 4);
        auto document = std::make_shared<ExplicitDocumentModifiableUniversalObjectData>();

        document->SetVector4I(givenKey, *setValue);

        // Act
        std::shared_ptr<ModifiableDocument> actual = document->ExportToDocument();

        // Assert
        std::shared_ptr<StoredDocumentNode> root = actual->GetRoot();
        ASSERT_TRUE(root) << "No root found";

        bool hasVector4IsNode = false;
        bool hasVector4INode = false;
        for (auto child = root->GetFirstChild(); child; child = child->GetAdjacentNode())
        {
            std::string name = StringHelpers::ToLower(child->Name());
            if (name == "vector4is")
            {
                hasVector4IsNode = true;
                for (auto stringChild = child->GetFirstChild(); stringChild; stringChild = stringChild->GetAdjacentNode())
                {
                    std::string innerName = StringHelpers::ToLower(stringChild->Name());
                    if (innerName == "vector4i")
                    {
                        hasVector4INode = true;

                        {
                            std::shared_ptr<StoredDocumentAttribute> attribute = stringChild->Attribute("key", CaseSensitivity::IgnoreCase);
                            ASSERT_TRUE(attribute) << "Vector4I node found but it did not have a Key attribute.";
                            ASSERT_EQ(givenKey, attribute->Value()) << "Value of Key did not match.";
                        }

                        {
                            std::shared_ptr<StoredDocumentAttribute> attribute = stringChild->Attribute("x", CaseSensitivity::IgnoreCase);
                            ASSERT_TRUE(attribute) << "Vector4I node found but it did not have a X attribute.";
                            ASSERT_EQ(std::to_string(setValue->GetX()), attribute->Value()) << "X Value of Key did not match.";
                        }

                        {
                            std::shared_ptr<StoredDocumentAttribute> attribute = stringChild->Attribute("y", CaseSensitivity::IgnoreCase);
                            ASSERT_TRUE(attribute) << "Vector4I node found but it did not have a Y attribute.";
                            ASSERT_EQ(std::to_string(setValue->GetY()), attribute->Value()) << "Y Value of Key did not match.";
                        }

                        {
                            std::shared_ptr<StoredDocumentAttribute> attribute = stringChild->Attribute("z", CaseSensitivity::IgnoreCase);
                            ASSERT_TRUE(attribute) << "Vector4I node found but it did not have a Z attribute.";
                            ASSERT_EQ(std::to_string(setValue->GetZ()), attribute->Value()) << "Z Value of Key did not match.";
                        }

                        {
                            std::shared_ptr<StoredDocumentAttribute> attribute = stringChild->Attribute("w", CaseSensitivity::IgnoreCase);
                            ASSERT_TRUE(attribute) << "Vector4I node found but it did not have a W attribute.";
                            ASSERT_EQ(std::to_string(setValue->GetW()), attribute->Value()) << "W Value of Key did not match.";
                        }
                    }
                }
            }
        }

        ASSERT_TRUE(hasVector4IsNode) << "No Vector4Is Node found";
        ASSERT_TRUE(hasVector4INode) << "No Vector4I Node found (singular)";
    }

#pragma endregion
}