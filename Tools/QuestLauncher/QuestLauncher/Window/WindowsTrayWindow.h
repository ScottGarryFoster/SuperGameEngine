#pragma once
#include <AsyncInfo.h>

#include "TrayWindow.h"

namespace QuestLauncher
{
    /// <summary>
    /// Creates and manages a window only used in the tray.
    /// </summary>
    class WindowsTrayWindow : public TrayWindow
    {
    public:
        WindowsTrayWindow(HINSTANCE handleCurrentInstance, HINSTANCE handlePreviousInstance, LPSTR commandLine, int showCommandPrompt);
        virtual ~WindowsTrayWindow() override;

        /// <summary>
        /// The title for the window.
        /// </summary>
        /// <returns>The title. </returns>
        virtual std::string GetTitle() const override;

    private:
        /// <summary>
        /// Icon as a windows icon, this needs to be a .ico.
        /// </summary>
        static inline HICON m_icon;

        /// <summary>
        /// The main window handler.
        /// </summary>
        static inline HWND m_mainWindowHandle;

        /// <summary>
        /// The class and details for the window.
        /// </summary>
        static inline WNDCLASS m_classForWindow;

        /// <summary>
        /// The stored data for the icon.
        /// </summary>
        static inline NOTIFYICONDATA m_notifyIcon;

        static void LoadIconImageFile(const std::string& path, int widthHeight);

        static void CreateNewWindow(HINSTANCE handleInstance, HICON icon, const std::string& title);

        static LRESULT CALLBACK WindowProcess(HWND handleWindow, UINT messageCode, WPARAM additionalInfo, LPARAM additionalInfoLong);
    };
}


