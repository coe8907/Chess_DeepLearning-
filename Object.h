#pragma once
#include "bitmaps.h"
#include "Input.h"
class Object :
	public bitmaps 
{
private:
	int drag = 1;
	int vex,vey = 0;

public:
	
	Object(std::string fileName, int xpos, int ypos, bool useTrans);
	Object(std::string fileName, int xpos, int ypos, int width, int height);
	Object(std::string fileName, int xpos, int ypos, int width, int height, bool alpha);
	Object(std::string fileName, int xpos, int ypos, bool useTrans, int width, int height);
	Object(std::string fileName, int xpos, int ypos, bool useTrans, int width, int height, int numberOfFrames);
	Object(std::string fileName, int xpos, int ypos,bool useTrans, int width, int height, int numberOfFrames, int numberOfLayers);
	~Object();
	void o_update();
	void paint();
	void setdrag(int i);
	void apply_force(int ammout, int die);
	bool basic_col();
	bool fullBoxcolison(Object * target);
	bool testcolision_T_L(Object * target);
	bool testcolision_T_R(Object * target);
	bool testcolision_B_L(Object * target);
	bool testcolision_B_R(Object * target);

	bool pixelColision_top(Object * target);
	
};

