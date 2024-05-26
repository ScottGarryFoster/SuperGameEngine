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
    std::stringstream ss;
    ss << m_binaryString->ToBinary("BinaryFile_V1.0.0");

    return ss.str();
}

void StandardBinaryFile::ImportBinaryData(const std::string& data)
{

}
