#ifndef CHUNK_H
#define CHUNK_H
#include "OpenGL_Includer.h"
#include "Shader.h"
#include "Blocks/Block.h"
#include "Blocks/Cobblestone.h"
#include "Blocks/Air.h"
#include "Blocks/Diamond.h"
#include "Blocks/Grass.h"
#include "Blocks/Stone.h"
#include "Blocks/LightBlock.h"


#define CHUNK_SIZE_X 16
#define CHUNK_SIZE_Y 256
#define CHUNK_SIZE_Z 16

class Block;
class World;
class Chunk
{
public:
    Chunk(glm::ivec2 position, World* world, int blockType);
    ~Chunk();

    void Render(Shader* shader);

    bool IsTrasparent(glm::ivec3 localPosition);


    void AddBlock(Block* block);

    Block* GetBlock(glm::ivec3 localPosition);

    glm::ivec2 GetPosition() const { return position; }

    glm::vec3 GetWorldPosition(glm::ivec3 localPosition);

    //call after all chunks are loaded
    void Init();

    //when block next to this chunk updated
    void MustReUpdate();

private:
    Block**** blocks = nullptr;

    void BuildVBOs(bool firstTime);
    //void RebuildVBOs();

    bool IsValid(glm::ivec3 localPosition);

    unsigned int VAO;

    /**
     * 0: vertices
     * 1: texture coordinates
     * 2: Tile Index
     **/
    unsigned int VBOs[3];

    int totalTriangles;

    //x, z
    glm::ivec2 position;
    glm::mat4 model;


    bool needsToRebuild = false;

    World* world;

    bool initDone = false;

    int totalBlocks = CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z;

};

#endif