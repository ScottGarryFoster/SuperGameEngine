#include "../../LibraryIncludes.h"
#include "../../../SuperGameEngine/Engine/Input/ControllerLayoutFromXML.h"

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
        EXPECT_EQ(expected, controllerType);
    }
}