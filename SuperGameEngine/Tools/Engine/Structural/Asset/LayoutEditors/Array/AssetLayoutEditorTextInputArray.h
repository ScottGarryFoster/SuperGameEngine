#pragma once
#include "../AssetLayoutEditor.h"
#include <memory>
#include <string>

#include "AssetLayoutEditorArray.h"

namespace SuperGameTools
{
    /// <summary>
    /// Encapsulates a single control within an Asset, described with an asset layout and file.
    /// </summary>
    class AssetLayoutEditorTextInputArray : public virtual AssetLayoutEditor, AssetLayoutEditorArray
    {
    public:
        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="map">Parameter to modify within the asset. </param>
        AssetLayoutEditorTextInputArray(const std::string& map);
        virtual ~AssetLayoutEditorTextInputArray();

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

        /// <summary>
        /// True when the given index is set in the object data.
        /// </summary>
        /// <param name="universalObjectData">A pointer to the asset. </param>
        /// <param name="arrayIndex">Index of the element. </param>
        /// <returns>True means exists. </returns>
        virtual bool DoesObjectContain(
            const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData,
            size_t arrayIndex) const override;

    private:

        /// <summary>
        /// The size of the text field by default (number of characters;
        /// </summary>
        const size_t m_defaultTextCapacity = 2048;

        /// <summary>
        /// The parameter within the Asset to modify.
        /// </summary>
        std::string m_map;
    };
}
