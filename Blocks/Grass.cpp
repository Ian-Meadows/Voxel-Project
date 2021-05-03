#include "Grass.h"

Grass::Grass(glm::ivec3 position) : Block(position)
{

}
Grass::~Grass()
{

}

int Grass::TopTile()
{
    return 3;
}
int Grass::BottomTile()
{
    return 1;
}
int Grass::LeftTile()
{
    return 2;
}
int Grass::RightTile()
{
    return 2;
}
int Grass::FrontTile()
{
    return 2;
}
int Grass::BackTile()
{
    return 2;
}