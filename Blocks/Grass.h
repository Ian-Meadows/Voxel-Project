#ifndef GRASS_H
#define GRASS_H
#include "Block.h"

class Grass : public Block
{
public:
    Grass(glm::ivec3 position);
    ~Grass();

private:
    int TopTile() override;
    int BottomTile() override;
    int LeftTile() override;
    int RightTile() override;
    int FrontTile() override;
    int BackTile() override;
};

#endif