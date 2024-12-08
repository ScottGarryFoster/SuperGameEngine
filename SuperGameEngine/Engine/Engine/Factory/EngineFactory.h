#pragma once
#include <string>
#include <functional>
#include <memory>
#include <map>

namespace SuperGameEngine
{
    class Engine;

    /// <summary>
    /// Provides the ability to create components within the engine.
    /// </summary>
    static class EngineFactory
    {
    public:
        /// <summary>
        /// Register a new component to create.
        /// </summary>
        /// <param name="type">Type of the component. </param>
        /// <param name="constructor">Construction method. Must have no parameters. </param>
        static void RegisterEngine(const std::string& type, std::function<std::shared_ptr<Engine>()> constructor);

        /// <summary>
        /// Create the given component type. 
        /// </summary>
        /// <param name="type">Type name for the component. </param>
        /// <returns>Type of the component. </returns>
        static std::shared_ptr<Engine> CreateEngine(const std::string& type);
    private:

        /// <summary>
        /// Get the map containing the component types (names and constructors)
        /// </summary>
        /// <returns>All registered components. </returns>
        static std::map<std::string, std::function<std::shared_ptr<Engine>()>>& GetMap()
        {
            // This is initialized here.
            static std::map<std::string, std::function<std::shared_ptr<Engine>()>> map;
            return map;
        }
    };
}

// All components should use:     REGISTER_COMPONENT(TYPENAME)
// on the component header to register themselves to this factory.
// Only SGE components can be created natively without a name.

#define REGISTER_ENGINE(TYPE, CLASS) \
    static bool CLASS##_registered = []() { \
        EngineFactory::RegisterEngine(TYPE, []() { return std::make_shared<CLASS>(); }); \
        return true; \
    }()