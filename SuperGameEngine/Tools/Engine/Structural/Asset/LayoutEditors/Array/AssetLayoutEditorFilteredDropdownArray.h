#pragma once
#include "../AssetLayoutEditor.h"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "AssetLayoutEditorArray.h"

namespace SuperGameTools
{
    /// <summary>
    /// Encapsulates a single control within an Asset, described with an asset layout and file.
    /// </summary>
    class AssetLayoutEditorFilteredDropdownArray : public virtual AssetLayoutEditor, AssetLayoutEditorArray
    {
    public:
        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="map">Parameter to modify within the asset. </param>
        /// <param name="values">Values to filter to. </param>
        AssetLayoutEditorFilteredDropdownArray(const std::string& map, const std::vector<std::string>& values);
        virtual ~AssetLayoutEditorFilteredDropdownArray();

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

        /// <summary>
        /// Called when the data object is saved.
        /// This should not actually need to save any data but can be used to clean up anything in edit
        /// ready to be saved data, most notably things like blank strings in arrays. 
        /// </summary>
        /// <param name="universalObjectData">A pointer to the asset. </param>
        virtual void OnSave(const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData) const override;

        /// <summary>
        /// Draw just the actual meat of the asset layout, the text box, the vector, the dropdown.
        /// Nothing to do with the array.
        /// </summary>
        /// <param name="universalObjectData">A pointer to data. </param>
        /// <param name="map">The map to use. </param>
        virtual void DrawSingleValue(
            const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData,
            const std::string& map) const override;

        /// <summary>
        /// Add a new string at the given index.
        /// </summary>
        /// <param name="universalObjectData">A pointer to the asset. </param>
        /// <param name="arrayIndex">The index to add a string. </param>
        /// <param name="map">Name of the entry without the index. </param>
        virtual void AddEntry(
            const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData,
            size_t arrayIndex,
            const std::string& map) const override;

        /// <summary>
        /// Remove an entry at the given point. Note everything will be shifted from this point.
        /// </summary>
        /// <param name="universalObjectData">A pointer to the asset. </param>
        /// <param name="arrayIndex">A pointer to the asset. </param>
        /// <param name="map">Name of the entry without the index. </param>
        virtual void RemoveEntry(
            const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData,
            size_t arrayIndex,
            const std::string& map) const override;
    private:
        /// <summary>
        /// Values to filter to.
        /// </summary>
        std::vector<std::string> m_values;

        /// <summary>
        /// Values as const char for the ImGui Call.
        /// </summary>
        std::vector<const char*> m_valuesChars;

        /// <summary>
        /// This is the values stored as a map used to quickly
        /// get the index from the value.
        /// </summary>
        /// <remarks>
        /// We are trading a little extra memory for quicker search time here.
        /// </remarks>
        std::unordered_map<std::string, int> m_valuesValueByIndex;

        /// <summary>
        /// The parameter within the Asset to modify.
        /// </summary>
        std::string m_map;
    };
}
