#include "ComponentTreeViewItem.h"

#include "Component.h"
#include "../SerializableProperties/ToolsSerializableProperty.h"

namespace SuperGameEngine
{
    class SerializableProperty;
}

using namespace SuperGameTools;

ComponentTreeViewItem::ComponentTreeViewItem(const std::shared_ptr<ContentManager>& contentManager) : TreeViewItem(contentManager)
{
}

void ComponentTreeViewItem::Draw()
{
    if (!m_component)
    {
        return;
    }

    for (const std::shared_ptr<ToolsSerializableProperty>& property : m_component->GetToolsProperties())
    {
        property->Draw();
    }
}

void ComponentTreeViewItem::SetComponent(const std::shared_ptr<Component>& component)
{
    m_component = component;
}
