#include "MyScene.h"

USING_NS_CC;

std::vector<std::vector<Position*>> positionStage;
std::vector<int> melti;
std::vector<int> meltj;
std::vector<Position*> stage;
std::vector<int> numi;
std::vector<int> numj;
bool sh = true;

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
	x = -180;
	for (int i = 0; i < 8; i++)
	{
		spos[i] = Point(origin.x + visibleSize.width / 2 + x, origin.y + visibleSize.height + 100);
		x += 50;
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

	auto sprite = Sprite::create("llkbg/llkbg1.png");

	// position the sprite on the center of the screen
	sprite->setPosition(origin.x + visibleSize.width / 2,origin.y + visibleSize.height/2);

	// add the sprite as a child to this layer
	this->addChild(sprite, 0);

	auto ku = Sprite::create("llk/kuang.png");
	ku->setPosition(0,0);
	// add the sprite as a child to this layer
	this->addChild(ku, 2, 101);

	Hide* hide = Hide::create();
	ku->runAction(hide);

	int a;
	char name[30];
	srand(time(NULL));
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			a = rand() % 7 + 1;
			sprintf(name, "llk/llk%d.png", a);

			Position *p=new Position(pos[i][j], name);
			stage.push_back(p);

			// create menu, it's an autorelease object
			menu = Menu::create(p->GetPic(), NULL);
			menu->setPosition(Point::ZERO);
			this->addChild(menu, 1);
		}
		positionStage.push_back(stage);
		stage.clear();
	}

	melt();
	

	this->scheduleUpdate();

	return true;
}

void MyScene::update(float dt)
{
	auto ku = getChildByTag(101);
	if (Position::flag == 1&&sh)
	{
		for (int i = 0; i < positionStage.size(); i++)
		{
			for (int j = 0; j < positionStage[i].size(); j++)
			{
				if (positionStage[i][j]->getSwap() == 1)
				{
					MoveTo* move = MoveTo::create(0, positionStage[i][j]->GetPos());
					auto hide = Sequence::create(DelayTime::create(0.01f), Show::create(), NULL);
					ku->runAction(Spawn::create(move, hide, NULL));
					sh = false;
				}
			}
		}
	}
	if (Position::flag == 2)
	{
		for (int i = 0; i < positionStage.size(); i++)
		{
			for (int j = 0; j < positionStage[i].size(); j++)
			{
				if (positionStage[i][j]->getSwap() == 1)
				{
					numi.push_back(i);
					numj.push_back(j);
				}
			}
		}

		if ((numi[0] == numi[1] && abs(numj[0] - numj[1]) == 1) || (numj[0] == numj[1] && abs(numi[0] - numi[1]) == 1))
		{
			cocos2d::MoveTo* move1 = cocos2d::MoveTo::create(0.3f, positionStage[numi[0]][numj[0]]->GetPos());
			cocos2d::MoveTo* move2 = cocos2d::MoveTo::create(0.3f, positionStage[numi[1]][numj[1]]->GetPos());

			positionStage[numi[0]][numj[0]]->GetPic()->runAction(Sequence::create(move2, DelayTime::create(0.3f), NULL));
			positionStage[numi[1]][numj[1]]->GetPic()->runAction(Sequence::create(move1, DelayTime::create(0.3f), NULL));

			Point po = positionStage[numi[0]][numj[0]]->GetPos();
			positionStage[numi[0]][numj[0]]->setPos(positionStage[numi[1]][numj[1]]->GetPos());
			positionStage[numi[1]][numj[1]]->setPos(po);

			positionStage[numi[0]][numj[0]]->initSwap();
			positionStage[numi[1]][numj[1]]->initSwap();

			std::swap(positionStage[numi[0]][numj[0]], positionStage[numi[1]][numj[1]]);

			if (!melt())
			{
				cocos2d::MoveTo* move3 = cocos2d::MoveTo::create(0.3f, positionStage[numi[0]][numj[0]]->GetPos());
				cocos2d::MoveTo* move4 = cocos2d::MoveTo::create(0.3f, positionStage[numi[1]][numj[1]]->GetPos());

				positionStage[numi[0]][numj[0]]->GetPic()->runAction(Sequence::create(DelayTime::create(0.3f), move4, NULL));
				positionStage[numi[1]][numj[1]]->GetPic()->runAction(Sequence::create(DelayTime::create(0.3f), move3, NULL));

				po = positionStage[numi[0]][numj[0]]->GetPos();
				positionStage[numi[0]][numj[0]]->setPos(positionStage[numi[1]][numj[1]]->GetPos());
				positionStage[numi[1]][numj[1]]->setPos(po);

				positionStage[numi[0]][numj[0]]->initSwap();
				positionStage[numi[1]][numj[1]]->initSwap();

				std::swap(positionStage[numi[0]][numj[0]], positionStage[numi[1]][numj[1]]);
			}

			numi.clear();
			numj.clear();
		}
		else
		{
			positionStage[numi[0]][numj[0]]->initSwap();
			positionStage[numi[1]][numj[1]]->initSwap();

			numi.clear();
			numj.clear();
		}
		
		Hide* hide = Hide::create();
		ku->runAction(hide);
		sh = true;
		Position::flag = 0;
	}
	if (Position::flag == 3)
	{
		Hide* hide = Hide::create();
		ku->runAction(hide);
		sh = true;
		Position::flag = 0;
	}
	
}

bool MyScene::melt()
{
	for (int i = 0; i < positionStage.size(); i++)
	{
		for (int j = 0; j < positionStage[i].size(); j++)
		{
			if (j < positionStage[i].size() - 2)
			{
				if (positionStage[i][j]->getName() == positionStage[i][j + 1]->getName() && positionStage[i][j]->getName() == positionStage[i][j + 2]->getName())
				{
					pushMeltPos(i, j);
					pushMeltPos(i, j + 1);
					pushMeltPos(i, j + 2);

					if (j + 3 < positionStage[i].size() && positionStage[i][j]->getName() == positionStage[i][j + 3]->getName())
					{
						pushMeltPos(i, j + 3);
						if (j + 4 < positionStage[i].size() && positionStage[i][j]->getName() == positionStage[i][j + 4]->getName())
						{
							pushMeltPos(i, j + 4);
						}
					}					
				}
			}

			if (i < positionStage.size() - 2)
			{
				if (positionStage[i][j]->getName() == positionStage[i+1][j]->getName() && positionStage[i][j]->getName() == positionStage[i + 2][j]->getName())
				{
					pushMeltPos(i, j);
					pushMeltPos(i + 1, j);
					pushMeltPos(i + 2, j);

					if (i + 3 < positionStage.size() && positionStage[i][j]->getName() == positionStage[i + 3][j]->getName())
					{
						pushMeltPos(i + 3, j);
						if (i + 4 < positionStage.size() && positionStage[i][j]->getName() == positionStage[i + 4][j]->getName())
						{
							pushMeltPos(i + 4, j);
						}
					}
				}
			}
		}
	}

	if (melti.size() != 0)
	{
		for (int i = 0; i < melti.size(); i++)
		{
			ScaleTo* m = ScaleTo::create(3.0f, 0.5f);

			ScaleTo* m1 = ScaleTo::create(0.0f, 1.0f);
			positionStage[melti[i]][meltj[i]]->GetPic()->runAction(Sequence::create(DelayTime::create(0.3f), m, DelayTime::create(0.3f),m1, NULL));
		}
		
		for (int i = 0; i < positionStage.size(); i++)
		{
			for (int j = 0; j < positionStage[i].size(); j++)
			{
				for (int k = 0; k < melti.size(); k++)
				{
					if (i == melti[k] && j == meltj[k])
					{
						positionStage[i][j]->setName("null");
					}
				}
			}
		}

		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (positionStage[j][i]->getName() == "null")
				{
					for (int k = j; k < 8; k++)
					{
						if (positionStage[k][i]->getName() != "null")
						{
							Point p = positionStage[k][i]->GetPos();
							positionStage[k][i]->setPos(positionStage[j][i]->GetPos());
							positionStage[j][i]->setPos(p);
							std::swap(positionStage[k][i], positionStage[j][i]);
							break;
						}
					}
				}
			}
		}
		int a;
		char name[30];
		srand(time(NULL));
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (positionStage[i][j]->getName() == "null")
				{
					a = rand() % 7 + 1;
					sprintf(name, "llk/llk%d.png", a);
					positionStage[i][j]->setName(name);

					MoveTo* move = MoveTo::create(0.0f, spos[j]);

					positionStage[i][j]->GetPic()->runAction(Sequence::create(DelayTime::create(3.0f), move, NULL));

					positionStage[i][j]->resetPic(name, spos[j]);

					auto menu = Menu::create(positionStage[i][j]->GetPic(), NULL);
					menu->setPosition(Point::ZERO);
					this->addChild(menu, 1);
				}
			}
		}

		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				MoveTo* move = MoveTo::create(1.0f, positionStage[i][j]->GetPos());
				positionStage[i][j]->GetPic()->runAction(Sequence::create(DelayTime::create(3.0f), move,NULL));
			}
		}


		melti.clear();
		meltj.clear();
		return true;
	}
	else
	{
		return false;
	}
}

void MyScene::pushMeltPos(int i, int j)
{
	int k;
	for (k = 0; k < melti.size(); k++)
	{
		if (i == melti[k] && j == meltj[k])
		{
			break;
		}
	}
	if (k == melti.size())
	{
		melti.push_back(i);
		meltj.push_back(j);
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
