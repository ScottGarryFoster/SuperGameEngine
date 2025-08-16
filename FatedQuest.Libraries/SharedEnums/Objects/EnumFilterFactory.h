#pragma once
#include <map>
#include <string>
#include <unordered_set>
#include <vector>

namespace FatedQuestLibraries
{
    /// <summary>
    /// Provides a way to list all the items in a given enum.
    /// </summary>
    class EnumFilterFactory
    {
    public:
        /// <summary>
        /// Register the values in an enum.
        /// </summary>
        /// <param name="type">Type name of the enum. </param>
        /// <param name="values">Values to register. </param>
        static void RegisterValues(const std::string& type, const std::vector<std::string>& values);

        /// <summary>
        /// Get the values in the enum.
        /// </summary>
        /// <param name="type">Type name of the enum. Note there is no case safety here. </param>
        /// <returns>The values of the enum.</returns>
        static std::vector<std::string> GetValues(const std::string& type);

        /// <summary>
        /// Get the values of the enum as a set
        /// (so that it is more efficient to validate user input) 
        /// </summary>
        /// <param name="type">Type name of the enum. Note there is no case safety here. </param>
        /// <returns>The values of the enum. </returns>
        static std::unordered_set<std::string> GetValuesAsSet(const std::string& type);
    private:

        /// <summary>
        /// Get the map containing the values of the enum.
        /// </summary>
        /// <returns>All values of the enums. </returns>
        static std::map<std::string, std::vector<std::string>>& GetMap()
        {
            // This is initialized here.
            static std::map<std::string, std::vector<std::string>> map;
            return map;
        }

        /// <summary>
        /// Get the map containing the set values of the enum (values as a set)
        /// </summary>
        /// <returns>All values of the enum. </returns>
        static std::map<std::string, std::unordered_set<std::string>>& GetSetMap()
        {
            // This is initialized here.
            static std::map<std::string, std::unordered_set<std::string>> setMap;
            return setMap;
        }
    };
}

// To use call: REGISTER_TOOLS_ENUM_FILTER(Type name, Vector of strings)
// This is safe to use in enum classes.
namespace FatedQuestLibraries {
#define REGISTER_TOOLS_ENUM_FILTER(TYPE, VALUES) \
    static bool CLASS##_registered = []() { \
        EnumFilterFactory::RegisterValues(TYPE, VALUES); \
        return true; \
    }()
}