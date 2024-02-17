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

    XMLDocument* document = nullptr;
    if (TryParseXMLDocument(xml, &document))
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
    XMLNode** sdlAxisToUniversalAxis)
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

bool ControllerLayoutFromXML::TryParseXMLDocument(FString& xml, XMLDocument** document)
{
    XMLDocument* doc = new XMLDocument();
    *document = doc;
    try 
    {
        doc->parse<0>(const_cast<char*>(xml.AsCharArr()));
    }
    catch (rapidxml::parse_error e)
    {
        delete* document;
        *document = nullptr;
    }

    return *document != nullptr;
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
    }

    return false;
}