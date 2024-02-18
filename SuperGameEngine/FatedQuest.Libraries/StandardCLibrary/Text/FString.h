#pragma once

#include <string>
#include <vector>
#include <iostream>

namespace StandardCLibrary
{
    /// <summary>
    /// The string type used by everything.
    /// </summary>
    class FString
    {
    public:
        FString();
        FString(const std::vector<std::string> contents);
        
        // As much as I like the va macro, it does not work well with strings.
        FString(const std::string str1);
        FString(const std::string str1, const std::string str2);
        FString(const std::string str1, const std::string str2, const std::string str3);
        FString(const std::string str1, const std::string str2, const std::string str3, const std::string str4);
        FString(const std::string str1, const std::string str2, const std::string str3, const std::string str4, const std::string str5);
        FString(const std::string str1, const std::string str2, const std::string str3, const std::string str4, const std::string str5,
            const std::string str6);
        FString(const std::string str1, const std::string str2, const std::string str3, const std::string str4, const std::string str5,
            const std::string str6, const std::string str7);
        FString(const std::string str1, const std::string str2, const std::string str3, const std::string str4, const std::string str5,
            const std::string str6, const std::string str7, const std::string str8);
        FString(const std::string str1, const std::string str2, const std::string str3, const std::string str4, const std::string str5,
            const std::string str6, const std::string str7, const std::string str8, const std::string str9);
        FString(const std::string str1, const std::string str2, const std::string str3, const std::string str4, const std::string str5,
            const std::string str6, const std::string str7, const std::string str8, const std::string str9, const std::string str10);

        FString operator+(const std::string& str) const;
        FString operator+(const FString& str) const;
        FString operator+(const int str) const;
        FString operator+(const long int str) const;
        FString operator+(const unsigned long int str) const;
        FString operator+(const double str) const;
        FString operator+(const float str) const;

        FString& operator+=(const std::string& str);
        FString& operator+=(const FString& str);
        FString& operator+=(const int str);
        FString& operator+=(const long int str);
        FString& operator+=(const unsigned long int str);
        FString& operator+=(const double str);
        FString& operator+=(const float str);

        bool operator==(const std::string& other) const;
        bool operator==(const FString& other) const;

        friend std::ostream& operator<<(std::ostream& os, const FString& obj);

        const std::string AsStdString() const;
        const char* AsCharArr() const;

        /// <summary>
        /// Reverts this FString to lowercase.
        /// </summary>
        /// <returns>Lowercase version of this FString in lowercase. </returns>
        FString ToLower() const;

        /// <summary>
        /// Converts this FString to Lowercase.
        /// </summary>
        void ConvertToLower();

        /// <summary>
        /// Reverts this FString to uppercase.
        /// </summary>
        /// <returns>uppercase version of this FString in uppercase. </returns>
        FString ToUpper() const;

        /// <summary>
        /// Converts this FString to uppercase.
        /// </summary>
        void ConvertToUpper();

        /// <summary>
        /// Returns true if the string is considered to have no significant value.
        /// </summary>
        /// <returns>True if the string is considered to have no significant value. </returns>
        bool IsEmptyOrWhitespace() const;

        /// <summary>
        /// Splits a string into pieces, by the given delimiter.
        /// </summary>
        /// <param name="toSplit">String to split. </param>
        /// <param name="by">Delimiter to split by. </param>
        /// <returns>A split string. </returns>
        /// <remark>This needed to not be a FList or FCollection due to Object using FString. </remark>
        static std::vector<FString> Split(FString& toSplit, FString by);

        /// <summary>
        /// Splits a string into pieces, by the given delimiter.
        /// </summary>
        /// <param name="toSplit">String to split. </param>
        /// <param name="by">Delimiter to split by. </param>
        /// <returns>A split string. </returns>
        /// <remark>This needed to not be a FList or FCollection due to Object using FString. </remark>
        static std::vector<std::string> Split(std::string& toSplit, std::string by);
    private:

        /// <summary>
        /// Contents of the FString.
        /// </summary>
        std::string m_storage;
    };
}

