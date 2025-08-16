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
        /// Add a new string at the given index.
        /// </summary>
        /// <param name="universalObjectData">A pointer to the asset. </param>
        /// <param name="arrayIndex">Index of the element. </param>
        /// <param name="map">Name of the entry without the index. </param>
        virtual void AddEntry(
            const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData,
            size_t arrayIndex,
            const std::string& map) const = 0;

        /// <summary>
        /// Remove an entry at the given point. Note everything will be shifted from this point.
        /// </summary>
        /// <param name="universalObjectData">A pointer to the asset. </param>
        /// <param name="arrayIndex">Index of the element. </param>
        /// <param name="map">Name of the entry without the index. </param>
        virtual void RemoveEntry(
            const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData,
            size_t arrayIndex,
            const std::string& map) const = 0;

        /// <summary>
        /// True when the given index is set in the object data.
        /// </summary>
        /// <param name="universalObjectData">A pointer to the asset. </param>
        /// <param name="arrayIndex">Index of the element. </param>
        /// <returns>True means exists. </returns>
        virtual bool DoesObjectContain(
            const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData,
            size_t arrayIndex) const = 0;

        /// <summary>
        /// Draws and may alter the data within the asset.
        /// </summary>
        /// <param name="universalObjectData">A pointer to the asset.</param>
        /// <param name="map">Name of the entry without the index. </param>
        virtual void DrawValueInTable(
            const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData,
            const std::string& map) const;

        /// <summary>
        /// Create the full name of an entry in the universal data object.
        /// </summary>
        /// <param name="map">Name of the entry without the index. </param>
        /// <param name="index">Index to gather for. </param>
        /// <returns>The name of the entry. </returns>
        std::string GetFullEntryName(const std::string& map, size_t index) const;

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
    };
}
