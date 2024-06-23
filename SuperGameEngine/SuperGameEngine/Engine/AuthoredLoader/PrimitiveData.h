#pragma once
#include <string>
#include <memory>
#include <vector>

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
        const std::vector<std::shared_ptr<PrimitiveData>>& GetChildren();

    private:
        /// <summary>
        /// Name of the current piece of data.
        /// </summary>
        std::string m_name;

        /// <summary>
        /// Children for this data.
        /// </summary>
        std::vector<std::shared_ptr<PrimitiveData>> m_children;
    };
}