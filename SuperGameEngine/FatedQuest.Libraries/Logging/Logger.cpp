#include "Logger.h"
#include <iostream>
using namespace StandardCLibrary;

void Logger::Info(FString message)
{
#ifdef _DEBUG
std::cout << "INFO: " << message.AsStdString() << std::endl;
#endif
}

void Logger::Warning(FString message)
{
#ifdef _DEBUG
std::cout << "WARNING: " << message.AsStdString() << std::endl;
#endif
}
void Logger::Error(FString message)
{
#ifdef _DEBUG
std::cout << "ERROR: " << message.AsStdString() << std::endl;
#endif
}

void Logger::Exception(FException exception, FString classType, FString method, FString message)
{
#ifdef _DEBUG
std::cout << "EXCEPTION " << exception.GetDisplayKey().AsStdString() << ": ["  << classType.AsStdString() << "::" << method.AsStdString()  << "] " << message.AsStdString() << std::endl;
#endif
}