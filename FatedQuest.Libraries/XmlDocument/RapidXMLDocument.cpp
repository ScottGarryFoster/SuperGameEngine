#include "RapidXMLDocument.h"
#include "FatedQuestLibraries.h"

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
    std::shared_ptr<RapidXML::XML_Document> document = TryParseXMLDocument(fileContents, didParse);
    if (!didParse)
    {
        // Could not parse.
        return false;
    }

    RapidXML::XML_Node* node = document->first_node();
    if (node)
    {
        m_rootNode = ParseNode(node);
    }

    return node;
}

bool RapidXMLDocument::Load(const std::string& fileContents)
{
    // We must create the string now and have it as a mutable string.
    // Rapid modifies the string contents inline as it parses.
    // This means this string must exist for as long as we are parsing and
    // must be mutable to override.
    std::string fileContentsMutable(fileContents);

    bool didParse = false;
    std::shared_ptr<RapidXML::XML_Document> document = TryParseXMLDocument(fileContentsMutable, didParse);
    if (!didParse)
    {
        // Could not parse.
        return false;
    }

    RapidXML::XML_Node* node = document->first_node();
    if (node)
    {
        m_rootNode = ParseNode(node);
    }

    return node;
}

std::shared_ptr<StoredDocumentNode> RapidXMLDocument::GetRoot()
{
    return m_rootNode;
}

std::shared_ptr<RapidXML::XML_Document> RapidXMLDocument::TryParseXMLDocument(const std::string& xmlContents, bool& didParse)
{
    std::shared_ptr<RapidXML::XML_Document> document = std::make_shared<RapidXML::XML_Document>();
    didParse = false;

    try
    {
        document->parse<0>(const_cast<char*>(&xmlContents[0]));
        didParse = true;
    }
    catch (rapidxml::parse_error e)
    {
        std::string what = e.what();
        Log::Error("Could not parse XML Document." + what, e.where<char>());
    }

    return document;
}

std::shared_ptr<RapidXMLNode> RapidXMLDocument::ParseNode(RapidXML::XML_Node* currentNode)
{
    std::shared_ptr<RapidXMLNode> parseNode = std::make_shared<RapidXMLNode>();
    std::string name = currentNode->name();
    parseNode->SetName(name);
    parseNode->SetInner(currentNode->value());

    std::vector<std::shared_ptr<StoredDocumentAttribute>> attributesInNode;
    for (RapidXML::XML_Attribute* child = currentNode->first_attribute(); child; child = child->next_attribute())
    {
        std::string name(child->name());
        std::string value(child->value());
        attributesInNode.push_back(std::make_shared<RapidXMLAttribute>(name, value));
    }
    parseNode->SetAttributes(attributesInNode);

    bool foundNode = false;
    std::shared_ptr<RapidXMLNode> firstChild;
    std::shared_ptr<RapidXMLNode> last;
    for (RapidXML::XML_Node* child = currentNode->first_node(); child; child = child->next_sibling())
    {
        std::shared_ptr<RapidXMLNode> current = ParseNode(child);
        if (foundNode)
        {
            last->GiveAdjacentNode(current);
        }
        last = current;

        if (!foundNode)
        {
            firstChild = current;
            foundNode = true;
        }
        else
        {
        }
    }

    parseNode->GiveFirstChild(firstChild);
    parseNode->GiveLastChild(last);

    return parseNode;
}
