#include "Position.h"

int Position::flag = 0;

Position::Position(cocos2d::Point pos, std::string name)
{
	this->pos = pos;
	this->name = name;
	pic = cocos2d::MenuItemImage::create(
		name,
		name,
		CC_CALLBACK_1(Position::move, this));
	pic->setPosition(pos);
	swap = 0;
}

cocos2d::MenuItemImage* Position::GetPic()
{
	return pic;
}

void Position::move(cocos2d::Ref* pSender)
{
	if (swap == 0)
	{
		swap = 1;
		flag++;
	}
	else
	{
		swap = 0;
		flag = 3;
	}
}

Position::~Position()
{
}

cocos2d::Point Position::GetPos()
{
	return pos;
}

void Position::setPos(cocos2d::Point pos)
{
	this->pos = pos;
}

void Position::initSwap()
{
	this->swap = 0;
}

int Position::getSwap()
{
	return swap;
}

std::string Position::getName()
{
	return name;
}

void Position::setName(std::string name)
{
	this->name = name;
}

void Position::resetPic(std::string name, cocos2d::Point pos)
{
	pic = cocos2d::MenuItemImage::create(
		name,
		name,
		CC_CALLBACK_1(Position::move, this));
	pic->setPosition(pos);
}