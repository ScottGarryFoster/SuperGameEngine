#pragma once
#include "../../LibraryIncludes.h"
#include "ControllerLayout.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Creates a Controller Layout from XML Format.
    /// </summary>
    class ControllerLayoutFromXML
    {
    public:
        ControllerLayoutFromXML();
        virtual ~ControllerLayoutFromXML();

        /// <summary>
        /// Creates a Controller Layout from XML format.
        /// You are responsible for the pointer which comes back, ensure you delete it.
        /// </summary>
        /// <param name="xml">Controller Layout in XML form. </param>
        /// <param name="error">If the input is incorrect, this is the reason why. </param>
        /// <returns>Controller Layout or nullptr if could not create. </returns>
        ControllerLayout* CreateFromXML(FString xml, FString& error);
    };
}