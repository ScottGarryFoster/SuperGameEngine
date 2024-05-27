#include "BinaryInt.h"
#include <iostream>
#include <sstream>

using namespace BinaryOperations;

std::string BinaryInt::ToBinary(const int& data)
{
    std::ostringstream oss(std::ios::binary);
    oss.write(reinterpret_cast<const char*>(&data), sizeof(data));
    return oss.str();
}

int BinaryInt::ToInt(const std::string& binary)
{
    std::istringstream iss(binary, std::ios::binary);

    int intLength;
    int returnNumber = 0;
    iss.read(reinterpret_cast<char*>(&returnNumber), sizeof(returnNumber));

    return returnNumber;
}

std::streampos BinaryOperations::BinaryInt::SizeOfDataInBinary(const int& data)
{
    return sizeof(int);
}