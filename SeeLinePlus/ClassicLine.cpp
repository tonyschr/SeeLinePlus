#include "stdafx.h"
#include "ClassicLine.h"

SIZE ClassicLine::GetWindowSize()
{
    // The line is as wide as the screen and two pixels high.
    return SIZE { GetScreenWidth(), 2 };
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
