#include "RapidDocumentToXml.h">
#include <sstream>

#include "../RapidXML.h"
#include "../../StoredDocument/AllReferences.h"

using namespace FatedQuestLibraries;
using namespace RapidXML;

std::string RapidDocumentToXml::ConvertToXml(
    const std::shared_ptr<StoredDocument>& storedDocument) const
{
    std::shared_ptr<XML_Document> xmlDocument = std::make_shared<XML_Document>();

    std::shared_ptr<XML_Node> currentParent = xmlDocument;
    AddNodeToDocument(xmlDocument, currentParent, storedDocument->GetRoot());

    // TODO: Figure out why this print is not working because RapidXml is no doubt faster than your code.
    std::string ss;
    //rapidxml::print(std::back_inserter(ss), *xmlDocument, 0);

    return ss;
}

void RapidDocumentToXml::AddNodeToDocument(const std::shared_ptr<XML_Document>& document,
    const std::shared_ptr<XML_Node>& parentNode, const std::shared_ptr<StoredDocumentNode>& currentStoredNode) const
{
    auto currentNode = document->allocate_node(node_element, currentStoredNode->Name().c_str());
    if (!currentStoredNode->Inner().empty())
    {
        currentNode->value(currentStoredNode->Inner().c_str());
    }

    for (std::shared_ptr<StoredDocumentAttribute> attribute : currentStoredNode->Attributes())
    {
        currentNode->append_attribute(document->allocate_attribute(attribute->Name().c_str(), attribute->Value().c_str()));
    }

    parentNode->append_node(currentNode);

    auto currentAsShared = std::shared_ptr<XML_Node>(currentNode);
    for (std::shared_ptr<StoredDocumentNode> child = currentStoredNode->GetFirstChild(); child; child = child->GetAdjacentNode())
    {
        AddNodeToDocument(document, currentAsShared, child);
    }
}
