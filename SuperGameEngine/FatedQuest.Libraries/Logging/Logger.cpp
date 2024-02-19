#include "Logger.h"
#include <iostream>
using namespace StandardCLibrary;

void Logger::Info(FString message)
{
#ifdef _DEBUG
std::cout << "INFO: " << message << std::endl;
#endif
}

void Logger::Warning(FString message)
{
#ifdef _DEBUG
std::cout << "WARNING: " << message << std::endl;
#endif
}
void Logger::Error(FString message)
{
#ifdef _DEBUG
std::cout << "ERROR: " << message << std::endl;
#endif
}

void Logger::Assert(FAsserts exception, FString classType, FString method, FString message)
{
#ifdef _DEBUG
std::cout << "ASSERT " << exception.GetDisplayKey() << ": ["  << classType << "::" << method  << "] " << message << std::endl;
#endif
}