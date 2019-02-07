#include "Entity.h"
#include <string.h>


Entity::Entity(std::string fileName, int xpos, int ypos, bool useTrans, int width, int height, int numberOfFrames, int numberOfLayers) : Object( fileName, xpos, ypos, useTrans, width, height, numberOfFrames, numberOfLayers)
{
}
Entity::Entity(std::string fileName, int xpos, int ypos, bool useTrans, int width, int height, int numberOfFrames) : Object(fileName, xpos, ypos, useTrans, width, height, numberOfFrames)
{
}
Entity::Entity(std::string fileName, int xpos, int ypos, bool useTrans, int width, int height) : Object(fileName, xpos, ypos, useTrans, width, height)
{
}
Entity::Entity(std::string fileName, int xpos, int ypos, bool useTrans) : Object(fileName, xpos, ypos, useTrans)
{
}



Entity::~Entity()
{
}

void Entity::e_update() {
	
	o_update();
}
