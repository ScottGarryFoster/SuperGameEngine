#pragma once
#include <string>
#include <vector>

namespace StandardCLibrary
{
    /// <summary>
    /// The string type used by everything.
    /// </summary>
    class FString
    {
    public:
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


        const std::string AsStdString();
        const char* AsCharArr();

    private:

        /// <summary>
        /// Contents of the FString.
        /// </summary>
        std::string m_storage;
    };
}

