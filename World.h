#ifndef WORLD_H
#define WORLD_H
#include "Chunk.h"
#include <unordered_map>
#include <vector>
#include "Shader.h"
#include "glm/glm.hpp"
#include <map>

enum BlockType
{
    cobble, air, light, grass, diamond, stone
};


struct GLMKeyFunctions {
	size_t operator()(const glm::ivec2& k)const
	{
		//zor x and y
		return std::hash<int>()(k.x) ^ std::hash<int>()(k.y);
	}

	bool operator()(const glm::ivec2& a, const glm::ivec2& b)const
	{
		return a.x == b.x && a.y == b.y;
	}
};


class World
{
public:
    World();
    ~World();

    void Render(Shader* shader);


    void Update(glm::mat4 projection);

    //ex 0,1,2 will translate to 0,16,32
    void AddChunk(glm::ivec2 chunkPosition, int blockType);



    void AddBlock(BlockType type, glm::ivec3 position);
    

    /*
    ex 0, 1, 2. not 0, 16, 32
    returns chunk or nullptr
    */
    Chunk* GetChunk(glm::ivec2 chunkCoord);

    glm::ivec2 WorldCoordToChunkCoord(glm::ivec3 worldCoord);

    glm::ivec3 LocalizePoint(glm::ivec3 point);

    Block* GetBlock(glm::ivec3 worldCoords);

    std::string GetPlacementBlockName();


    void ChangePlacementBlock(BlockType block);

private:
    std::unordered_map<glm::ivec2, Chunk*, GLMKeyFunctions, GLMKeyFunctions> chunks;


    void PlaceBlock();

    void RemoveBlock();

    glm::mat4 projection;

    BlockType placementBlock = stone;

    //removes an area of blocks
    void RemoveArea();

    void PlaceArea();


    void BuildHouse();

};

#endif