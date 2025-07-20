#include "StackTraceLine.h"

using namespace FatedQuestLibraries;

StackTraceLine::StackTraceLine(
    const std::string& name, 
    const std::string& address)
{
    m_name = name;
    m_address = address;
    m_filename = {};
    m_line = -1;
}

StackTraceLine::StackTraceLine(
    const std::string& name, 
    const std::string& address, 
    const std::string& filename,
    int lineNumber)
{
    m_name = name;
    m_address = address;
    m_filename = filename;
    m_line = lineNumber;
}

std::string StackTraceLine::GetName() const
{
    return m_name;
}

std::string StackTraceLine::GetAddress() const
{
    return m_address;
}

std::string StackTraceLine::GetFilename() const
{
    return m_filename;
}

int StackTraceLine::GetLineNumber() const
{
    return m_line;
}
