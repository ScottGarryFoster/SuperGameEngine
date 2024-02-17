#pragma once
#include "../../RapidXML.h"
#include "../../LibraryIncludes.h"
#include "ControllerLayout.h"

using namespace rapidxml;
namespace SuperGameEngine
{
    /// <summary>
    /// Creates a Controller Layout from XML Format.
    /// </summary>
    class ControllerLayoutFromXML
    {
    public:
        ControllerLayoutFromXML();
        virtual ~ControllerLayoutFromXML();

        const std::string MainTagName = "ControllerLayout";
        const std::string MetaTagName = "Metadata";
        const std::string ButtonTagName = "SDLToUniversalButtons";
        const std::string AxisToButtonTagName = "AxisToButtons";

        /// <summary>
        /// Creates a Controller Layout from XML format.
        /// You are responsible for the pointer which comes back, ensure you delete it.
        /// </summary>
        /// <param name="xml">Controller Layout in XML form. </param>
        /// <param name="error">If the input is incorrect, this is the reason why. </param>
        /// <returns>Controller Layout or nullptr if could not create. </returns>
        ControllerLayout* CreateFromXML(FString xml, FString& error);

    private:
        /// <summary>
        /// Tries to parse the document into XML.
        /// You need to clean up the Document pointer from this!
        /// </summary>
        /// <param name="xml">XML form of Controller Layout.</param>
        /// <param name="document">If parsed this is the parsed document out.</param>
        /// <returns>True means did parse.</returns>
        bool TryParseXMLDocument(FString& xml, XMLDocument** document);

        /// <summary>
        /// Extracts the child nodes
        /// </summary>
        /// <param name="document">Document to find the data. </param>
        void ExtractTopLevelNodes(
            XMLDocument* document,
            XMLNode** metaNode,
            XMLNode** sdlToUniversalButtons,
            XMLNode** axisToButtons,
            XMLNode** sdlHatToDpad,
            XMLNode** sdlAxisToUniversalAxis);

        /// <summary>
        /// Extracts data from the meta tag section of the document.
        /// </summary>
        /// <param name="document">Document parsed. </param>
        /// <param name="controllerLayout">Location to write the data to. </param>
        /// <param name="error">If you fail to parse data, write an error in here. </param>
        /// <returns>True means data was in the correct format. </returns>
        bool ParseMetaTag(XMLNode* metaNode, ControllerLayout* controllerLayout, FString& error);
    };
}