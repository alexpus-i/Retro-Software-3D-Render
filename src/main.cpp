#include "engine.hpp"
#include <cassert>
#include <vector>

struct Vertices
{
    std::vector<float> vx;
    std::vector<float> vy;
};

Vertices vert;


void AddVertex(float x, float y)
{
    vert.vx.push_back(x);
    vert.vy.push_back(y);
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


// void DrawLine()
// {
//     assert(vert.vx.size() == vert.vy.size()
//         && "size of vx-vy are not the same");


//     const int leng = vert.vx.size();
//     if(leng < 2) { return; }

//     for(int i=1; i < leng; i++)
//     {
//         float StartX = vert.vx[i-1];
//         float EndX = vert.vx[i];


//     }
// }


int main(void)
{
    if(!Engine_Init()) { return 1;}


    AddVertex(40, 180);
    AddVertex(80, 180);


    while (ProcessEvents())
    {

        ClearPixels(RGBA(0, 0, 0, 255));
        DrawVertices();
        Engine_Update();
       }

    Engine_Quit();
    return 0;
}
