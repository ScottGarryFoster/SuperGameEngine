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

    RapidXML::XMLDocument* document = TryParseXMLDocument(path);
    if (document == nullptr)
    {
        // Could not parse.
        return false;
    }

    RapidXML::XMLNode* node = document->first_node();
    m_rootNode = std::make_shared<RapidXMLNode>();
    std::string name = node->name();
    m_rootNode->SetName(name);

    return true;
}

std::shared_ptr<XMLNode> RapidXMLDocument::GetRoot()
{
    return m_rootNode;
}

RapidXML::XMLDocument* RapidXMLDocument::TryParseXMLDocument(const std::string& path)
{
    std::string fileContents = File::ReadFileContents(path);

    RapidXML::XMLDocument* document = new RapidXML::XMLDocument();
    try
    {
        document->parse<0>(const_cast<char*>(fileContents.c_str()));
    }
    catch (rapidxml::parse_error e)
    {
        delete document;
        document = nullptr;
    }

    return document;
}
