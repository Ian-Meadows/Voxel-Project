#include "Diamond.h"

Diamond::Diamond(glm::ivec3 position) : Block(position)
{

}
Diamond::~Diamond()
{

}

int Diamond::TopTile()
{
    return 5;
}
int Diamond::BottomTile()
{
    return 5;
}
int Diamond::LeftTile()
{
    return 5;
}
int Diamond::RightTile()
{
    return 5;
}
int Diamond::FrontTile()
{
    return 5;
}
int Diamond::BackTile()
{
    return 5;
}