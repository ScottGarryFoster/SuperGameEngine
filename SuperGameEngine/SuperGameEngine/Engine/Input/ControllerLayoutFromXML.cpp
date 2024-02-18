#include "ControllerLayoutFromXML.h"


using namespace SuperGameEngine;
using namespace StandardCLibrary;
using namespace rapidxml;
ControllerLayoutFromXML::ControllerLayoutFromXML()
{
}

ControllerLayoutFromXML::~ControllerLayoutFromXML()
{
}

ControllerLayout* ControllerLayoutFromXML::CreateFromXML(FString xml, FString& error)
{
    ControllerLayout* finalLayout = nullptr;

    XMLDocument* document = TryParseXMLDocument(xml);
    if (document != nullptr)
    {
        XMLNode *rootNode = document->first_node();
        FString name = FString(rootNode->name());
        if (name == FString("ControllerLayout"))
        {
            finalLayout = new ControllerLayout();

            XMLNode* metaNode = nullptr;
            XMLNode* sdlToUniversalButtons = nullptr;
            XMLNode* axisToButtons = nullptr;
            XMLNode* sdlHatToDpad = nullptr;
            XMLNode* sdlAxisToUniversalAxis = nullptr;
            ExtractTopLevelNodes(document, &metaNode, &sdlToUniversalButtons,
                &axisToButtons, &sdlHatToDpad, &sdlAxisToUniversalAxis);

            if (metaNode != nullptr)
            {
                ParseMetaTag(metaNode, finalLayout, error);
            }

            if (sdlToUniversalButtons != nullptr)
            {
                ParseSdlToUniversalButtonsTag(sdlToUniversalButtons, finalLayout, error);
            }
        }

    }

    if (document != nullptr)
    {
        delete document;
    }

    return finalLayout;
}

void ControllerLayoutFromXML::ExtractTopLevelNodes(
    XMLDocument* document,
    XMLNode** metaNode,
    XMLNode** sdlToUniversalButtons,
    XMLNode** axisToButtons,
    XMLNode** sdlHatToDpad,
    XMLNode** sdlAxisToUniversalAxis) const
{
    XMLNode* rootNode = document->first_node();
    for (XMLNode* childNode = rootNode->first_node(); childNode; childNode = childNode->next_sibling())
    {
        if (*metaNode == nullptr && FString(childNode->name()) == MetaTagName)
        {
            *metaNode = childNode;
        }
        else if (*sdlToUniversalButtons == nullptr && FString(childNode->name()) == ButtonTagName)
        {
            *sdlToUniversalButtons = childNode;
        }
        else if (*axisToButtons == nullptr && FString(childNode->name()) == AxisToButtonTagName)
        {
            *axisToButtons = childNode;
        }
    }
}

XMLDocument* ControllerLayoutFromXML::TryParseXMLDocument(FString& xml)
{
    XMLDocument* document = new XMLDocument();
    try 
    {
        document->parse<0>(const_cast<char*>(xml.AsCharArr()));
    }
    catch (rapidxml::parse_error e)
    {
        delete document;
        document = nullptr;
    }

    return document;
}

bool ControllerLayoutFromXML::ParseMetaTag(
    XMLNode* metaNode, ControllerLayout* controllerLayout, FString& error)
{
    for (XMLAttribute* attribute = metaNode->first_attribute(); attribute; attribute = attribute->next_attribute())
    {
        if (FString(attribute->name()).ToLower() == "controller")
        {
            Controller foundValue = EController::FromString(attribute->value());
            if (foundValue == Controller::Unknown)
            {
                error += FString("Could not parse controller value: ") + attribute->value() + ". ";
            }
            else
            {
                controllerLayout->Controller = foundValue;
            }
        }
        else if (FString(attribute->name()).ToLower() == "axis")
        {
            int result = -1;
            FString input = FString(attribute->value());
            if (IntHelpers::TryParse(input, result))
            {
                controllerLayout->Axis = result;
            }
            else
            {
                error += FString("Could not parse axis value: ") + attribute->value() + ". ";
            }
        }
        else if (FString(attribute->name()).ToLower() == "buttons")
        {
            int result = -1;
            FString input = FString(attribute->value());
            if (IntHelpers::TryParse(input, result))
            {
                controllerLayout->Buttons = result;
            }
            else
            {
                error += FString("Could not parse buttons value: ") + attribute->value() + ". ";
            }
        }
    }

    return true;
}

bool ControllerLayoutFromXML::ParseSdlToUniversalButtonsTag(
        XMLNode* node, ControllerLayout* controllerLayout, FString& error)
{
    for (XMLNode* childNode = node->first_node(); childNode; childNode = childNode->next_sibling())
    {
        if (FString(childNode->name()) != ButtonTagSingularName)
        {
            continue;
        }

        ParseSdlToUniversalButtonTag(childNode, controllerLayout, error);
    }
    return true;
}

bool ControllerLayoutFromXML::ParseSdlToUniversalButtonTag(
        XMLNode* node, ControllerLayout* controllerLayout, FString& error)
{
    // Let's create a pair here
    std::pair<int, UniversalControllerButton> extractedData;
    extractedData.first = -1;
    extractedData.second = UniversalControllerButton::Unknown;
    for (XMLAttribute* attribute = node->first_attribute(); attribute; attribute = attribute->next_attribute())
    {
        if (FString(attribute->name()).ToLower() == "sdlbutton")
        {
            int result = -1;
            FString input = FString(attribute->value());
            if (IntHelpers::TryParse(input, result))
            {
                extractedData.first = result;
            }
            else
            {
                error += FString("Could not parse sdl buttons value: ")
                    + attribute->value() + ". ";
            }
        }
        else if (FString(attribute->name()).ToLower() == "universalcontrollerbutton")
        {
            UniversalControllerButton foundValue = EUniversalControllerButton::FromString(attribute->value());
            if (foundValue == UniversalControllerButton::Unknown)
            {
                error += FString("Could not parse universal controller button value: ")
                    + attribute->value() + ". ";
            }
            else
            {
                extractedData.second = foundValue;
            }
        }
    }

    if (!controllerLayout->SDLToUniversalButton.Any(
        [extractedData](const std::pair<int, UniversalControllerButton>& x)
        {
            return x.first == extractedData.first || x.second == extractedData.second;
        }))
    {
        controllerLayout->SDLToUniversalButton.Add(extractedData);
    }

    return true;
}
