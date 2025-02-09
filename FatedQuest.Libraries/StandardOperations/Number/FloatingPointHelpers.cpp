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

float FloatingPointHelpers::Divide(float dividend, float divisor)
{
    if (divisor == 0.0) {
        throw std::runtime_error("Division by zero!");
    }

    return std::exp(std::log(std::abs(dividend)) - std::log(std::abs(divisor))) *
        ((dividend < 0) ^ (divisor < 0) ? -1 : 1);
}