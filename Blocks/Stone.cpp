#include "Stone.h"

Stone::Stone(glm::ivec3 position) : Block(position)
{

}
Stone::~Stone()
{

}

int Stone::TopTile()
{
    return 4;
}
int Stone::BottomTile()
{
    return 4;
}
int Stone::LeftTile()
{
    return 4;
}
int Stone::RightTile()
{
    return 4;
}
int Stone::FrontTile()
{
    return 4;
}
int Stone::BackTile()
{
    return 4;
}