#pragma once
#include "Object.h"
class Entity :
	public Object, public Input
{
public:
	Entity();
	Entity(std::string fileName, int xpos, int ypos, bool useTrans, int width, int height, int numberOfFrames, int numberOfLayers);
	Entity(std::string fileName, int xpos, int ypos, bool useTrans, int width, int height, int numberOfFrames);
	Entity(std::string fileName, int xpos, int ypos, bool useTrans, int width, int height);
	Entity(std::string fileName, int xpos, int ypos, bool useTrans);
	~Entity();
	void e_update();
	void GetInput();
};

