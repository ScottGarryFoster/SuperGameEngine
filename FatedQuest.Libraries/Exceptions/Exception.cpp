#include "Exception.h"

#include <vector>

#include "StackTrace/WindowsStackTrace.h"
#ifdef _WINDOWS
#include <Windows.h>
#include <DbgHelp.h>
#include <vector>
#include <string>
#include <sstream>
#include <exception>
#endif

using namespace FatedQuestLibraries;

Exception::Exception(const std::string& message)// : std::exception(message.c_str())
{
    m_message = message;
    m_type = "Exception";

    m_callStack = {};
#ifdef _WINDOWS
    m_callStack = std::make_shared<WindowsStackTrace>(1);
#endif
}

std::string Exception::CallStack() const
{
    if (m_callStack)
    {
        return m_callStack->ToString();
        
    }
    
    return "No call stack created. Note: Call stacks are only implemented for windows.";
    
}

std::string Exception::Message() const
{
    return m_message;
}

std::string Exception::Type() const
{
    return m_type;
}

std::string Exception::ToString()
{
    return m_type + ": " + m_message + "\n" + CallStack();
}
