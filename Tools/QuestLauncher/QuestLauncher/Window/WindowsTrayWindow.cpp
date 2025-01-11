#include "WindowsTrayWindow.h"

#include "../Menu/DebugMenuItem.h"
#define WM_TRAYICON (WM_USER + 1)

using namespace QuestLauncher;

WindowsTrayWindow::WindowsTrayWindow(HINSTANCE handleCurrentInstance, HINSTANCE handlePreviousInstance, LPSTR commandLine, int showCommandPrompt)
{
    m_headerAlignment = TextAlignment::Center;

    m_menuItems.emplace_back(std::make_shared<DebugMenuItem>("Options", ActionType::ShowWindow, MenuType::Header));
    m_menuItems.emplace_back(std::make_shared<DebugMenuItem>("ShowWindow", ActionType::ShowWindow, MenuType::Simple));
    m_menuItems.emplace_back(std::make_shared<DebugMenuItem>("Custom", ActionType::Custom, MenuType::Simple));

    m_menuItems.emplace_back(std::make_shared<DebugMenuItem>("Separator", ActionType::Close, MenuType::Separator));
    m_menuItems.emplace_back(std::make_shared<DebugMenuItem>("Close", ActionType::Close, MenuType::Simple));


    LoadIconImageFile("icon.ico", 192);

    CreateNewWindow(handleCurrentInstance, m_icon, "This is a window");

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
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
            POINT point;
            GetCursorPos(&point);
            HMENU handleMenu = CreatePopupMenu();

            int i = 0;
            for (const std::shared_ptr<MenuItem>& item : m_menuItems)
            {
                if (item->GetMenuType() == MenuType::Header)
                {
                    std::string label = item->GetLabel();
                    std::wstring wideString = std::wstring(label.begin(), label.end());
                    MENUITEMINFO header;
                    header.cbSize = sizeof(MENUITEMINFO);
                    header.fMask = MIIM_FTYPE | MIIM_ID | MIIM_DATA;
                    header.fType = MFT_OWNERDRAW;
                    header.dwTypeData = wideString.data();
                    header.wID = i;             // ID for WM_DRAWITEM
                    InsertMenuItem(handleMenu, i, TRUE, &header);
                }
                else if (item->GetMenuType() == MenuType::Simple)
                {
                    std::string label = item->GetLabel();
                    std::wstring wideString = std::wstring(label.begin(), label.end());

                    MENUITEMINFO header;
                    header.cbSize = sizeof(MENUITEMINFO);
                    header.fMask = MIIM_FTYPE | MIIM_ID | MIIM_DATA;
                    header.fType = MFT_OWNERDRAW;
                    header.dwTypeData = wideString.data();
                    header.wID = i;             // ID for WM_DRAWITEM
                    InsertMenuItem(handleMenu, i, TRUE, &header);


                    //AppendMenu(handleMenu, MF_STRING, i, wideString.c_str());
                }
                else
                {
                    InsertMenu(handleMenu, i, MF_SEPARATOR, 0, NULL);
                }

                ++i;
            }

            // Prevents menu auto-closing
            SetForegroundWindow(handleWindow);
            TrackPopupMenu(handleMenu, TPM_BOTTOMALIGN | TPM_LEFTALIGN, point.x, point.y, 0, handleWindow, NULL);
            DestroyMenu(handleMenu);
        }
        break;

    case WM_COMMAND:
    {
        size_t place = LOWORD(additionalInfo);
        if (place < m_menuItems.size())
        {
            const std::shared_ptr<MenuItem> item = m_menuItems.at(place);

            switch (item->GetActionType())
            {
            case ActionType::ShowWindow:
                ShowWindow(m_mainWindowHandle, SW_SHOW);
                break;
            case ActionType::Close:
                Shell_NotifyIcon(NIM_DELETE, &m_notifyIcon);
                PostQuitMessage(0);
                break;
            case ActionType::Custom:
            default:
                break;
            }
        }
    }
        break;

    case WM_DRAWITEM:
    {
        LPDRAWITEMSTRUCT pdis = (LPDRAWITEMSTRUCT)additionalInfoLong;

        UINT i = pdis->itemID;
        const std::shared_ptr<MenuItem> item = m_menuItems.at(i);

        switch (item->GetMenuType())
        {
        case MenuType::Header:
            DrawHeader(pdis, item);
            break;
        case MenuType::Simple:
            DrawItem(pdis, item);
            break;
        }
    }
        break;
    case WM_DESTROY:
        Shell_NotifyIcon(NIM_DELETE, &m_notifyIcon);
        PostQuitMessage(0);
        break;
    case WM_MEASUREITEM:
    {
        MEASUREITEMSTRUCT* mis = (MEASUREITEMSTRUCT*)additionalInfoLong;
        if (mis->CtlType == ODT_MENU)
        {
            mis->itemWidth = 70;
            return TRUE;
        }
        break;
    }
    default:
        return DefWindowProc(handleWindow, messageCode, additionalInfo, additionalInfoLong);
    }
    return 0;
}

void WindowsTrayWindow::DrawItem(LPDRAWITEMSTRUCT& drawDeconstruct, const std::shared_ptr<MenuItem>& item)
{
    std::string label = item->GetLabel();
    std::wstring wideString = std::wstring(label.begin(), label.end());

    // Set colours.
    if (drawDeconstruct->itemState & ODS_SELECTED)
    {
        SetBkColor(drawDeconstruct->hDC, RGB(170, 168, 193));
        FillRect(drawDeconstruct->hDC, &drawDeconstruct->rcItem, (HBRUSH)(COLOR_MENU + 1));
        SetTextColor(drawDeconstruct->hDC, RGB(0, 0, 0));
    }
    else {
        SetBkColor(drawDeconstruct->hDC, RGB(48, 48, 48));
        FillRect(drawDeconstruct->hDC, &drawDeconstruct->rcItem, (HBRUSH)(COLOR_MENU + 1));
        SetTextColor(drawDeconstruct->hDC, RGB(255, 255, 255));
    }

    int xPosition = GetXPosition(drawDeconstruct->hDC, drawDeconstruct->rcItem, wideString, TextAlignment::Left);
    ExtTextOut(drawDeconstruct->hDC, xPosition, drawDeconstruct->rcItem.top, ETO_OPAQUE | ETO_CLIPPED, &drawDeconstruct->rcItem, wideString.c_str(), wideString.length(), NULL);
}

void WindowsTrayWindow::DrawHeader(LPDRAWITEMSTRUCT& drawDeconstruct, const std::shared_ptr<MenuItem>& item)
{
    std::string label = item->GetLabel();
    std::wstring wideString = std::wstring(label.begin(), label.end());

    // Set colours.
    if (drawDeconstruct->itemState & ODS_SELECTED)
    {
        SetBkColor(drawDeconstruct->hDC, RGB(170, 168, 193));
        FillRect(drawDeconstruct->hDC, &drawDeconstruct->rcItem, (HBRUSH)(COLOR_MENU + 1));
        SetTextColor(drawDeconstruct->hDC, RGB(0, 0, 0));
    }
    else {
        SetBkColor(drawDeconstruct->hDC, RGB(17, 16, 35));
        FillRect(drawDeconstruct->hDC, &drawDeconstruct->rcItem, (HBRUSH)(COLOR_MENU + 1));
        SetTextColor(drawDeconstruct->hDC, RGB(255, 255, 255));
    }

    int xPosition = GetXPosition(drawDeconstruct->hDC, drawDeconstruct->rcItem, wideString, m_headerAlignment);
    ExtTextOut(drawDeconstruct->hDC, xPosition, drawDeconstruct->rcItem.top, ETO_OPAQUE | ETO_CLIPPED, &drawDeconstruct->rcItem, wideString.c_str(), wideString.length(), NULL);
}

int WindowsTrayWindow::GetXPosition(const HDC& hdc, const RECT& rect, const std::wstring& text, TextAlignment alignment)
{
    // Align the text
    SIZE textSize;
    int xPosition = 0;
    int padding = 10;
    switch (alignment)
    {
    case TextAlignment::Left:
        xPosition += padding;
        break;
    case TextAlignment::Center:
        GetTextExtentPoint32(hdc, text.c_str(), text.length(), &textSize);
        xPosition = xPosition = rect.left + (rect.right - rect.left - textSize.cx) / 2;
        break;
    case TextAlignment::Right:
        GetTextExtentPoint32(hdc, text.c_str(), text.length(), &textSize);
        xPosition = rect.right - textSize.cx - padding;
        break;
    }

    return xPosition;
}
