#include "Logger.h"
#include <iostream>

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