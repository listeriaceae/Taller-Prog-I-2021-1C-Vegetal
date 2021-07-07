#pragma once

class Ladder
{
public:
    constexpr Ladder(float x, float bottom, float top)
    : x{x}, bottom{bottom}, top{top} {}
    constexpr float getX() const { return x; }
    constexpr float getBottom() const { return bottom; }
    constexpr float getTop() const { return top; }

private:
    const float x;
    const float bottom;
    const float top;
};