#include "TestToolsComponent.h"
#include "../../SuperGameEngine/Structural/GameObject/GameObject.h"
#include "../../FatedQuest.Libraries/StandardCLibrary/LibraryIncludes.h"

using namespace SuperGameEngineTools;
using namespace SuperGameEngine;
using namespace StandardCLibrary;

void TestToolsComponent::Setup(SceneLoadPackage* loadPackage, GameObject* parent)
{
    GameComponent::Setup(loadPackage, parent);

    m_text = parent->AddComponent<TextComponent>();
    m_text->SetText(FText("TEST"));
    
}
