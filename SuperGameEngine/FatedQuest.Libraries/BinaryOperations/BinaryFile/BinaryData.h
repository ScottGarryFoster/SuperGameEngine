#pragma once
#include <string>

namespace BinaryOperations
{
    /// <summary>
    /// Represents a file which can be read from and saved to a binary file.
    /// </summary>
    class BinaryData
    {
    public:

        /// <summary>
        /// Add an int to the file.
        /// This means this int would be considered as part of the reading
        /// and writing process.
        /// </summary>
        /// <param name="key">What to call this int. </parm>
        /// This must be a unique name for this int.</param>
        virtual void AddInt(std::string key) = 0;

        /// <summary>
        /// Set the value of an int.
        /// </summary>
        /// <param name="key">Unique name for the int. </param>
        /// <param name="value">New value to set. </param>
        virtual void SetInt(std::string key, int value) = 0;

        /// <summary>
        /// Try to get the value of the int.
        /// Returns default if not set.
        /// </summary>
        /// <param name="key">Unique name for the int. </param>
        /// <param name="defaultValue">Default value to use if not set. </param>
        /// <returns>Value of the int or default if not found. </returns>
        virtual int TryGetInt(std::string key, int defaultValue) = 0;

        /// <summary>
        /// Add an string to the file.
        /// This means this int would be considered as part of the reading
        /// and writing process.
        /// </summary>
        /// <param name="key">What to call this string. </parm>
        /// This must be a unique name for this int.</param>
        virtual void AddString(std::string key) = 0;

        /// <summary>
        /// Set the value of an string.
        /// </summary>
        /// <param name="key">Unique name for the string. </param>
        /// <param name="value">New value to set. </param>
        virtual void SetString(std::string key, std::string value) = 0;

        /// <summary>
        /// Try to get the value of the string.
        /// Returns default if not set.
        /// </summary>
        /// <param name="key">Unique name for the string. </param>
        /// <param name="defaultValue">Default value to use if not set. </param>
        /// <returns>Value of the string or default if not found. </returns>
        virtual std::string TryGetString(std::string key, std::string defaultValue) = 0;

        /// <summary>
        /// Export the data in a binary form.
        /// </summary>
        /// <returns>The data in a binary form. </returns>
        virtual const std::string ExportBinaryData() = 0;

        /// <summary>
        /// Import data in a binary form.
        /// Will wipe any existing data.
        /// </summary>
        /// <param name="data">Data in a binary form.</param>
        virtual void ImportBinaryData(const std::string& data) = 0;
    };
}