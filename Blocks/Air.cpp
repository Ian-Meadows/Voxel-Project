#include "Air.h"

Air::Air(glm::ivec3 position) : Block(position)
{

}
Air::~Air()
{

}

bool Air::IsTransparent()
{
    return true;
}

bool Air::Exists()
{
    return false;
}


int Air::TopTile()
{
    return -1;
}
int Air::BottomTile()
{
    return -1;
}
int Air::LeftTile()
{
    return -1;
}
int Air::RightTile()
{
    return -1;
}
int Air::FrontTile()
{
    return -1;
}
int Air::BackTile()
{
    return -1;
}