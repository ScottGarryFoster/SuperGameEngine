#pragma once
#include <memory>
#include <string>

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
        virtual ~ControllerLayoutFromXML() = default;

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
        virtual std::shared_ptr<ControllerLayout> CreateFromDocument(
            const std::shared_ptr<StoredDocument>& document,
            std::string& error) const = 0;
    };
}
