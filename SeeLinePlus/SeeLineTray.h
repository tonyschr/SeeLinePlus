#pragma once

#include "TrayIcon.h"
#include "LineWindow.h"

class SeeLineTray
{
public:
    SeeLineTray();
    ~SeeLineTray();
    
    bool Create();
    void Close();

private:
    virtual LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    static LRESULT CALLBACK WndProcStatic(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

    HWND m_hwnd;
    HICON m_icon;
    TrayIcon m_trayicon;
    std::vector<std::unique_ptr<LineWindow>> m_lineWindows;

    void ShowTrayMenu(const POINT& pt);
    void ToggleLine(std::unique_ptr<LineWindow>& lineWindow);
    void OnLeftClick();
};
