#ifndef BLOCK_LIGHT_H
#define BLOCK_LIGHT_H
#include "Light.h"

class BlockLight : public Light
{
public: 
    BlockLight(glm::vec3 position);
    ~BlockLight();

    void Remove();
    bool Exists() const { return exists; }

private:
    bool exists = true;
};


#endif