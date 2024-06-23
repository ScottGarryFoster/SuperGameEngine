#pragma once
#include "PrimitiveDataLoader.h"
#include "../../RapidXML.h"

using namespace rapidxml;

namespace SuperGameEngine
{
    /// <summary>
    /// Loads basic data from an external source given the source is in the XML format.
    /// </summary>
    class XMLPrimitiveDataLoader : public PrimitiveDataLoader
    {
    public:
        /// <summary>
        /// Extract basic data into a portable source.
        /// </summary>
        /// <param name="data">XML Data to extract from. </param>
        /// <returns>Extracted data. Will be empty if could not extract. </returns>
        virtual const std::shared_ptr<PrimitiveData> ExtractData(const std::string& data) override;

    private:
        /// <summary>
        /// Parse the XML string into a XMLDocument.
        /// </summary>
        /// <param name="contents">String contents of a file or data source. </param>
        /// <param name="document">Document parsed. </param>
        /// <returns>True means could parse. </returns>
        bool ParseDocument(const std::string& contents, std::shared_ptr<XMLDocument> document);

        /// <summary>
        /// Extract a single node of the data. 
        /// This is recursive and will search down the tree for all data.
        /// </summary>
        /// <param name="node">Primitive data to add this Nodes data to. </param>
        /// <param name="data">Data point this is classified as. </param>
        void AddNodeToData(const XMLNode* node, std::shared_ptr<PrimitiveData>& data);
    };
}