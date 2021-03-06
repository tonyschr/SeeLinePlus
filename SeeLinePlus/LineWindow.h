#pragma once

#include "resource.h"
#include <windows.h>
#include <vector>

// For simplicity, don't require Gdiplus:: prefix.
using namespace Gdiplus;

class LineWindow
{
public:
    virtual ~LineWindow();

    void Show();
    void Hide();
    bool IsVisible();

    // Returns the name of the line.
    virtual std::wstring GetName() = 0;

protected:
    LineWindow();

    // Returns 'true' if the window should follow the mouse cursor and 'false'
    // if it should be a floating, draggable window.
    virtual bool WindowFollowsMouse() = 0;

    // Returns the width and height of the line (maximum drawing area).
    virtual SIZE GetWindowSize() = 0;

    // Returns the offset of the window. For lines that follow the cursor this
    // is the offset from the mouse. For draggable windows this the initial offset
    // from the top left-hand corner of the screen.
    virtual POINT GetWindowOffset() { return POINT { 0, 0 }; };

    // Method that draws the line using GDI+ Graphics object sized to the window.
    virtual void DrawLineBitmap(Graphics& graphics) = 0;

private:
    static const DWORD c_timerPollID;
    static const DWORD c_timerPollTimeoutMilliseconds;
    static const LPCWSTR c_szSeeLinePlusWindowName;
    static const LPCWSTR c_szSeeLinePlusWindowClass;

    // Window message handling
    LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    static LRESULT CALLBACK s_WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    // Private helper methods
    void StartTimer();
    void StopTimer();
    void OnPollMouseTimer();
    void MoveWindowRelativeToMouse(const POINT& mousePoint);
    void UpdateLayerBitmap();
        
    HWND m_window;
};


