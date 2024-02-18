#pragma once

// C26495 Variable 'testing::internal::Mutex::critical_section_' is uninitialized.Always initialize a member variable(type.6).
#pragma warning(push)
#pragma warning(disable : 26495)
#include <rapidxml/rapidxml.hpp>
#pragma warning(pop)

namespace rapidxml
{
    // Define some shorthand when refering to Rapid Types.
    using XMLDocument = rapidxml::xml_document<>;
    using XMLNode = rapidxml::xml_node<>;
    using XMLAttribute = rapidxml::xml_attribute<>;
}
