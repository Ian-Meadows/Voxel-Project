#include "Block.h"
#include "../Chunk.h"


Block::Block(glm::ivec3 position)
{
    this->position = position;
}
Block::~Block()
{

}


void Block::LoadArray(float* main, float* addition, int additionSize, int* currentIndex, bool multiplyPosition)
{
    if(multiplyPosition)
    {
        for(int i = 0; i < additionSize; i+=3)
        {
            main[*currentIndex] = addition[i] + position.x;
            main[(*currentIndex) + 1] = addition[i+1] + position.y;
            main[(*currentIndex)+2] = addition[i+2] + position.z;
            (*currentIndex)+=3;
        }
    }
    else
    {
        for(int i = 0; i < additionSize; ++i)
        {
            main[*currentIndex] = addition[i];
            (*currentIndex)++;
        }
    }
    
}

float* Block::GetVertices()
{
    float* vertecies = new float[VERTEX_MAX];
    int index = 0;
    LoadArray(vertecies, backVertices, 18, &index, true);//back
    LoadArray(vertecies, frontVertices, 18, &index, true);//front
    LoadArray(vertecies, topVertices, 18, &index, true);//top
    LoadArray(vertecies, bottomVertices, 18, &index, true);//bottom
    LoadArray(vertecies, leftVertices, 18, &index, true);//left
    LoadArray(vertecies, rightVertices, 18, &index, true);//right

    return vertecies;
}

float* Block::GetTexCoords()
{
    float* texCoords = new float[TEX_COORDS_MAX];
    int index = 0;
    LoadArray(texCoords, topTexCoords, 12, &index, false);
    LoadArray(texCoords, topTexCoords, 12, &index, false);
    LoadArray(texCoords, topTexCoords, 12, &index, false);
    LoadArray(texCoords, topTexCoords, 12, &index, false);
    LoadArray(texCoords, topTexCoords, 12, &index, false);
    LoadArray(texCoords, topTexCoords, 12, &index, false);

    return texCoords;
}

/**
 * Places:
 * 0: Is Itself transparent
 * 1: Front
 * 2: Back
 * 3: Top
 * 4: Bottom
 * 5: Left
 * 6: Right
 **/
int Block::GetNeighbors(Chunk* chunk)
{
    int value = 0;
    if(!Exists())
    {
        return 1;
    }
    value |= !Exists();
    value |= chunk->IsTrasparent(glm::ivec3(0, 0, -1) + position) << 1;//front
    value |= chunk->IsTrasparent(glm::ivec3(0, 0, 1) + position) << 2;//back
    value |= chunk->IsTrasparent(glm::ivec3(0, 1, 0) + position) << 3;//top
    value |= chunk->IsTrasparent(glm::ivec3(0, -1, 0) + position) << 4;//bottom
    value |= chunk->IsTrasparent(glm::ivec3(-1, 0, 0) + position) << 5;//left
    value |= chunk->IsTrasparent(glm::ivec3(1, 0, 0) + position) << 6;//right

    return value;
}

int* Block::GetTileIndex()
{
    int* tileIndices = new int[TOTAL_TILES];

    //front
    tileIndices[0] = FrontTile();

    //back
    tileIndices[1] = BackTile();

    //top
    tileIndices[2] = TopTile();

    //bottom
    tileIndices[3] = BottomTile();

    //left
    tileIndices[4] = LeftTile();

    //right
    tileIndices[5] = RightTile();

    return tileIndices;
}


int Block::TopTile()
{
    return 0;
}
int Block::BottomTile()
{
    return 1;
}
int Block::LeftTile()
{
    return 2;
}
int Block::RightTile()
{
    return 3;
}
int Block::FrontTile()
{
    return 4;
}
int Block::BackTile()
{
    return 5;
}


bool Block::IsTransparent() 
{
    return false;
}

bool Block::Exists()
{
    return true;
}