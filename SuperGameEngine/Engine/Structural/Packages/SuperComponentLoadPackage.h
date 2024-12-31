#pragma once
#include <memory>
#include "ComponentLoadPackage.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Everything a component needs to run.
    /// </summary>
    class SuperComponentLoadPackage : public ComponentLoadPackage
    {
    public:
        /// <summary>
        /// Provides and manages all shared resources.
        /// </summary>
        /// <returns>Provides and manages all shared resources. </returns>
        [[nodiscard]] virtual std::shared_ptr<ContentManager> GetContentManager() const override;

        /// <summary>
        /// Set the content manager for the package.
        /// </summary>
        /// <param name="contentManager">Provides and manages all shared resources. </param>
        virtual void SetContentManager(std::shared_ptr<ContentManager> contentManager);

        /// <summary>
        /// Helps to parse serializable objects.
        /// </summary>
        /// <returns>Helps to parse serializable objects. </returns>
        virtual std::shared_ptr<SerializableParser> GetParser() const;

        /// <summary>
        /// Set the Serializable Parser for the package.
        /// </summary>
        /// <param name="serializableParser">New Serializable Parser. </param>
        virtual void SetSerializableParser(const std::shared_ptr<SerializableParser>& serializableParser);
    private:
        /// <summary>
        /// Provides and manages all shared resources.
        /// </summary>
        std::shared_ptr<ContentManager> m_contentManager;

        /// <summary>
        /// Helps to parse serializable objects.
        /// </summary>
        std::shared_ptr<SerializableParser> m_serializableParser;
    };
}

