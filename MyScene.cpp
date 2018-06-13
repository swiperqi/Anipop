#include "MyScene.h"

USING_NS_CC;

std::vector<Position*> stage;
std::vector<int> num;
int n = 0;
Scene* MyScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MyScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MyScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	int x = -180, y = -180;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			pos[i][j]=Point(origin.x + visibleSize.width / 2 + x, origin.y + visibleSize.height / 2 + y);

			x += 50;
		}
		x = -180;
		y += 50;
	}

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(MyScene::menuCloseCallback, this));

	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	auto label = LabelTTF::create("Link", "Arial", 24);
	label->setColor(ccc3(0,0,0));
	// position the label on the center of the screen
	label->setPosition(Point(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 1);

	label = LabelTTF::create("Grade:0", "Arial", 18);
	label->setColor(ccc3(0, 0, 0));
	// position the label on the center of the screen
	label->setPosition(Point(origin.x + visibleSize.width / 2 - 100,
		origin.y + visibleSize.height - label->getContentSize().height - 50));

	// add the label as a child to this layer
	this->addChild(label, 1);

	label = LabelTTF::create("Step:0", "Arial", 18);
	label->setColor(ccc3(0, 0, 0));
	// position the label on the center of the screen
	label->setPosition(Point(origin.x + visibleSize.width / 2 + 100,
		origin.y + visibleSize.height - label->getContentSize().height - 50));

	// add the label as a child to this layer
	this->addChild(label, 1);

	// add "HelloWorld" splash screen"

	auto sprite = Sprite::create("llkbg/llkbg2.png");

	// position the sprite on the center of the screen
	sprite->setPosition(origin.x + visibleSize.width / 2,origin.y + visibleSize.height/2);

	// add the sprite as a child to this layer
	this->addChild(sprite, 0);

	int a;
	char name[30];
	srand(time(NULL));
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			a = rand() % 15 + 1;
			sprintf(name, "llk/llk%d.png", a);

			Position *p=new Position(pos[i][j], name);
			stage.push_back(p);

			// create menu, it's an autorelease object
			menu = Menu::create(p->GetPic(), NULL);
			menu->setPosition(Point::ZERO);
			this->addChild(menu, 1);
		}

	}

	this->scheduleUpdate();

	return true;
}

void MyScene::update(float dt)
{
	
	if (Position::flag == 2)
	{
		for (int i = 0; i < stage.size(); i++)
		{
			if (stage[i]->getSwap() == 1)
			{
				num.push_back(i);
				n++;
			}
		}

		if (n == 2)
		{
			cocos2d::MoveTo* move1 = cocos2d::MoveTo::create(0.3f, stage[num[0]]->GetPos());
			cocos2d::MoveTo* move2 = cocos2d::MoveTo::create(0.3f, stage[num[1]]->GetPos());

			stage[num[0]]->GetPic()->runAction(move2);
			stage[num[1]]->GetPic()->runAction(move1);

			Point po = stage[num[0]]->GetPos();
			stage[num[0]]->setPos(stage[num[1]]->GetPos());
			stage[num[1]]->setPos(po);

			stage[num[0]]->initSwap();
			stage[num[1]]->initSwap();

			num.clear();

			n = 0;
		}
		Position::flag = 0;
	}
}

void MyScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
