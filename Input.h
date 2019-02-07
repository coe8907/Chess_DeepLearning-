#pragma once
class Input
{
	
protected:
	struct pos{
		int x = 0; 
		int y = 0;
	};
	
	struct keys {
		bool right = false;
		bool left = false;
		bool up = false;
		bool down = false;
		bool esc = false;
	};
	pos getmousepos();
	
	

public:
	keys I_Update();
	pos last_click;
	void clear_last_click() { last_click.x - 10; last_click.y = -10; }
	Input();
	~Input();
	
};

