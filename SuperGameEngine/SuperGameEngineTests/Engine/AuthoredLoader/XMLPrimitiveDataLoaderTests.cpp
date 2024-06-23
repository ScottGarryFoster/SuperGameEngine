#include "../../LibraryIncludes.h"
#include "../../../SuperGameEngine/Engine/AuthoredLoader/XMLPrimitiveDataLoader.h"

using namespace StandardCLibrary;
using namespace SuperGameEngine;

namespace SuperGameEngineTests_Engine_AuthoredLoader
{
    class XMLPrimitiveDataLoaderTests : public ::testing::Test
    {
    public:
        XMLPrimitiveDataLoaderTests()
        {
        }

    protected:

        std::shared_ptr<PrimitiveDataLoader> m_primitiveDataLoader;

        void SetUp() override
        {
            m_primitiveDataLoader = std::make_shared<XMLPrimitiveDataLoader>();
        }

        void TearDown() override
        {
            m_primitiveDataLoader.reset();
        }
    };

    TEST_F(XMLPrimitiveDataLoaderTests, ExtractData_ReturnsEmptyData_WhenDataIsNotValidXML)
    {
        std::string given = "T";

        std::shared_ptr<PrimitiveData> actual = m_primitiveDataLoader->ExtractData(given);

        ASSERT_FALSE(actual);
    }

    TEST_F(XMLPrimitiveDataLoaderTests, ExtractData_ReturnsPrimitiveData_WhenDataIsValidXML)
    {
        std::string given = "<RandomTag></RandomTag>";

        std::shared_ptr<PrimitiveData> actual = m_primitiveDataLoader->ExtractData(given);

        ASSERT_TRUE(actual);
    }

    TEST_F(XMLPrimitiveDataLoaderTests, ExtractData_ReturnsNameOfFirstTag_WhenTagFoundInFile)
    {
        std::string given = "<RandomTag></RandomTag>";
        std::string expected = "RandomTag";

        std::shared_ptr<PrimitiveData> actual = m_primitiveDataLoader->ExtractData(given);

        ASSERT_EQ(expected, actual->GetName());
    }

    TEST_F(XMLPrimitiveDataLoaderTests, ExtractData_ReturnsChildName_WhenTagHasAChildName)
    {
        std::string given = "<RandomTag><InnerTag></InnerTag></RandomTag>";
        std::string expected = "InnerTag";

        std::shared_ptr<PrimitiveData> actual = m_primitiveDataLoader->ExtractData(given);

        ASSERT_EQ(1, actual->GetChildren().size());
        ASSERT_EQ(expected, actual->GetChildren()[0]->GetName());
    }

    TEST_F(XMLPrimitiveDataLoaderTests, ExtractData_ReturnsAllChildrensNames_WhenGivenACompleteTree)
    {
        // Arrange
        std::string given = "<RandomTag>";
            given += "<InnerTag>";
                given += "<InnerName1 />";
                given += "<InnerName2 />";
                given += "<InnerName3 />";
                given += "<InnerName4 />";
            given += "</InnerTag>";
            given += "<InnerTagB>";
                given += "<InnerName1B />";
                given += "<InnerName2B />";
                given += "<InnerName3B />";
                given += "<InnerName4B />";
            given += "</InnerTag>";
        given += "</RandomTag>";

        std::string expectedNames = "InnerTag";
        std::vector<std::string> expectedNamesInner1 = std::vector<std::string>();
        expectedNamesInner1.push_back("InnerName1");
        expectedNamesInner1.push_back("InnerName2");
        expectedNamesInner1.push_back("InnerName3");
        expectedNamesInner1.push_back("InnerName4");

        std::string expectedNamesB = "InnerTagB";
        std::vector<std::string> expectedNamesInner1B = std::vector<std::string>();
        expectedNamesInner1B.push_back("InnerName1B");
        expectedNamesInner1B.push_back("InnerName2B");
        expectedNamesInner1B.push_back("InnerName3B");
        expectedNamesInner1B.push_back("InnerName4B");

        // Act
        std::shared_ptr<PrimitiveData> actual = m_primitiveDataLoader->ExtractData(given);

        // Assert
        ASSERT_EQ(2, actual->GetChildren().size());
        ASSERT_EQ(expectedNames, actual->GetChildren()[0]->GetName());
        ASSERT_EQ(expectedNamesB, actual->GetChildren()[1]->GetName());

        ASSERT_EQ(expectedNamesInner1.size(), actual->GetChildren()[0]->GetChildren().size());
        ASSERT_EQ(expectedNamesInner1B.size(), actual->GetChildren()[1]->GetChildren().size());
        for (size_t i = 0; i < actual->GetChildren()[0]->GetChildren().size(); ++i)
        {
            std::shared_ptr<PrimitiveData> data = actual->GetChildren()[0]->GetChildren()[i];
            ASSERT_EQ(expectedNamesInner1[i], data->GetName()) << "Inner Children 1 not equal, index: " << i;
        }

        for (size_t i = 0; i < actual->GetChildren()[1]->GetChildren().size(); ++i)
        {
            std::shared_ptr<PrimitiveData> data = actual->GetChildren()[1]->GetChildren()[i];
            ASSERT_EQ(expectedNamesInner1B[i], data->GetName()) << "Inner Children 1B not equal, index: " << i;
        }
    }


}