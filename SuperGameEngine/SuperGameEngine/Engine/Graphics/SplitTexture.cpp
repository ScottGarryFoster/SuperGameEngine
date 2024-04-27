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

    m_splits = std::vector<RectangleInt>();
}

SplitTexture::~SplitTexture()
{

}

std::vector<RectangleInt> SplitTexture::GetSplits()
{
    return m_splits;
}

void SplitTexture::AddSplit(const RectangleInt& newLocation)
{
    m_splits.push_back(newLocation);
}

void SplitTexture::Draw(int split, const RectangleInt& screenLocation) const
{
    int lastElement = (int)m_splits.size() - 1;
    if (split < 0 || split > lastElement)
    {
        return;
    }

    m_superTexture->Draw(m_splits[split], screenLocation);
}