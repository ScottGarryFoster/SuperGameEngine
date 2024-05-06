#include "SimpleRenderPacket.h"

using namespace SuperGameEngine;
using namespace StandardCLibrary;

SimpleRenderPacket::SimpleRenderPacket()
{
    this->renderPackets = std::make_shared< FList<std::pair<RectangleInt, RectangleInt>>>();

}

SimpleRenderPacket::~SimpleRenderPacket()
{
    this->renderPackets.reset();
}

void SimpleRenderPacket::Clear()
{
    this->renderPackets = std::make_shared<FList<std::pair<RectangleInt, RectangleInt>>>();
}

void SimpleRenderPacket::AddDrawPacket(const RectangleInt textureRectangle, const RectangleInt screenRectangle)
{
    this->renderPackets->Add(std::pair(textureRectangle, screenRectangle));
}

const std::shared_ptr<FList<std::pair<RectangleInt, RectangleInt>>> SimpleRenderPacket::GetRenderPacket(const FVector2D& offsetLocation) const
{
    std::shared_ptr<FList<std::pair<RectangleInt, RectangleInt>>> returnPacket = std::make_shared< FList<std::pair<RectangleInt, RectangleInt>>>();

    for (std::pair<RectangleInt, RectangleInt> textureScreen : *this->renderPackets)
    {
        RectangleInt textureRec = textureScreen.first;
        RectangleInt screenRec = textureScreen.second;

        screenRec.SetX(screenRec.GetLeft() + offsetLocation.GetX());
        screenRec.SetY(screenRec.GetTop() + offsetLocation.GetY());

        returnPacket->Add(std::pair(textureRec, screenRec));
    }

    return returnPacket;
}

void SimpleRenderPacket::DrawPacket(std::shared_ptr<SuperTexture> texture, const FVector2D& offsetLocation) const
{
    for (std::pair<RectangleInt, RectangleInt> textureScreen : *this->renderPackets)
    {
        RectangleInt textureRec = textureScreen.first;
        RectangleInt screenRec = textureScreen.second;

        screenRec.SetX(screenRec.GetLeft() + offsetLocation.GetX());
        screenRec.SetY(screenRec.GetTop() + offsetLocation.GetY());

        texture->Draw(textureRec, screenRec);
    }
}
