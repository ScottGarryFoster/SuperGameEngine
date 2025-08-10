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
    class AssetLayoutEditorFilteredDropdown : public virtual AssetLayoutEditor
    {
    public:
        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="map">Parameter to modify within the asset. </param>
        /// <param name="values">Values to filter to. </param>
        AssetLayoutEditorFilteredDropdown(const std::string& map, const std::vector<std::string>& values);
        virtual ~AssetLayoutEditorFilteredDropdown();

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
