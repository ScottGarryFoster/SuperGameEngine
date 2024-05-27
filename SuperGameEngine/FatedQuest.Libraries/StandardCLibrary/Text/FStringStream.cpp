#include "FStringStream.h"

using namespace StandardCLibrary;

FStringStream::FStringStream(std::shared_ptr<std::stringstream> stringStream)
{
    m_stringStream = stringStream;
    if (!m_stringStream)
    {
        m_stringStream = std::make_shared<std::stringstream>();
    }

    m_customSeekLocation = 0;
}

FStringStream::FStringStream(std::shared_ptr<std::istringstream> stringStream)
{
    m_binaryInStringStream = stringStream;
    if (!m_binaryInStringStream)
    {
        m_binaryInStringStream = std::make_shared<std::istringstream>();
    }

    m_customSeekLocation = 0;
}

FStringStream::~FStringStream()
{
}

void FStringStream::Read(char* input, std::streamsize count)
{
    if (m_stringStream)
    {
        m_stringStream->read(input, count);
    }
    else
    {
        m_binaryInStringStream->read(input, count);
    }
}

void FStringStream::SeekTo(size_t location)
{
    m_customSeekLocation = location;
}

void FStringStream::MoveSeekBy(size_t location)
{
    m_customSeekLocation += location;
}

std::string FStringStream::GetAllString()
{
    if (m_stringStream)
    {
        return m_stringStream->str();
    }
    else
    {
        return m_binaryInStringStream->str();
    }
}

std::string StandardCLibrary::FStringStream::GetSeekedString()
{
    std::string entireString = GetAllString();
    size_t newStringLength = entireString.size() - m_customSeekLocation;

    std::string returnString;
    returnString.resize(newStringLength);

    if (m_stringStream)
    {
        m_stringStream->seekg(m_customSeekLocation, std::ios::beg);
        m_stringStream->read(&returnString[0], newStringLength);
    }
    else
    {
        m_binaryInStringStream->seekg(m_customSeekLocation, std::ios::beg);
        m_binaryInStringStream->read(&returnString[0], newStringLength);
    }

    return returnString;
}
