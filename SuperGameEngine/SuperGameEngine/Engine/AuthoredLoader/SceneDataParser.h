#pragma once
#include "PrimitiveDataParser.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Parses data as though the data repsents a scene.
    /// </summary>
    class SceneDataParser : public PrimitiveDataParser
    {
    public:
        /// <summary>
        /// Parse the given data into Parsed data.
        /// </summary>
        /// <param name="primitiveData">
        /// Primitive Data in a String format.
        /// </param>
        /// <returns>A parsed version of the data. </returns>
        virtual const std::shared_ptr<ParsedData> ParseData(const std::shared_ptr<PrimitiveData> primitiveData) override;

    private:
        /// <summary>
        /// The data name for a Scene.
        /// </summary>
        const std::string m_sceneName = "Scene";

        /// <summary>
        /// The data name for a GameObject.
        /// </summary>
        const std::string m_gameObjectName = "GameObject";

        /// <summary>
        /// The data name for a Game Component.
        /// </summary>
        const std::string m_gameComponentsName = "GameComponent";

        /// <summary>
        /// The data name for a property.
        /// </summary>
        const std::string m_property = "Property";

        /// <summary>
        /// Finds and Adds GameObjects.
        /// </summary>
        /// <param name="primitive">Unparsed data. </param>
        /// <returns>GameObject data. </returns>
        const std::shared_ptr<ParsedData> AddGameObjects(const std::shared_ptr<const PrimitiveData> primitive);

        /// <summary>
        /// Finds and Adds GameComponents.
        /// </summary>
        /// <param name="primitive">Unparsed data. </param>
        /// <returns>GameComponent data. </returns>
        const std::shared_ptr<ParsedData> AddGameComponents(const std::shared_ptr<const PrimitiveData> primitive);

        /// <summary>
        /// Finds and Adds Properties.
        /// </summary>
        /// <param name="primitive">Unparsed data. </param>
        /// <returns>Properties data. </returns>
        const std::shared_ptr<ParsedData> AddProperties(const std::shared_ptr<const PrimitiveData> primitive);

        /// <summary>
        /// Create and parse property data.
        /// Decides the type of property to parse and then the particular method will parse the data.
        /// </summary>
        /// <param name="primitive">Unparsed data. </param>
        /// <param name="type">The property type. </param>
        /// <returns>Parsed property if posible Empty if not. </returns>
        /// <remark>
        /// This is arguably the most important part as this is point in the code logic changes based upon what is authoured.
        /// </remark>
        const std::shared_ptr<ParsedData> CreatePropertyOfType(
            const std::shared_ptr<const PrimitiveData> primitive,
            const std::string& type);

        /// <summary>
        /// Creates a String property.
        /// </summary>
        /// <param name="primitive">Unparsed data. </param>
        /// <returns>Parsed property. </returns>
        const std::shared_ptr<ParsedData> CreateStringProperty(const std::shared_ptr<const PrimitiveData> primitive);

        /// <summary>
        /// Creates a Int property.
        /// </summary>
        /// <param name="primitive">Unparsed data. </param>
        /// <returns>Parsed property. </returns>
        const std::shared_ptr<ParsedData> CreateIntProperty(const std::shared_ptr<const PrimitiveData> primitive);
    };
}