#include "SplitTexture.h"
#include "SimpleRenderPacket.h"

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

    FPoint size = m_superTexture->Size();
    m_textureArea = std::make_shared<RectangleInt>(0, 0, size.GetX(), size.GetY());

    m_splits = std::vector<RectangleInt>();
    this->cachedRenderPacket = std::make_shared<SimpleRenderPacket>();
}

SplitTexture::~SplitTexture()
{
    this->cachedRenderPacket.reset();
}

std::vector<RectangleInt> SplitTexture::GetSplits()
{
    return m_splits;
}

bool SplitTexture::AddSplit(const RectangleInt& newLocation)
{
    if (!Contains(*m_textureArea, newLocation))
    {
        return false;
    }

    m_splits.push_back(newLocation);
    return true;
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

bool SuperGameEngine::SplitTexture::LoadAsset(std::shared_ptr<AssetLoader> assetLoader, FString key)
{
    return assetLoader->LoadAsset(this, key);
}

std::shared_ptr<RenderPacket> SplitTexture::GetObjectRenderPacket()
{
    return this->cachedRenderPacket;
}

void SplitTexture::DrawPacket(std::shared_ptr<RenderPacket> renderPacket, std::shared_ptr<Transform> transform)
{
    renderPacket->DrawPacket(m_superTexture, *transform->GetLocation());
}

bool SplitTexture::Contains(const RectangleInt& left, const RectangleInt& right) const
{
    // You start before
    if (left.GetLeft() > right.GetLeft())
    {
        return false;
    }

    // You end after
    if (left.GetRight() < right.GetRight())
    {
        return false;
    }

    // You start before
    if (left.GetTop() > right.GetTop())
    {
        return false;
    }

    // You end after
    if (left.GetBottom() < right.GetBottom())
    {
        return false;
    }

    return true;
}
