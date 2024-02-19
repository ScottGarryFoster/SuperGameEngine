#pragma once
#include "../../LibraryIncludes.h"
#include "Controller.hpp"
#include "UniversalControllerButton.hpp"
#include "UniversalControllerAxis.hpp"
#include "ControllerLayoutCollection.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Aids in Mapping the SDL Joystick to Universal Controller Mappings.
    /// </summary>
    class ControllerMapper : public Object
    {
    public:
        ControllerMapper(ControllerLayoutCollection* controllerCollection);

        /// <summary>
        /// Attempts to map the SDL button code to the corisponding Universal controller button.
        /// This can fail if you are attempting to find a button which is not on the controller.
        /// Not every controller will have a DPad and Four Facebuttons for instance.
        /// </summary>
        /// <param name="controller">Controller to map. </param>
        /// <param name="SDLButton">Button to test. </param>
        /// <returns>Universal Button we believe might work or Unknown if there is no clear answer. </returns>
        UniversalControllerButton GetUniversalControllerButtonFromSDLButton(Controller controller, int SDLButton) const;

        /// <summary>
        /// Returns the number of buttons on the given controller.
        /// </summary>
        /// <param name="controller">Controller to test.</param>
        /// <returns>
        /// Number of SDL based buttons on the controller or 
        /// -1 if there are none / it is not a valid controller.
        /// </returns>
        int GetSDLButtonsOnController(Controller controller) const;

        /// <summary>
        /// Some axis are mapped to Axis, such as Triggers or the DPad.
        /// These you would want to act both as a Boolean button and as a granular
        /// axis and therefore you want to do a pass on the state of these as buttons.
        /// </summary>
        /// <param name="controller">Controller to map. </param>
        /// <returns>All axis mapped to universal buttons or empty list if there are none.</returns>
        std::vector<std::pair<int, UniversalControllerButton>> GetUniversalControllerButtonMappedToAxis(Controller controller) const;

        /// <summary>
        /// The number of axis we expect on the controller.
        /// </summary>
        /// <param name="controller">Controller to test.</param>
        /// <returns>
        /// Number of SDL based axis on the controller or 
        /// -1 if there are none / it is not a valid controller.
        /// </returns>
        int GetSDLAxisOnController(Controller controller) const;

        /// <summary>
        /// Gets a Universal Axis Mapping from the SDL Mapping.
        /// </summary>
        /// <param name="controller">Controller to look for the mapping of. </param>
        /// <param name="SDLAxis">SDL Axis to get context for. </param>
        /// <returns>Axis mapping information. </returns>
        AxisToUniversalAxis GetUniversalAxisMapping(Controller controller, int SDLAxis) const;

        /// <summary>
        /// Get the Hat Mapped to DPad.
        /// </summary>
        /// <param name="controller">Controller to check. </param>
        /// <returns>The hat mapped to DPad. -1 means no hat is mapped. </returns>
        int GetSDLHatMappedToDPad(Controller controller) const;

        /// <summary>
        /// Uses the input from an SDL Hat and converts it to a DPad button.
        /// </summary>
        /// <param name="hatState">State of the given hat. </param>
        /// <returns>The universal button for the dpad or unknown if unpressed.</returns>
        UniversalControllerButton GetHatStateMappedToDPad(int hatState);

        /// <summary>
        /// Detirmines if the given value from an axis on the controller should be considered
        /// a 'pressed' value.
        /// </summary>
        /// <param name="controller">Controller to test. </param>
        /// <param name="button">Button to test. </param>
        /// <param name="SDLAxis">Axis to test. </param>
        /// <param name="axisValue">Axis value to test. </param>
        /// <returns>
        /// True means it should. False means it should not. 
        /// Will be false if axis is not to meant to be mapped to a button.
        /// </returns>
        bool IsGivenAxisValueAPressedValueForButton(Controller controller, UniversalControllerButton button, int SDLAxis, int axisValue) const;
    private:

        /// <summary>
        /// Gives access to the controllers loaded in the session.
        /// </summary>
        ControllerLayoutCollection* m_controllerCollection;
    };
}