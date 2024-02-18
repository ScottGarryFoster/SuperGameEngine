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

        ASSERT_EQ(m_controllerLayout, nullptr) << "Could not parse XML: " << errors;
    }

    TEST_F(ControllerLayoutFromXMLTests, CreateFromXML_ReturnsEmptyControllerLayout_WhenGivenEmptyTagsTest)
    {
        FString given = "<ControllerLayout></ControllerLayout>";
        Controller expected = Controller::Unknown;
        FString errors;

        m_controllerLayout = m_controllerLayoutFromXML->CreateFromXML(given, errors);

        ASSERT_NE(m_controllerLayout, nullptr) << "Could not parse XML: " << errors;
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

        ASSERT_NE(m_controllerLayout, nullptr) << "Could not parse XML: " << errors;
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

        ASSERT_NE(m_controllerLayout, nullptr) << "Could not parse XML: " << errors;
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

        ASSERT_NE(m_controllerLayout, nullptr) << "Could not parse XML: " << errors;
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

        ASSERT_NE(m_controllerLayout, nullptr) << "Could not parse XML: " << errors;
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

        ASSERT_NE(m_controllerLayout, nullptr) << "Could not parse XML: " << errors;
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

        ASSERT_NE(m_controllerLayout, nullptr) << "Could not parse XML: " << errors;
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

        ASSERT_NE(m_controllerLayout, nullptr) << "Could not parse XML: " << errors;
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

        ASSERT_NE(m_controllerLayout, nullptr) << "Could not parse XML: " << errors;
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

        ASSERT_NE(m_controllerLayout, nullptr) << "Could not parse XML: " << errors;
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

        ASSERT_NE(m_controllerLayout, nullptr) << "Could not parse XML: " << errors;
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
        ASSERT_NE(m_controllerLayout, nullptr) << "Could not parse XML: " << errors;
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
        ASSERT_NE(m_controllerLayout, nullptr) << "Could not parse XML: " << errors;
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
        ASSERT_NE(m_controllerLayout, nullptr) << "Could not parse XML: " << errors;
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
        ASSERT_NE(m_controllerLayout, nullptr) << "Could not parse XML: " << errors;
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

    TEST_F(ControllerLayoutFromXMLTests, CreateFromXML_DoesNotAddInvalidSDLButton_WhenGivenOne)
    {
        // Arrange
        int invalidButton = -1;
        UniversalControllerButton expectedUniversalButton = UniversalControllerButton::FaceButtonDown;

        FString given = "<ControllerLayout>";
        given += FString("<SDLToUniversalButtons>");
        given += FString("<SDLToUniversalButton SDLButton=\"") + invalidButton;
        given += FString("\" UniversalControllerButton=\"") +
            EUniversalControllerButton::ToString(expectedUniversalButton) + FString("\" />");
        given += FString("</SDLToUniversalButtons>");
        given += "</ControllerLayout>";
        FString errors;

        // Act
        m_controllerLayout = m_controllerLayoutFromXML->CreateFromXML(given, errors);

        // Assert
        ASSERT_NE(m_controllerLayout, nullptr) << "Could not parse XML: " << errors;
        FList<std::pair<int, UniversalControllerButton>> actual = m_controllerLayout->SDLToUniversalButton;
        ASSERT_EQ(0, actual.Count());
    }

    TEST_F(ControllerLayoutFromXMLTests, CreateFromXML_DoesNotAddInvalidUniversalButton_WhenGivenOne)
    {
        // Arrange
        int validButton = 0;
        UniversalControllerButton invalidUniversalButton = UniversalControllerButton::Unknown;

        FString given = "<ControllerLayout>";
        given += FString("<SDLToUniversalButtons>");
        given += FString("<SDLToUniversalButton SDLButton=\"") + validButton;
        given += FString("\" UniversalControllerButton=\"") +
            EUniversalControllerButton::ToString(invalidUniversalButton) + FString("\" />");
        given += FString("</SDLToUniversalButtons>");
        given += "</ControllerLayout>";
        FString errors;

        // Act
        m_controllerLayout = m_controllerLayoutFromXML->CreateFromXML(given, errors);

        // Assert
        ASSERT_NE(m_controllerLayout, nullptr) << "Could not parse XML: " << errors;
        FList<std::pair<int, UniversalControllerButton>> actual = m_controllerLayout->SDLToUniversalButton;
        ASSERT_EQ(0, actual.Count());
    }
#pragma endregion

#pragma region AxisToButtons
    TEST_F(ControllerLayoutFromXMLTests, CreateFromXML_AddsAAxisToButton_WhenGivenAValidEntry)
    {
        // Arrange
        int givenAxis = 0;
        UniversalControllerButton givenButton = UniversalControllerButton::DPadDown;
        ControllerComparisonType givenComparison = ControllerComparisonType::Greater;
        int givenCompareValue = 42;

        FString given = "<ControllerLayout>\n";
        given += FString("<AxisToButtons>\n");
        given += FString("<AxisToButton Axis=\"") + givenAxis;
        given += FString("\" UniversalControllerButton=\"");
        given += FString(EUniversalControllerButton::ToString(givenButton)) + "\" ";
        given += FString("EvaluationComparison=\"") + FString(EControllerComparisonType::ToString(givenComparison)) + "\" ";
        given += FString("EvaluationValue=\"") + givenCompareValue + "\"";
        given += FString(" />\n");
        given += FString("</AxisToButtons>\n");
        given += FString("</ControllerLayout>\n");
        FString errors;

        // Act
        m_controllerLayout = m_controllerLayoutFromXML->CreateFromXML(given, errors);

        ASSERT_NE(m_controllerLayout, nullptr) << "Could not parse XML: " << errors;
        FList<ControllerAxisMappedToButton> actual = m_controllerLayout->AxisToButton;
        ASSERT_EQ(1, actual.Count());

        int axis = actual[0].Axis;
        ASSERT_EQ(givenAxis, axis) << errors;

        UniversalControllerButton button = actual[0].Button;
        ASSERT_EQ(givenButton, button) << errors;

        ControllerComparisonType comparison = actual[0].Evaluation.Comparison;
        ASSERT_EQ(givenComparison, comparison) << errors;

        int comparisonValue = actual[0].Evaluation.Value;
        ASSERT_EQ(givenCompareValue, comparisonValue) << errors;
    }

    TEST_F(ControllerLayoutFromXMLTests, CreateFromXML_AddsMultiEntries_WhenGivenMultipleUniqueEntries)
    {
        // Arrange
        int givenAxis = 0;
        UniversalControllerButton givenButton = UniversalControllerButton::DPadDown;
        ControllerComparisonType givenComparison = ControllerComparisonType::Greater;
        int givenCompareValue = 42;

        int givenSecondAxis = 0;
        UniversalControllerButton givenSecondButton = UniversalControllerButton::DPadDown;
        ControllerComparisonType givenSecondComparison = ControllerComparisonType::Greater;
        int givenSecondCompareValue = 42;

        FString given = "<ControllerLayout>";
        given += FString("<AxisToButtons>");

        given += FString("<AxisToButton Axis=\"") + givenAxis;
        given += FString("\" UniversalControllerButton=\"");
        given += FString(EUniversalControllerButton::ToString(givenButton)) + "\" ";
        given += FString("EvaluationComparison=\"") + FString(EControllerComparisonType::ToString(givenComparison)) + "\" ";
        given += FString("EvaluationValue=\"") + givenCompareValue + "\"";
        given += FString(" />");

        given += FString("<AxisToButton Axis=\"") + givenSecondAxis;
        given += FString("\" UniversalControllerButton=\"");
        given += FString(EUniversalControllerButton::ToString(givenSecondButton)) + "\" ";
        given += FString("EvaluationComparison=\"") + FString(EControllerComparisonType::ToString(givenSecondComparison)) + "\" ";
        given += FString("EvaluationValue=\"") + givenSecondCompareValue + "\"";
        given += FString(" />");

        given += FString("</AxisToButtons>");
        given += FString("</ControllerLayout>");
        FString errors;

        // Act
        m_controllerLayout = m_controllerLayoutFromXML->CreateFromXML(given, errors);

        ASSERT_NE(m_controllerLayout, nullptr) << "Could not parse XML: " << errors;
        FList<ControllerAxisMappedToButton> actual = m_controllerLayout->AxisToButton;
        ASSERT_EQ(2, actual.Count());

        int axis = actual[0].Axis;
        ASSERT_EQ(givenAxis, axis) << errors;

        UniversalControllerButton button = actual[0].Button;
        ASSERT_EQ(givenButton, button) << errors;

        ControllerComparisonType comparison = actual[0].Evaluation.Comparison;
        ASSERT_EQ(givenComparison, comparison) << errors;

        int comparisonValue = actual[0].Evaluation.Value;
        ASSERT_EQ(givenCompareValue, comparisonValue) << errors;

        axis = actual[1].Axis;
        ASSERT_EQ(givenSecondAxis, axis) << errors;

        button = actual[1].Button;
        ASSERT_EQ(givenSecondButton, button) << errors;

        comparison = actual[1].Evaluation.Comparison;
        ASSERT_EQ(givenSecondComparison, comparison) << errors;

        comparisonValue = actual[1].Evaluation.Value;
        ASSERT_EQ(givenSecondCompareValue, comparisonValue) << errors;
    }

    TEST_F(ControllerLayoutFromXMLTests, CreateFromXML_DoesNotAddEntry_WhenGivenInvalidAxis)
    {
        // Arrange
        int invalidAxis = -1;
        UniversalControllerButton givenButton = UniversalControllerButton::DPadDown;
        ControllerComparisonType givenComparison = ControllerComparisonType::Greater;
        int givenCompareValue = 42;

        FString given = "<ControllerLayout>";
        given += FString("<AxisToButtons>");
        given += FString("<AxisToButton Axis=\"") + invalidAxis;
        given += FString("\" UniversalControllerButton=\"");
        given += FString(EUniversalControllerButton::ToString(givenButton)) + "\" ";
        given += FString("EvaluationComparison=\"") + FString(EControllerComparisonType::ToString(givenComparison)) + "\" ";
        given += FString("EvaluationValue=\"") + givenCompareValue + FString("\"");
        given += FString(" />");
        given += FString("</AxisToButtons>");
        given += FString("</ControllerLayout>");
        FString errors;

        // Act
        m_controllerLayout = m_controllerLayoutFromXML->CreateFromXML(given, errors);

        ASSERT_NE(m_controllerLayout, nullptr) << "Could not parse XML: " << errors;
        FList<ControllerAxisMappedToButton> actual = m_controllerLayout->AxisToButton;
        ASSERT_EQ(0, actual.Count());
    }

    TEST_F(ControllerLayoutFromXMLTests, CreateFromXML_DoesNotAddEntry_WhenGivenInvalidButton)
    {
        // Arrange
        int validButton = 0;
        UniversalControllerButton invalidButton = UniversalControllerButton::Unknown;
        ControllerComparisonType givenComparison = ControllerComparisonType::Greater;
        int givenCompareValue = 42;

        FString given = "<ControllerLayout>";
        given += FString("<AxisToButtons>");
        given += FString("<AxisToButton Axis=\"") + validButton;
        given += FString("\" UniversalControllerButton=\"");
        given += FString(EUniversalControllerButton::ToString(invalidButton)) + "\" ";
        given += FString("EvaluationComparison=\"") + FString(EControllerComparisonType::ToString(givenComparison)) + "\" ";
        given += FString("EvaluationValue=\"") + givenCompareValue + FString("\"");
        given += FString(" />");
        given += FString("</AxisToButtons>");
        given += FString("</ControllerLayout>");
        FString errors;

        // Act
        m_controllerLayout = m_controllerLayoutFromXML->CreateFromXML(given, errors);

        ASSERT_NE(m_controllerLayout, nullptr) << "Could not parse XML: " << errors;
        FList<ControllerAxisMappedToButton> actual = m_controllerLayout->AxisToButton;
        ASSERT_EQ(0, actual.Count());
    }

    TEST_F(ControllerLayoutFromXMLTests, CreateFromXML_DoesNotAddEntry_WhenGivenInvalidComparison)
    {
        // Arrange
        int validButton = 0;
        UniversalControllerButton validUniversalButton = UniversalControllerButton::DPadLeft;
        ControllerComparisonType invalidComparison = ControllerComparisonType::Unknown;
        int givenCompareValue = 42;

        FString given = "<ControllerLayout>";
        given += FString("<AxisToButtons>");
        given += FString("<AxisToButton Axis=\"") + validButton;
        given += FString("\" UniversalControllerButton=\"");
        given += FString(EUniversalControllerButton::ToString(validUniversalButton)) + "\" ";
        given += FString("EvaluationComparison=\"") + FString(EControllerComparisonType::ToString(invalidComparison)) + "\" ";
        given += FString("EvaluationValue=\"") + givenCompareValue + FString("\"");
        given += FString(" />");
        given += FString("</AxisToButtons>");
        given += FString("</ControllerLayout>");
        FString errors;

        // Act
        m_controllerLayout = m_controllerLayoutFromXML->CreateFromXML(given, errors);

        ASSERT_NE(m_controllerLayout, nullptr) << "Could not parse XML: " << errors;
        FList<ControllerAxisMappedToButton> actual = m_controllerLayout->AxisToButton;
        ASSERT_EQ(0, actual.Count());
    }

    TEST_F(ControllerLayoutFromXMLTests, CreateFromXML_DoesNotAddEntry_WhenGivenInvalidComparisonValue)
    {
        // Arrange
        int validButton = 0;
        UniversalControllerButton validUniversalButton = UniversalControllerButton::DPadLeft;
        ControllerComparisonType validComparison = ControllerComparisonType::Unknown;
        FString invalidComparisonValue = FString("NOTANUMBER");

        FString given = "<ControllerLayout>";
        given += FString("<AxisToButtons>");
        given += FString("<AxisToButton Axis=\"") + validButton;
        given += FString("\" UniversalControllerButton=\"");
        given += FString(EUniversalControllerButton::ToString(validUniversalButton)) + "\" ";
        given += FString("EvaluationComparison=\"") + FString(EControllerComparisonType::ToString(validComparison)) + "\" ";
        given += FString("EvaluationValue=\"") + invalidComparisonValue + "\"";
        given += FString(" />");
        given += FString("</AxisToButtons>");
        given += FString("</ControllerLayout>");
        FString errors;

        // Act
        m_controllerLayout = m_controllerLayoutFromXML->CreateFromXML(given, errors);

        ASSERT_NE(m_controllerLayout, nullptr) << "Could not parse XML: " << errors;
        FList<ControllerAxisMappedToButton> actual = m_controllerLayout->AxisToButton;
        ASSERT_EQ(0, actual.Count());
    }

#pragma endregion
}