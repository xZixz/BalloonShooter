/*
 * StageChooserScene.cpp
 *
 *  Created on: Sep 29, 2014
 *      Author: dudu
 */

#include "StageChooserScene.h"
#include "../manager/StageManager.h"
#include "../model/StageBtn.h"
#include "GameScene.h"
#include "UniverseScene.h"

#define STAGE_CHOOSER_SCENE_BG "stage_chooser_bg.png"
#define HEART_STAGE_CHOOSER_SCENE_FILE "heart.png"
#define STAR_COUNT_BASE_FILE "star_count_base.png"

#define STAGE_CHOOSER_SCENE_ZORDER 1
#define STAGE_ICON_MENU_ZORDER 2
#define STAGE_ICON_ZORDER 3
#define HEART_STAGE_CHOOSER_SCENE_ZORDER 3
#define STAR_COUNT_BASE_ZORDER 3

#define ROW_NUM 4
#define TOTAL_STAGE 16
#define ROW_SPACE 40
#define COLUMN_SPACE 70
#define TOP_DISTANCE_TO_STAGE_LIST 315

#define HEART_STAGE_CHOOSER_SCENE_POS Vec2(144,1506)
#define STAR_COUNT_BASE_POS Vec2(734,1503)
#define CURRENT_STAR_LABEL_POS Vec2(163,38)

Scene* StageChooserScene::createScene(const std::string& planet_name){
	Scene* scene = Scene::create();
	StageChooserScene* layer = StageChooserScene::create(planet_name);
	scene->addChild(layer);
	return scene;
}

StageChooserScene* StageChooserScene::create(const std::string& planet_name){
	StageChooserScene* stage_chooser_scene = new StageChooserScene();
	if (stage_chooser_scene && stage_chooser_scene->init(planet_name)){
		stage_chooser_scene->autorelease();
		return stage_chooser_scene;
	}
	CC_SAFE_DELETE(stage_chooser_scene);
	return nullptr;
}

bool StageChooserScene::init(const std::string& planet_name){
	if (Layer::init()){
		planet_name_ = planet_name;

		Size winsize = Director::getInstance()->getWinSize();

		Sprite* bg = Sprite::create(STAGE_CHOOSER_SCENE_BG);
		bg->setPosition(winsize/2);
		addChild(bg,STAGE_CHOOSER_SCENE_ZORDER);

		Sprite* heart = Sprite::create(HEART_STAGE_CHOOSER_SCENE_FILE);
		heart->setPosition(HEART_STAGE_CHOOSER_SCENE_POS);
		addChild(heart,HEART_STAGE_CHOOSER_SCENE_ZORDER);

		Sprite* star_count_base_sprite = Sprite::create(STAR_COUNT_BASE_FILE);
		star_count_base_sprite->setPosition(STAR_COUNT_BASE_POS);
		addChild(star_count_base_sprite,STAR_COUNT_BASE_ZORDER);

		std::vector<StageInfo*> stage_info_list = StageManager::getInstance()->getStageInfosByName(planet_name_);
		log("stage_info_list size: %ld", stage_info_list.size());

		int total_star = 3 * TOTAL_STAGE;
		int current_star = 0;
		for (StageInfo* stage_info : stage_info_list){
			current_star = stage_info->getStarNum();
		}

		char tmp_char[20];
		sprintf(tmp_char,"%d/%d",current_star,total_star);
		Label* current_star_label = Label::create(tmp_char,"Arial",40);
		current_star_label->setPosition(CURRENT_STAR_LABEL_POS);
		star_count_base_sprite->addChild(current_star_label);

		Menu* menu = Menu::create();
		menu->setPosition(Vec2::ZERO);
		addChild(menu,STAGE_ICON_MENU_ZORDER);

		for (int i = 0; i < TOTAL_STAGE; i ++){
			StageInfo* stage_info = nullptr;
			StageBtn* btn = nullptr;
				log("start create available btn");
			if (i < stage_info_list.size()){
				for (int j = 0; j < stage_info_list.size(); j++){
					log("getting stage info");
					StageInfo* tmp_info = (StageInfo*) stage_info_list.at(j);
					log("get stage info done");
					log("no of tmp_info: %d",tmp_info->getNo());
					if (tmp_info->getNo() == (i+1)){
						stage_info = tmp_info;
						log("found stage info");
						break;
					}
				}
				log("done searching");
				btn = StageBtn::create(planet_name_,CC_CALLBACK_1(StageChooserScene::stageBtnCallback,this),stage_info->getStarNum());
				btn->setTag(i+1);
				log("avaible btn created");
			} else {
				log("start create disable btn");
				btn = StageBtn::create(planet_name_,CC_CALLBACK_1(StageChooserScene::stageBtnCallback,this),0);
				btn->setEnabled(false);
				log("disable btn created");
			}
			int row_index = i % 4;
			int column_index = i / 4;
			float pos_x = ROW_SPACE + btn->getContentSize().width/2 + row_index * (btn->getContentSize().width + ROW_SPACE);
			float pos_y = winsize.height- (TOP_DISTANCE_TO_STAGE_LIST + btn->getContentSize().height/2 + (column_index * (btn->getContentSize().height + COLUMN_SPACE)));
			btn->setPosition(Vec2(pos_x,pos_y));
			menu->addChild(btn,STAGE_ICON_ZORDER);
		}

		setKeypadEnabled(true);

		return true;
	}
	return false;
}

void StageChooserScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* unusedEvent){
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE){
		Director::getInstance()->replaceScene(UniverseScene::createScene());
	}
}

void StageChooserScene::stageBtnCallback(Ref* sender){
	MenuItem* btn = (MenuItem*)sender;
	int tag = btn->getTag();
	Stage stage;
	stage.planet_name_ = planet_name_;
	stage.no_ = tag;
	Director::getInstance()->replaceScene(GameScene::createScene(stage));
}

StageChooserScene::StageChooserScene() {
}

StageChooserScene::~StageChooserScene() {
}

