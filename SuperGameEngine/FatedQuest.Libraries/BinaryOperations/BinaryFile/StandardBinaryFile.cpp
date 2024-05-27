#include "StandardBinaryFile.h"
#include "../../StandardCLibrary/LibraryIncludes.h"

#include <string>
#include <map>
#include <iostream>
#include <sstream>

using namespace BinaryOperations;

StandardBinaryFile::StandardBinaryFile()
{
    m_binaryString = std::make_shared<BinaryString>();
    m_intValues = std::map<std::string, int>();
}

StandardBinaryFile::~StandardBinaryFile()
{
}

void StandardBinaryFile::AddInt(std::string key)
{
    auto result = m_intValues.insert(std::make_pair(key, 0));
}

void StandardBinaryFile::SetInt(std::string key, int value)
{
    if (m_intValues.find(key) != m_intValues.end())
    {
        m_intValues[key] = value;
    }
}

int StandardBinaryFile::TryGetInt(std::string key, int defaultValue)
{
    int returnValue = 0;
    if (m_intValues.find(key) == m_intValues.end())
    {
        returnValue = defaultValue;
    }
    else
    {
        returnValue = m_intValues[key];
    }

    return returnValue;
}

const std::string StandardBinaryFile::ExportBinaryData()
{
    std::stringstream stringStream;
    stringStream << m_binaryString->ToBinary("BinaryFile_V1.0.0");

    size_t t = m_intValues.size();
    stringStream << m_binaryString->ToBinary(std::to_string(t));
    for (const std::pair<std::string, int>& pair : m_intValues)
    {
        stringStream << m_binaryString->ToBinary(pair.first);
        stringStream << m_binaryString->
            ToBinary(std::to_string(pair.second));
    }

    stringStream.seekg(0, std::ios_base::beg);

    std::string remainingString;
    std::getline(stringStream, remainingString);

    return stringStream.str();
}

void StandardBinaryFile::ImportBinaryData(const std::string& data)
{
    std::shared_ptr<std::istringstream> iss = std::make_shared<std::istringstream>(data, std::ios::binary);
    std::shared_ptr<FStringStream> stringStream = std::make_shared<FStringStream>(iss);
    std::string currentData = data;

    std::string version = m_binaryString->ToPlainText(currentData);
    currentData = MoveStreamPointer(stringStream, version);

    std::string numberOfKeysText = m_binaryString->ToPlainText(currentData);
    int numberOfIntKeys = -1;
    if (!TryParseInt(numberOfKeysText, numberOfIntKeys))
    {
        return;
    }
    currentData = MoveStreamPointer(stringStream, numberOfKeysText);
    

    for (size_t i = 0; i < numberOfIntKeys; ++i)
    {
        std::string keyName = m_binaryString->ToPlainText(currentData);
        currentData = MoveStreamPointer(stringStream, keyName);

        std::string intValueText = m_binaryString->ToPlainText(currentData);
        int intValue = -1;
        currentData = MoveStreamPointer(stringStream, intValueText);

        if (!TryParseInt(intValueText, intValue))
        {
            continue;
        }

        if (m_intValues.find(keyName) != m_intValues.end())
        {
            m_intValues[keyName] = intValue;
        }
    }
}

std::string BinaryOperations::StandardBinaryFile::MoveStreamPointer(std::shared_ptr<FStringStream> stringStream, std::string value)
{
    size_t sizeInBinary = m_binaryString->SizeOfDataInBinary(value);
    stringStream->MoveSeekBy(sizeInBinary);
    return stringStream->GetSeekedString();
}

std::string BinaryOperations::StandardBinaryFile::MoveStreamPointer(std::shared_ptr<FStringStream> stringStream, int value)
{
    size_t sizeInBinary = m_binaryInt->SizeOfDataInBinary(value);
    stringStream->MoveSeekBy(sizeInBinary);
    return stringStream->GetSeekedString();
}

bool BinaryOperations::StandardBinaryFile::TryParseInt(std::string& data, int& output)
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