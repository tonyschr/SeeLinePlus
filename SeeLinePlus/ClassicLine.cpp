#include "stdafx.h"
#include "ClassicLine.h"

std::wstring ClassicLine::GetName()
{
    return L"Classic line";
}

SIZE ClassicLine::GetWindowSize()
{
    // The line is as wide as the screen and two pixels high.
    return SIZE { GetScreenWidth(), 2 };
}

POINT ClassicLine::GetWindowOffset()
{
    return POINT { 0, 10 };
}

bool ClassicLine::WindowFollowsMouse()
{
    return true;
}

void ClassicLine::DrawLineBitmap(Graphics& graphics)
{
    // White line, with ~40% opacity.
    SolidBrush lightGreyBrush(Color(100, 255, 255, 255));
    graphics.FillRectangle(&lightGreyBrush, 0, 0, GetScreenWidth(), 1);

    // Black line, with ~40% opacity.
    SolidBrush darkGreyBrush(Color(100, 0, 0, 0));
    graphics.FillRectangle(&darkGreyBrush, 0, 1, GetScreenWidth(), 1);
}
