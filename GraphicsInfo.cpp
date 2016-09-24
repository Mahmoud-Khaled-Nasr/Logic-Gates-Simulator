#include "GraphicsInfo.h"

GraphicsInfo::GraphicsInfo(int X, int Y, int Width, int Height)
{
    SetX(X);
    SetY(Y);
    SetWidth(Width);
    SetHeight(Height);
}

GraphicsInfo::GraphicsInfo(std::pair<int,int> Point, std::pair<int,int> Size)
{
    SetX(Point.first);
    SetY(Point.second);
    SetWidth(Size.first);
    SetHeight(Size.second);
}

int GraphicsInfo::GetX() const
{
    return X;
}

int GraphicsInfo::GetY() const
{
    return Y;
}

int GraphicsInfo::GetWidth() const
{
    return Width;
}

int GraphicsInfo::GetHeight() const
{
    return Height;
}

std::pair<int,int> GraphicsInfo::GetOrigin() const
{
    return std::pair<int,int> (X, Y);
}

std::pair<int,int> GraphicsInfo::GetCenter() const
{
    return std::pair<int,int> (X+Width/2.0+0.5, Y+Height/2.0+0.5);
}

void GraphicsInfo::SetX(int X)
{
    this->X = X;
}

void GraphicsInfo::SetY(int Y)
{
    this->Y = Y;
}

void GraphicsInfo::SetWidth(int Width)
{
    this->Width = Width;
}

void GraphicsInfo::SetHeight(int Height)
{
    this->Height = Height;
}

void GraphicsInfo::ShiftBy(std::pair<int,int> Delta)
{
    X += Delta.first;
    Y += Delta.second;
}

bool GraphicsInfo::Contains(int x, int y) const
{
    return (x > X && x < X+Width && y > Y && y < Y+Height);
}

bool GraphicsInfo::Contains(std::pair<int,int> Point) const
{
    return (Point.first > X && Point.first < X+Width && Point.second > Y && Point.second < Y+Height);
}
