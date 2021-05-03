#ifndef STONE_H
#define STONE_H
#include "Block.h"

class Stone : public Block
{
public:
    Stone(glm::ivec3 position);
    ~Stone();

private:
    int TopTile() override;
    int BottomTile() override;
    int LeftTile() override;
    int RightTile() override;
    int FrontTile() override;
    int BackTile() override;
};

#endif