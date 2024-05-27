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
    m_intValues = std::map<std::string, IntValue>();
}

StandardBinaryFile::~StandardBinaryFile()
{
}

void StandardBinaryFile::AddInt(std::string key)
{
    IntValue intValue;
    auto result = m_intValues.insert(std::make_pair(key, intValue));
}

void StandardBinaryFile::SetInt(std::string key, int value)
{
    if (m_intValues.find(key) != m_intValues.end())
    {
        m_intValues[key].Value = value;
        m_intValues[key].IsSet = true;
    }
}

int StandardBinaryFile::TryGetInt(std::string key, int defaultValue)
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

const std::string StandardBinaryFile::ExportBinaryData()
{
    std::stringstream stringStream;
    stringStream << m_binaryString->ToBinary("BinaryFile_V1.0.0");

    stringStream << m_binaryInt->ToBinary(m_intValues.size());
    for (const std::pair<std::string, IntValue>& pair : m_intValues)
    {
        stringStream << m_binaryString->ToBinary(pair.first);
        stringStream << m_binaryInt->ToBinary(pair.second.Value);
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

    currentData = ProcessIntKeys(stringStream);
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

std::string StandardBinaryFile::ProcessIntKeys(std::shared_ptr<FStringStream> stringStream)
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
