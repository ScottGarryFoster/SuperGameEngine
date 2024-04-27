#include "SplitTexture.h"

using namespace SuperGameEngine;
using namespace StandardCLibrary;

SplitTexture::SplitTexture(std::shared_ptr<SuperTexture> superTexture)
{
    if (!superTexture)
    {
        Logger::Assert(ArgumentNullException(), GetTypeName(), FString("Construction"),
            FString("superTexture must not be null"));
    }
    m_superTexture = superTexture;

    m_splits = std::vector<Rectangle>();
}

SplitTexture::~SplitTexture()
{

}

std::vector<Rectangle> SplitTexture::GetSplits()
{
    return m_splits;
}

void SplitTexture::AddSplit(const Rectangle& newLocation)
{
    m_splits.push_back(newLocation);
}

void SplitTexture::Draw(int split, FPoint& location)
{
    FPoint f = FPoint(0, 0);
    m_superTexture->Draw(f, f);
}