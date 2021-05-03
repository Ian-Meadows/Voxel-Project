#include "MovingLight.h"
#include "Debugger.h"


MovingLight::MovingLight(glm::vec3 position) : Light(position, true)
{
    offset = glm::vec3(position.x, position.y, position.z);
}
MovingLight::~MovingLight()
{

}

void MovingLight::ChangeOffset(glm::vec3 newOffset)
{
    this->offset = newOffset;
}

void MovingLight::Update()
{
    double x = Sin(Time::GetTime() * 100);
    double z = Cos(Time::GetTime() * 100);

    position.x = (x * 2) + offset.x;
    position.z = (z * 2) + offset.z;
    position.y = offset.y;
}