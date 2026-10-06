#include "engine.hpp"
#include <cassert>
#include <cstdlib>
#include <vector>

struct Vertices
{
    std::vector<float> vx;
    std::vector<float> vy;
};

Vertices vert;


void AddVertex(Vector2 positon)
{
    vert.vx.push_back(positon.x);
    vert.vy.push_back(positon.y);
}


void DrawVertices()
{
    assert(vert.vx.size() == vert.vy.size()
        && "size of vx-vy are not the same");

    const int leng = vert.vx.size();

    for(int i=0; i < leng; i++)
    {
        DrawPixel(vert.vx[i], vert.vy[i], RGBA(255, 0, 0, 255));
    }
}


void DrawLine(Vector2 start, Vector2 end, u32 color)
{
    int x1 = static_cast<int>(start.x);
    int y1 = static_cast<int>(start.y);
    int x2 = static_cast<int>(end.x);
    int y2 = static_cast<int>(end.y);

    int DistX = abs(x2 - x1);
    int DistY = abs(y2 - y1);
    int StepX = (x1 < x2) ? 1 : -1;
    int StepY = (y1 < y2) ? 1 : -1;
    int err = DistX - DistY;

    while(true)
    {
        DrawPixel(x1, y1, color);


        if(x1 == x2 && y1 == y2) break;

        int e2 = err * 2;
        if(e2 > -DistY)
        {
            err -= DistY;
            x1 += StepX;
        }
        if(e2 < DistX)
        {
            err += DistX;
            y1 += StepY;
        }
    }
}


void DrawTriangle(Vector2 vertex1, Vector2 vertex2, Vector2 vertex3, u32 color)
{
    DrawLine(vertex1, vertex2, color);
    DrawLine(vertex2, vertex3, color);
    DrawLine(vertex3, vertex1, color);
}


int main(void)
{
    if(!Engine_Init()) { return 1;}

    Vector2 vertex1 = { 240, 180 };
    Vector2 vertex2 = { 260, 200 };
    Vector2 vertex3 = { 260, 180 };


    while (ProcessEvents())
    {

        ClearPixels(BLACK);
        DrawTriangle(vertex1, vertex2, vertex3, RED);
        DrawVertices();
        Engine_Update();
       }

    Engine_Quit();
    return 0;
}
