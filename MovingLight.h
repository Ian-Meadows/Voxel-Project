#ifndef MOVING_LIGHT_H
#define MOVING_LIGHT_H
#include "Light.h"
#include "Time.h"

class MovingLight : public Light
{
public: 
    MovingLight(glm::vec3 position);
    ~MovingLight();

    void Update() override;

    void ChangeOffset(glm::vec3 newOffset);

private:
    glm::vec3 offset;
};

#endif