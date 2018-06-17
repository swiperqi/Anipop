#ifndef __MYSCENE_SCENE_H__
#define __MYSCENE_SCENE_H__

#include "cocos2d.h"
#include "Position.h"

class MyScene : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	void update(float dt);

	bool melt();

	void pushMeltPos(int i, int j);

	// implement the "static create()" method manually
	CREATE_FUNC(MyScene);
private:
	cocos2d::Point pos[8][8];
};

#endif // __HELLOWORLD_SCENE_H__
