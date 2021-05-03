#include "TextureAtlas.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

TextureAtlas::TextureAtlas(int imageSizes, int spacing)
{
    this->imageSizes = imageSizes;
    this->spacing = spacing;
}
TextureAtlas::TextureAtlas(int imageSizes, int spacing, std::vector<TileImage> tiles)
{
    this->imageSizes = imageSizes;
    this->spacing = spacing;
    this->tiles.insert(this->tiles.end(), tiles.begin(), tiles.end());
}

TextureAtlas::~TextureAtlas()
{
    if (image != nullptr) 
    {
        for (int i = 0; i < imageWidth; i++) {
            for (int j = 0; j < imageHeight; j++) {
                delete[] image[i][j];
            }
            delete[] image[i];
        }
        delete[] image;
	}
    if(normalImage != nullptr)
    {
        for (int i = 0; i < imageWidth; i++) {
            for (int j = 0; j < imageHeight; j++) {
                delete[] normalImage[i][j];
            }
            delete[] normalImage[i];
        }
        delete[] normalImage;
    }
    if(specularImage != nullptr)
    {
        for (int i = 0; i < imageWidth; i++) {
            for (int j = 0; j < imageHeight; j++) {
                delete[] specularImage[i][j];
            }
            delete[] specularImage[i];
        }
        delete[] specularImage;
    }
	
}

void TextureAtlas::AddTile(TileImage tile)
{
    tiles.push_back(tile);
}
void TextureAtlas::AddTiles(std::vector<TileImage> tiles)
{
    this->tiles.insert(this->tiles.end(), tiles.begin(), tiles.end());
}

void TextureAtlas::Build()
{

    if(isBuilt)
    {
        ErrorHandler::Warning("Texture Atlas already built");
        return;
    }
    stbi_set_flip_vertically_on_load(true);  

    int total = tiles.size();
    int size = (int)ceil(sqrt((double)total));
    
    imageWidth = size * imageSizes + (size * spacing);
    imageHeight = size * imageSizes + (size * spacing);
    totalImages = size * size;
    imagesInLength = size;


    //init image in texture atlas
    image = new char**[imageWidth];
    normalImage = new char**[imageWidth];
    specularImage = new char**[imageWidth];
    for (int i = 0; i < imageWidth; i++) 
    {
        image[i] = new char*[imageHeight];
        normalImage[i] = new char*[imageHeight];
        specularImage[i] = new char*[imageHeight];
        for (int j = 0; j < imageHeight; j++) 
        {
            image[i][j] = new char[4];
            normalImage[i][j] = new char[4];
            specularImage[i][j] = new char[4];
        }
    }

    //init to 0
    for (int x = 0; x < imageWidth; x++) 
    {
        for (int y = 0; y < imageHeight; y++) 
        {
            for (int z = 0; z < 4; z++) 
            {
                image[x][y][z] = 0;
                normalImage[x][y][z] = 0;
                specularImage[x][y][z] = 0;
            }
        }
    }

    int width, height, nrChannels;

    //for width for loop
    int currentMaxWidth = imageSizes;
    int currentMaxHeight = imageSizes;
    int currentYStart = 0;
    int x = 0;
    int y = 0;

    for (int i = 0; i < total; i++) 
    {
        unsigned char *data = stbi_load(tiles[i].texture.c_str(), &width, &height, &nrChannels, 0);
        unsigned char *data_n = stbi_load(tiles[i].normal.c_str(), &width, &height, &nrChannels, 0);
        unsigned char *data_s = stbi_load(tiles[i].specular.c_str(), &width, &height, &nrChannels, 0);
        if (data == nullptr) 
        {
            std::cout << "failed to load texture " << tiles[i].texture << ". Cannot create texture atlas. returning."<<std::endl;
            return;
        }
        if (data_n == nullptr) 
        {
            std::cout << "failed to load normal map " << tiles[i].normal << ". Cannot create normal atlas. returning."<<std::endl;
            return;
        }
        if (data_s == nullptr) 
        {
            std::cout << "failed to load specular map " << tiles[i].specular << ". Cannot create specular atlas. returning."<<std::endl;
            return;
        }

        //textureAtlas->AddNewImageLocation(iFiles[i]->name, i);

        //std::cout << size << std::endl;
        int imageIndex = 0;

        //if image overflows and will be cut off
        if (x + width > imageWidth) 
        {
            currentMaxWidth = imageSizes;
            x = 0;
            currentMaxHeight += imageSizes + spacing;
            currentYStart += imageSizes + spacing;
            
        }
        
        for (; x < currentMaxWidth && x < imageWidth; x++) 
        {
            for (y = currentYStart; y < currentMaxHeight && y < imageHeight; y++) 
            {
                //rgba
                if (nrChannels == 4) 
                {
                    for (int z = 0; z < 4; z++) 
                    {
                        image[x][y][z] = data[imageIndex];
                        normalImage[x][y][z] = data_n[imageIndex];
                        specularImage[x][y][z] = data_s[imageIndex];
                        imageIndex++;
                    }
                }
                //rgb
                else if(nrChannels == 3)
                {
                    for (int z = 0; z < 3; z++) 
                    {
                        image[x][y][z] = data[imageIndex];
                        normalImage[x][y][z] = data_n[imageIndex];
                        specularImage[x][y][z] = data_s[imageIndex];
                        imageIndex++;
                    }
                    //set alpha
                    image[x][y][3] = 0xff;
                    normalImage[x][y][3] = 0xff;
                    specularImage[x][y][3] = 0xff;
                }
                else 
                {
                    std::cout << "what texture have you brought to this program? cannot make texture/normal/specular atlas. returning" << std::endl;
                    return;
                }
            }
        }
        x += spacing;
        if (currentMaxWidth >= imageWidth) 
        {
            currentMaxWidth = -spacing;
            x = 0;
            currentMaxHeight+= imageSizes + spacing;
            currentYStart += imageSizes + spacing;
        }
        currentMaxWidth += imageSizes + spacing;

        stbi_image_free(data);
        stbi_image_free(data_n);
        stbi_image_free(data_s);
    }

    //load texture
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int s;
    char* compressedImage = CompressTexture(&s);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, compressedImage);

    delete[] compressedImage;
    ErrorHandler::ErrCheck("texture atlas");

    //load normal
    glGenTextures(1, &normalID);
    glBindTexture(GL_TEXTURE_2D, normalID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    compressedImage = CompressNormal(&s);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, compressedImage);

    delete[] compressedImage;
    ErrorHandler::ErrCheck("normal atlas");


    //load specular
    glGenTextures(1, &specularID);
    glBindTexture(GL_TEXTURE_2D, specularID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    compressedImage = CompressSpecular(&s);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, compressedImage);

    delete[] compressedImage;
    ErrorHandler::ErrCheck("specular atlas");



}

void TextureAtlas::Load(GLenum texture, GLenum normal, GLenum specular)
{
    glActiveTexture(texture);
    glBindTexture(GL_TEXTURE_2D, ID);
    glActiveTexture(normal);
    glBindTexture(GL_TEXTURE_2D, normalID);
    glActiveTexture(specular);
    glBindTexture(GL_TEXTURE_2D, specularID);
}

char* TextureAtlas::CompressTexture(int* sizeOut)
{
    if (image == nullptr) {
		*sizeOut = 0;
		return nullptr;
	}

	int s = imageWidth * imageHeight * 4;
	*sizeOut = s;

	char* compressedImage = new char[s];

	int i = 0;
	for (int x = 0; x < imageWidth; x++) {
		for (int y = 0; y < imageHeight; y++) {
			for (int rgba = 0; rgba < 4; rgba++) {
				compressedImage[i] = image[x][y][rgba];
				i++;
			}
		}
	}

	return compressedImage;
}

char* TextureAtlas::CompressNormal(int* sizeOut)
{
    if (normalImage == nullptr) {
		*sizeOut = 0;
		return nullptr;
	}

	int s = imageWidth * imageHeight * 4;
	*sizeOut = s;

	char* compressedImage = new char[s];

	int i = 0;
	for (int x = 0; x < imageWidth; x++) {
		for (int y = 0; y < imageHeight; y++) {
			for (int rgba = 0; rgba < 4; rgba++) {
				compressedImage[i] = normalImage[x][y][rgba];
				i++;
			}
		}
	}

	return compressedImage;
}
char* TextureAtlas::CompressSpecular(int* sizeOut)
{
    if (specularImage == nullptr) {
		*sizeOut = 0;
		return nullptr;
	}

	int s = imageWidth * imageHeight * 4;
	*sizeOut = s;

	char* compressedImage = new char[s];

	int i = 0;
	for (int x = 0; x < imageWidth; x++) {
		for (int y = 0; y < imageHeight; y++) {
			for (int rgba = 0; rgba < 4; rgba++) {
				compressedImage[i] = specularImage[x][y][rgba];
				i++;
			}
		}
	}

	return compressedImage;
}


unsigned int TextureAtlas::GetID()
{
    return ID;
}
