#pragma once

// C4067 unexpected tokens following preprocessor directive - expected a newline
#pragma warning(disable : 4067)

#include "Text/FString.h"
#include "File/File.h"
#include "File/Directory.h"
#include "Collection/Organised/FList.hpp";
#include "Collection/Vector/VectorHelpers.hpp";
#include "Structural/FVector2D.h"
#include "Structural/FObservableVector2D.h"
#include "Structural/FPoint.h"
#include "Events/FEvent.h"
#include "Events/FEventObserver.h"
#include "Events/FEventArguments.h"
#include "Extentions/IntHelpers.hpp"
#include "Extentions/FloatingPointHelpers.hpp"
#include "Object/TypeHelpers.hpp"
#include "Object/Object.h"
#include "Object/Asserts/ArgumentNullException.hpp"
#include "Object/Asserts/NotImplementedException.hpp"
#include "Object/Asserts/SystemNullReference.hpp"
#include "Structural/FVectorLocationEventArguments.h"
#include "Structural/FPointLocationEventArguments.h"