#pragma once
#include <string>
#include <memory>
#include <vector>
#include <map>

namespace SuperGameEngine
{
    /// <summary>
    /// Basic representation of data.
    /// </summary>
    class PrimitiveData
    {
    public:
        PrimitiveData();
        PrimitiveData(std::string& name, std::vector<std::shared_ptr<PrimitiveData>> children);

        /// <summary>
        /// Name of the current piece of data.
        /// </summary>
        /// <returns>Name of the current piece of data.</returns>
        std::string GetName() const;

        /// <summary>
        /// Children Data for this piece of data.
        /// </summary>
        /// <returns>All children. </returns>
        const std::vector<std::shared_ptr<const PrimitiveData>>& GetChildren() const;

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
    private:
        /// <summary>
        /// Name of the current piece of data.
        /// </summary>
        std::string m_name;

        /// <summary>
        /// Children for this data.
        /// </summary>
        std::vector<std::shared_ptr<const PrimitiveData>> m_children;

        /// <summary>
        /// All proeprties for this data.
        /// </summary>
        std::map<std::string, std::string> m_properties;
    };
}