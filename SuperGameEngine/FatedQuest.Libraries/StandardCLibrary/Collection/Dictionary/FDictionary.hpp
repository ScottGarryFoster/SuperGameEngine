#pragma once
#include <map>

#include "../../Object/Object.h"

namespace StandardCLibrary
{
    /// <summary>
    /// Data stored as a set.
    /// </summary>
    template<typename Key, typename Value>
    class FDictionary : public Object
    {
    public:
        FDictionary(){}

        /// <summary>
        /// Sets value in the dictionary.
        /// Does not fail.
        /// </summary>
        /// <param name="key">Key to use. </param>
        /// <param name="value">Value to use. </param>
        inline void SetValue(const Key& key, Value& value)
        {
            if (KeyExists(key))
            {
                m_map[key] = value;
            }
            else
            {
                m_map.insert(std::make_pair(key, value));
            }
        }

        /// <summary>
        /// Sets value if it is in the dictionary.
        /// </summary>
        /// <param name="key">Key to use. </param>
        /// <param name="value">Value to use. </param>
        /// <returns>True means did set value. </returns>
        inline bool TrySetValue(const Key& key, Value& value)
        {
            bool keyExists = KeyExists(key);
            if (keyExists)
            {
                SetValue(key, value);
            }

            return keyExists;
        }

        /// <summary>
        /// Checks to see if the key exists.
        /// </summary>
        /// <param name="key">Key to use. </param>
        /// <returns>True means key exists. </returns>
        inline bool KeyExists(const Key& key) const
        {
            return m_map.find(key) != m_map.end();
        }

        /// <summary>
        /// Tries to get the value if it exists.
        /// </summary>
        /// <param name="key">Key to use. </param>
        /// <param name="value">Value found. </param>
        /// <returns>True means found value. </returns>
        inline bool TryGetValue(const Key& key, Value& value) const
        {
            bool keyExists = KeyExists(key);
            if (keyExists)
            {
                auto iterator = m_map.find(key);
                value = iterator->second;
            }

            return keyExists;
        }

        /// <summary>
        /// Interator for Map.
        /// </summary>
        auto begin() const
        {
            return m_map.begin();
        }

        /// <summary>
        /// Interator for Map.
        /// </summary>
        auto end() const
        {
            return m_map.end();
        }

    private:

        /// <summary>
        /// Storage of the dictionary.
        /// </summary>
        std::map<Key, Value> m_map;
    };
}