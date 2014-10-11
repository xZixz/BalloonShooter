/*
 * ResultScene.cpp
 *
 *  Created on: Sep 25, 2014
 *      Author: dudu
 */

#include "ResultScene.h"
#include "MainMenuScene.h"

#define RESULT_BG_ZORDER 1
#define YOU_WIN_TEXT_ZORDER 2
#define YOU_FAILED_TEXT_ZORDER 2
#define SCORE_BASE_ZORDER 2
#define SCORE_TEXT_ZORDER 3
#define MENU_ZORDER 3
#define STAR_BG_ZORDER 3

#define YOU_WIN_TEXT_POS Vec2(471,1416)
#define YOU_FAILED_TEXT_POS Vec2(478,1416)
#define TO_MENU_BTN_POS Vec2(263,688)
#define NEXT_LEVEL_BTN_POS Vec2(685,688)
#define WIN_RETRY_LEVEL_BTN_POS Vec2(472,440)
#define FAILED_RETRY_LEVEL_BTN_POS Vec2(685,688)
#define SCORE_BASE_POS Vec2(478,948)
#define SCORE_TEXT_POS Vec2(414,951)
#define STAR_1_POS Vec2(304,1150)
#define STAR_2_POS Vec2(478,1211)
#define STAR_3_POS Vec2(648,1150)

#define TO_MENU_BTN_TAG 10
#define NEXT_LEVEL_BTN_TAG 11
#define RETRY_LEVEL_BTN_TAG 12

Scene* ResultScene::createScene(bool is_win, int score, int star_num){
	Scene* scene = Scene::create();
	ResultScene* layer = ResultScene::create(is_win,score,star_num);
	scene->addChild(layer);
	return scene;
}

ResultScene* ResultScene::create(bool is_win, int score, int star_num){
	ResultScene* resultScene = new ResultScene();
	if (resultScene && resultScene->init(is_win,score,star_num)){
		resultScene->autorelease();
		return resultScene;
	}
	CC_SAFE_DELETE(resultScene);
	return nullptr;
}

bool ResultScene::init(bool is_win, int score, int star_num){
	if (Layer::init()){
		is_win_ = is_win;
		score_ = score;
		star_num_ = star_num;

		Size winsize = Director::getInstance()->getWinSize();

		Sprite* bg = Sprite::create("result_bg.png");
		bg->setPosition(winsize/2);
		addChild(bg,RESULT_BG_ZORDER);

		Menu* menu = Menu::create();
		menu->setPosition(Vec2::ZERO);
		addChild(menu,MENU_ZORDER);

		MenuItemImage* to_menu_btn = MenuItemImage::create("to_menu_btn.png","to_menu_btn.png",CC_CALLBACK_1(ResultScene::btnCallback,this));
		to_menu_btn->setTag(TO_MENU_BTN_TAG);
		to_menu_btn->setPosition(TO_MENU_BTN_POS);
		menu->addChild(to_menu_btn);

		MenuItemImage* retry_level_btn = MenuItemImage::create("retry_level_btn.png","retry_level_btn.png",CC_CALLBACK_1(ResultScene::btnCallback,this));
		retry_level_btn->setTag(RETRY_LEVEL_BTN_TAG);
		menu->addChild(retry_level_btn);

		Sprite* score_base_sprite = Sprite::create("score_base.png");
		score_base_sprite->setPosition(SCORE_BASE_POS);
		addChild(score_base_sprite,SCORE_BASE_ZORDER);

//		Label* score_text = Label::createWithTTF("0","Marker Felt.ttf",30);
//		score_text->setAnchorPoint(Vec2(0.0f,0.5f));
//		score_text->setPosition(SCORE_TEXT_POS);
//		addChild(score_text,SCORE_TEXT_ZORDER);

		Sprite* star_1_sprite = Sprite::create("result_star_bg.png");
		star_1_sprite->setPosition(STAR_1_POS);
		addChild(star_1_sprite,STAR_BG_ZORDER);

		if (star_num_ >= 1){
			Sprite* star = Sprite::create("result_star.png");
			star->setPosition(star_1_sprite->getContentSize()/2);
			star_1_sprite->addChild(star);
		}

		Sprite* star_2_sprite = Sprite::create("result_star_bg.png");
		star_2_sprite->setPosition(STAR_2_POS);
		addChild(star_2_sprite,STAR_BG_ZORDER);

		if (star_num_ >= 2){
			Sprite* star = Sprite::create("result_star.png");
			star->setPosition(star_2_sprite->getContentSize()/2);
			star_2_sprite->addChild(star);
		}

		Sprite* star_3_sprite = Sprite::create("result_star_bg.png");
		star_3_sprite->setPosition(STAR_3_POS);
		addChild(star_3_sprite,STAR_BG_ZORDER);

		if (star_num_ >= 3){
			Sprite* star = Sprite::create("result_star.png");
			star->setPosition(star_3_sprite->getContentSize()/2);
			star_3_sprite->addChild(star);
		}

		// Win result
		if (is_win_){
			Sprite* you_win_sprite = Sprite::create("you_win.png");
			you_win_sprite->setPosition(YOU_WIN_TEXT_POS);
			addChild(you_win_sprite,YOU_WIN_TEXT_ZORDER);

			MenuItemImage* next_level_btn = MenuItemImage::create("next_level_btn.png","next_level_btn.png",CC_CALLBACK_1(ResultScene::btnCallback,this));
			next_level_btn->setTag(NEXT_LEVEL_BTN_TAG);
			next_level_btn->setPosition(NEXT_LEVEL_BTN_POS);
			menu->addChild(next_level_btn);

			retry_level_btn->setPosition(WIN_RETRY_LEVEL_BTN_POS);
		}

		// Fail result
		else {
			Sprite* you_failed_sprite = Sprite::create("you_failed.png");
			you_failed_sprite->setPosition(YOU_FAILED_TEXT_POS);
			addChild(you_failed_sprite,YOU_FAILED_TEXT_ZORDER);

			retry_level_btn->setPosition(FAILED_RETRY_LEVEL_BTN_POS);
		}

		return true;
	}
	return false;
}

void ResultScene::btnCallback(Ref* sender){
	MenuItem* btn = (MenuItem*)sender;
	int tag = btn->getTag();
	switch (tag){
		case TO_MENU_BTN_TAG:
			Director::getInstance()->replaceScene(MainMenuScene::createScene());
			break;
		case NEXT_LEVEL_BTN_TAG:

			break;
		case RETRY_LEVEL_BTN_TAG:

			break;
		default:
			break;
	}
}

ResultScene::ResultScene():
is_win_(false),
score_(0),
star_num_(0)
{
}

ResultScene::~ResultScene() {
}
