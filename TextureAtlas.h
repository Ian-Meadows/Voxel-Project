#ifndef TEXTURE_ATLAS_H
#define TEXTURE_ATLAS_H
#include "OpenGL_Includer.h"
#include <vector>
#include <string>


#include "ErrorHandler.h"

struct TileImage
{
    //paths
    std::string texture, normal, specular;
    TileImage(std::string texture, std::string normal, std::string specular)
    {
        this->texture = texture;
        this->normal = normal;
        this->specular = specular;
    }
};

class TextureAtlas
{
public:
    TextureAtlas(int imageSizes, int spacing);
    TextureAtlas(int imageSizes, int spacing, std::vector<TileImage> tiles);
    ~TextureAtlas();

    void AddTile(TileImage tile);
    void AddTiles(std::vector<TileImage> tiles);

    //build image using all texture paths given
    void Build();

    //compress image into a 1D array
    char* CompressTexture(int* sizeOut);
    char* CompressNormal(int* sizeOut);
    char* CompressSpecular(int* sizeOut);

    void Load(GLenum texture, GLenum normal, GLenum specular);

    unsigned int GetID();
    int GetTotalImages() const 
    {
        return totalImages;
    }
    int GetImageSizes() const 
    {
        return imageSizes;
    }
    int GetSpacing() const
    {
        return spacing;
    }

private:
    bool isBuilt = false;
    unsigned int ID, normalID, specularID;
    std::vector<TileImage> tiles;
    int imageSizes, spacing;

    int imageWidth;
    int imageHeight;
    int totalImages;
    int imagesInLength;
    char*** image = nullptr;
    char*** normalImage = nullptr;
    char*** specularImage = nullptr;

};

#endif