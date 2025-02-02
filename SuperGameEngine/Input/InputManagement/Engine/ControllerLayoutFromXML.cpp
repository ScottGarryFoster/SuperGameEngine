#include "ControllerLayoutFromXML.h"

#include "../../../../FatedQuest.Libraries/StoredDocument/StoredDocument.h"
#include "ControllerLayout.h"
#include "../../../../FatedQuest.Libraries/StandardOperations/Number/IntHelpers.h"
#include "../../../../FatedQuest.Libraries/StandardOperations/Text/StringHelpers.h"
#include "../../../../FatedQuest.Libraries/Logger/AllReferences.h"

using namespace SuperGameInput;

ControllerLayoutFromXML::ControllerLayoutFromXML()
{
    m_mainTagName = StringHelpers::ToLower(MainTagName);
    m_metaTagName = StringHelpers::ToLower(MetaTagName);
    m_buttonTagName = StringHelpers::ToLower(ButtonTagName);
    m_buttonTagSingularName = StringHelpers::ToLower(ButtonTagSingularName);
    m_axisToButtonTagName = StringHelpers::ToLower(AxisToButtonTagName);
    m_axisToButtonTagSingularName = StringHelpers::ToLower(AxisToButtonTagSingularName);
    m_hatSDLMappingName = StringHelpers::ToLower(HatSDLMappingName);
    m_sDLToUniversalAxesName = StringHelpers::ToLower(SDLToUniversalAxesName);
    m_sDLToUniversalAxesSingularName = StringHelpers::ToLower(SDLToUniversalAxesSingularName);
}

ControllerLayoutFromXML::~ControllerLayoutFromXML()
{
}

std::shared_ptr<ControllerLayout> ControllerLayoutFromXML::CreateFromDocument(
    const std::shared_ptr<StoredDocument>& document, 
    std::string& error)
{
    if (!document->GetRoot())
    {
        error = "No root to the document found, was it loaded?";
        return {};
    }

    if (StringHelpers::ToLower(document->GetRoot()->Name()) != m_mainTagName)
    {
        error = "Root tag does not match a controller layout. Is this a layout?";
        return {};
    }

    std::string methodName = "std::shared_ptr<ControllerLayout> ControllerLayoutFromXML::CreateFromDocument"
                             "(const std::shared_ptr<StoredDocument>&,std::string&)";
    bool parsedMetaTag = false;
    auto layout = std::make_shared<ControllerLayout>();
    for (std::shared_ptr<StoredDocumentNode> child = document->GetRoot()->GetFirstChild(); child; child = child->GetAdjacentNode())
    {
        std::string name = StringHelpers::ToLower(child->Name());
        if (m_metaTagName == name)
        {
            if (ParseMetaData(child, layout))
            {
                parsedMetaTag = true;
            }
        }
        else if (m_buttonTagName == name)
        {
            if (!ParseSDLToUniversalButtons(child, layout))
            {
                Log::Warning("Could not parse SDLToUniversalButtons in Controller Layout.",
                    methodName);
            }
        }
    }

    if (!parsedMetaTag)
    {
        return {};
    }

    return layout;
}

bool ControllerLayoutFromXML::ParseMetaData(
    const std::shared_ptr<StoredDocumentNode>& node,
    const std::shared_ptr<ControllerLayout>& controllerLayout) const
{
    bool parsedSuccessfullySoFar = true;
    if (const std::shared_ptr<StoredDocumentAttribute> attribute = 
        node->Attribute("Name",CaseSensitivity::IgnoreCase))
    {
        if (attribute->Value().empty())
        {
            parsedSuccessfullySoFar = false;
        }
        else
        {
            controllerLayout->Name = attribute->Value();
        }
    }
    else
    {
        parsedSuccessfullySoFar = false;
    }

    if (const std::shared_ptr<StoredDocumentAttribute> attribute =
        node->Attribute("Controller", CaseSensitivity::IgnoreCase))
    {
        if (attribute->Value().empty())
        {
            parsedSuccessfullySoFar = false;
        }
        else
        {
            Controller parsed = EController::FromString(attribute->Value());
            if (parsed == Controller::Unknown)
            {
                parsedSuccessfullySoFar = false;
            }
            else
            {
                controllerLayout->Controller = parsed;
            }

        }
    }
    else
    {
        parsedSuccessfullySoFar = false;
    }

    if (const std::shared_ptr<StoredDocumentAttribute> attribute =
        node->Attribute("Axis", CaseSensitivity::IgnoreCase))
    {
        if (attribute->Value().empty())
        {
            parsedSuccessfullySoFar = false;
        }
        else
        {
            int output = -1;
            if (IntHelpers::TryParse(attribute->Value(), output))
            {
                controllerLayout->Axis = output;
            }
            else
            {
                parsedSuccessfullySoFar = false;
            }
        }
    }
    else
    {
        parsedSuccessfullySoFar = false;
    }

    if (const std::shared_ptr<StoredDocumentAttribute> attribute =
        node->Attribute("Buttons", CaseSensitivity::IgnoreCase))
    {
        if (attribute->Value().empty())
        {
            parsedSuccessfullySoFar = false;
        }
        else
        {
            int output = -1;
            if (IntHelpers::TryParse(attribute->Value(), output))
            {
                controllerLayout->Buttons = output;
            }
            else
            {
                parsedSuccessfullySoFar = false;
            }
        }
    }
    else
    {
        parsedSuccessfullySoFar = false;
    }

    return parsedSuccessfullySoFar;
}

bool ControllerLayoutFromXML::ParseSDLToUniversalButtons(
    const std::shared_ptr<StoredDocumentNode>& node,
    const std::shared_ptr<ControllerLayout>& controllerLayout) const
{
    for (std::shared_ptr<StoredDocumentNode> child = node->GetFirstChild(); child; child = child->GetAdjacentNode())
    {
        std::string name = StringHelpers::ToLower(child->Name());
        if (m_buttonTagSingularName == name)
        {
            std::pair<int, UniversalControllerButton> output;
            if (ParseSDLToUniversalButton(child, output))
            {
                controllerLayout->SDLToUniversalButton.emplace_back(output);
            }
        }
    }

    return true;
}

bool ControllerLayoutFromXML::ParseSDLToUniversalButton(const std::shared_ptr<StoredDocumentNode>& node,
    std::pair<int, UniversalControllerButton>& singleSDLButtonMapping) const
{
    bool parsedSuccessfullySoFar = true;
    if (const std::shared_ptr<StoredDocumentAttribute> attribute =
        node->Attribute("SDLButton", CaseSensitivity::IgnoreCase))
    {
        if (attribute->Value().empty())
        {
            parsedSuccessfullySoFar = false;
        }
        else
        {
            int output = -1;
            if (IntHelpers::TryParse(attribute->Value(), output))
            {
                singleSDLButtonMapping.first = output;
            }
            else
            {
                parsedSuccessfullySoFar = false;
            }
        }
    }
    else
    {
        parsedSuccessfullySoFar = false;
    }

    if (const std::shared_ptr<StoredDocumentAttribute> attribute =
        node->Attribute("UniversalControllerButton", CaseSensitivity::IgnoreCase))
    {
        if (attribute->Value().empty())
        {
            parsedSuccessfullySoFar = false;
        }
        else
        {
            UniversalControllerButton parsed = EUniversalControllerButton::FromString(attribute->Value());
            if (parsed == UniversalControllerButton::Unknown)
            {
                parsedSuccessfullySoFar = false;
            }
            else
            {
                singleSDLButtonMapping.second = parsed;
            }

        }
    }
    else
    {
        parsedSuccessfullySoFar = false;
    }

    return parsedSuccessfullySoFar;
}