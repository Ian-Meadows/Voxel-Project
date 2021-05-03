#ifndef LIGHT_BLOCK_H
#define LIGHT_BLOCK_H
#include "Block.h"
#include "../BlockLight.h"
#include "../LightHandler.h"

class Chunk;
class LightBlock : public Block
{
public:
    LightBlock(glm::ivec3 position, Chunk* chunk);
    ~LightBlock();

    bool IsTransparent() override;
    bool Exists() override;

private:
    int TopTile() override;
    int BottomTile() override;
    int LeftTile() override;
    int RightTile() override;
    int FrontTile() override;
    int BackTile() override;

    BlockLight* light;
    
};


#endif