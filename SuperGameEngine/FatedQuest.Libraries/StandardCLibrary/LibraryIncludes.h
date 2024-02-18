#pragma once

// C4067 unexpected tokens following preprocessor directive - expected a newline
#pragma warning(disable : 4067)

#include "Text/FString.h"
#include "File/File.h"
#include "File/Directory.h"
#include "Collection/Organised/FList.hpp";
#include "Structural/FVector2D.h"
#include "Structural/FPoint.h"
#include "Events/FEvent.h"
#include "Events/FEventObserver.h"
#include "Events/FEventArguments.h"
#include "Object/TypeHelpers.hpp"
#include "Object/Object.h"
#include "Object/Exceptions/ArgumentNullException.hpp"
#include "Object/Exceptions/NotImplementedException.hpp"
#include "Object/Exceptions/SystemNullReference.hpp"
#include "Structural/FVectorLocationEventArguments.h"
#include "Structural/FPointLocationEventArguments.h"
#include "Extentions/IntHelpers.hpp"