#pragma once

// C4067 unexpected tokens following preprocessor directive - expected a newline
#pragma warning(disable : 4067)

// C26819 Unannotated fallthrough between switch labels (es.78).
#pragma warning(push)
#pragma warning(disable : 26819)
#include <SDL_stdinc.h>
#pragma warning(pop)