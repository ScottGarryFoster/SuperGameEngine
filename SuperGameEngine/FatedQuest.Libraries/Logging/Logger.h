#pragma once
#include "../StandardCLibrary/FString.h"
using namespace StandardCLibrary;

class Logger
{
public:
    static void Info(FString message);
    static void Warning(FString message);
    static void Error(FString message);
};

