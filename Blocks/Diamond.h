#ifndef DIAMOND_H
#define DIAMOND_H
#include "Block.h"

class Diamond : public Block
{
public:
    Diamond(glm::ivec3 position);
    ~Diamond();

private:
    int TopTile() override;
    int BottomTile() override;
    int LeftTile() override;
    int RightTile() override;
    int FrontTile() override;
    int BackTile() override;
};

#endif