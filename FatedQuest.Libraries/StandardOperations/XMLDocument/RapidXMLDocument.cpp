#include "RapidXMLDocument.h"
#include "../AllReferences.h"

using namespace FatedQuestLibraries;

RapidXMLDocument::RapidXMLDocument()
{
}

bool RapidXMLDocument::LoadFromFile(const std::string& path)
{
    bool couldParse = false;
    if (!File::Exists(path))
    {
        // Early out. No file, nothing to parse.
        return false;
    }

    // We must create the string now and have it as a mutable string.
    // Rapid modifies the string contents inline as it parses.
    // This means this string must exist for as long as we are parsing and
    // must be mutable to override.
    std::string fileContents = File::ReadFileContents(path);

    bool didParse = false;
    std::shared_ptr<RapidXML::XMLDocument> document = TryParseXMLDocument(fileContents, didParse);
    if (!didParse)
    {
        // Could not parse.
        return false;
    }

    RapidXML::XMLNode* node = document->first_node();
    m_rootNode = ParseNode(node);

    return true;
}

bool RapidXMLDocument::Load(const std::string& fileContents)
{
    // We must create the string now and have it as a mutable string.
    // Rapid modifies the string contents inline as it parses.
    // This means this string must exist for as long as we are parsing and
    // must be mutable to override.
    std::string fileContentsMutable(fileContents);

    bool didParse = false;
    std::shared_ptr<RapidXML::XMLDocument> document = TryParseXMLDocument(fileContentsMutable, didParse);
    if (!didParse)
    {
        // Could not parse.
        return false;
    }

    RapidXML::XMLNode* node = document->first_node();
    m_rootNode = ParseNode(node);

    return true;
}

std::shared_ptr<XMLNode> RapidXMLDocument::GetRoot()
{
    return m_rootNode;
}

std::shared_ptr<RapidXML::XMLDocument> RapidXMLDocument::TryParseXMLDocument(const std::string& xmlContents, bool& didParse)
{
    std::shared_ptr<RapidXML::XMLDocument> document = std::make_shared<RapidXML::XMLDocument>();
    didParse = false;

    try
    {
        document->parse<0>(const_cast<char*>(&xmlContents[0]));
        didParse = true;
    }
    catch (rapidxml::parse_error e)
    {
    }

    return document;
}

std::shared_ptr<RapidXMLNode> RapidXMLDocument::ParseNode(RapidXML::XMLNode* currentNode)
{
    std::shared_ptr<RapidXMLNode> parseNode = std::make_shared<RapidXMLNode>();
    std::string name = currentNode->name();
    parseNode->SetName(name);

    std::vector<std::shared_ptr<XMLAttribute>> attributesInNode;
    for (RapidXML::XMLAttribute* child = currentNode->first_attribute(); child; child = child->next_attribute())
    {
        std::stringstream myStreamString;
        myStreamString << child->name();
        std::string myString = myStreamString.str();

        const char* n = child->name();
        std::string name(child->name());
        std::string value(child->value());
        attributesInNode.push_back(std::make_shared<RapidXMLAttribute>(name, value));
    }
    parseNode->SetAttributes(attributesInNode);

    bool foundNode = false;
    std::shared_ptr<RapidXMLNode> firstChild;
    std::shared_ptr<RapidXMLNode> last;
    for (RapidXML::XMLNode* child = currentNode->first_node(); child; child = child->next_sibling())
    {
        std::shared_ptr<RapidXMLNode> current = ParseNode(child);
        last = current;

        if (!foundNode)
        {
            firstChild = current;
            foundNode = true;
        }
        else
        {
            current->GiveAdjacentNode(last);
        }
    }

    parseNode->GiveFirstChild(firstChild);
    parseNode->GiveLastChild(last);

    return parseNode;
}
