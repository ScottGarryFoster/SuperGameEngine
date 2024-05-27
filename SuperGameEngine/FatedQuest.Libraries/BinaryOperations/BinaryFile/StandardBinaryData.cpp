#include "StandardBinaryData.h"
#include "../../StandardCLibrary/LibraryIncludes.h"

#include <string>
#include <map>
#include <iostream>
#include <sstream>

using namespace BinaryOperations;

StandardBinaryData::StandardBinaryData()
{
    m_binaryString = std::make_shared<BinaryString>();
    m_intValues = std::map<std::string, IntValue>();
    m_stringValues = std::map<std::string, StringValue>();
}

StandardBinaryData::~StandardBinaryData()
{
}

void StandardBinaryData::AddInt(std::string key)
{
    IntValue intValue;
    auto result = m_intValues.insert(std::make_pair(key, intValue));
}

void StandardBinaryData::SetInt(std::string key, int value)
{
    if (m_intValues.find(key) != m_intValues.end())
    {
        m_intValues[key].Value = value;
        m_intValues[key].IsSet = true;
    }
}

int StandardBinaryData::TryGetInt(std::string key, int defaultValue)
{
    int returnValue = defaultValue;
    if (m_intValues.find(key) != m_intValues.end())
    {
        if (m_intValues[key].IsSet)
        {
            returnValue = m_intValues[key].Value;
        }
    }

    return returnValue;
}

void StandardBinaryData::AddString(std::string key)
{
    StringValue stringValue;
    auto result = m_stringValues.insert(std::make_pair(key, stringValue));
}

void StandardBinaryData::SetString(std::string key, std::string value)
{
    if (m_stringValues.find(key) != m_stringValues.end())
    {
        m_stringValues[key].Value = value;
        m_stringValues[key].IsSet = true;
    }
}

std::string StandardBinaryData::TryGetString(std::string key, std::string defaultValue)
{
    std::string returnValue = defaultValue;
    if (m_stringValues.find(key) != m_stringValues.end())
    {
        if (m_stringValues[key].IsSet)
        {
            returnValue = m_stringValues[key].Value;
        }
    }

    return returnValue;
}

const std::string StandardBinaryData::ExportBinaryData()
{
    std::stringstream stringStream;
    stringStream << m_binaryString->ToBinary("BinaryFile_V1.0.0");

    stringStream << m_binaryInt->ToBinary(m_intValues.size());
    for (const std::pair<std::string, IntValue>& pair : m_intValues)
    {
        stringStream << m_binaryString->ToBinary(pair.first);
        stringStream << m_binaryInt->ToBinary(pair.second.Value);
    }

    stringStream << m_binaryInt->ToBinary(m_stringValues.size());
    for (const std::pair<std::string, StringValue>& pair : m_stringValues)
    {
        stringStream << m_binaryString->ToBinary(pair.first);
        stringStream << m_binaryString->ToBinary(pair.second.Value);
    }

    return stringStream.str();
}

void StandardBinaryData::ImportBinaryData(const std::string& data)
{
    std::shared_ptr<std::istringstream> iss = std::make_shared<std::istringstream>(data, std::ios::binary);
    std::shared_ptr<FStringStream> stringStream = std::make_shared<FStringStream>(iss);
    std::string currentData = data;

    std::string version = m_binaryString->ToPlainText(currentData);
    currentData = MoveStreamPointer(stringStream, version);

    currentData = ProcessIntKeys(stringStream);
    currentData = ProcessStringKeys(stringStream);
}

std::string BinaryOperations::StandardBinaryData::MoveStreamPointer(std::shared_ptr<FStringStream> stringStream, std::string value)
{
    size_t sizeInBinary = m_binaryString->SizeOfDataInBinary(value);
    stringStream->MoveSeekBy(sizeInBinary);
    return stringStream->GetSeekedString();
}

std::string BinaryOperations::StandardBinaryData::MoveStreamPointer(std::shared_ptr<FStringStream> stringStream, int value)
{
    size_t sizeInBinary = m_binaryInt->SizeOfDataInBinary(value);
    stringStream->MoveSeekBy(sizeInBinary);
    return stringStream->GetSeekedString();
}

bool BinaryOperations::StandardBinaryData::TryParseInt(std::string& data, int& output)
{
    output = -1;
    try
    {
        output = std::stoi(data);
        return true;
    }
    catch (const std::exception e)
    {

    }

    return false;
}

std::string StandardBinaryData::ProcessIntKeys(std::shared_ptr<FStringStream> stringStream)
{
    std::string currentData = stringStream->GetSeekedString();

    for (const std::pair<std::string, IntValue>& pair : m_intValues)
    {
        m_intValues[pair.first].IsSet = false;
    }

    int numberOfKeysText = m_binaryInt->ToInt(currentData);
    currentData = MoveStreamPointer(stringStream, numberOfKeysText);
    for (size_t i = 0; i < numberOfKeysText; ++i)
    {
        std::string keyName = m_binaryString->ToPlainText(currentData);
        currentData = MoveStreamPointer(stringStream, keyName);

        int intValue = m_binaryInt->ToInt(currentData);
        currentData = MoveStreamPointer(stringStream, intValue);

        if (m_intValues.find(keyName) != m_intValues.end())
        {
            m_intValues[keyName].Value = intValue;
            m_intValues[keyName].IsSet = true;
        }
    }

    return currentData;
}

std::string StandardBinaryData::ProcessStringKeys(std::shared_ptr<FStringStream> stringStream)
{
    std::string currentData = stringStream->GetSeekedString();

    for (const std::pair<std::string, StringValue>& pair : m_stringValues)
    {
        m_stringValues[pair.first].IsSet = false;
    }

    int numberOfKeysText = m_binaryInt->ToInt(currentData);
    currentData = MoveStreamPointer(stringStream, numberOfKeysText);
    for (size_t i = 0; i < numberOfKeysText; ++i)
    {
        std::string keyName = m_binaryString->ToPlainText(currentData);
        currentData = MoveStreamPointer(stringStream, keyName);

        std::string stringValue = m_binaryString->ToPlainText(currentData);
        currentData = MoveStreamPointer(stringStream, stringValue);

        if (m_stringValues.find(keyName) != m_stringValues.end())
        {
            m_stringValues[keyName].Value = stringValue;
            m_stringValues[keyName].IsSet = true;
        }
    }

    return currentData;
}
