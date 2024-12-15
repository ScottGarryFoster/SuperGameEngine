#include "SuperTextureWrapper.h"
#include "../../../FatedQuestReferences.h"

using namespace SuperGameEngine;
using namespace FatedQuestLibraries;

SuperTextureWrapper::SuperTextureWrapper(const std::shared_ptr<Texture>& texture)
{
    if (!texture)
    {
        throw std::invalid_argument("SuperTextureWrapper: Texture is required.");
    }

    m_texture = texture;
}

SuperTextureWrapper::~SuperTextureWrapper() = default;

void SuperTextureWrapper::Draw() const
{
    m_texture->Draw();
}

void SuperTextureWrapper::Draw(const FPoint& location) const
{
    m_texture->Draw(location);
}

void SuperTextureWrapper::Draw(const FPoint& location, const FPoint& size) const
{
    m_texture->Draw(location, size);
}

void SuperTextureWrapper::Draw(const RectangleInt& textureRectangle, const RectangleInt& screenRectangle) const
{
    m_texture->Draw(textureRectangle, screenRectangle);
}

bool SuperTextureWrapper::RepresentSameImage(std::shared_ptr<SuperTexture> texture) const
{
    std::string first = StringHelpers::ToLower(m_texture->GetLoadedFilePath());

    auto textureWrapper = std::static_pointer_cast<SuperTextureWrapper>(texture);
    if (!textureWrapper->m_texture)
    {
        return false;
    }

    std::string second = StringHelpers::ToLower(textureWrapper->m_texture->GetLoadedFilePath());

    return first == second;
}

bool SuperTextureWrapper::RepresentSameImage(std::string filePath) const
{
    std::string first = StringHelpers::ToLower(m_texture->GetLoadedFilePath());
    std::string second = StringHelpers::ToLower(filePath);

    return first == second;
}

FPoint SuperTextureWrapper::Size() const
{
    return m_texture->Size();
}

bool SuperTextureWrapper::Remake(std::vector<std::string>& errors)
{
    return m_texture->Remake(errors);
}
