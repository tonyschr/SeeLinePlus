#include "stdafx.h"
#include "resource.h"
#include "SeeLineTray.h"

// Line types
#include "RulerLine.h"
#include "ClassicLine.h"
#include "FancyLine.h"

HINSTANCE g_hInstance = NULL;

SeeLineTray::SeeLineTray() :
    m_hwnd(nullptr)
{
    m_icon = LoadTrayIcon(IDI_SMALL);

    // Add the various lines.
    m_lineWindows.push_back(std::make_unique<ClassicLine>());
    m_lineWindows.push_back(std::make_unique<FancyLine>());
    m_lineWindows.push_back(std::make_unique<RulerLine>());
}

SeeLineTray::~SeeLineTray()
{
    if (m_icon != nullptr)
    {
        DestroyIcon(m_icon);
        m_icon = nullptr;
    }
}

bool SeeLineTray::Create()
{
    bool created = false;

    WNDCLASSEX wcex = { 0 };
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = (WNDPROC)WndProcStatic;
    wcex.hInstance = g_hInstance;
    wcex.lpszClassName = L"SeeLineTrayClass";

    if (RegisterClassEx(&wcex) != 0)
    {
        m_hwnd = CreateWindowEx(0,
            L"SeeLineTrayClass",
            L"SeeLineTrayWindow",
            WS_OVERLAPPEDWINDOW,
            0,
            0,
            2,
            2,
            NULL,
            NULL,
            g_hInstance,
            NULL);
        if (m_hwnd != nullptr)
        {
            SetWindowLongPtr(m_hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

            if (m_trayicon.Create(m_hwnd, m_icon))
            {
                created = true;
            }
        }
    }

    return created;
}

void SeeLineTray::Close()
{
    DestroyWindow(m_hwnd);
}

LRESULT CALLBACK SeeLineTray::WndProcStatic(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    SeeLineTray* tray = nullptr;

    if (message == WM_NCCREATE)
    {
        tray = reinterpret_cast<SeeLineTray*>(reinterpret_cast<LPCREATESTRUCT>(lParam)->lpCreateParams);
        if (tray != nullptr)
        {
            SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<INT_PTR>(tray));
        }
    }
    else
    {
        tray = reinterpret_cast<SeeLineTray*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    }

    LRESULT result = 0;
    if (tray != nullptr)
    {
        result = tray->WndProc(hwnd, message, wParam, lParam);
    }
    else
    {
        result = DefWindowProc(hwnd, message, wParam, lParam);
    }

    return result;
}

LRESULT CALLBACK SeeLineTray::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_TRAYICON_NOTIFY:
    {
        switch (lParam)
        {
        case WM_CONTEXTMENU:
        case WM_RBUTTONUP:
            ShowTrayMenu();
        break;

        case WM_LBUTTONUP:
            OnLeftClick();
            break;
        }
    }
    break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}

void SeeLineTray::ShowTrayMenu()
{
    POINT pt = { 0 };
    GetCursorPos(&pt);

    HMENU hMenu = CreatePopupMenu();
    if (hMenu != NULL)
    {
        const UINT c_closeMenuId = 1000;
        const UINT c_baseLineId = 2000;

        // Add all the lines to the menu.
        for (int i = 0; i < m_lineWindows.size(); i++)
        {
            UINT flags = MF_STRING;
            if (m_lineWindows[i]->IsVisible())
            {
                flags |= MF_CHECKED;
            }

            AppendMenu(hMenu, flags, c_baseLineId + i, m_lineWindows[i]->GetName().c_str());
        }

        AppendMenu(hMenu, MF_SEPARATOR, 0, nullptr);
        AppendMenu(hMenu, MF_STRING, c_closeMenuId, L"Close");

        SetForegroundWindow(m_hwnd);
        UINT id = (UINT)TrackPopupMenu(hMenu,
            TPM_NONOTIFY | TPM_RETURNCMD,
            pt.x,
            pt.y,
            0,
            m_hwnd,
            NULL);
        PostMessage(m_hwnd, WM_NULL, 0, 0);
        DestroyMenu(hMenu);

        switch (id)
        {
        case c_closeMenuId:
            Close();
            break;

        default:
            ToggleLine(m_lineWindows[id - c_baseLineId]);
            break;
        }
    }
}
// Toggles the visibility of the specified line.
void SeeLineTray::ToggleLine(std::unique_ptr<LineWindow>& lineWindow)
{
    if (lineWindow->IsVisible())
    {
        lineWindow->Hide();
    }
    else
    {
        lineWindow->Show();
    }
}

void SeeLineTray::OnLeftClick()
{
    // Toggle the default (first) line when the user left-clicks the tray icon.
    if (m_lineWindows.size() > 0)
    {
        ToggleLine(m_lineWindows[0]);
    }
}

