#include "Object.h"
#include <iostream>
#include "include\SDL.h"


Object::Object(std::string fileName, int xpos, int ypos,bool useTrans = false, int width = -1, int height= -1, int numberOfFrames = -1 ,int numberOfLayers = -1) : bitmaps::bitmaps(fileName, xpos, ypos, width, height, useTrans,numberOfFrames,numberOfLayers)
{
	  
}
Object::Object(std::string fileName, int xpos, int ypos, bool useTrans = false, int width = -1, int height = -1, int numberOfFrames = -1) : bitmaps::bitmaps(fileName, xpos, ypos, width, height, useTrans,numberOfFrames)
{

}
Object::Object(std::string fileName, int xpos, int ypos, bool useTrans = false, int width = -1, int height = -1) : bitmaps::bitmaps(fileName, xpos, ypos,width,height, useTrans)
{

}
Object::Object(std::string fileName, int xpos, int ypos, bool useTrans = false) : bitmaps::bitmaps(fileName, xpos, ypos, useTrans)
{

}

Object::Object(std::string fileName, int xpos, int ypos, int width = -1, int height = -1) : bitmaps::bitmaps(fileName, xpos, ypos, width, height)
{

}

Object::Object(std::string fileName, int xpos, int ypos, int width = -1, int height = -1,bool alpha = false) : bitmaps::bitmaps(fileName, xpos, ypos, width, height,alpha)
{

}


void Object::o_update()
{
	setx (vex);
	sety (vey); 



	if (vex > 0) {
		if (vex - drag < 0) {
			vex = 0;
			
		}
		else {
			vex -= drag;
		}
	}
	else if (vex < 0) {
		if (vex + drag > 0) {
			vex = 0;
		}
		else {
			vex += drag;
		}
	}




	if (vey > 0) {
		if (vey - drag < 0) {
			vey = 0;
		}else
		vey -= drag;
	}
	else if (vey < 0) {
		if (vey + drag > 0) {
			vey = 0;
		}else
		vey += drag;
	}
}


void Object::paint()
{
	draw();
}
void Object::setdrag(int i) {
	drag = i;
}

void Object::apply_force(int ammout, int plane)
{
	if (plane == 0) {
		if (vex < 10 && vex > -10) {
			vex += ammout;
		}
	}
	else {
		if (vey < 5 && vey > -5)
			vey += ammout;
	}


}

bool Object::basic_col() {

	return false;
}
bool Object::fullBoxcolison(Object * target) {
	if (testcolision_T_L(target) || testcolision_T_R(target) ||
		testcolision_B_L(target)|| testcolision_B_R(target)) {
		return true;
	}
	return false;
}
bool Object::testcolision_T_L (Object * target) {
	if (pos.m_x >= target->pos.m_x && pos.m_x <= target->pos.m_x + target->pos.m_w) {
		if (pos.m_y >= target->pos.m_y && pos.m_y <= target->pos.m_y + target->pos.m_h) {
			return true;
		}
	}
	return false;
}
bool Object::testcolision_T_R(Object * target) {
	if (pos.m_x+pos.m_w >= target->pos.m_x && pos.m_x + pos.m_w <= target->pos.m_x + target->pos.m_w) {
		if (pos.m_y >= target->pos.m_y && pos.m_y <= target->pos.m_y + target->pos.m_h) {
			return true;
		}
	}
	return false;
}
bool Object::testcolision_B_L(Object * target) {
	if (pos.m_x >= target->pos.m_x && pos.m_x <= target->pos.m_x + target->pos.m_w) {
		if (pos.m_y + pos.m_h >= target->pos.m_y && pos.m_y + pos.m_h <= target->pos.m_y + target->pos.m_h) {
			return true;
		}
	}
	return false;
}
bool Object::testcolision_B_R(Object * target) {
	if (pos.m_x + pos.m_w >= target->pos.m_x && pos.m_x + pos.m_w <= target->pos.m_x + target->pos.m_w) {
		if (pos.m_y + pos.m_h >= target->pos.m_y && pos.m_y + pos.m_h <= target->pos.m_y + target->pos.m_h) {
			return true;
		}
	}
	return false;
}
bool Object::pixelColision_top(Object * target) {
	
	return false;
}


Object::~Object()
{

}
