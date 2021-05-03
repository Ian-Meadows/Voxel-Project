#ifndef AIR_H
#define AIR_H
#include "Block.h"

class Air : public Block
{
public:
    Air(glm::ivec3 position);
    ~Air();

    bool IsTransparent() override;

    bool Exists() override;

private:
    int TopTile() override;
    int BottomTile() override;
    int LeftTile() override;
    int RightTile() override;
    int FrontTile() override;
    int BackTile() override;
    
};


#endif