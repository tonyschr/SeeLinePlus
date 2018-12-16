
#pragma once

static const UINT TRAYICON_ID = 500;
static const UINT WM_TRAYICON_NOTIFY  = WM_USER + 600;

class TrayIcon
{
public:
    TrayIcon();
    ~TrayIcon();

    bool Create(HWND window);
    void Destroy();

private:
    HWND m_hwnd;
};
