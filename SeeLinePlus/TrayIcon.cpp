#include "stdafx.h"
#include "Resource.h"
#include "TrayIcon.h"

TrayIcon::TrayIcon() : 
    m_notifyWindow(nullptr)
{
}

TrayIcon::~TrayIcon()
{
    Destroy();
}

bool TrayIcon::Create(HWND notifyWindow, HICON icon)
{
    m_notifyWindow = notifyWindow;

    NOTIFYICONDATA notifydata = { 0 };
    notifydata.cbSize = sizeof(NOTIFYICONDATA);
    notifydata.hWnd = m_notifyWindow;
    notifydata.uID = TRAYICON_ID;
    notifydata.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
    notifydata.uCallbackMessage = WM_TRAYICON_NOTIFY;
    notifydata.hIcon = icon;
    StringCchCopy(notifydata.szTip, ARRAYSIZE(notifydata.szTip), L"SeeLine Plus");

    return Shell_NotifyIcon(NIM_ADD, &notifydata);
}

void TrayIcon::Destroy()
{
    if (m_notifyWindow != nullptr)
    {
        NOTIFYICONDATA notifydata = { 0 };        
        notifydata.cbSize = sizeof(NOTIFYICONDATA);
        notifydata.hWnd = m_notifyWindow;
        notifydata.uID = TRAYICON_ID;
        
        Shell_NotifyIcon(NIM_DELETE, &notifydata);
    }
}

HICON LoadTrayIcon(UINT resourceId)
{
    return (HICON)LoadImage(g_instance,
        MAKEINTRESOURCE(resourceId),
        IMAGE_ICON,
        16,
        16,
        0);
}
