#pragma once

#include "cocos2d.h"
#include <vector>

class Position
{
public:
	Position(cocos2d::Point pos,std::string name);
	~Position();
	cocos2d::Point GetPos();
	void move(cocos2d::Ref* pSender);
	cocos2d::MenuItemImage* GetPic();
	void picMove();
	void setPos(cocos2d::Point pos);
	void initSwap();
	int getSwap();
	static int flag;
	std::string getName();
	void setName(std::string name);
private:
	cocos2d::Point pos;
	cocos2d::MenuItemImage* pic;
	std::string name;
	int swap;
};
