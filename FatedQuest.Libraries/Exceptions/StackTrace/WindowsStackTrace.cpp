#include "WindowsStackTrace.h"
#include "StackTraceLine.h"
#include "../../Logger/AllReferences.h"

#ifdef _WINDOWS

#pragma comment(lib, "Dbghelp.lib")
#include <Windows.h>
#include <DbgHelp.h>
#include <sstream>

#endif

using namespace FatedQuestLibraries;

WindowsStackTrace::WindowsStackTrace(unsigned int startFrame, unsigned int maxFrames)
{
#ifdef _WINDOWS

    // Capture
    std::vector<PVOID> frames;
    frames.resize(maxFrames);
    USHORT captured = CaptureStackBackTrace(
        startFrame + 4,
        maxFrames,
        frames.data(),
        nullptr
    );
    frames.resize(captured);

    // Get the symbols to acquire the names / locations
    HANDLE process = GetCurrentProcess();
    SymSetOptions(SYMOPT_LOAD_LINES | SYMOPT_UNDNAME);
    if (!SymInitialize(process, nullptr, TRUE))
    {
        Log::Error("Could not gather symbols.", "WindowsStackTrace::WindowsStackTrace");
        return;
    }

    // Setup Symbol storage
    SYMBOL_INFO* symbol = nullptr;
    constexpr size_t maxNameLength = 256;
    symbol = static_cast<SYMBOL_INFO*>(std::malloc(
        sizeof(SYMBOL_INFO) + maxNameLength * sizeof(char)
    ));
    symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
    symbol->MaxNameLen = maxNameLength;


    for (auto currentFrame : frames)
    {
        DWORD64 address = reinterpret_cast<DWORD64>(currentFrame);
        std::string addressAsString = std::to_string(address);

        DWORD64 displacement = 0;
        if (SymFromAddr(process, reinterpret_cast<DWORD64>(currentFrame), &displacement, symbol))
        {
            // If we have the symbol from the address attempt to get more information
            IMAGEHLP_LINE64 line = {};
            line.SizeOfStruct = sizeof(line);

            DWORD lineDisplacement = 0;
            if (SymGetLineFromAddr64
                (process, reinterpret_cast<DWORD64>(currentFrame), &lineDisplacement, &line)
                )
            {
                m_lines.emplace_back(std::make_shared<StackTraceLine>(symbol->Name, addressAsString, line.FileName, line.LineNumber));
            }
            else
            {
                m_lines.emplace_back(std::make_shared<StackTraceLine>(symbol->Name, addressAsString));
            }
        }
        else
        {
            m_lines.emplace_back(std::make_shared<StackTraceLine>("Could not find name", addressAsString));
        }
    }

    // Remember symbol is a raw pointer.
    std::free(symbol);
    SymCleanup(process);
#else
    Log::Error("Attempted to get call stack using windows but platform is not windows.",
        "WindowsStackTrace::WindowsStackTrace(unsigned int, unsigned int)");
#endif
}

std::string WindowsStackTrace::ToString() const
{
    std::string toLine = {};
    for (const std::shared_ptr<StackTraceLine>& line : m_lines)
    {
        if (line->GetName().empty())
        {
            continue;
        }

        if (line->GetLineNumber() == -1)
        {
            continue;
        }

        if (line->GetFilename().empty())
        {
            toLine += line->GetAddress() + " on line " + std::to_string(line->GetLineNumber()) + "\n";
        }
        else
        {
            toLine += line->GetName() + " in file " + line->GetFilename() + " on line " + std::to_string(line->GetLineNumber()) + "\n";
        }
    }

    return toLine;
}

std::vector<std::shared_ptr<StackTraceLine>> WindowsStackTrace::Lines() const
{
    return m_lines;
}
