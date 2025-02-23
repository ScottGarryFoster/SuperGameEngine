#pragma once

// C26495 Variable 'testing::internal::Mutex::critical_section_' is uninitialized.Always initialize a member variable(type.6).
#pragma warning(push)
#pragma warning(disable : 26495)
#include <rapidxml.hpp>
#include <rapidxml_utils.hpp>
#include <rapidxml_print.hpp>
#pragma warning(pop)

using namespace rapidxml;
namespace RapidXML
{
    // Define some shorthand when referring to Rapid Types.
    using XML_Document = xml_document<>;
    using XML_Node = xml_node<>;
    using XML_Attribute = xml_attribute<>;
}