#include "World.h"
#include "ErrorHandler.h"
#include "Input.h"
#include "Debugger.h"
#include "Camera.h"
#include "Window.h"
#include <math.h>
#include "LightHandler.h"
#include "Camera.h"

World::World()
{
    //good seed to use
    srand(1);
    //create 49 chunks. A total of 200,704 blocks(if you count the air blocks)
    for(int x = 0; x <= 6; ++x)
    {
        for(int y = 0; y <= 6; ++y)
        {
            AddChunk(glm::ivec2(x, y), rand() % 4);
        }
    }

    //call init because all chunks are loaded
    for(auto pair : chunks)
    {
        pair.second->Init();
    }
    AddBlock(stone, glm::ivec3(42, 102, 42));
    AddBlock(light, glm::ivec3(42, 103, 42));

    BuildHouse();
}

World::~World()
{
    for(auto pair : chunks)
    {
        delete pair.second;
    }
} 

void World::BuildHouse()
{

    //base
    AddBlock(stone, glm::ivec3(47, 102, 35));
    AddBlock(stone, glm::ivec3(48, 102, 35));
    AddBlock(stone, glm::ivec3(49, 102, 35));
    AddBlock(stone, glm::ivec3(50, 102, 35));
    AddBlock(stone, glm::ivec3(51, 102, 35));

    AddBlock(stone, glm::ivec3(47, 102, 40));
    AddBlock(stone, glm::ivec3(48, 102, 40));
    AddBlock(stone, glm::ivec3(49, 102, 40));
    AddBlock(stone, glm::ivec3(50, 102, 40));
    AddBlock(stone, glm::ivec3(51, 102, 40));

    AddBlock(stone, glm::ivec3(51, 102, 36));
    AddBlock(stone, glm::ivec3(51, 102, 37));
    AddBlock(stone, glm::ivec3(51, 102, 38));
    AddBlock(stone, glm::ivec3(51, 102, 39));
    

    //base 2
    AddBlock(stone, glm::ivec3(47, 103, 35));
    AddBlock(stone, glm::ivec3(48, 103, 35));
    AddBlock(light, glm::ivec3(49, 103, 35));//light
    AddBlock(stone, glm::ivec3(50, 103, 35));
    AddBlock(stone, glm::ivec3(51, 103, 35));

    AddBlock(stone, glm::ivec3(47, 103, 40));
    AddBlock(stone, glm::ivec3(48, 103, 40));
    AddBlock(stone, glm::ivec3(49, 103, 40));
    AddBlock(stone, glm::ivec3(50, 103, 40));
    AddBlock(stone, glm::ivec3(51, 103, 40));

    AddBlock(stone, glm::ivec3(51, 103, 36));
    AddBlock(stone, glm::ivec3(51, 103, 37));
    AddBlock(stone, glm::ivec3(51, 103, 38));
    AddBlock(stone, glm::ivec3(51, 103, 39));

    //base 3
    AddBlock(stone, glm::ivec3(47, 104, 35));
    AddBlock(stone, glm::ivec3(48, 104, 35));
    AddBlock(stone, glm::ivec3(49, 104, 35));
    AddBlock(stone, glm::ivec3(50, 104, 35));
    AddBlock(stone, glm::ivec3(51, 104, 35));

    AddBlock(stone, glm::ivec3(47, 104, 40));
    AddBlock(stone, glm::ivec3(48, 104, 40));
    AddBlock(stone, glm::ivec3(49, 104, 40));
    AddBlock(stone, glm::ivec3(50, 104, 40));
    AddBlock(stone, glm::ivec3(51, 104, 40));

    AddBlock(stone, glm::ivec3(51, 104, 36));
    AddBlock(stone, glm::ivec3(51, 104, 37));
    AddBlock(stone, glm::ivec3(51, 104, 38));
    AddBlock(stone, glm::ivec3(51, 104, 39));


    //roof
    AddBlock(grass, glm::ivec3(47, 105, 35));
    AddBlock(grass, glm::ivec3(48, 105, 35));
    AddBlock(grass, glm::ivec3(49, 105, 35));
    AddBlock(grass, glm::ivec3(50, 105, 35));
    AddBlock(grass, glm::ivec3(51, 105, 35));

    AddBlock(grass, glm::ivec3(47, 105, 40));
    AddBlock(grass, glm::ivec3(48, 105, 40));
    AddBlock(grass, glm::ivec3(49, 105, 40));
    AddBlock(grass, glm::ivec3(50, 105, 40));
    AddBlock(grass, glm::ivec3(51, 105, 40));

    AddBlock(grass, glm::ivec3(51, 105, 36));
    AddBlock(grass, glm::ivec3(51, 105, 37));
    AddBlock(grass, glm::ivec3(51, 105, 38));
    AddBlock(grass, glm::ivec3(51, 105, 39));

    AddBlock(grass, glm::ivec3(47, 105, 36));
    AddBlock(grass, glm::ivec3(47, 105, 37));
    AddBlock(grass, glm::ivec3(47, 105, 38));
    AddBlock(grass, glm::ivec3(47, 105, 39));

    AddBlock(grass, glm::ivec3(48, 105, 36));
    AddBlock(grass, glm::ivec3(48, 105, 37));
    AddBlock(grass, glm::ivec3(48, 105, 38));
    AddBlock(grass, glm::ivec3(48, 105, 39));
    
    AddBlock(grass, glm::ivec3(49, 105, 36));
    AddBlock(grass, glm::ivec3(49, 105, 37));
    AddBlock(grass, glm::ivec3(49, 105, 38));
    AddBlock(grass, glm::ivec3(49, 105, 39));

    AddBlock(grass, glm::ivec3(50, 105, 36));
    AddBlock(grass, glm::ivec3(50, 105, 37));
    AddBlock(grass, glm::ivec3(50, 105, 38));
    AddBlock(grass, glm::ivec3(50, 105, 39));

    
}  

void World::AddBlock(BlockType type, glm::ivec3 position)
{
    Block* block;
    glm::ivec3 localPos = LocalizePoint(position);
    Chunk* chunk = GetChunk(WorldCoordToChunkCoord(position)); 
    //null check
    if(chunk == nullptr)
    {
        return;
    } 
    switch (type)
    {
        case cobble:
            block = new Cobblestone(localPos);
            break;
        case air:
            block = new Air(localPos);
            break;
        case light:
            block = new LightBlock(localPos, chunk);
            break;
        case diamond:
            block = new Diamond(localPos);
            break;
        case grass:
            block = new Grass(localPos);
            break;
        case stone:
            block = new Stone(localPos);
            break;
        default:
            block = new Cobblestone(localPos);
            break;
    }

    //null already checked
    chunk->AddBlock(block);


    //Check for Neighboring chunks

    glm::ivec3 positions[4] = 
    {
        (glm::ivec3(1, 0, 0) + position),
        (glm::ivec3(-1, 0, 0) + position),
        (glm::ivec3(0, 0, -1) + position),
        (glm::ivec3(0, 0, 1) + position)
    };

    for(auto pos : positions)
    {
        Chunk* newChunk = GetChunk(WorldCoordToChunkCoord(pos));

        if(newChunk != nullptr && newChunk->GetPosition() != chunk->GetPosition())
        {
            //found a different chunk. Tell it to re-update its VBOs
            newChunk->MustReUpdate();
        }
    }


}

void World::Update(glm::mat4 projection)
{
    this->projection = projection;

    //place block
    if(Input::GetMouseButtonPressed(0))
    {
        Camera::DisableCurser();
        PlaceBlock();
    }
    if(Input::GetKeyPressed(KeyCode::SPACE))
    {
        PlaceBlock();
    }
    //remove block
    if(Input::GetMouseButtonPressed(1) || Input::GetKeyPressed(KeyCode::R))
    {
        RemoveBlock();
    }
    //remove area
    if(Input::GetKeyPressed(KeyCode::E))
    {
        RemoveArea();
    }

    if(Input::GetKeyPressed(KeyCode::Q))
    {
        PlaceArea();
    }
}



void World::AddChunk(glm::ivec2 chunkPosition, int blockType)
{
    chunks[chunkPosition] = new Chunk(glm::ivec2(chunkPosition.x * CHUNK_SIZE_X, chunkPosition.y * CHUNK_SIZE_Z), this, blockType);
}

void World::Render(Shader* shader)
{
    for(auto chunk : chunks)
    {
        chunk.second->Render(shader);
    }
}

Chunk* World::GetChunk(glm::ivec2 chunkCoord)
{
    if(chunks.find(chunkCoord) != chunks.end())
    {
        return chunks[chunkCoord];
    }
    else
    {
        return nullptr;
    }
}

Block* World::GetBlock(glm::ivec3 worldCoords)
{
    Chunk* chunk = GetChunk(WorldCoordToChunkCoord(worldCoords));

    if(chunk != nullptr)
    {
        return chunk->GetBlock(LocalizePoint(worldCoords));
    }
    else
    {
        return nullptr;
    }
}

//accommodates for mod ignoring negatives
int CustomMod(int num, int mod)
{
    return abs(num % mod);
    if(num < 0)
    {
        return mod + (num % mod) - 1;
        //return mod + (num % mod);
    }
    else
    {
        return num % mod;
    }
}

glm::ivec3 World::LocalizePoint(glm::ivec3 point)
{
    return glm::ivec3(CustomMod(point.x, CHUNK_SIZE_X), CustomMod(point.y, CHUNK_SIZE_Y), CustomMod(point.z, CHUNK_SIZE_Z));
}

glm::ivec2 World::WorldCoordToChunkCoord(glm::ivec3 worldCoord)
{
    
    return glm::ivec2(floor(worldCoord.x / (double)CHUNK_SIZE_X), floor(worldCoord.z / (double)CHUNK_SIZE_Z));
}

std::string World::GetPlacementBlockName()
{
    switch(placementBlock)
    {
        case cobble:
            return "cobble";
            break;
        case air:
            return "air";
            break;
        case light:
            return "light " + std::to_string(LightHandler::GetTotalLightsInUse()) + "/" + std::to_string(MAX_LIGHTS);
            break;
        case grass:
            return "grass";
            break;
        case diamond:
            return "diamond";
            break;
        case stone:
            return "stone";
            break;
        default:
            return "Not implemented";
            break;
    }
}

void World::ChangePlacementBlock(BlockType block)
{
    placementBlock = block;
}

void World::PlaceBlock()
{


    float x = 0.5f;
    float y = 0.5f;


    glm::vec3 position = Camera::GetPosition();

    glm::vec3 screenMiddle = glm::vec3(x, y, 1.0f);
    glm::vec3 pos = glm::unProject(screenMiddle, Camera::GetView(), projection, glm::vec4(0, 0, 1, 1));

    glm::vec3 dir = glm::normalize(pos) * 0.025f;

    for(int i = 0; i < 1000; ++i)
    {
        position += dir;
        Block* block = GetBlock(position);

        if(block != nullptr && block->Exists())
        {
            //go back one because the raycast just hit a block.
            position -= dir;
            AddBlock(placementBlock, position);
            break;
        }

        
    }

    
}

void World::RemoveBlock()
{
    glm::vec3 screenMiddle = glm::vec3(Window::GetWidth() / 2.0f, Window::GetHeight() / 2.0f, 1.0f);
    glm::vec3 pos = glm::unProject(screenMiddle, Camera::GetView(), projection, glm::vec4(0, 0, Window::GetWidth(), Window::GetHeight()));
    glm::vec3 dir = glm::normalize(pos) * 0.25f;
    glm::vec3 position = Camera::GetPosition();

    for(int i = 0; i < 100; ++i)
    {
        position += dir;
        Block* block = GetBlock(position);

        if(block != nullptr && block->Exists())
        {
            //add air block where there was a block
            AddBlock(air, position);
            break;
        }
        
    }
}

void World::RemoveArea()
{
    glm::ivec3 pos = Camera::GetPosition();


    for(int x = pos.x - 8; x < pos.x + 8; ++x)
    {
        for(int y = pos.y - 16; y < pos.y + 16; ++y)
        {
            for(int z = pos.z - 8; z < pos.z + 8; ++z)
            {
                AddBlock(air, glm::ivec3(x, y, z));
            }
        }
    }

}

void World::PlaceArea()
{
    glm::ivec3 pos = Camera::GetPosition();

    BlockType blockType = placementBlock;

    if(blockType == light)
    {
        blockType = stone;
    }

    pos.y-=2;


    for(int x = pos.x - 8; x < pos.x + 8; ++x)
    {
        for(int y = pos.y - 16; y < pos.y; ++y)
        {
            for(int z = pos.z - 8; z < pos.z + 8; ++z)
            {
                AddBlock(blockType, glm::ivec3(x, y, z));
            }
        }
    }
}