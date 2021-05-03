#include "BlockLight.h"

BlockLight::BlockLight(glm::vec3 position) : Light(position)
{

}
BlockLight::~BlockLight()
{

}

void BlockLight::Remove()
{
    exists = false;
}