#pragma once
#include <memory>
#include <SDL_events.h>
#include <string>

#include "LayoutSettings.h"

namespace FatedQuestLibraries
{
    class DocumentToXml;
    class ModifiableNode;
    class StoredDocumentNode;
}

namespace SuperGameEngine
{
    class RectangleInt;
}

using namespace SuperGameEngine;
using namespace FatedQuestLibraries;

namespace SuperGameTools
{
    class SettingsPaths;

    /// <summary>
    /// Settings about the main window.
    /// </summary>
    class ToolsLayoutSettings : public LayoutSettings
    {
    public:
        ToolsLayoutSettings(
            const std::shared_ptr<SettingsPaths>& paths, 
            const std::string& settingsFile, 
            const std::shared_ptr<DocumentToXml>& documentToXml);
        virtual ~ToolsLayoutSettings() override = default;

        /// <summary>
        /// Handle the current event.
        /// </summary>
        /// <param name="event">Current event. </param>
        virtual void Event(SDL_Event event);

        /// <summary>
        /// If updated writes settings.
        /// </summary>
        virtual void WriteSettings();

        /// <summary>
        /// Read the settings back in.
        /// </summary>
        virtual void ReadSettings();

        /// <summary>
        /// The window width to use when creating the main window.
        /// </summary>
        /// <returns>The window width to use when creating the main window. </returns>
        virtual int WindowWidth() const override;

        /// <summary>
        /// The window height to use when creating the main window.
        /// </summary>
        /// <returns>The window height to use when creating the main window. </returns>
        virtual int WindowHeight() const override;

        /// <summary>
        /// The X position to start the window in.
        /// </summary>
        /// <returns>The X position to start the window in. </returns>
        virtual int WindowX() const override;

        /// <summary>
        /// The Y position to start the window in.
        /// </summary>
        /// <returns>The Y position to start the window in. </returns>
        virtual int WindowY() const override;

    private:

        /// <summary>
        /// True means there is data to be written.
        /// </summary>
        bool m_isDirty;

        /// <summary>
        /// Helps when finding paths with settings.
        /// </summary>
        std::shared_ptr<SettingsPaths> m_settingsPaths;

        /// <summary>
        /// The path to save for this settings file. Full file path.
        /// </summary>
        std::string m_thisFilePath;

        /// <summary>
        /// Just what was given on construction, not the full file path.
        /// </summary>
        std::string m_thisFilename;

        /// <summary>
        /// Converts a Stored Document to XML.
        /// </summary>
        std::shared_ptr<DocumentToXml> m_documentToXml;

        /// <summary>
        /// Position and size for main window.
        /// </summary>
        std::shared_ptr<RectangleInt> m_mainWindow;

        /// <summary>
        /// Attempts to load in size from the document.
        /// </summary>
        /// <param name="node">Node to draw from. </param>
        /// <returns>True means could parse. </returns>
        bool ParseSize(const std::shared_ptr<StoredDocumentNode>& node) const;

        /// <summary>
        /// Creates a node representing size.
        /// </summary>
        /// <returns>A node representing size. </returns>
        std::shared_ptr<ModifiableNode> SerialiseSize() const;
    };
}
