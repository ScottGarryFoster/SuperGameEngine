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

        /// <summary>
        /// Main XML Tag for the document.
        /// </summary>
        const std::string MainTagName = "ControllerLayout";

        /// <summary>
        /// Contains metadata for the controller.
        /// </summary>
        const std::string MetaTagName = "Metadata";

        /// <summary>
        /// Contains SDL to Universal Button mapping.
        /// </summary>
        const std::string ButtonTagName = "SDLToUniversalButtons";

        /// <summary>
        /// A single SDL to Universal Button mapping.
        /// </summary>
        const std::string ButtonTagSingularName = "SDLToUniversalButton";

        /// <summary>
        /// Contains SDL Axis mapped to Universal Buttons.
        /// </summary>
        const std::string AxisToButtonTagName = "AxisToButtons";

        /// <summary>
        /// A single Axis mapped to a Universal Button.
        /// </summary>
        const std::string AxisToButtonTagSingularName = "AxisToButton";

        /// <summary>
        /// The SDL Hat Mapped to the DPad.
        /// </summary>
        const std::string HatSDLMappingName = "HatSDLMapping";

        /// <summary>
        /// Contains SDL Axes mapped to Universal Axis
        /// </summary>
        const std::string SDLToUniversalAxesName = "SDLToUniversalAxes";

        /// <summary>
        /// A single Axis mapped to a Universal Axis.
        /// </summary>
        const std::string SDLToUniversalAxesSingularName = "SDLToUniversalAxis";

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
        /// <param name="xml">Data as XML. </param>
        /// <returns>
        /// Document pointer if parsed or nullptr if not parsed.
        /// YOU NEED TO CLEAN UP THE DATA FOR THIS POINTER.
        /// </returns>
        XMLDocument* TryParseXMLDocument(FString& xml);

        /// <summary>
        /// Extracts the child nodes
        /// </summary>
        /// <param name="document">Document to find the data. </param>
        /// <param name="metaNode">Tag found with the name <c>MetaTagName</c>. </param>
        /// <param name="sdlToUniversalButtons">Tag found with the name <c>ButtonTagName</c>. </param>
        /// <param name="axisToButtons">Tag found with the name <c>AxisToButtonTagName</c>. </param>
        /// <param name="sdlHatToDpad">Tag found with the name <c>HatSDLMappingName</c>. </param>
        /// <param name="sdlAxisToUniversalAxis">Tag found with the name <c>SDLToUniversalAxesName</c>. </param>
        void ExtractTopLevelNodes(
            XMLDocument* document,
            XMLNode** metaNode,
            XMLNode** sdlToUniversalButtons,
            XMLNode** axisToButtons,
            XMLNode** sdlHatToDpad,
            XMLNode** sdlAxisToUniversalAxis) const;

        /// <summary>
        /// Extracts data from the meta tag section of the document.
        /// </summary>
        /// <param name="document">Document parsed. </param>
        /// <param name="controllerLayout">Location to write the data to. </param>
        /// <param name="error">If you fail to parse data, write an error in here. </param>
        /// <returns>True means data was in the correct format. </returns>
        bool ParseMetaTag(XMLNode* metaNode, ControllerLayout* controllerLayout, FString& error);

        /// <summary>
        /// Parses the SDLToUniversalButtons tag.
        /// </summary>
        /// <param name="node">SDLToUniversalButtons XMLNode. </param>
        /// <param name="controllerLayout">Layout to add data to. </param>
        /// <param name="error">Errors to add to when parsing. </param>
        /// <returns>True means no errors occured. </returns>
        bool ParseSdlToUniversalButtonsTag(XMLNode* node, ControllerLayout* controllerLayout, FString& error);

        /// <summary>
        /// Parses the SDLToUniversalButton tag. (The singular tag)
        /// </summary>
        /// <param name="node">SDLToUniversalButton XMLNode. </param>
        /// <param name="controllerLayout">Layout to add data to. </param>
        /// <param name="error">Errors to add to when parsing. </param>
        /// <returns>True means no errors occured. </returns>
        bool ParseSdlToUniversalButtonTag(XMLNode* node, ControllerLayout* controllerLayout, FString& error);

        /// <summary>
        /// Parses the AxisToButtons tag.
        /// </summary>
        /// <param name="node">AxisToButtons XMLNode. </param>
        /// <param name="controllerLayout">Layout to add data to. </param>
        /// <param name="error">Errors to add to when parsing. </param>
        /// <returns>True means no errors occured. </returns>
        bool ParseAxisToButtonsTag(XMLNode* node, ControllerLayout* controllerLayout, FString& error);

        /// <summary>
        /// Parses the AxisToButton tag. (The singular tag)
        /// </summary>
        /// <param name="node">AxisToButton XMLNode. </param>
        /// <param name="controllerLayout">Layout to add data to. </param>
        /// <param name="error">Errors to add to when parsing. </param>
        /// <returns>True means no errors occured. </returns>
        bool ParseAxisToButtonTag(XMLNode* node, ControllerLayout* controllerLayout, FString& error);

        /// <summary>
        /// Parses the HatSDLMapping tag.
        /// </summary>
        /// <param name="node">HatSDLMapping XMLNode. </param>
        /// <param name="controllerLayout">Layout to add data to. </param>
        /// <param name="error">Errors to add to when parsing. </param>
        /// <returns>True means no errors occured. </returns>
        bool ParseSDLHatToDpadTag(XMLNode* node, ControllerLayout* controllerLayout, FString& error);

        /// <summary>
        /// Parses the SDLToUniversalAxes tag.
        /// </summary>
        /// <param name="node">SDLToUniversalAxes XMLNode. </param>
        /// <param name="controllerLayout">Layout to add data to. </param>
        /// <param name="error">Errors to add to when parsing. </param>
        /// <returns>True means no errors occured. </returns>
        bool ParseSDLToUniversalAxesTag(XMLNode* node, ControllerLayout* controllerLayout, FString& error);

        /// <summary>
        /// Parses the SDLToUniversalAxis tag. (The singular tag)
        /// </summary>
        /// <param name="node">SDLToUniversalAxis XMLNode. </param>
        /// <param name="controllerLayout">Layout to add data to. </param>
        /// <param name="error">Errors to add to when parsing. </param>
        /// <returns>True means no errors occured. </returns>
        bool ParseSDLToUniversalAxisTag(XMLNode* node, ControllerLayout* controllerLayout, FString& error);
    };
}