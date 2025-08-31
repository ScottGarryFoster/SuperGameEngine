#include "FloatingPointHelpers.h"
#include <cstdlib>
#include <stdexcept>
#include <complex>

using namespace FatedQuestLibraries;

bool FloatingPointHelpers::AreEqual(float left, float right)
{
    // The places to be accurate within.
    float epsilon = 0.00001f;

    return std::abs(left - right) < epsilon;
}

bool FloatingPointHelpers::AreEqual(double left, double right)
{
    // The places to be accurate within.
    double epsilon = 0.00001;

    return std::abs(left - right) < epsilon;
}

bool FloatingPointHelpers::AreEqual(float left, double right)
{
    // The places to be accurate within.
    float epsilon = 0.00001f;

    return std::abs(left - right) < epsilon;
}

bool FloatingPointHelpers::AreEqual(double left, float right)
{
    // The places to be accurate within.
    float epsilon = 0.00001f;

    return std::abs(left - right) < epsilon;
}

bool FloatingPointHelpers::AreEqual(float left, int right)
{
    // The places to be accurate within.
    float epsilon = 0.00001f;

    float rightFloat = static_cast<float>(right);

    return std::abs(left - rightFloat) < epsilon;
}

bool FloatingPointHelpers::AreEqual(int left, float right)
{
    // The places to be accurate within.
    float epsilon = 0.00001f;

    float leftFloat = static_cast<float>(left);

    return std::abs(leftFloat - right) < epsilon;
}

bool FloatingPointHelpers::AreEqual(double left, int right)
{
    // The places to be accurate within.
    float epsilon = 0.00001f;

    return std::abs(left - right) < epsilon;
}

bool FloatingPointHelpers::AreEqual(int left, double right)
{
    // The places to be accurate within.
    float epsilon = 0.00001f;

    return std::abs(left - right) < epsilon;
}

float FloatingPointHelpers::Divide(float dividend, float divisor)
{
    if (divisor == 0.0)
    {
        throw std::runtime_error("Division by zero!");
    }

    return std::exp(std::log(std::abs(dividend)) - std::log(std::abs(divisor))) *
        ((dividend < 0) ^ (divisor < 0) ? -1 : 1);
}

bool FloatingPointHelpers::TryParse(const std::string& parsing, float& outValue)
{
    outValue = -1;
    try
    {
        outValue = std::stof(parsing);
        return true;
    }
    catch (const std::exception e)
    {

    }

    return false;
}

bool FloatingPointHelpers::TryParse(const std::string& parsing, double& outValue)
{
    outValue = -1;
    try
    {
        outValue = std::stod(parsing);
        return true;
    }
    catch (const std::exception e)
    {

    }

    return false;
}

std::string FloatingPointHelpers::RemoveUnneededZeros(float value)
{
    return RemoveUnneededZeros(std::to_string(value));
}

std::string FloatingPointHelpers::RemoveUnneededZeros(double value)
{
    return RemoveUnneededZeros(std::to_string(value));
}

std::string FloatingPointHelpers::RemoveUnneededZeros(const std::string& value)
{
    size_t decimalPosition = value.find('.');
    if (decimalPosition == std::string::npos)
    {
        return value;
    }

    size_t end = value.size() - 1;
    while (end > decimalPosition && value[end] == '0')
    {
        --end;
    }

    if (end == decimalPosition)
    {
        --end;
    }

    return value.substr(0, end + 1);
}
