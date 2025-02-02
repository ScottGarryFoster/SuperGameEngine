#pragma once
#include <memory>
#include <string>

#include "ControllerAxisMappedToButton.h"
#include "UniversalControllerButton.h"

namespace FatedQuestLibraries
{
    class StoredDocumentNode;
    class StoredDocument;
}

using namespace FatedQuestLibraries;

namespace SuperGameInput
{
    struct ControllerLayout;

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
        inline static const std::string MainTagName = "ControllerLayout";

        /// <summary>
        /// Contains metadata for the controller.
        /// </summary>
        inline static const std::string MetaTagName = "Metadata";

        /// <summary>
        /// Contains SDL to Universal Button mapping.
        /// </summary>
        inline static const std::string ButtonTagName = "SDLToUniversalButtons";

        /// <summary>
        /// A single SDL to Universal Button mapping.
        /// </summary>
        inline static const std::string ButtonTagSingularName = "SDLToUniversalButton";

        /// <summary>
        /// Contains SDL Axis mapped to Universal Buttons.
        /// </summary>
        inline static const std::string AxisToButtonTagName = "AxisToButtons";

        /// <summary>
        /// A single Axis mapped to a Universal Button.
        /// </summary>
        inline static const std::string AxisToButtonTagSingularName = "AxisToButton";

        /// <summary>
        /// The SDL Hat Mapped to the DPad.
        /// </summary>
        inline static const std::string HatSDLMappingName = "HatSDLMapping";

        /// <summary>
        /// Contains SDL Axes mapped to Universal Axis
        /// </summary>
        inline static const std::string SDLToUniversalAxesName = "SDLToUniversalAxes";

        /// <summary>
        /// A single Axis mapped to a Universal Axis.
        /// </summary>
        inline static const std::string SDLToUniversalAxesSingularName = "SDLToUniversalAxis";

        /// <summary>
        /// Creates a Controller Layout from XML format.
        /// </summary>
        /// <param name="document">Document parsed as a StoredDocument. </param>
        /// <param name="error">If the input is incorrect, this is the reason why. </param>
        /// <returns>Controller Layout or empty if could not create. </returns>
        std::shared_ptr<ControllerLayout> CreateFromDocument(
            const std::shared_ptr<StoredDocument>& document, 
            std::string& error);

    private:

        /// <summary>
        /// Main XML Tag for the document.
        /// </summary>
        std::string m_mainTagName;

        /// <summary>
        /// Contains metadata for the controller.
        /// </summary>
        std::string m_metaTagName;

        /// <summary>
        /// Contains SDL to Universal Button mapping.
        /// </summary>
        std::string m_buttonTagName;

        /// <summary>
        /// A single SDL to Universal Button mapping.
        /// </summary>
        std::string m_buttonTagSingularName;

        /// <summary>
        /// Contains SDL Axis mapped to Universal Buttons.
        /// </summary>
        std::string m_axisToButtonTagName;

        /// <summary>
        /// A single Axis mapped to a Universal Button.
        /// </summary>
        std::string m_axisToButtonTagSingularName;

        /// <summary>
        /// The SDL Hat Mapped to the DPad.
        /// </summary>
        std::string m_hatSDLMappingName;

        /// <summary>
        /// Contains SDL Axes mapped to Universal Axis
        /// </summary>
        std::string m_sDLToUniversalAxesName;

        /// <summary>
        /// A single Axis mapped to a Universal Axis.
        /// </summary>
        std::string m_sDLToUniversalAxesSingularName;

        /// <summary>
        /// Parses the metadata section of the document.
        /// </summary>
        /// <param name="node">Metadata node.</param>
        /// <param name="controllerLayout">Controller layout to add data to</param>
        /// <returns>True means parsed successfully. </returns>
        bool ParseMetaData(const std::shared_ptr<StoredDocumentNode>& node, const std::shared_ptr<ControllerLayout>& controllerLayout) const;

        /// <summary>
        /// Parses the SDLToUniversalButtons node.
        /// </summary>
        /// <param name="node">SDLToUniversalButtons node.</param>
        /// <param name="controllerLayout">Controller layout to add data to. </param>
        /// <returns>True means parsed successfully. </returns>
        bool ParseSDLToUniversalButtons(const std::shared_ptr<StoredDocumentNode>& node, const std::shared_ptr<ControllerLayout>& controllerLayout) const;

        /// <summary>
        /// Parses the SDLToUniversalButton node.
        /// </summary>
        /// <param name="node">SDLToUniversalButton node.</param>
        /// <param name="singleSDLButtonMapping">Output from parsing. Discarded if returns false. </param>
        /// <returns>True means parsed successfully. </returns>
        bool ParseSDLToUniversalButton(const std::shared_ptr<StoredDocumentNode>& node, std::pair<int, UniversalControllerButton>& singleSDLButtonMapping) const;

        /// <summary>
        /// Parses the AxisToButtons node.
        /// </summary>
        /// <param name="node">AxisToButtons node.</param>
        /// <param name="controllerLayout">Controller layout to add data to. </param>
        /// <returns>True means parsed successfully. </returns>
        bool ParseAxisToButtons(const std::shared_ptr<StoredDocumentNode>& node, const std::shared_ptr<ControllerLayout>& controllerLayout) const;

        /// <summary>
        /// Parses the AxisToButton node.
        /// </summary>
        /// <param name="node">AxisToButton node.</param>
        /// <param name="singleAxisToButton">Output from parsing. Discarded if returns false. </param>
        /// <returns>True means parsed successfully. </returns>
        bool ParseAxisToButton(const std::shared_ptr<StoredDocumentNode>& node, ControllerAxisMappedToButton& singleAxisToButton) const;
    };
}
