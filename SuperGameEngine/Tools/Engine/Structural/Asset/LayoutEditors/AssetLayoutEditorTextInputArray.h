#pragma once
#include "AssetLayoutEditor.h"
#include <memory>
#include <string>

namespace SuperGameTools
{
    /// <summary>
    /// Encapsulates a single control within an Asset, described with an asset layout and file.
    /// </summary>
    class AssetLayoutEditorTextInputArray : public virtual AssetLayoutEditor
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
    private:

        /// <summary>
        /// The size of the text field by default (number of characters;
        /// </summary>
        const size_t m_defaultTextCapacity = 2048;

        /// <summary>
        /// The parameter within the Asset to modify.
        /// </summary>
        std::string m_map;

        /// <summary>
        /// Draw a single row in the array.
        /// </summary>
        /// <param name="universalObjectData">A pointer to the asset. </param>
        /// <param name="arrayIndex">Index to draw. </param>
        /// <returns>True means keep the value. False means delete. </returns>
        bool DrawSingleArrayValue(
            const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData, 
            size_t arrayIndex) const;

        /// <summary>
        /// Add a new string at the given index.
        /// </summary>
        /// <param name="universalObjectData">A pointer to the asset. </param>
        /// <param name="arrayIndex">The index to add a string. </param>
        void AddEntry(
            const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData,
            size_t arrayIndex) const;

        /// <summary>
        /// Remove an entry at the given point. Note everything will be shifted from this point.
        /// </summary>
        /// <param name="universalObjectData">A pointer to the asset. </param>
        /// <param name="arrayIndex">A pointer to the asset. </param>
        void RemoveEntry(
            const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData,
            size_t arrayIndex) const;

        /// <summary>
        /// Create the full name of an entry in the universal data object.
        /// </summary>
        /// <param name="index">Index to gather for. </param>
        /// <returns>The name of the entry. </returns>
        std::string GetFullEntryName(size_t index) const;
    };
}
