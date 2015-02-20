/*
 * UniverseScene.cpp
 *
 *  Created on: Sep 25, 2014
 *      Author: dudu
 */

#include "UniverseScene.h"
#include "../manager/StageManager.h"
#include "../model/PlanetBtn.h"
#include "../scene/MainMenuScene.h"
#include "../scene/StageChooserScene.h"
#include "../GameConstants.h"

#define UNIVERSE_PLIST_FILE_1 "universe1.plist"
#define UNIVERSE_PLIST_FILE_2 "universe2.plist"

#define UNIVERSE_BG_ZORDER 1
#define MENU_BTN_ZORDER 2
#define PLANET_ANIMATION_FRAME_NUM 5

#define MOON_BTN_POS Vec2(297,501)
#define MARS_BTN_POS Vec2(217,930)
#define VENUS_BTN_POS Vec2(736,632)
#define MERCURY_BTN_POS Vec2(731,997)
#define JUPITER_BTN_POS Vec2(426,1175)

#define MOON_BTN_TAG 3
#define MARS_BTN_TAG 4
#define VENUS_BTN_TAG 5
#define MERCURY_BTN_TAG 6
#define JUPITER_BTN_TAG 7

Scene* UniverseScene::createScene(){
	Scene* scene = Scene::create();
	UniverseScene* layer = UniverseScene::create();
	scene->addChild(layer);
	return scene;
}

bool UniverseScene::init(){
	if (Layer::init()){
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(UNIVERSE_PLIST_FILE_1);
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(UNIVERSE_PLIST_FILE_2);

		Size winSize = Director::getInstance()->getWinSize();
		Sprite* bg = Sprite::createWithSpriteFrameName("universe_bg.png");
		bg->setPosition(winSize/2);
		addChild(bg,UNIVERSE_BG_ZORDER);

		char tmp_str [20];
		Menu* menu = Menu::create();
		menu->setPosition(Vec2::ZERO);
		addChild(menu,MENU_BTN_ZORDER);

		//-------- Moon
		sprintf(tmp_str,"%s_01.png",MOON_NAME);
		Sprite* moon_sprite = Sprite::createWithSpriteFrameName(tmp_str);
		PlanetBtn* moon_btn = PlanetBtn::create(moon_sprite,moon_sprite,CC_CALLBACK_1(UniverseScene::btnCallback,this));
		moon_btn->setPosition(MOON_BTN_POS);
		moon_btn->setTag(MOON_BTN_TAG);
		PlanetInfo* moon_info = StageManager::getInstance()->getPlanetInfoByName(MOON_NAME);
		if (!moon_info->getIsUnlocked()){
			moon_btn->setLocked();
		}


		menu->addChild(moon_btn);
		Vector<SpriteFrame*> moon_frames;
		for (int i = 0; i < PLANET_ANIMATION_FRAME_NUM; i++){
			sprintf(tmp_str,"%s_%02d.png",MOON_NAME,i+1);
			SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(tmp_str);
			moon_frames.pushBack(frame);
		}
		Animation* moon_anim = Animation::createWithSpriteFrames(moon_frames,0.1f,-1);
		moon_sprite->runAction(Animate::create(moon_anim));

		//-------- Mars
		sprintf(tmp_str,"%s_01.png",MARS_NAME);
		Sprite* mars_sprite = Sprite::createWithSpriteFrameName(tmp_str);
		PlanetBtn* mars_btn = PlanetBtn::create(mars_sprite,mars_sprite,CC_CALLBACK_1(UniverseScene::btnCallback,this));
		mars_btn->setPosition(MARS_BTN_POS);
		mars_btn->setTag(MARS_BTN_TAG);
		PlanetInfo* mars_info = StageManager::getInstance()->getPlanetInfoByName(MARS_NAME);
		if (!mars_info->getIsUnlocked()){
			mars_btn->setLocked();
		}

		menu->addChild(mars_btn);
		Vector<SpriteFrame*> mars_frames;
		for (int i = 0; i < PLANET_ANIMATION_FRAME_NUM; i++){
			sprintf(tmp_str,"%s_%02d.png",MARS_NAME,i+1);
			SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(tmp_str);
			mars_frames.pushBack(frame);
		}
		Animation* mars_anim = Animation::createWithSpriteFrames(mars_frames,0.1f,-1);
		mars_sprite->runAction(Animate::create(mars_anim));

		//-------- Venus
		sprintf(tmp_str,"%s_01.png",VENUS_NAME);
		Sprite* venus_sprite = Sprite::createWithSpriteFrameName(tmp_str);
		PlanetBtn* venus_btn = PlanetBtn::create(venus_sprite,venus_sprite,CC_CALLBACK_1(UniverseScene::btnCallback,this));
		venus_btn->setPosition(VENUS_BTN_POS);
		venus_btn->setTag(VENUS_BTN_TAG);
		PlanetInfo* venus_info = StageManager::getInstance()->getPlanetInfoByName(VENUS_NAME);
		if (!venus_info->getIsUnlocked()){
			venus_btn->setLocked();
		}

		menu->addChild(venus_btn);
		Vector<SpriteFrame*> venus_frames;
		for (int i = 0; i < PLANET_ANIMATION_FRAME_NUM; i++){
			sprintf(tmp_str,"%s_%02d.png",VENUS_NAME,i+1);
			SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(tmp_str);
			venus_frames.pushBack(frame);
		}
		Animation* venus_anim = Animation::createWithSpriteFrames(venus_frames,0.1f,-1);
		venus_sprite->runAction(Animate::create(venus_anim));

		//-------- Mercury
		sprintf(tmp_str,"%s_01.png",MERCURY_NAME);
		Sprite* mercury_sprite = Sprite::createWithSpriteFrameName(tmp_str);
		PlanetBtn* mercury_btn = PlanetBtn::create(mercury_sprite,mercury_sprite,CC_CALLBACK_1(UniverseScene::btnCallback,this));
		mercury_btn->setPosition(MERCURY_BTN_POS);
		mercury_btn->setTag(MERCURY_BTN_TAG);
		PlanetInfo* mercury_info = StageManager::getInstance()->getPlanetInfoByName(MERCURY_NAME);
		if (!mercury_info->getIsUnlocked()){
			mercury_btn->setLocked();
		}

		menu->addChild(mercury_btn);
		Vector<SpriteFrame*> mercury_frames;
		for (int i = 0; i < PLANET_ANIMATION_FRAME_NUM; i++){
			sprintf(tmp_str,"%s_%02d.png",MERCURY_NAME,i+1);
			SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(tmp_str);
			mercury_frames.pushBack(frame);
		}
		Animation* mercury_anim = Animation::createWithSpriteFrames(mercury_frames,0.1f,-1);
		mercury_sprite->runAction(Animate::create(mercury_anim));

		//-------- Jupiter
		sprintf(tmp_str,"%s_01.png",JUPITER_NAME);
		Sprite* jupiter_sprite = Sprite::createWithSpriteFrameName(tmp_str);
		PlanetBtn* jupiter_btn = PlanetBtn::create(jupiter_sprite,jupiter_sprite,CC_CALLBACK_1(UniverseScene::btnCallback,this));
		jupiter_btn->setPosition(JUPITER_BTN_POS);
		jupiter_btn->setTag(JUPITER_BTN_TAG);
		PlanetInfo* jupiter_info = StageManager::getInstance()->getPlanetInfoByName(JUPITER_NAME);
		if (!jupiter_info->getIsUnlocked()){
			jupiter_btn->setLocked();
		}

		menu->addChild(jupiter_btn);
		Vector<SpriteFrame*> jupiter_frames;
		for (int i = 0; i < PLANET_ANIMATION_FRAME_NUM; i++){
			sprintf(tmp_str,"%s_%02d.png",JUPITER_NAME,i+1);
			SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(tmp_str);
			jupiter_frames.pushBack(frame);
		}
		Animation* jupiter_anim = Animation::createWithSpriteFrames(jupiter_frames,0.1f,-1);
		jupiter_sprite->runAction(Animate::create(jupiter_anim));

		setKeyboardEnabled(true);

		return true;
	}
	return false;
}

void UniverseScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* unusedEvent){
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE){
		TransitionFade* white_fade_transition = TransitionFade::create(1.0f, MainMenuScene::createScene(), Color3B::WHITE);
		Director::getInstance()->replaceScene(white_fade_transition);
	}
}

void UniverseScene::btnCallback(Ref* sender){
	int tag = ((MenuItem*)sender)->getTag();
	switch (tag){
	case MOON_BTN_TAG:
		{
			TransitionFade* white_fade_transition = TransitionFade::create(1.0f,StageChooserScene::createScene(MOON_NAME), Color3B::WHITE);
			Director::getInstance()->replaceScene(white_fade_transition);
		}
		break;
	case VENUS_BTN_TAG:
		break;
	case JUPITER_BTN_TAG:
		break;
	case MARS_BTN_TAG:
		break;
	case MERCURY_BTN_TAG:
		break;
	default:
		break;
	}
}

UniverseScene::UniverseScene() {

}

UniverseScene::~UniverseScene() {
}

