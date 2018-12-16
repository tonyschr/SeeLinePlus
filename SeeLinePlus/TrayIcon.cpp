#include "stdafx.h"
#include "Resource.h"
#include "TrayIcon.h"

TrayIcon::TrayIcon() : 
    m_hwnd(NULL)
{
}

TrayIcon::~TrayIcon()
{
    Destroy();
}

bool TrayIcon::Create(HWND window)
{
    if(window != NULL)
    {
        m_hwnd = window;

        HICON icon = (HICON)LoadImage(g_instance,
            MAKEINTRESOURCE(IDI_SMALL),
            IMAGE_ICON,
            16,
            16,
            0);

        NOTIFYICONDATA notifydata = { 0 };
        notifydata.cbSize = sizeof(NOTIFYICONDATA);
        notifydata.hWnd = m_hwnd;
        notifydata.uID = TRAYICON_ID;
        notifydata.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
        notifydata.uCallbackMessage = WM_TRAYICON_NOTIFY;
        notifydata.hIcon = icon;
        StringCchCopy(notifydata.szTip, ARRAYSIZE(notifydata.szTip), L"SeeLine Plus");
    
        BOOL fRes = Shell_NotifyIcon(NIM_ADD, &notifydata);
        if(!fRes)
        {
            m_hwnd = NULL;
        }
    }
    
    return m_hwnd != NULL;
}

void TrayIcon::Destroy()
{
    if(m_hwnd != NULL)
    {
        NOTIFYICONDATA notifydata = { 0 };        
        notifydata.cbSize = sizeof(NOTIFYICONDATA);
        notifydata.hWnd = m_hwnd;
        notifydata.uID = TRAYICON_ID;
        
        Shell_NotifyIcon(NIM_DELETE, &notifydata);
    }
}
