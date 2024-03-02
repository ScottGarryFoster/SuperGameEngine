#include "TechniqueRenderer.h"
#include "../../../LibraryIncludes.h"

using namespace SuperGameEngine;
TechniqueRenderer::TechniqueRenderer(SDL_Renderer* renderer)
{
    m_renderer = renderer;
    m_techniques = std::vector< std::weak_ptr<DrawableTechnique>>();
}

TechniqueRenderer::~TechniqueRenderer()
{
}

void TechniqueRenderer::GiveTechnique(std::weak_ptr<DrawableTechnique> newTechnique)
{
    m_techniques.push_back(newTechnique);
}

void SuperGameEngine::TechniqueRenderer::Draw()
{
    for (std::weak_ptr<DrawableTechnique> tech : m_techniques)
    {
        std::shared_ptr<DrawableTechnique> shared = tech.lock();
        if (shared)
        {
            shared->Draw(m_renderer);
        }
    }
}

void TechniqueRenderer::Clean()
{
    std::vector< std::weak_ptr<DrawableTechnique>> toRemove = 
        std::vector< std::weak_ptr<DrawableTechnique>>();
    for (std::weak_ptr<DrawableTechnique> tech : m_techniques)
    {
        std::shared_ptr<DrawableTechnique> shared = tech.lock();
        if (!shared)
        {
            toRemove.push_back(tech);
        }
    }

    for (std::weak_ptr<DrawableTechnique> tech : toRemove)
    {
        VectorHelpers::RemoveValue(m_techniques, tech);
    }

}
