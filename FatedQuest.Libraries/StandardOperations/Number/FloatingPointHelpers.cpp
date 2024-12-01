#include "FloatingPointHelpers.h"
#include <cstdlib>

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
