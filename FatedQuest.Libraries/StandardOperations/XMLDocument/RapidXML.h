#pragma once

// C26495 Variable 'testing::internal::Mutex::critical_section_' is uninitialized.Always initialize a member variable(type.6).
#pragma warning(push)
#pragma warning(disable : 26495)
#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_utils.hpp>
#include <rapidxml/rapidxml_print.hpp>
#pragma warning(pop)

using namespace rapidxml;
namespace RapidXML
{
    // Define some shorthand when refering to Rapid Types.
    using XMLDocument = xml_document<>;
    using XMLNode = xml_node<>;
    using XMLAttribute = xml_attribute<>;
}