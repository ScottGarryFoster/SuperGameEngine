#pragma once
#include <functional>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <typeindex>

namespace FatedQuestLibraries
{
    /// <summary>
    /// Stores all class types by name.
    /// Used for casting when loading from file.
    /// </summary>
    class ClassTypes
    {
    public:
        static ClassTypes& GetInstance()
        {
            static ClassTypes instance;
            return instance;
        }

        /// <summary>
        /// Registers class for recreation.
        /// </summary>
        /// <typeparam name="T">Type to register.</typeparam>
        /// <param name="name">Name to store alongside the type.</param>
        template <typename T>
        void RegisterClass(const std::string& name)
        {
            m_registry[name] = []() { return std::make_shared<T>(); };
            m_typeRegistry.emplace(name,std::type_index(typeid(T)));
        }

        /// <summary>
        /// Attempt to create the class.
        /// </summary>
        /// <param name="name">Name to attempt to find. </param>
        /// <returns>Returns a new version of the class or nullopt. </returns>
        std::optional<std::shared_ptr<void>> Create(const std::string& name)
        {
            if (!m_registry.contains(name))
            {
                return std::nullopt;
            }

            return m_registry[name]();
        }

        /// <summary>
        /// Check to see if the given type is registered.
        /// </summary>
        /// <param name="name">Name to find. </param>
        /// <returns>True means is registered. Does not guarantee it can be created. </returns>
        bool IsRegistered(const std::string& name) const
        {
            return m_registry.contains(name);
        }

        /// <summary>
        /// Get the actual type from name for comparisons.
        /// </summary>
        /// <param name="name">Name to find. </param>
        /// <returns>The type if registered or nullopt. </returns>
        std::optional<std::type_index> GetType(const std::string& name) const
        {
            if (!m_typeRegistry.contains(name))
            {
                return std::nullopt;
            }

            return m_typeRegistry.at(name);
        }

    private:
        /// <summary>
        /// All constructors by type name.
        /// </summary>
        std::unordered_map<std::string, std::function<std::shared_ptr<void>()>> m_registry;

        /// <summary>
        /// All types by type name.
        /// </summary>
        std::unordered_map<std::string, std::type_index> m_typeRegistry;
    };

#define REGISTER_CLASS(CLASS_NAME)                                                  \
    namespace {                                                                     \
        struct CLASS_NAME##Registrar  {                                             \
            CLASS_NAME##Registrar () {                                              \
                ClassTypes::GetInstance().RegisterClass<CLASS_NAME>(#CLASS_NAME);   \
            }                                                                       \
        };                                                                          \
        static CLASS_NAME##Registrar global_##CLASS_NAME##_registrar;               \
    }
}