#include "stdafx.h"
#include "LineWindow.h"


const DWORD LineWindow::c_timerPollID = 1000;  // Unique ID for the timer
const DWORD LineWindow::c_timerPollTimeoutMilliseconds = 10;  // Poll every 10 milliseconds
const LPCWSTR LineWindow::c_szSeeLinePlusWindowName = L"SeeLine Plus";
const LPCWSTR LineWindow::c_szSeeLinePlusWindowClass = L"SeeLinePlusWindowClass";

LineWindow::LineWindow() :
    m_window(NULL)
{
}

LineWindow::~LineWindow()
{
}

void LineWindow::Initialize()
{
    WNDCLASSEX wcex = { 0 };
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = (WNDPROC)s_WndProc;
    wcex.hInstance = g_instance;
    wcex.lpszClassName = c_szSeeLinePlusWindowClass;
    RegisterClassEx(&wcex);

    SIZE size = GetWindowSize();

    // WS_EX_LAYERED - Special type of window that enables transparency
    // WS_EX_TOPMOST - Positions the window above all other windows
    // WS_EX_TOOLWINDOW - Don't show an icon in the taskbar for this window
    DWORD extendedStyles = WS_EX_LAYERED | WS_EX_TOPMOST | WS_EX_TOOLWINDOW;
    if (WindowFollowsMouse())
    {
        // WS_EX_TRANSPARENT - Prevents input from going to the window accidentally
        extendedStyles |= WS_EX_TRANSPARENT;
    }

    m_window = CreateWindowEx(
        extendedStyles,
        c_szSeeLinePlusWindowClass,
        c_szSeeLinePlusWindowName,
        WS_POPUP | WS_VISIBLE,
        0,
        0,
        size.cx,
        size.cy,
        NULL,
        NULL,
        g_instance,
        this);

    UpdateLayerBitmap();

    if (WindowFollowsMouse())
    {
        StartTimer();
    }
}

bool LineWindow::IsAlreadyRunning()
{
    // Search for top-level windows of this type, and return |true| if any exist.
    return FindWindow(c_szSeeLinePlusWindowClass, c_szSeeLinePlusWindowClass) != NULL;
}

void LineWindow::CloseAll()
{
    // Find and close all LineWindow windows.
    //EnumDesktopWindows()
}

// Helper to call non-static WndProc. Boilerplate code that works for more scenarios than
// we care about, but is well-tested.
LRESULT CALLBACK LineWindow::s_WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LineWindow* lineWindow = nullptr;

    if (uMsg == WM_NCCREATE)
    {
        lineWindow = reinterpret_cast<LineWindow*>(reinterpret_cast<LPCREATESTRUCT>(lParam)->lpCreateParams);
        if (lineWindow != nullptr)
        {
            SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<INT_PTR>(lineWindow));
        }
    }
    else
    {
        lineWindow = reinterpret_cast<LineWindow*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    }

    if (lineWindow != NULL)
    {
        return lineWindow->WndProc(hwnd, uMsg, wParam, lParam);
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK LineWindow::WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LRESULT lResult = 0;
    bool fHandled = false;

    switch (uMsg)
    {
    case WM_CLOSE:
        StopTimer();
        DestroyWindow(hwnd);
        fHandled = true;
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        fHandled = true;
        break;

    case WM_ERASEBKGND:
        fHandled = true;
        break;

    case WM_NCHITTEST:
        if (!WindowFollowsMouse())
        {
            // If the window isn't attached to the mouse, let it be draggable like a title bar (caption).
            lResult = HTCAPTION;
            fHandled = true;
        }
        break;

    case WM_TIMER:
        switch (wParam)
        {
        case c_timerPollID:
            OnPollMouseTimer();
            break;
        }
        break;
    }

    if (!fHandled) 
    {
        lResult = DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return lResult;
}

void LineWindow::StartTimer()
{
    SetTimer(m_window, c_timerPollID, c_timerPollTimeoutMilliseconds, NULL);
}

void LineWindow::StopTimer()
{
    KillTimer(m_window, c_timerPollID);
}

void LineWindow::OnPollMouseTimer()
{
    POINT ptMouse = { 0, 0 };
    GetCursorPos(&ptMouse);

    MoveWindowRelativeToMouse(ptMouse);
}

void LineWindow::MoveWindowRelativeToMouse(const POINT& ptMouse)
{
    SetWindowPos(m_window,
        HWND_TOPMOST,
        ptMouse.x,
        ptMouse.y + 10,
        0,
        0,
        SWP_NOACTIVATE | SWP_NOSIZE);

}

void LineWindow::UpdateLayerBitmap() 
{
    RECT rc;
    GetClientRect(m_window, &rc);

    // Create a new bitmap and select it into the device context for rendering onto.
    HBITMAP bitmap = CreateCompatibleBitmap(GetDC(NULL), RECTWIDTH(rc), RECTHEIGHT(rc));
    HDC hdcBitmap = CreateCompatibleDC(GetDC(NULL));
    HBITMAP oldBitmap = (HBITMAP)SelectObject(hdcBitmap, bitmap);

    // Create GDI+ graphics object on top of the bitmap, and clear to transparent black.
    Graphics graphics(hdcBitmap);
    graphics.Clear(Color(0, 0, 0, 0));

    // Let our subclasses fill in the bitmap.
    DrawLineBitmap(graphics);

    // Now apply the bitmap to to the layered window.
    BLENDFUNCTION blend = { 0 };
    blend.BlendOp = AC_SRC_OVER;
    blend.SourceConstantAlpha = 255;
    blend.AlphaFormat = AC_SRC_ALPHA;

    POINT ptPos = { 0, 0 };
    SIZE sizeWnd = { RECTWIDTH(rc), RECTHEIGHT(rc) };
    POINT ptSrc = { 0, 0 };

    UpdateLayeredWindow(m_window, GetDC(NULL), &ptPos, &sizeWnd, hdcBitmap, &ptSrc, 0, &blend, ULW_ALPHA);

    // Cleanup
    SelectObject(hdcBitmap, oldBitmap);
    ReleaseDC(NULL, hdcBitmap);
    DeleteObject(bitmap);
}
