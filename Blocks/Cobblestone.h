#ifndef COBBLESTONE_H
#define COBBLESTONE_H
#include "Block.h"

class Cobblestone : public Block
{
public:
    Cobblestone(glm::ivec3 position);
    ~Cobblestone();

private:
    int TopTile() override;
    int BottomTile() override;
    int LeftTile() override;
    int RightTile() override;
    int FrontTile() override;
    int BackTile() override;
};

#endif