#pragma once
#include <string>
#include <vector>
#include <memory>
#include <map>

namespace SuperGameEngine
{
    class ParsedData
    {
    public:
        ParsedData();
        ParsedData(std::string& name, std::vector<std::shared_ptr<ParsedData>> children);

        /// <summary>
        /// Name of the current piece of data.
        /// </summary>
        /// <returns>Name of the current piece of data.</returns>
        const std::string GetName() const;

        /// <summary>
        /// Children Data for this piece of data.
        /// </summary>
        /// <returns>All children. </returns>
        const std::vector<std::shared_ptr<const ParsedData>>& GetChildren() const;

        /// <summary>
        /// Tries to get the Property if found within the data.
        /// </summary>
        /// <param name="propertyName">Name of the Property. Case sensitive.</param>
        /// <param name="propertyValue">Value of the property if found. </param>
        /// <returns>True means found. </returns>
        const bool TryGetProperty(const std::string& propertyName, std::string& propertyValue) const;

        /// <summary>
        /// Sets a property with the given value.
        /// </summary>
        /// <param name="propertyName">Name of the property. Case sensitive. </param>
        /// <param name="propertyValue">Value of the property if found. </param>
        void SetProperty(const std::string& propertyName, const std::string& propertyValue);

        /// <summary>
        /// Tries to get the Property if found within the data.
        /// </summary>
        /// <param name="propertyName">Name of the Property. Case sensitive.</param>
        /// <param name="propertyValue">Value of the property if found. </param>
        /// <returns>True means found. </returns>
        const bool TryGetProperty(const std::string& propertyName, int& propertyValue) const;

        /// <summary>
        /// Sets a property with the given value.
        /// </summary>
        /// <param name="propertyName">Name of the property. Case sensitive. </param>
        /// <param name="propertyValue">Value of the property if found. </param>
        void SetProperty(const std::string& propertyName, const int& propertyValue);

        /// <summary>
        /// Tries to get the Property if found within the data.
        /// </summary>
        /// <param name="propertyName">Name of the Property. Case sensitive.</param>
        /// <param name="propertyValue">Value of the property if found. </param>
        /// <returns>True means found. </returns>
        const bool TryGetProperty(const std::string& propertyName, float& propertyValue) const;

        /// <summary>
        /// Sets a property with the given value.
        /// </summary>
        /// <param name="propertyName">Name of the property. Case sensitive. </param>
        /// <param name="propertyValue">Value of the property if found. </param>
        void SetProperty(const std::string& propertyName, const float& propertyValue);

        /// <summary>
        /// Tries to get the Property if found within the data.
        /// </summary>
        /// <param name="propertyName">Name of the Property. Case sensitive.</param>
        /// <param name="propertyValue">Value of the property if found. </param>
        /// <returns>True means found. </returns>
        const bool TryGetBoolProperty(const std::string& propertyName, bool& propertyValue) const;

        /// <summary>
        /// Sets a property with the given value.
        /// </summary>
        /// <param name="propertyName">Name of the property. Case sensitive. </param>
        /// <param name="propertyValue">Value of the property if found. </param>
        void SetBoolProperty(const std::string& propertyName, const bool& propertyValue);
    private:
        /// <summary>
        /// Name of the current piece of data.
        /// </summary>
        std::string m_name;

        /// <summary>
        /// Children for this data.
        /// </summary>
        std::vector<std::shared_ptr<const ParsedData>> m_children;

        /// <summary>
        /// All proeprties for this data.
        /// </summary>
        std::map<std::string, std::string> m_properties;

        /// <summary>
        /// All int proeprties for this data.
        /// </summary>
        std::map<std::string, int> m_intProperties;

        /// <summary>
        /// All float proeprties for this data.
        /// </summary>
        std::map<std::string, float> m_floatProperties;

        /// <summary>
        /// All bool proeprties for this data.
        /// </summary>
        std::map<std::string, bool> m_boolProperties;
    };

}