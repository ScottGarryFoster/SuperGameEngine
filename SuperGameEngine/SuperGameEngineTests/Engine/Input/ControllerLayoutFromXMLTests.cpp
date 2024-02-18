#include "../../LibraryIncludes.h"
#include "../../../SuperGameEngine/Engine/Input/ControllerLayoutFromXML.h"
#include "../../../SuperGameEngine/Engine/Input/Controller.hpp"

using namespace StandardCLibrary;
using namespace SuperGameEngine;

namespace SuperGameEngine_Engine_Input
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

        ASSERT_EQ(m_controllerLayout, nullptr);
    }

    TEST_F(ControllerLayoutFromXMLTests, CreateFromXML_ReturnsEmptyControllerLayout_WhenGivenEmptyTagsTest)
    {
        FString given = "<ControllerLayout></ControllerLayout>";
        Controller expected = Controller::Unknown;
        FString errors;

        m_controllerLayout = m_controllerLayoutFromXML->CreateFromXML(given, errors);

        ASSERT_NE(m_controllerLayout, nullptr);
        Controller controllerType = m_controllerLayout->Controller;
        ASSERT_EQ(expected, controllerType)
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

        ASSERT_NE(m_controllerLayout, nullptr);
        Controller controllerType = m_controllerLayout->Controller;
        ASSERT_EQ(expected, controllerType) 
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

        ASSERT_NE(m_controllerLayout, nullptr);
        Controller controllerType = m_controllerLayout->Controller;
        ASSERT_EQ(expected, controllerType)
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

        ASSERT_NE(m_controllerLayout, nullptr);
        Controller controllerType = m_controllerLayout->Controller;
        ASSERT_EQ(expected, controllerType)
            << "Expected: " << EController::ToString(expected)
            << " Actual: " << EController::ToString(controllerType)
            << " Errors: " << errors;
        ASSERT_NE("", errors.AsStdString())
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

        ASSERT_NE(m_controllerLayout, nullptr);
        Controller controllerType = m_controllerLayout->Controller;
        ASSERT_EQ(expected, controllerType)
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

        ASSERT_NE(m_controllerLayout, nullptr);
        int actual = m_controllerLayout->Axis;
        ASSERT_EQ(expected, actual)
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

        ASSERT_NE(m_controllerLayout, nullptr);
        int actual = m_controllerLayout->Axis;
        ASSERT_EQ(expected, actual)
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

        ASSERT_NE(m_controllerLayout, nullptr);
        int actual = m_controllerLayout->Axis;
        ASSERT_EQ(expected, actual)
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

        ASSERT_NE(m_controllerLayout, nullptr);
        int actual = m_controllerLayout->Buttons;
        ASSERT_EQ(expected, actual)
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

        ASSERT_NE(m_controllerLayout, nullptr);
        int actual = m_controllerLayout->Buttons;
        ASSERT_EQ(expected, actual)
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

        ASSERT_NE(m_controllerLayout, nullptr);
        int actual = m_controllerLayout->Buttons;
        ASSERT_EQ(expected, actual)
            << "Expected: " << expected
            << " Actual: " << actual
            << " Errors: " << errors;
    }

#pragma endregion

#pragma region SDLToUniversalButtons
    TEST_F(ControllerLayoutFromXMLTests, CreateFromXML_AddsASDLToUniversalButton_WhenGivenAValidButton)
    {
        // Arrange
        int expectedButton = 1;
        UniversalControllerButton expectedUniversalButton = UniversalControllerButton::FaceButtonDown;

        FString given = "<ControllerLayout>";
        given += FString("<SDLToUniversalButtons>");
        given += FString("<SDLToUniversalButton SDLButton=\"") + expectedButton;
        given += FString("\" UniversalControllerButton=\"") +
            EUniversalControllerButton::ToString(expectedUniversalButton) + FString("\" />");
        given += FString("</SDLToUniversalButtons>");
        given += "</ControllerLayout>";
        FString errors;

        // Act
        m_controllerLayout = m_controllerLayoutFromXML->CreateFromXML(given, errors);

        // Assert
        ASSERT_NE(m_controllerLayout, nullptr);
        FList<std::pair<int, UniversalControllerButton>> actual = m_controllerLayout->SDLToUniversalButton;
        ASSERT_EQ(1, actual.Count());

        int actualSDLButton = m_controllerLayout->SDLToUniversalButton[0].first;
        ASSERT_EQ(expectedButton, actualSDLButton)
            << "Expected: " << expectedButton
            << " Actual: " << actualSDLButton
            << " Errors: " << errors;

        UniversalControllerButton actualButton = m_controllerLayout->SDLToUniversalButton[0].second;
        ASSERT_EQ(expectedUniversalButton, actualButton)
            << "Expected: " << EUniversalControllerButton::ToString(expectedUniversalButton)
            << " Actual: " << EUniversalControllerButton::ToString(actualButton)
            << " Errors: " << errors;
    }

    TEST_F(ControllerLayoutFromXMLTests, CreateFromXML_DoesNotAddDuplicateSDLButtons_WhenGivenADuplicate)
    {
        // Arrange
        int givenButton = 1;
        UniversalControllerButton validButton = UniversalControllerButton::FaceButtonDown;
        UniversalControllerButton otherValidButton = UniversalControllerButton::DPadDown;

        FString given = "<ControllerLayout>";
        given += FString("<SDLToUniversalButtons>");

        given += FString("<SDLToUniversalButton SDLButton=\"") + givenButton;
        given += FString("\" UniversalControllerButton=\"") +
            EUniversalControllerButton::ToString(validButton) + FString("\" />");

        given += FString("<SDLToUniversalButton SDLButton=\"") + givenButton;
        given += FString("\" UniversalControllerButton=\"") +
            EUniversalControllerButton::ToString(otherValidButton) + FString("\" />");

        given += FString("</SDLToUniversalButtons>");
        given += "</ControllerLayout>";
        FString errors;

        // Act
        m_controllerLayout = m_controllerLayoutFromXML->CreateFromXML(given, errors);

        // Assert
        ASSERT_NE(m_controllerLayout, nullptr);
        FList<std::pair<int, UniversalControllerButton>> actual = m_controllerLayout->SDLToUniversalButton;
        ASSERT_EQ(1, actual.Count());
    }

    TEST_F(ControllerLayoutFromXMLTests, CreateFromXML_DoesNotAddDuplicateUniversalButtons_WhenGivenADuplicate)
    {
        // Arrange
        UniversalControllerButton givenButton = UniversalControllerButton::FaceButtonDown;
        int validSDLButton = 1;
        int otherValidSDLButton = 1;

        FString given = "<ControllerLayout>";
        given += FString("<SDLToUniversalButtons>");

        given += FString("<SDLToUniversalButton SDLButton=\"") + validSDLButton;
        given += FString("\" UniversalControllerButton=\"") +
            EUniversalControllerButton::ToString(givenButton) + FString("\" />");

        given += FString("<SDLToUniversalButton SDLButton=\"") + otherValidSDLButton;
        given += FString("\" UniversalControllerButton=\"") +
            EUniversalControllerButton::ToString(givenButton) + FString("\" />");

        given += FString("</SDLToUniversalButtons>");
        given += "</ControllerLayout>";
        FString errors;

        // Act
        m_controllerLayout = m_controllerLayoutFromXML->CreateFromXML(given, errors);

        // Assert
        ASSERT_NE(m_controllerLayout, nullptr);
        FList<std::pair<int, UniversalControllerButton>> actual = m_controllerLayout->SDLToUniversalButton;
        ASSERT_EQ(1, actual.Count());
    }

    TEST_F(ControllerLayoutFromXMLTests, CreateFromXML_AddsMultipleButtons_WhenGivenUniqueEntries)
    {
        // Arrange
        int expectedButton = 1;
        UniversalControllerButton expectedUniversalButton = UniversalControllerButton::FaceButtonDown;
        int secondExpectedButton = 2;
        UniversalControllerButton secondExpectedUniversalButton = UniversalControllerButton::DPadDown;

        FString given = "<ControllerLayout>";
        given += FString("<SDLToUniversalButtons>");

        given += FString("<SDLToUniversalButton SDLButton=\"") + expectedButton;
        given += FString("\" UniversalControllerButton=\"") +
            EUniversalControllerButton::ToString(expectedUniversalButton) + FString("\" />");

        given += FString("<SDLToUniversalButton SDLButton=\"") + secondExpectedButton;
        given += FString("\" UniversalControllerButton=\"") +
            EUniversalControllerButton::ToString(secondExpectedUniversalButton) + FString("\" />");

        given += FString("</SDLToUniversalButtons>");
        given += "</ControllerLayout>";
        FString errors;

        // Act
        m_controllerLayout = m_controllerLayoutFromXML->CreateFromXML(given, errors);

        // Assert
        ASSERT_NE(m_controllerLayout, nullptr);
        FList<std::pair<int, UniversalControllerButton>> actual = m_controllerLayout->SDLToUniversalButton;
        ASSERT_EQ(2, actual.Count());

        int actualSDLButton = m_controllerLayout->SDLToUniversalButton[0].first;
        ASSERT_EQ(expectedButton, actualSDLButton)
            << "Expected: " << expectedButton
            << " Actual: " << actualSDLButton
            << " Errors: " << errors;

        UniversalControllerButton actualButton = m_controllerLayout->SDLToUniversalButton[0].second;
        ASSERT_EQ(expectedUniversalButton, actualButton)
            << "Expected: " << EUniversalControllerButton::ToString(expectedUniversalButton)
            << " Actual: " << EUniversalControllerButton::ToString(actualButton)
            << " Errors: " << errors;

        int secondActualSDLButton = m_controllerLayout->SDLToUniversalButton[1].first;
        ASSERT_EQ(secondExpectedButton, secondActualSDLButton)
            << "Expected: " << secondActualSDLButton
            << " Actual: " << secondExpectedButton
            << " Errors: " << errors;

        UniversalControllerButton secondActualButton = m_controllerLayout->SDLToUniversalButton[1].second;
        ASSERT_EQ(secondExpectedUniversalButton, secondActualButton)
            << "Expected: " << EUniversalControllerButton::ToString(secondExpectedUniversalButton)
            << " Actual: " << EUniversalControllerButton::ToString(secondActualButton)
            << " Errors: " << errors;
    }
#pragma endregion
}