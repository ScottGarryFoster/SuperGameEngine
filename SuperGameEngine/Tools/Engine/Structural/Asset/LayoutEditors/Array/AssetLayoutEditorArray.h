#pragma once
#include "../AssetLayoutEditor.h"
#include <memory>
#include <string>

namespace SuperGameTools
{
    /// <summary>
    /// The array logic for Asset Layouts.
    /// </summary>
    class AssetLayoutEditorArray
    {
    public:
        /// <summary>
        /// Draw just the actual meat of the asset layout, the text box, the vector, the dropdown.
        /// Nothing to do with the array.
        /// </summary>
        /// <param name="universalObjectData">A pointer to data. </param>
        /// <param name="map">The map to use. </param>
        virtual void DrawSingleValue(
            const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData,
            const std::string& map) const = 0;

        /// <summary>
        /// Draws and may alter the data within the asset.
        /// </summary>
        /// <param name="universalObjectData">A pointer to the asset.</param>
        /// <param name="map">Name of the entry without the index. </param>
        virtual void DrawValueInTable(
            const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData,
            const std::string& map) const;

        /// <summary>
        /// Called when the data object is saved.
        /// This should not actually need to save any data but can be used to clean up anything in edit
        /// ready to be saved data, most notably things like blank strings in arrays. 
        /// </summary>
        /// <param name="universalObjectData">A pointer to the asset. </param>
        /// <param name="map">Name of the entry without the index. </param>
        virtual void OnSaveCleanUpArray(
            const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData,
            const std::string& map) const;
    private:

        /// <summary>
        /// Draw a single row in the array.
        /// </summary>
        /// <param name="universalObjectData">A pointer to the asset. </param>
        /// <param name="arrayIndex">Index to draw. </param>
        /// <param name="map">Name of the entry without the index. </param>
        /// <returns>True means keep the value. False means delete. </returns>
        bool DrawASingleRow(
            const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData,
            size_t arrayIndex,
            const std::string& map) const;

        /// <summary>
        /// Add a new string at the given index.
        /// </summary>
        /// <param name="universalObjectData">A pointer to the asset. </param>
        /// <param name="arrayIndex">The index to add a string. </param>
        /// <param name="map">Name of the entry without the index. </param>
        void AddEntry(
            const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData,
            size_t arrayIndex,
            const std::string& map) const;

        /// <summary>
        /// Remove an entry at the given point. Note everything will be shifted from this point.
        /// </summary>
        /// <param name="universalObjectData">A pointer to the asset. </param>
        /// <param name="arrayIndex">A pointer to the asset. </param>
        /// <param name="map">Name of the entry without the index. </param>
        void RemoveEntry(
            const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData,
            size_t arrayIndex,
            const std::string& map) const;

        /// <summary>
        /// Create the full name of an entry in the universal data object.
        /// </summary>
        /// <param name="map">Name of the entry without the index. </param>
        /// <param name="index">Index to gather for. </param>
        /// <returns>The name of the entry. </returns>
        std::string GetFullEntryName(const std::string& map, size_t index) const;
    };
}
