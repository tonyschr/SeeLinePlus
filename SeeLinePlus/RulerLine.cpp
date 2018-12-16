#include "stdafx.h"
#include "RulerLine.h"

SIZE RulerLine::GetWindowSize()
{
    // The line is as wide as the screen and two pixels high.
    return SIZE{ GetWidth(), GetHeight() };
}

bool RulerLine::WindowFollowsMouse()
{
    return false;
}

void RulerLine::DrawLineBitmap(Graphics& graphics)
{
    // Fill with a yellow background with some transparency.
    SolidBrush yellowBackgroundBGrush(Color(200, 200, 200, 60));
    graphics.FillRectangle(&yellowBackgroundBGrush, 0, 0, GetWidth(), GetHeight());

    // Create the pen and brush for drawing the lines and text.
    Pen markingsPen(Color(255, 0, 0, 0));
    SolidBrush markingsBrush(Color(255, 0, 0, 0));

    // Create the font for rendering the numbers.
    Font numbersFont(L"Arial", 10);
    StringFormat format;
    format.SetAlignment(StringAlignmentNear);

    for (int i = 10; i < GetWidth(); i += 10)
    {
        if ((i % 100) == 0)
        {
            WCHAR pixels[16];
            StringCchPrintf(pixels, ARRAYSIZE(pixels), L"%d", i);

            graphics.DrawLine(&markingsPen, i, 0, i, 60);

            // Define the rectangle for the text. Slightly lower and to the left of the
            // end of the line we just drew. 1000px for the width so the text never wraps.
            RectF layoutRect(static_cast<float>(i) - 10, 64, 1000, 60);

            graphics.DrawString(
                pixels,
                static_cast<int>(wcslen(pixels)),
                &numbersFont,
                layoutRect,
                &format,
                &markingsBrush);
        }
        else
        {
            graphics.DrawLine(&markingsPen, i, 0, i, 30);
        }
    }
}

int RulerLine::GetWidth()
{
    return GetScreenWidth() / 2;
}

int RulerLine::GetHeight()
{
    return 100;
}