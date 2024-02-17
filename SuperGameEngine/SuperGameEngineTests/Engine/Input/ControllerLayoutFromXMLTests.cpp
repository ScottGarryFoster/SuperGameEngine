#include "../../LibraryIncludes.h"
#include "../../../SuperGameEngine/Engine/Input/ControllerLayoutFromXML.h"
#include "../../../SuperGameEngine/Engine/Input/Controller.hpp"

using namespace StandardCLibrary;
using namespace SuperGameEngine;

namespace SuperGameEngine_Engine_Input_ControllerLayoutFromXMLTests
{
    class ControllerLayoutFromXMLTests : public ::testing::Test
    {
    public:
        ControllerLayoutFromXMLTests()
        {
            m_controllerLayoutFromXML = nullptr;
            m_controllerLayout = nullptr;
        }

    protected:

        ControllerLayoutFromXML* m_controllerLayoutFromXML;
        ControllerLayout* m_controllerLayout;

        void SetUp() override
        {
            m_controllerLayoutFromXML = new ControllerLayoutFromXML();
        }

        void TearDown() override
        {
            delete m_controllerLayoutFromXML;
            if (m_controllerLayout != nullptr)
            {
                delete m_controllerLayout;
            }
        }
    };

    TEST_F(ControllerLayoutFromXMLTests, CreateFromXML_ReturnsNullptr_WhenFirstTagIsNotControllerLayout)
    {
        FString given = "<RandomTag></RandomTag>";
        FString errors;

        m_controllerLayout = m_controllerLayoutFromXML->CreateFromXML(given, errors);

        EXPECT_EQ(m_controllerLayout, nullptr);
    }

    TEST_F(ControllerLayoutFromXMLTests, CreateFromXML_ReturnsEmptyControllerLayout_WhenGivenEmptyTagsTest)
    {
        FString given = "<ControllerLayout></ControllerLayout>";
        Controller expected = Controller::Unknown;
        FString errors;

        m_controllerLayout = m_controllerLayoutFromXML->CreateFromXML(given, errors);

        EXPECT_NE(m_controllerLayout, nullptr);
        Controller controllerType = m_controllerLayout->Controller;
        EXPECT_EQ(expected, controllerType)
            << "Expected: " << EController::ToString(expected)
            << " Actual: " << EController::ToString(controllerType)
            << " Errors: " << errors;
    }

#pragma region MetaTag Controller

    TEST_F(ControllerLayoutFromXMLTests, CreateFromXML_SetsController_WhenGivenAValidController)
    {
        Controller expected = Controller::Xbox360Controller;
        FString controllerExpected = EController::ToString(expected);
        FString given = "<ControllerLayout>";
        given += FString("<Metadata Controller=\"") + controllerExpected + "\" />";
        given += "</ControllerLayout>";
        FString errors;

        m_controllerLayout = m_controllerLayoutFromXML->CreateFromXML(given, errors);

        EXPECT_NE(m_controllerLayout, nullptr);
        Controller controllerType = m_controllerLayout->Controller;
        EXPECT_EQ(expected, controllerType) 
            << "Expected: " << EController::ToString(expected)
            << " Actual: " << EController::ToString(controllerType)
            << " Errors: " << errors;
    }

    TEST_F(ControllerLayoutFromXMLTests, CreateFromXML_HandlesBlankControllerValue_WhenGivenOneInTheCorrectLocation)
    {
        Controller expected = Controller::Unknown;
        FString given = "<ControllerLayout>";
        given += FString("<Metadata Controller=\"\" />");
        given += "</ControllerLayout>";
        FString errors;

        m_controllerLayout = m_controllerLayoutFromXML->CreateFromXML(given, errors);

        EXPECT_NE(m_controllerLayout, nullptr);
        Controller controllerType = m_controllerLayout->Controller;
        EXPECT_EQ(expected, controllerType)
            << "Expected: " << EController::ToString(expected)
            << " Actual: " << EController::ToString(controllerType)
            << " Errors: " << errors;
    }

    TEST_F(ControllerLayoutFromXMLTests, CreateFromXML_HandlesIncorrectValueButProvidesError_WhenGivenOneInTheCorrectLocation)
    {
        Controller expected = Controller::Unknown;
        FString controllerGiven = "NOTACONTROLLER";
        ASSERT_EQ(Controller::Unknown, EController::FromString(controllerGiven.AsStdString()));

        FString given = "<ControllerLayout>";
        given += FString("<Metadata Controller=\"") + controllerGiven + "\" />";
        given += "</ControllerLayout>";
        FString errors;

        m_controllerLayout = m_controllerLayoutFromXML->CreateFromXML(given, errors);

        EXPECT_NE(m_controllerLayout, nullptr);
        Controller controllerType = m_controllerLayout->Controller;
        EXPECT_EQ(expected, controllerType)
            << "Expected: " << EController::ToString(expected)
            << " Actual: " << EController::ToString(controllerType)
            << " Errors: " << errors;
        EXPECT_NE("", errors.AsStdString())
            << "Expected NOT: " << ""
            << " Actual: " << errors;
    }

    TEST_F(ControllerLayoutFromXMLTests, CreateFromXML_ReturnsDefault_WhenNotGivenController)
    {
        Controller expected = Controller::Unknown;
        FString given = "<ControllerLayout>";
        given += FString("<Metadata />");
        given += "</ControllerLayout>";
        FString errors;

        m_controllerLayout = m_controllerLayoutFromXML->CreateFromXML(given, errors);

        EXPECT_NE(m_controllerLayout, nullptr);
        Controller controllerType = m_controllerLayout->Controller;
        EXPECT_EQ(expected, controllerType)
            << "Expected: " << EController::ToString(expected)
            << " Actual: " << EController::ToString(controllerType)
            << " Errors: " << errors;
    }
#pragma endregion

#pragma region MetaTag Axis

    TEST_F(ControllerLayoutFromXMLTests, CreateFromXML_SetsAxis_WhenGivenAValidNumber)
    {
        int expected = 1;
        FString given = "<ControllerLayout>";
        given += FString("<Metadata Axis=\"") + expected + "\" />";
        given += "</ControllerLayout>";
        FString errors;

        m_controllerLayout = m_controllerLayoutFromXML->CreateFromXML(given, errors);

        EXPECT_NE(m_controllerLayout, nullptr);
        int actual = m_controllerLayout->Axis;
        EXPECT_EQ(expected, actual)
            << "Expected: " << expected
            << " Actual: " << actual
            << " Errors: " << errors;
    }

    TEST_F(ControllerLayoutFromXMLTests, CreateFromXML_DoesNotSetAxis_WhenNumberGivenIsInvalid)
    {
        int expected = -1;
        FString givenNumber = "NOTANUMBER";
        FString given = "<ControllerLayout>";
        given += FString("<Metadata Axis=\"") + givenNumber + "\" />";
        given += "</ControllerLayout>";
        FString errors;

        m_controllerLayout = m_controllerLayoutFromXML->CreateFromXML(given, errors);

        EXPECT_NE(m_controllerLayout, nullptr);
        int actual = m_controllerLayout->Axis;
        EXPECT_EQ(expected, actual)
            << "Expected: " << expected
            << " Actual: " << actual
            << " Errors: " << errors;
    }

    TEST_F(ControllerLayoutFromXMLTests, CreateFromXML_AxisReturnsDefault_WhenNotSet)
    {
        int expected = -1;
        FString given = "<ControllerLayout>";
        given += FString("<Metadata />");
        given += "</ControllerLayout>";
        FString errors;

        m_controllerLayout = m_controllerLayoutFromXML->CreateFromXML(given, errors);

        EXPECT_NE(m_controllerLayout, nullptr);
        int actual = m_controllerLayout->Axis;
        EXPECT_EQ(expected, actual)
            << "Expected: " << expected
            << " Actual: " << actual
            << " Errors: " << errors;
    }

#pragma endregion

#pragma region MetaTag Buttons

    TEST_F(ControllerLayoutFromXMLTests, CreateFromXML_SetsButtons_WhenGivenAValidNumber)
    {
        int expected = 1;
        FString given = "<ControllerLayout>";
        given += FString("<Metadata Buttons=\"") + expected + "\" />";
        given += "</ControllerLayout>";
        FString errors;

        m_controllerLayout = m_controllerLayoutFromXML->CreateFromXML(given, errors);

        EXPECT_NE(m_controllerLayout, nullptr);
        int actual = m_controllerLayout->Buttons;
        EXPECT_EQ(expected, actual)
            << "Expected: " << expected
            << " Actual: " << actual
            << " Errors: " << errors;
    }

    TEST_F(ControllerLayoutFromXMLTests, CreateFromXML_DoesNotSetButtons_WhenNumberGivenIsInvalid)
    {
        int expected = -1;
        FString givenNumber = "NOTANUMBER";
        FString given = "<ControllerLayout>";
        given += FString("<Metadata Buttons=\"") + givenNumber + "\" />";
        given += "</ControllerLayout>";
        FString errors;

        m_controllerLayout = m_controllerLayoutFromXML->CreateFromXML(given, errors);

        EXPECT_NE(m_controllerLayout, nullptr);
        int actual = m_controllerLayout->Buttons;
        EXPECT_EQ(expected, actual)
            << "Expected: " << expected
            << " Actual: " << actual
            << " Errors: " << errors;
    }

    TEST_F(ControllerLayoutFromXMLTests, CreateFromXML_ButtonsReturnsDefault_WhenNotSet)
    {
        int expected = -1;
        FString given = "<ControllerLayout>";
        given += FString("<Metadata />");
        given += "</ControllerLayout>";
        FString errors;

        m_controllerLayout = m_controllerLayoutFromXML->CreateFromXML(given, errors);

        EXPECT_NE(m_controllerLayout, nullptr);
        int actual = m_controllerLayout->Buttons;
        EXPECT_EQ(expected, actual)
            << "Expected: " << expected
            << " Actual: " << actual
            << " Errors: " << errors;
    }

#pragma endregion
}