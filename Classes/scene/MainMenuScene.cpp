/*
 * MainMenuScene.cpp
 *
 *  Created on: Sep 6, 2014
 *      Author: dudu
 */

#include "MainMenuScene.h"
#include "../model/GrowButton.h"
#include "../scene/GameScene.h"
#include "../scene/UniverseScene.h"

#define MAIN_MENU_BG_FILE "main_menu_bg.png"
#define MM_GATE_BTN "mm_gate_btn.png"
#define MM_GATE_TEXT "mm_gate_text.png"
#define MM_GATE_FIRE_1 "mm_gate_fire_1.png"
#define MM_GATE_FIRE_2 "mm_gate_fire_2.png"
#define MM_GATE_FIRE_3 "mm_gate_fire_3.png"
#define MM_GATE_FIRE_4 "mm_gate_fire_4.png"
#define MM_OPTION_BTN "mm_option_btn.png"
#define MM_OPTION_FIRE_1 "mm_option_fire_1.png"
#define MM_OPTION_FIRE_2 "mm_option_fire_2.png"
#define MM_OPTION_TEXT "mm_option_text.png"
#define MM_ENDLESS_BTN "mm_endless_btn.png"
#define MM_ENDLESS_FIRE_1 "mm_endless_fire_1.png"
#define MM_ENDLESS_FIRE_2 "mm_endless_fire_2.png"
#define MM_ENDLESS_TEXT "mm_endless_text.png"
#define MM_RANK_BTN "mm_rank_btn.png"
#define MM_RANK_FIRE_1 "mm_rank_fire_1.png"
#define MM_RANK_FIRE_2 "mm_rank_fire_2.png"
#define MM_RANK_TEXT "mm_rank_text.png"

#define BG_ZORDER 1
#define MENU_ZORDER 2

#define GATE_BTN_POS Vec2(306,1022)
#define GATE_BTN_TEXT_POS Vec2(271,273)
#define MM_GATE_FIRE_1_POS Vec2(299,270)
#define MM_GATE_FIRE_2_POS Vec2(282,287)
#define MM_GATE_FIRE_3_POS Vec2(266,277)
#define MM_GATE_FIRE_4_POS Vec2(281,280)
#define OPTION_BTN_POS Vec2(224,508)
#define OPTION_BTN_TEXT_POS Vec2(162,156)
#define MM_OPTION_FIRE_1_POS Vec2(145,162)
#define MM_OPTION_FIRE_2_POS Vec2(171,161)
#define ENDLESS_BTN_POS Vec2(697,686)
#define ENDLESS_BTN_TEXT_POS Vec2(221,215)
#define MM_ENDLESS_FIRE_1_POS Vec2(192,220)
#define MM_ENDLESS_FIRE_2_POS Vec2(231,230)
#define RANK_BTN_POS Vec2(620,282)
#define MM_RANK_FIRE_1_POS Vec2(79,90)
#define MM_RANK_FIRE_2_POS Vec2(94,90)

#define GATE_BTN_TAG 11
#define ENDLESS_BTN_TAG 12

Scene* MainMenuScene::createScene(){
	Scene* scene = Scene::create();
	MainMenuScene* layer = MainMenuScene::create();
	scene->addChild(layer);
	return scene;
}

bool MainMenuScene::init(){
	if (Layer::init()){
		Size winSize = Director::getInstance()->getWinSize();
		Sprite* bg = Sprite::create(MAIN_MENU_BG_FILE);
		bg->setPosition(winSize/2);
		addChild(bg,BG_ZORDER);

		Menu* menu = Menu::create();
		menu->setPosition(Vec2::ZERO);
		addChild(menu,MENU_ZORDER);
		GrowButton* gameBtn = GrowButton::create(MM_GATE_BTN,CC_CALLBACK_1(MainMenuScene::menuCallback,this));
		gameBtn->setTag(GATE_BTN_TAG);
		gameBtn->setPosition(GATE_BTN_POS);
		menu->addChild(gameBtn);

		float spin_T = 5;
		Sprite* gateBtn_fire_1 = Sprite::create(MM_GATE_FIRE_1);
		gateBtn_fire_1->setPosition(gameBtn->getContentSize()/2);
		gameBtn->addChild(gateBtn_fire_1);
		RotateBy* spin_1 = RotateBy::create(spin_T,-360);
		gateBtn_fire_1->runAction(RepeatForever::create(spin_1));

		Sprite* gateBtn_fire_2 = Sprite::create(MM_GATE_FIRE_2);
		gateBtn_fire_2->setPosition(gameBtn->getContentSize()/2);
		gameBtn->addChild(gateBtn_fire_2);
		RotateBy* spin_2 = RotateBy::create(spin_T,360);
		gateBtn_fire_2->runAction(RepeatForever::create(spin_2));

		Sprite* gateBtn_fire_3 = Sprite::create(MM_GATE_FIRE_3);
		gateBtn_fire_3->setPosition(gameBtn->getContentSize()/2);
		gameBtn->addChild(gateBtn_fire_3);
		RotateBy* spin_3 = RotateBy::create(spin_T,-360);
		gateBtn_fire_3->runAction(RepeatForever::create(spin_3));

		Sprite* gateBtn_fire_4 = Sprite::create(MM_GATE_FIRE_4);
		gateBtn_fire_4->setPosition(gameBtn->getContentSize()/2);
		gameBtn->addChild(gateBtn_fire_4);
		RotateBy* spin_4 = RotateBy::create(spin_T,360);
		gateBtn_fire_4->runAction(RepeatForever::create(spin_4));

		Sprite* gateBtn_text = Sprite::create(MM_GATE_TEXT);
		gateBtn_text->setPosition(GATE_BTN_TEXT_POS);
		gameBtn->addChild(gateBtn_text);

		GrowButton* optionBtn = GrowButton::create(MM_OPTION_BTN,CC_CALLBACK_1(MainMenuScene::menuCallback,this));
		optionBtn->setPosition(OPTION_BTN_POS);
		menu->addChild(optionBtn);

		Sprite* optionBtn_fire_1 = Sprite::create(MM_OPTION_FIRE_1);
		optionBtn_fire_1->setPosition(optionBtn->getContentSize()/2);
		optionBtn->addChild(optionBtn_fire_1);
		RotateBy* spin_5 = RotateBy::create(spin_T,-360);
		optionBtn_fire_1->runAction(RepeatForever::create(spin_5));

		Sprite* optionBtn_fire_2 = Sprite::create(MM_OPTION_FIRE_2);
		optionBtn_fire_2->setPosition(optionBtn->getContentSize()/2);
		optionBtn->addChild(optionBtn_fire_2);
		RotateBy* spin_6 = RotateBy::create(spin_T,360);
		optionBtn_fire_2->runAction(RepeatForever::create(spin_6));

		Sprite* optionBtn_text = Sprite::create(MM_OPTION_TEXT);
		optionBtn_text->setPosition(OPTION_BTN_TEXT_POS);
		optionBtn->addChild(optionBtn_text);

		GrowButton* endlessBtn = GrowButton::create(MM_ENDLESS_BTN,CC_CALLBACK_1(MainMenuScene::menuCallback,this));
		endlessBtn->setTag(ENDLESS_BTN_TAG);
		endlessBtn->setPosition(ENDLESS_BTN_POS);
		menu->addChild(endlessBtn);

		Sprite* endlessBtn_fire_1 = Sprite::create(MM_ENDLESS_FIRE_1);
		endlessBtn_fire_1->setPosition(endlessBtn->getContentSize()/2);
		endlessBtn->addChild(endlessBtn_fire_1);
		RotateBy* spin_7 = RotateBy::create(spin_T,-360);
		endlessBtn_fire_1->runAction(RepeatForever::create(spin_7));

		Sprite* endlessBtn_fire_2 = Sprite::create(MM_ENDLESS_FIRE_2);
		endlessBtn_fire_2->setPosition(endlessBtn->getContentSize()/2);
		endlessBtn->addChild(endlessBtn_fire_2);
		RotateBy* spin_8 = RotateBy::create(spin_T,360);
		endlessBtn_fire_2->runAction(RepeatForever::create(spin_8));

		Sprite* endlessBtn_text = Sprite::create(MM_ENDLESS_TEXT);
		endlessBtn_text->setPosition(ENDLESS_BTN_TEXT_POS);
		endlessBtn->addChild(endlessBtn_text);

		GrowButton* rankBtn = GrowButton::create(MM_RANK_BTN,CC_CALLBACK_1(MainMenuScene::menuCallback,this));
		rankBtn->setPosition(RANK_BTN_POS);
		menu->addChild(rankBtn);

		Sprite* rankBtn_fire_1 = Sprite::create(MM_RANK_FIRE_1);
		rankBtn_fire_1->setPosition(rankBtn->getContentSize()/2);
		rankBtn->addChild(rankBtn_fire_1);
		RotateBy* spin_9 = RotateBy::create(spin_T,-360);
		rankBtn_fire_1->runAction(RepeatForever::create(spin_9));

		Sprite* rankBtn_fire_2 = Sprite::create(MM_RANK_FIRE_2);
		rankBtn_fire_2->setPosition(rankBtn->getContentSize()/2);
		rankBtn->addChild(rankBtn_fire_2);
		RotateBy* spin_10 = RotateBy::create(spin_T,360);
		rankBtn_fire_2->runAction(RepeatForever::create(spin_10));

		setKeyboardEnabled(true);

		return true;
	}
	return false;
}

void MainMenuScene::menuCallback(Ref* sender){
	MenuItem* menuItem = (MenuItem*)sender;
	int tag = menuItem->getTag();
	switch (tag){
	case GATE_BTN_TAG:
//		Director::getInstance()->replaceScene(GameScene::createScene());
		Director::getInstance()->replaceScene(UniverseScene::createScene());
		break;
	case ENDLESS_BTN_TAG:
		break;
	default:
		break;
	}
}

void MainMenuScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* unusedEvent){
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE){
		Director::getInstance()->end();
	}
}

MainMenuScene::MainMenuScene() {
	// TODO Auto-generated constructor stub

}

MainMenuScene::~MainMenuScene() {
	// TODO Auto-generated destructor stub
}

