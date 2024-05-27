#pragma once
#include <string>
#include <functional>
#include <memory>
#include <map>

namespace SuperGameEngine
{
    class GameComponent;

    /// <summary>
    /// Provides the ability to create components within the engine.
    /// </summary>
    static class ComponentFactory
    {
    public:
        /// <summary>
        /// Register a new component to create.
        /// </summary>
        /// <param name="type">Type of the component. </param>
        /// <param name="constructor">Construction method. Must have no parameters. </param>
        static void RegisterComponent(const std::string& type, std::function<std::shared_ptr<GameComponent>()> constructor);

        /// <summary>
        /// Create the given component type. 
        /// </summary>
        /// <param name="type">Type name for the component. </param>
        /// <returns>Type of the component. </returns>
        static std::shared_ptr<GameComponent> CreateComponent(const std::string& type);
    private:

        /// <summary>
        /// Get the map containing the component types (names and constructors)
        /// </summary>
        /// <returns>All registered components. </returns>
        static std::map<std::string, std::function<std::shared_ptr<GameComponent>()>>& GetMap()
        {
            // This is intialised here.
            static std::map<std::string, std::function<std::shared_ptr<GameComponent>()>> map;
            return map;
        }
    };
}

// All components should use:     REGISTER_COMPONENT(TYPENAME)
// on the component header to register themselves to this factory.
// Only SGE components can be created natively without a name.

#define REGISTER_COMPONENT(TYPE) \
    namespace { \
        auto reg_##TYPE = []() { \
            ComponentFactory::RegisterComponent(#TYPE, []() { return std::make_shared<TYPE>(); }); \
            return 0; \
        }(); \
    }
