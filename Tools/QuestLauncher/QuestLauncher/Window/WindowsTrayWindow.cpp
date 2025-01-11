#include "WindowsTrayWindow.h"
#define WM_TRAYICON (WM_USER + 1)

using namespace QuestLauncher;

WindowsTrayWindow::WindowsTrayWindow(HINSTANCE handleCurrentInstance, HINSTANCE handlePreviousInstance, LPSTR commandLine, int showCommandPrompt)
{
    LoadIconImageFile("icon.ico", 192);

    CreateNewWindow(handleCurrentInstance, m_icon, "This is a window");

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

WindowsTrayWindow::~WindowsTrayWindow()
{
}

std::string WindowsTrayWindow::GetTitle() const
{
    return {};
}

void WindowsTrayWindow::LoadIconImageFile(const std::string& path, int widthHeight)
{
    std::wstring wideString = std::wstring(path.begin(), path.end());
    m_icon = (HICON)LoadImage(NULL, wideString.c_str(), IMAGE_ICON, widthHeight, widthHeight, LR_LOADFROMFILE);
}

void WindowsTrayWindow::CreateNewWindow(HINSTANCE handleInstance, HICON icon, const std::string& title)
{
    m_classForWindow = {};
    m_classForWindow.lpfnWndProc = WindowProcess;
    m_classForWindow.hInstance = handleInstance;
    m_classForWindow.lpszClassName = TEXT("TrayAppClass");
    m_classForWindow.hIcon = icon;
    RegisterClass(&m_classForWindow);

    SendMessage(m_mainWindowHandle, WM_SETICON, ICON_BIG, (LPARAM)icon);
    SendMessage(m_mainWindowHandle, WM_SETICON, ICON_SMALL, (LPARAM)icon);

    std::wstring wideString = std::wstring(title.begin(), title.end());
    m_mainWindowHandle = CreateWindowEx(0, m_classForWindow.lpszClassName, wideString.c_str(),
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 300, 200,
        NULL, NULL, handleInstance, NULL);

    // Create the tray which is the main part.
    m_notifyIcon.cbSize = sizeof(NOTIFYICONDATA);
    m_notifyIcon.hWnd = m_mainWindowHandle;
    m_notifyIcon.uID = 1;
    m_notifyIcon.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    m_notifyIcon.uCallbackMessage = WM_TRAYICON;
    m_notifyIcon.hIcon = icon;
    lstrcpy(m_notifyIcon.szTip, TEXT("My Tray Application"));
    Shell_NotifyIcon(NIM_ADD, &m_notifyIcon);

    ShowWindow(m_mainWindowHandle, SW_HIDE);
}

LRESULT WindowsTrayWindow::WindowProcess(HWND handleWindow, UINT messageCode, WPARAM additionalInfo, LPARAM additionalInfoLong)
{
    switch (messageCode)
    {
    case WM_TRAYICON:
        if (additionalInfoLong == WM_LBUTTONDOWN)
        {
            POINT p;
            GetCursorPos(&p);
            HMENU hMenu = CreatePopupMenu();
            AppendMenu(hMenu, MF_STRING, 0, TEXT("Show Window"));
            AppendMenu(hMenu, MF_STRING, 1, TEXT("Exit"));
            SetForegroundWindow(handleWindow);  // Prevents menu auto-closing
            TrackPopupMenu(hMenu, TPM_BOTTOMALIGN | TPM_LEFTALIGN, p.x, p.y, 0, handleWindow, NULL);
            DestroyMenu(hMenu);
        }
        break;

    case WM_COMMAND:
        switch (LOWORD(additionalInfo))
        {
        case 0:
            // This shows the application window itself which we probably do not need.
            ShowWindow(m_mainWindowHandle, SW_SHOW);
            break;
        case 1:
            Shell_NotifyIcon(NIM_DELETE, &m_notifyIcon);
            PostQuitMessage(0);
            break;
        }
        break;

    case WM_DESTROY:
        Shell_NotifyIcon(NIM_DELETE, &m_notifyIcon);
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(handleWindow, messageCode, additionalInfo, additionalInfoLong);
    }
    return 0;
}
