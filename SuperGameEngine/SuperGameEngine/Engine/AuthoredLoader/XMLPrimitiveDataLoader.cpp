#include "XMLPrimitiveDataLoader.h"

using namespace SuperGameEngine;
using namespace rapidxml;
const std::shared_ptr<PrimitiveData> XMLPrimitiveDataLoader::ExtractData(const std::string& data)
{
    std::shared_ptr<XMLDocument> document = std::make_shared<XMLDocument>();
    bool didParse = ParseDocument(data, document);
    if(!didParse)
    {
        return std::shared_ptr<PrimitiveData>();
    }

    XMLNode* rootNode = document->first_node();

    std::shared_ptr<PrimitiveData> primitiveData;
    std::vector<std::shared_ptr<PrimitiveData>> children = std::vector<std::shared_ptr<PrimitiveData>>();
    for (XMLNode* childNode = rootNode->first_node(); childNode; childNode = childNode->next_sibling())
    {
        std::shared_ptr<PrimitiveData> child = std::make_shared<PrimitiveData>();
        AddNodeToData(childNode, child);
        children.push_back(child);
    }

    std::string nameAsString = rootNode->name();
    primitiveData = std::make_shared<PrimitiveData>(nameAsString, children);

    return primitiveData;
}

bool XMLPrimitiveDataLoader::ParseDocument(const std::string& contents, std::shared_ptr<XMLDocument> document)
{
    bool didParse = false;
    try
    {
        document->parse<0>(const_cast<char*>(contents.c_str()));
        didParse = true;
    }
    catch (rapidxml::parse_error e)
    {
        // Did not parse.
    }

    return didParse;
}

void XMLPrimitiveDataLoader::AddNodeToData(const XMLNode* node, std::shared_ptr<PrimitiveData>& data)
{
    std::vector<std::shared_ptr<PrimitiveData>> children = std::vector<std::shared_ptr<PrimitiveData>>();
    for (XMLNode* childNode = node->first_node(); childNode; childNode = childNode->next_sibling())
    {
        std::shared_ptr<PrimitiveData> child = std::make_shared<PrimitiveData>();
        AddNodeToData(childNode, child);
        children.push_back(child);
    }

    std::string nameAsString = node->name();
    data = std::make_shared<PrimitiveData>(nameAsString, children);
}
