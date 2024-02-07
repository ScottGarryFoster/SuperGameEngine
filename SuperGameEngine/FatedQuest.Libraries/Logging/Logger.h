#pragma once
#include "../StandardCLibrary/Text/FString.h"
#include "../StandardCLibrary/Object/FException.h"
using namespace StandardCLibrary;

class Logger
{
public:
    static void Info(FString message);
    static void Warning(FString message);
    static void Error(FString message);
    static void Exception(FException exception, FString classType, FString method, FString message);
};

