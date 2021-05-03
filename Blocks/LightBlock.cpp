#include "LightBlock.h"
#include "../Chunk.h"

LightBlock::LightBlock(glm::ivec3 position, Chunk* chunk) : Block(position)
{
    
    light = new BlockLight(chunk->GetWorldPosition(position));
    LightHandler::AddLight(light);
}
LightBlock::~LightBlock()
{
    LightHandler::RemoveLight(light);
}

bool LightBlock::IsTransparent()
{
    return true;
}

bool LightBlock::Exists()
{
    return true;
}


int LightBlock::TopTile()
{
    return 6;
}
int LightBlock::BottomTile()
{
    return 6;
}
int LightBlock::LeftTile()
{
    return 6;
}
int LightBlock::RightTile()
{
    return 6;
}
int LightBlock::FrontTile()
{
    return 6;
}
int LightBlock::BackTile()
{
    return 6;
}