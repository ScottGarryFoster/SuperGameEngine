#pragma once

#include "../SuperGameEngine/Structural/TestClass.h"
#include <memory>

using namespace SuperGameEngine;

class Test
{
public:
    inline void t()
    {
        std::shared_ptr<TestClass> testClass = std::make_shared<TestClass>();

        testClass->SetHello(4);
    }
};