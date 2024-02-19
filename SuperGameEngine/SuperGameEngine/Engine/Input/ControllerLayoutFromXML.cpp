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

            if (axisToButtons != nullptr)
            {
                ParseAxisToButtonsTag(axisToButtons, finalLayout, error);
            }

            if (sdlHatToDpad != nullptr)
            {
                ParseSDLHatToDpadTag(sdlHatToDpad, finalLayout, error);
            }

            if (sdlAxisToUniversalAxis != nullptr)
            {
                ParseSDLToUniversalAxesTag(sdlAxisToUniversalAxis, finalLayout, error);
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
        else if (*sdlHatToDpad == nullptr && FString(childNode->name()) == HatSDLMappingName)
        {
            *sdlHatToDpad = childNode;
        }
        else if (*sdlAxisToUniversalAxis == nullptr && FString(childNode->name()) == SDLToUniversalAxesName)
        {
            *sdlAxisToUniversalAxis = childNode;
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
        if (FString(attribute->name()).ToLower() == "name")
        {
            FString name = FString(attribute->value());
            if (!name.IsEmptyOrWhitespace())
            {
                controllerLayout->Name = name;
            }
        }
        else if (FString(attribute->name()).ToLower() == "controller")
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

    bool isValid = true;
    if (extractedData.first == -1)
    {
        isValid = false;
    }
    else if (extractedData.second == UniversalControllerButton::Unknown)
    {
        isValid = false;
    }

    if (isValid == true && !controllerLayout->SDLToUniversalButton.Any(
        [extractedData](const std::pair<int, UniversalControllerButton>& x)
        {
            return x.first == extractedData.first || x.second == extractedData.second;
        }))
    {
        controllerLayout->SDLToUniversalButton.Add(extractedData);
    }

    return isValid;
}

bool ControllerLayoutFromXML::ParseAxisToButtonsTag(
        XMLNode* node, ControllerLayout* controllerLayout, FString& error)
{
    for (XMLNode* childNode = node->first_node(); childNode; childNode = childNode->next_sibling())
    {
        if (FString(childNode->name()) != AxisToButtonTagSingularName)
        {
            continue;
        }

        ParseAxisToButtonTag(childNode, controllerLayout, error);
    }

    return true;
}

bool ControllerLayoutFromXML::ParseAxisToButtonTag(
        XMLNode* node, ControllerLayout* controllerLayout, FString& error)
{
    ControllerAxisMappedToButton extractedData;
    bool didParseComparisonValue = false;
    for (XMLAttribute* attribute = node->first_attribute(); attribute; attribute = attribute->next_attribute())
    {
        FString name = FString(attribute->name()).ToLower();
        if (name == "axis")
        {
            int result = -1;
            FString input = FString(attribute->value());
            if (IntHelpers::TryParse(input, result))
            {
                extractedData.Axis = result;
            }
            else
            {
                error += FString("Could not parse axis value: ")
                    + attribute->value() + ". ";
            }
        }
        else if (name == "universalcontrollerbutton")
        {
            UniversalControllerButton foundValue = EUniversalControllerButton::FromString(attribute->value());
            if (foundValue == UniversalControllerButton::Unknown)
            {
                error += FString("Could not parse universal controller button value: ")
                    + attribute->value() + ". ";
            }
            else
            {
                extractedData.Button = foundValue;
            }
        }
        else if (name == "evaluationvalue")
        {
            int result = -1;
            FString input = FString(attribute->value());
            if (IntHelpers::TryParse(input, result))
            {
                extractedData.Evaluation.Value = result;
                didParseComparisonValue = true;
            }
            else
            {
                error += FString("Could not parse Evaluation Value value: ")
                    + attribute->value() + ". ";
            }
        }
        else if (name == "evaluationcomparison")
        {
            ControllerComparisonType foundValue = EControllerComparisonType::FromString(attribute->value());
            if (foundValue == ControllerComparisonType::Unknown)
            {
                error += FString("Could not parse universal controller button value: ")
                    + attribute->value() + ". ";
            }
            else
            {
                extractedData.Evaluation.Comparison = foundValue;
            }
        }
    }

    bool isValid = true;
    if (extractedData.Axis <= -1)
    {
        isValid = false;
    }
    else if (extractedData.Button == UniversalControllerButton::Unknown)
    {
        isValid = false;
    }
    else if (extractedData.Evaluation.Comparison == ControllerComparisonType::Unknown)
    {
        isValid = false;
    }
    else if (!didParseComparisonValue)
    {
        // As any int value is technically 'valid' we need explictly keep 
        // track of successful parses for this value.
        isValid = false;
    }

    if (isValid == true && !controllerLayout->AxisToButton.Any(
        [extractedData](const ControllerAxisMappedToButton& x)
        {
            return x.Axis == extractedData.Axis || x.Button == extractedData.Button;
        }))
    {
        controllerLayout->AxisToButton.Add(extractedData);
    }


    return false;
}

bool ControllerLayoutFromXML::ParseSDLHatToDpadTag(
        XMLNode* node, ControllerLayout* controllerLayout, FString& error)
{
    int extractedValue = -1;
    bool didExtract = false;
    for (XMLAttribute* attribute = node->first_attribute(); attribute; attribute = attribute->next_attribute())
    {
        FString name = FString(attribute->name()).ToLower();
        if (name == "sdltobuttonvalue")
        {
            int result = -1;
            FString input = FString(attribute->value());
            if (IntHelpers::TryParse(input, result))
            {
                extractedValue = result;
                didExtract = true;
                //extractedData.Axis = result;
            }
            else
            {
                error += FString("Could not parse axis value: ")
                    + attribute->value() + ". ";
            }
        }
    }

    if (didExtract && extractedValue > -1)
    {
        controllerLayout->HatMappedToDpad = extractedValue;
    }

    return didExtract;
}

bool ControllerLayoutFromXML::ParseSDLToUniversalAxesTag(
        XMLNode* node, ControllerLayout* controllerLayout, FString& error)
{
    for (XMLNode* childNode = node->first_node(); childNode; childNode = childNode->next_sibling())
    {
        if (FString(childNode->name()) != SDLToUniversalAxesSingularName)
        {
            continue;
        }

        ParseSDLToUniversalAxisTag(childNode, controllerLayout, error);
    }
    return true;
}

bool ControllerLayoutFromXML::ParseSDLToUniversalAxisTag(
        XMLNode* node, ControllerLayout* controllerLayout, FString& error)
{
    AxisToUniversalAxis extractedValue;
    for (XMLAttribute* attribute = node->first_attribute(); attribute; attribute = attribute->next_attribute())
    {
        FString name = FString(attribute->name()).ToLower();
        if (name == "sdlaxis")
        {
            int result = -1;
            FString input = FString(attribute->value());
            if (IntHelpers::TryParse(input, result))
            {
                extractedValue.SDLAxis = result;
            }
            else
            {
                error += FString("Could not parse axis value: ")
                    + attribute->value() + ". ";
            }
        }
        else if (name == "universalcontrolleraxis")
        {
            UniversalControllerAxis foundValue = EUniversalControllerAxis::FromString(attribute->value());
            if (foundValue == UniversalControllerAxis::Unknown)
            {
                error += FString("Could not parse universal controller axis value: ")
                    + attribute->value() + ". ";
            }
            else
            {
                extractedValue.UniversalAxis = foundValue;
            }
        }
        else if (name == "deadzone")
        {
            int result = -1;
            FString input = FString(attribute->value());
            if (IntHelpers::TryParse(input, result))
            {
                extractedValue.Deadzone = result;
                extractedValue.HasDeadzone = true;
            }
            else
            {
                error += FString("Could not parse deadzone value: ")
                    + attribute->value() + ". ";
            }
        }
    }

    bool isValid = true;
    if (extractedValue.SDLAxis <= -1)
    {
        isValid = false;
    }
    else if (extractedValue.UniversalAxis == UniversalControllerAxis::Unknown)
    {
        isValid = false;
    }

    if (isValid == true && !controllerLayout->SDLAxisToUniversalAxis.Any(
        [extractedValue](const AxisToUniversalAxis& x)
        {
            return x.SDLAxis == extractedValue.SDLAxis || x.UniversalAxis == extractedValue.UniversalAxis;
        }))
    {
        controllerLayout->SDLAxisToUniversalAxis.Add(extractedValue);
    }

    return isValid;
}
