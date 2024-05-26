#include "BinaryString.h"
#include <iostream>
#include <sstream>

using namespace BinaryOperations;

std::string BinaryString::ToBinary(const std::string& plainText)
{
    std::ostringstream oss(std::ios::binary);

    size_t stringLength = plainText.size();
    oss.write(reinterpret_cast<const char*>(&stringLength), sizeof(stringLength));
    oss.write(plainText.c_str(), stringLength);

    return oss.str();
}

std::string BinaryString::ToPlainText(const std::string& binary)
{
    std::istringstream iss(binary, std::ios::binary);

    size_t stringLength;
    iss.read(reinterpret_cast<char*>(&stringLength), sizeof(stringLength));

    std::string returnString = "";
    returnString.resize(stringLength);
    iss.read(&returnString[0], stringLength);

    return returnString;
}
