#pragma once

#include "LineWindow.h"

class ClassicLine : public LineWindow
{
public:
    SIZE GetWindowSize() override;

protected:
    bool WindowFollowsMouse() override;
    void DrawLineBitmap(Graphics& graphics) override;
};