#include "SimpleDocumentToXml.h"
#include "../StoredDocument.h"
#include <sstream>

#include "../../StandardOperations/Text/StringHelpers.h"

using namespace FatedQuestLibraries;

std::string SimpleDocumentToXml::ConvertToXml(
    const std::shared_ptr<StoredDocument>& storedDocument) const
{
    std::string currentXml = {};
    AddNodeToDocument(currentXml, storedDocument->GetRoot(), 0);

    return currentXml;
}

void SimpleDocumentToXml::AddNodeToDocument(
    std::string& currentXml,
    const std::shared_ptr<StoredDocumentNode>& currentStoredNode,
    int numberOfIndents) const
{
    std::stringstream ss;
    ss << ReturnIndentsForNumber(numberOfIndents);
    ss << "<" << currentStoredNode->Name();
    for (const std::shared_ptr<StoredDocumentAttribute> attribute : currentStoredNode->Attributes())
    {
        ss << " \"" << Escape(attribute->Name()) << "\"=\"" << Escape(attribute->Value()) << "\"";
    }


    bool areInnerAttributes = false;
    std::string inner = {};
    for (std::shared_ptr<StoredDocumentNode> child = currentStoredNode->GetFirstChild(); child; child = child->GetAdjacentNode())
    {
        AddNodeToDocument(inner, child, numberOfIndents + 1);
        areInnerAttributes = true;
    }

    if (areInnerAttributes)
    {
        ss << ">\n" << inner;
        
        if (!currentStoredNode->Inner().empty())
        {
            ss << ReturnIndentsForNumber(numberOfIndents + 1);
            ss << Escape(currentStoredNode->Inner());
            if (ss.str().back() != '\n')
            {
                ss << "\n";
            }
        }
        ss << ReturnIndentsForNumber(numberOfIndents);
        ss << "</" << currentStoredNode->Name() << ">\n";
    }
    else
    {
        if (currentStoredNode->Inner().empty())
        {
            ss << " />\n";
        }
        else
        {
            ss << ">\n";

            ss << ReturnIndentsForNumber(numberOfIndents + 1);
            ss << Escape(currentStoredNode->Inner());
            if (ss.str().back() != '\n')
            {
                ss << "\n";
            }

            ss << ReturnIndentsForNumber(numberOfIndents);
            ss << "</" << currentStoredNode->Name() << ">\n";
        }
    }

    currentXml += ss.str();
}

std::string SimpleDocumentToXml::ReturnIndentsForNumber(int indents) const
{
    std::stringstream ss;
    for (int i = 0; i < indents; ++i)
    {
        ss << "    ";
    }

    return ss.str();
}

std::string SimpleDocumentToXml::Escape(const std::string& input) const
{
    std::string output = StringHelpers::ReplaceAll(input, "\"", "&quot;");
    output = StringHelpers::ReplaceAll(output, "'", "&apos;");
    output = StringHelpers::ReplaceAll(output, "<", "&lt;");
    output = StringHelpers::ReplaceAll(output, ">", "&gt;");
    output = StringHelpers::ReplaceAll(output, "&", "&amp;");

    return output;
}