#ifndef BLOCK_H
#define BLOCK_H
//#include "../OpenGL_Includer.h"
#include "../glm/glm.hpp"

#define VERTEX_MAX 108
#define TEX_COORDS_MAX 72
#define TOTAL_TILES 6


class Chunk;
class Block
{
public:
    Block(glm::ivec3 position);
    virtual ~Block();
    glm::ivec3 position;

    virtual float* GetVertices() final;
    virtual float* GetTexCoords() final;
    virtual int* GetTileIndex() final;
    virtual int GetNeighbors(Chunk* chunk) final;

    virtual bool IsTransparent();

    virtual bool Exists();

protected:
    virtual int TopTile();
    virtual int BottomTile();
    virtual int LeftTile();
    virtual int RightTile();
    virtual int FrontTile();
    virtual int BackTile();

    

private:



    void LoadArray(float* main, float* addition, int additionSize, int* currentIndex, bool multiplyPosition);
    //vertices
    float backVertices[18] = 
    {

       0.5, 0.5, -0.5, //upper right
       0.5, -0.5, -0.5, //bottom right
       -0.5, -0.5, -0.5, //bottom left
        
        -0.5, -0.5, -0.5, //bottom left
        -0.5, 0.5, -0.5,//upper left
        0.5, 0.5, -0.5 //upper right
        
    };
    float frontVertices[18] = 
    {
        -0.5, -0.5, 0.5, //bottom left
        0.5, -0.5, 0.5, //bottom right
        0.5, 0.5, 0.5, //upper right

        0.5, 0.5, 0.5, //upper right
        -0.5, 0.5, 0.5,//upper left
        -0.5, -0.5, 0.5 //bottom left
        
    };

    float topVertices[18] = 
    {
        0.5f,  0.5f,  0.5f, //upper right
         0.5f,  0.5f, -0.5f, //bottom right
         -0.5f,  0.5f, -0.5f, //bottom left
         
        -0.5f,  0.5f, -0.5f,  //bottom left
        -0.5f,  0.5f,  0.5f, //upper left
         0.5f,  0.5f,  0.5f //upper right
        
        
    };

    float bottomVertices[18] = 
    {
        -0.5f, -0.5f, -0.5f,  
         0.5f, -0.5f, -0.5f,  
         0.5f, -0.5f,  0.5f,
           
         0.5f, -0.5f,  0.5f,  
        -0.5f, -0.5f,  0.5f,  
        -0.5f, -0.5f, -0.5f  
    };

    float leftVertices[18] = 
    {
        -0.5f,  0.5f,  0.5f,  
        -0.5f,  0.5f, -0.5f,  
        -0.5f, -0.5f, -0.5f, 

        -0.5f, -0.5f, -0.5f,  
        -0.5f, -0.5f,  0.5f,  
        -0.5f,  0.5f,  0.5f  
    };

    float rightVertices[18] = 
    {
        0.5f, -0.5f, -0.5f, //upper right
         0.5f,  0.5f, -0.5f, //bottom right
         0.5f,  0.5f,  0.5f,  //bottom left
         
        0.5f,  0.5f,  0.5f, //bottom left
        0.5f, -0.5f,  0.5f, //upper left
         0.5f, -0.5f, -0.5f //upper right
         
         
    };


    //texture coordinates
    float topTexCoords[12] = 
    {
        0, 0,
        1, 0,
        1, 1,

        1, 1,
        0, 1,
        0, 0
    };

};


#endif