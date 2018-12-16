#pragma once

#include "resource.h"
#include <windows.h>
#include <vector>

// For simplicity, don't require Gdiplus:: prefix.
using namespace Gdiplus;

class LineWindow
{
public:
    void Initialize();
    static bool IsAlreadyRunning();
    static void CloseAll();

protected:
    LineWindow();
    virtual ~LineWindow();

    virtual bool WindowFollowsMouse() = 0;
    virtual SIZE GetWindowSize() = 0;
    virtual void DrawLineBitmap(Graphics& graphics) = 0;

private:
    static const DWORD c_timerPollID;
    static const DWORD c_timerPollTimeoutMilliseconds;
    static const LPCWSTR c_szSeeLinePlusWindowName;
    static const LPCWSTR c_szSeeLinePlusWindowClass;

    // Window message handling
    LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    static LRESULT CALLBACK s_WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    // Private functions
    void StartTimer();
    void StopTimer();
    void OnPollMouseTimer();
    void MoveWindowRelativeToMouse(const POINT& ptMouse);
    void UpdateLayerBitmap();
        
    HWND m_window;
};


