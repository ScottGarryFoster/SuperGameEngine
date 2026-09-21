#pragma once
#include <string>
#include "LayoutEditor.h"

namespace SuperGameTools
{
    class LayoutRequirements;
    /// <summary>
    /// Escapulates a single control for entering data into a universal data file.
    /// This allows a link to another asset to be added.
    /// </summary>
    class LayoutEditorAssetLink : public virtual LayoutEditor
    {
    public:
        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="map">Parameter to modify within the asset. </param>
        /// <param name="values">Values to filter to. </param>
        LayoutEditorAssetLink(const std::string& map, const std::shared_ptr<LayoutRequirements>& layoutRequirements);
        virtual ~LayoutEditorAssetLink();
        
        /// <summary>
        /// Update loop call for the given asset to prepare anything for the layout.
        /// </summary>
        /// <param name="universalObjectData">A pointer to the asset. </param>
        virtual void Update(const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData) 
            const override;

        /// <summary>
        /// Draws and may alter the data within the asset.
        /// </summary>
        /// <param name="universalObjectData">A pointer to the asset.</param>
        virtual void Draw(const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData) 
            const override;

        /// <summary>
        /// Draws the label of the editor.
        /// </summary>
        /// <param name="universalObjectData">A pointer to the asset.</param>
        virtual void DrawLabel(
            const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData) 
            const override;

        /// <summary>
        /// Draws the value editor for the editor.
        /// </summary>
        /// <param name="universalObjectData">A pointer to the asset.</param>
        virtual void DrawValue(
            const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData) 
            const override;

        /// <summary>
        /// Called when the data object is saved.
        /// This should not actually need to save any data but can be used to clean up anything in edit
        /// ready to be saved data, most notably things like blank strings in arrays. 
        /// </summary>
        /// <param name="universalObjectData">A pointer to the asset. </param>
        virtual void OnSave(const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData) 
            const override {}//No op

        /// <summary>
        /// Is true when this layout is required and therefore should be shown.
        /// </summary>
        /// <param name="universalObjectData">A pointer to the asset. </param>
        /// <returns>Is true when this layout is required and therefore should be shown. </returns>
        virtual bool ShouldShow(const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData) 
            const override;
        
    private:
        /// <summary>
        /// The size of the text field by default (number of characters)
        /// </summary>
        const size_t m_defaultTextCapacity = 2048;
        
        /// <summary>
        /// The parameter within the Asset to modify.
        /// </summary>
        std::string m_map;

        /// <summary>
        /// Resolves requirements for layout editors.
        /// </summary>
        std::shared_ptr<LayoutRequirements> m_layoutRequirements;
        
        /// <summary>
        /// Add the drag and drop functionality.
        /// </summary>
        /// <param name="xTop">X at the beginning of the element. </param>
        /// <param name="yTop">Y at the beginning of the element. </param>
        /// <param name="xBottom">X at the end of the element. </param>
        /// <param name="yBottom">Y at the end of the element. </param>
        void EnableDropTarget(float xTop, float yTop, float xBottom, float yBottom, 
            const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData) const;
    };
}
