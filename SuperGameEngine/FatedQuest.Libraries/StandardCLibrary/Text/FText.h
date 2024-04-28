#pragma once

#include <string>
#include <vector>
#include <iostream>

namespace StandardCLibrary
{
    /// <summary>
    /// Used to store text.
    /// </summary>
    class FText
    {
    public:
        FText();
        FText(const std::vector<std::string> contents);

        // As much as I like the va macro, it does not work well with strings.
        FText(const std::string str1);
        FText(const std::string str1, const std::string str2);
        FText(const std::string str1, const std::string str2, const std::string str3);
        FText(const std::string str1, const std::string str2, const std::string str3, const std::string str4);
        FText(const std::string str1, const std::string str2, const std::string str3, const std::string str4, const std::string str5);
        FText(const std::string str1, const std::string str2, const std::string str3, const std::string str4, const std::string str5,
            const std::string str6);
        FText(const std::string str1, const std::string str2, const std::string str3, const std::string str4, const std::string str5,
            const std::string str6, const std::string str7);
        FText(const std::string str1, const std::string str2, const std::string str3, const std::string str4, const std::string str5,
            const std::string str6, const std::string str7, const std::string str8);
        FText(const std::string str1, const std::string str2, const std::string str3, const std::string str4, const std::string str5,
            const std::string str6, const std::string str7, const std::string str8, const std::string str9);
        FText(const std::string str1, const std::string str2, const std::string str3, const std::string str4, const std::string str5,
            const std::string str6, const std::string str7, const std::string str8, const std::string str9, const std::string str10);

        FText(const std::vector<std::wstring> contents);

        // As much as I like the va macro, it does not work well with strings.
        FText(const std::wstring str1);
        FText(const std::wstring str1, const std::wstring str2);
        FText(const std::wstring str1, const std::wstring str2, const std::wstring str3);
        FText(const std::wstring str1, const std::wstring str2, const std::wstring str3, const std::wstring str4);
        FText(const std::wstring str1, const std::wstring str2, const std::wstring str3, const std::wstring str4, const std::wstring str5);
        FText(const std::wstring str1, const std::wstring str2, const std::wstring str3, const std::wstring str4, const std::wstring str5,
            const std::wstring str6);
        FText(const std::wstring str1, const std::wstring str2, const std::wstring str3, const std::wstring str4, const std::wstring str5,
            const std::wstring str6, const std::wstring str7);
        FText(const std::wstring str1, const std::wstring str2, const std::wstring str3, const std::wstring str4, const std::wstring str5,
            const std::wstring str6, const std::wstring str7, const std::wstring str8);
        FText(const std::wstring str1, const std::wstring str2, const std::wstring str3, const std::wstring str4, const std::wstring str5,
            const std::wstring str6, const std::wstring str7, const std::wstring str8, const std::wstring str9);
        FText(const std::wstring str1, const std::wstring str2, const std::wstring str3, const std::wstring str4, const std::wstring str5,
            const std::wstring str6, const std::wstring str7, const std::wstring str8, const std::wstring str9, const std::wstring str10);


        FText operator+(const std::wstring& str) const;
        FText operator+(const std::string& str) const;
        FText operator+(const FText& str) const;
        FText operator+(const int str) const;
        FText operator+(const long int str) const;
        FText operator+(const unsigned long int str) const;
        FText operator+(const double str) const;
        FText operator+(const float str) const;

        FText& operator+=(const std::wstring& str);
        FText& operator+=(const std::string& str);
        FText& operator+=(const FText& str);
        FText& operator+=(const int str);
        FText& operator+=(const long int str);
        FText& operator+=(const unsigned long int str);
        FText& operator+=(const double str);
        FText& operator+=(const float str);

        bool operator==(const std::wstring& other) const;
        bool operator==(const std::string& other) const;
        bool operator==(const FText& other) const;

        inline friend std::ostream& operator<<(std::ostream& os, const FText& obj)
        {
            return os << obj.AsStdString();
        }

        /// <summary>
        /// Returns a String representing the text.
        /// </summary>
        /// <returns>String for the text. </returns>
        /// <remark> 
        /// This is a lossy convertion! String is narrower than Wide String.
        /// Try to remain in the Wide String or FText realm
        /// </remark>
        const std::string AsStdString() const;
        const wchar_t* AsCharArr() const;

        /// <summary>
        /// Returns a Wide String representing the text.
        /// </summary>
        /// <returns>String for the text. </returns>
        const std::wstring AsStdWstring() const;

        /// <summary>
        /// Reverts this FString to lowercase.
        /// </summary>
        /// <returns>Lowercase version of this FString in lowercase. </returns>
        FText ToLower() const;

        /// <summary>
        /// Converts this FString to Lowercase.
        /// </summary>
        void ConvertToLower();

        /// <summary>
        /// Reverts this FString to uppercase.
        /// </summary>
        /// <returns>uppercase version of this FString in uppercase. </returns>
        FText ToUpper() const;

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
        static std::vector<FText> Split(FText& toSplit, FText by);

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
        std::wstring m_storage;

        /// <summary>
        /// Converts String to Wide String.
        /// </summary>
        /// <param name="value">String value. </param>
        /// <returns>Converted Wide Value. </returns>
        /// <remark>
        /// This is safe as string has less bytes.
        /// </remark>
        std::wstring ConvertToWide(const std::string value) const;

        /// <summary>
        /// Converts Wide String to String.
        /// </summary>
        /// <param name="value">Wide String.</param>
        /// <returns>Converted String. </returns>
        /// <remark>
        /// This is a lossy convertion as String is narrower.
        /// </remark>
        std::string ConvertFromWide(const std::wstring value) const;
    };
}
