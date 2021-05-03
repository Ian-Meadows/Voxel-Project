#include "Chunk.h"
#include <iostream>
#include "Debugger.h"
#include <bitset>
#include "Camera.h"
#include <random>
#include "ErrorHandler.h"

#include "glm/gtc/matrix_transform.hpp"
#include "World.h"

#include "LightHandler.h"

Chunk::Chunk(glm::ivec2 position, World* world, int blockType)
{
    this->world = world;

    //pre calculate model matrix
    this->position = position;
    model = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, 0, position.y));

    //load blocks into chunk
    blocks = new Block***[CHUNK_SIZE_X];
    for(int x = 0; x < CHUNK_SIZE_X; ++x)
    {
        blocks[x] = new Block**[CHUNK_SIZE_Y];
        for(int y = 0; y < CHUNK_SIZE_Y; ++y)
        {
            blocks[x][y] = new Block*[CHUNK_SIZE_Z];
            for(int z = 0; z < CHUNK_SIZE_Z; ++z)
            {
                if(y <= 100)
                {
                    if(rand() % 1000 == 1)
                    {
                        blocks[x][y][z] = new Diamond(glm::ivec3(x, y, z));
                    }
                    else if(rand() % 500 == 1)
                    {
                        blocks[x][y][z] = new Grass(glm::ivec3(x, y, z));
                    }
                    else if(rand() % 1000 == 1)
                    {
                        blocks[x][y][z] = new Cobblestone(glm::ivec3(x, y, z));
                    }
                    else
                    {
                        blocks[x][y][z] = new Stone(glm::ivec3(x, y, z));
                    }
                    
                }
                else if(y == 101)
                {
                    //blocks[x][y][z] = new Stone(glm::ivec3(x, y, z));
                    switch (blockType)
                    {
                        case 0:
                            blocks[x][y][z] = new Grass(glm::ivec3(x, y, z));
                            break;
                        case 1:
                            blocks[x][y][z] = new Diamond(glm::ivec3(x, y, z));
                            break;
                        case 2:
                            blocks[x][y][z] = new Stone(glm::ivec3(x, y, z));
                            break;
                        case 3:
                            blocks[x][y][z] = new Cobblestone(glm::ivec3(x, y, z));
                            break;
                        
                        default:
                            blocks[x][y][z] = new Diamond(glm::ivec3(x, y, z));
                            break;
                    }
                    
                }
                else
                {
                    blocks[x][y][z] = new Air(glm::ivec3(x, y, z));
                }
                
                
                
            }
        }
    }
    if(position == glm::ivec2(32, 32))
    {
        AddBlock(new Grass(glm::ivec3(10, 102, 8)));
        AddBlock(new Diamond(glm::ivec3(12, 102, 12)));
        AddBlock(new Stone(glm::ivec3(8, 102, 10)));
    }
    

    
}
Chunk::~Chunk()
{
    if(blocks == nullptr)
    {
        return;
    }
    for (int x = 0; x < CHUNK_SIZE_X; ++x) {
		for (int y = 0; y < CHUNK_SIZE_Y; ++y) {
            for(int z = 0; z < CHUNK_SIZE_Z; ++z)
            {
                if(blocks[x][y][z] != nullptr)
                {
                    delete blocks[x][y][z];
                }
            }
			delete[] blocks[x][y];
		}
		delete[] blocks[x];
	}
	delete[] blocks;
}

void Chunk::Init()
{
    if(initDone)
    {
        return;
    }

    BuildVBOs(true);
    initDone = true;
}


void Chunk::Render(Shader* shader)
{
    if(needsToRebuild)
    {
        //RebuildVBOs();
        BuildVBOs(false);
        //chunk changed to lights need to change
        LightHandler::FullRebuildRequired();
    }
    shader->setMat4("model", model);
    glBindVertexArray(VAO);
    //glDrawArrays(GL_TRIANGLES, 0, totalTriangles);
    //glDrawElementsInstanced(GL_POINTS, 1, GL_UNSIGNED_INT, 0, CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z);
    //glDrawArraysInstanced(GL_POINTS, 0, 0, CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z);
    glDrawArrays(GL_POINTS, 0, totalBlocks);

    //Debugger::PrintVector(Camera::GetPosition(), "camera pos");

}

void Chunk::AddBlock(Block* block)
{
    glm::ivec3 blockPosition = block->position;
    if(IsValid(blockPosition))
    {
        if(blocks[blockPosition.x][blockPosition.y][blockPosition.z] != nullptr)
        {
            delete blocks[blockPosition.x][blockPosition.y][blockPosition.z];
        }
        blocks[blockPosition.x][blockPosition.y][blockPosition.z] = block;
        needsToRebuild = true;
    }
    
}

Block* Chunk::GetBlock(glm::ivec3 localPosition)
{
    if(IsValid(localPosition))
    {
        return blocks[localPosition.x][localPosition.y][localPosition.z];
    }
    else
    {
        return nullptr;
    }
}

void Chunk::BuildVBOs(bool firstTime)
{
    if(firstTime)
    {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(3, VBOs);
    }
    

    glBindVertexArray(VAO);


    totalBlocks = 0;
    for(int x = 0; x < CHUNK_SIZE_X; ++x)
    {
        for(int y = 0; y < CHUNK_SIZE_Y; ++y)
        {
            for(int z = 0; z < CHUNK_SIZE_Z; ++z)
            {
                int blockTotal = blocks[x][y][z]->GetNeighbors(this);

                //0 = 0000000. This is because GetNeighbors returns 0's in positions where block face does not has a neighbor
                if(blocks[x][y][z]->Exists() && blockTotal != 0)
                {
                    ++totalBlocks;
                }
            }
        }
    }

    int positionsSize = totalBlocks;
    int tileIndicesSize = totalBlocks * TOTAL_TILES;
    int openFacesSize = totalBlocks;

    glm::ivec3* positions = new glm::ivec3[positionsSize];
    int positionsIndex = 0;

    int* openFaces = new int[openFacesSize];
    int openFacesIndex = 0;

    int* tileIndices = new int[tileIndicesSize];
    int tileIndicesIndex = 0;


    for(int x = 0; x < CHUNK_SIZE_X; ++x)
    {
        for(int y = 0; y < CHUNK_SIZE_Y; ++y)
        {
            for(int z = 0; z < CHUNK_SIZE_Z; ++z)
            {
                int blockTotal = blocks[x][y][z]->GetNeighbors(this);
                //0 = 0000000. This is because GetNeighbors returns 0's in positions where block face does not has a neighbor
                if(!(blocks[x][y][z]->Exists() && blockTotal != 0))
                {
                    //don't add to arrays because it will not actually render
                    continue;
                }
                //positions
                positions[positionsIndex] = blocks[x][y][z]->position;
                ++positionsIndex;


                //open faces
                openFaces[openFacesIndex] = blocks[x][y][z]->GetNeighbors(this);
                openFacesIndex++;

                
                //tile Indices
                int* newTileIndecies = blocks[x][y][z]->GetTileIndex();
                for(int i = 0; i < TOTAL_TILES; ++i)
                {
                    tileIndices[tileIndicesIndex] = newTileIndecies[i];
                    tileIndicesIndex++;
                }
                
                delete[] newTileIndecies;
            }
        }
    }
    

    //positions
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::ivec3) * positionsSize, positions, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //open faces
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(int) * openFacesSize, openFaces, GL_STATIC_DRAW);
    glVertexAttribIPointer(1, 1, GL_INT, 1 * sizeof(int), (void*)0);
    glEnableVertexAttribArray(1);

    //faces
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(int) * tileIndicesSize, tileIndices, GL_STATIC_DRAW);
    //setup array
    glEnableVertexAttribArray(2);//0 front
    glVertexAttribIPointer(2, 1, GL_INT, 6 * sizeof(int), (void*)0);
    glEnableVertexAttribArray(3);//1 back
    glVertexAttribIPointer(3, 1, GL_INT, 6 * sizeof(int), (void*)(1 * sizeof(int)));
    glEnableVertexAttribArray(4);//2 top
    glVertexAttribIPointer(4, 1, GL_INT, 6 * sizeof(int), (void*)(2 * sizeof(int)));
    glEnableVertexAttribArray(5);//3 bottom
    glVertexAttribIPointer(5, 1, GL_INT, 6 * sizeof(int), (void*)(3 * sizeof(int)));
    glEnableVertexAttribArray(6);//4 left
    glVertexAttribIPointer(6, 1, GL_INT, 6 * sizeof(int), (void*)(4 * sizeof(int)));
    glEnableVertexAttribArray(7);//5 right
    glVertexAttribIPointer(7, 1, GL_INT, 6 * sizeof(int), (void*)(5 * sizeof(int)));
    

    delete[] positions;
    delete[] tileIndices;
    delete[] openFaces;

    needsToRebuild = false;
}

void Chunk::MustReUpdate()
{
    needsToRebuild = true;
}

glm::vec3 Chunk::GetWorldPosition(glm::ivec3 localPosition)
{
    return glm::vec3(localPosition.x + position.x, localPosition.y, localPosition.z + position.y);
}

bool Chunk::IsTrasparent(glm::ivec3 localPosition)
{
    if(IsValid(localPosition))
    {
        return blocks[localPosition.x][localPosition.y][localPosition.z]->IsTransparent();
    }
    else
    {
        //outside of chunk so ask world for it
        Block* block = world->GetBlock(GetWorldPosition(localPosition));
        if(block != nullptr)
        {
            return block->IsTransparent();
        }
        else
        {
            return true;
        }
        
    }
}

bool Chunk::IsValid(glm::ivec3 localPosition)
{
    if(localPosition.x < 0 || localPosition.y < 0 || localPosition.z < 0 ||
        localPosition.x >= CHUNK_SIZE_X || localPosition.y >= CHUNK_SIZE_Y || localPosition.z >= CHUNK_SIZE_Z)
    {
        return false;
    }
    else
    {
        return true;
    }
    
}