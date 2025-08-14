#pragma once
#include "AssetLayoutEditor.h"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace SuperGameTools
{
    /// <summary>
    /// Encapsulates a single control within an Asset, described with an asset layout and file.
    /// This represents a string input but filtered to a set of options which is represented as a dropdown.
    /// </summary>
    class AssetLayoutEditorVector4I : public virtual AssetLayoutEditor
    {
    public:
        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="map">Parameter to modify within the asset. </param>
        /// <param name="values">Values to filter to. </param>
        AssetLayoutEditorVector4I(const std::string& map);
        virtual ~AssetLayoutEditorVector4I();

        /// <summary>
        /// Update loop call for the given asset to prepare anything for the layout.
        /// </summary>
        /// <param name="universalObjectData">A pointer to the asset. </param>
        virtual void Update(const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData) const override;

        /// <summary>
        /// Draws and may alter the data within the asset.
        /// </summary>
        /// <param name="universalObjectData">A pointer to the asset.</param>
        virtual void Draw(const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData) const override;

        /// <summary>
        /// Draws the label of the editor.
        /// </summary>
        /// <param name="universalObjectData">A pointer to the asset.</param>
        virtual void DrawLabel(
            const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData) const override;

        /// <summary>
        /// Draws the value editor for the editor.
        /// </summary>
        /// <param name="universalObjectData">A pointer to the asset.</param>
        virtual void DrawValue(
            const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData) const override;

    private:
        /// <summary>
        /// The size of the text field by default (number of characters;
        /// </summary>
        const uint16_t m_defaultTextCapacity = 2048;

        /// <summary>
        /// The parameter within the Asset to modify.
        /// </summary>
        std::string m_map;

        /// <summary>
        /// Draw a text box.
        /// </summary>
        /// <param name="label">Label text. </param>
        /// <param name="value">Value in the box. </param>
        /// <returns>True means changed. </returns>
        bool TextInput(const std::string& label, std::string& value) const;
    };
}
