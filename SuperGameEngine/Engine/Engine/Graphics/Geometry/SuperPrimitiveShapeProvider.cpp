#include "SuperPrimitiveShapeProvider.h"
#include "SuperPrimitiveRectangle.h"

using namespace SuperGameEngine;
using namespace FatedQuestLibraries;

SuperPrimitiveShapeProvider::SuperPrimitiveShapeProvider(const std::shared_ptr<SDLRendererReader>& renderer)
{
    m_renderer = renderer;
}

std::shared_ptr<PrimitiveRectangle> SuperPrimitiveShapeProvider::CreateRectangle(
    const FVector2F& location, 
    const FVector2F& size) const
{
    return std::make_shared<SuperPrimitiveRectangle>(m_renderer, location, size);
}
