/*
 * GameScene.cpp
 *
 *  Created on: Sep 10, 2014
 *      Author: dudu
 */

#include "GameScene.h"
#include "../manager/BallManager.h"
#include "../scene/MainMenuScene.h"
#include "../scene/ResultScene.h"
#include "../GameConstants.h"
#include "../GameMacros.h"

#define GAME_SCENE_BG_FILE "game_scene_bg.png"

#define GAME_SCENE_BACK_GROUND_ZORDER 1
#define BOOK_ZORDER 7
#define MAGIC_CIRCLE_ZORDER 9
#define BALL_ZORDER 20
#define TOP_WALL_ZORDER 5
#define BASE_ZORDER 4
#define MAGIC_STAND_ZORDER 7

#define BOOK_POS Vec2(480,234)
#define TOP_WALL_POS Vec2(480,1543)
#define MAGIC_STAND_POS Vec2(814,165)
#define BALL_SPAWN_POS Vec2(813,251)
#define BALL_READY_POS Vec2(480,280)
#define MAGIC_CIRCLE_POS Vec2(483,247)

#define PLAY_SCENE_SIDE_BOUND 50
#define PLAY_SCENE_TOP_BOUND 115

#define SLOT_PER_ROW_NUM 10
#define ROW_NUM 20

#define E_ 43.0f
#define EV3_ 74.5f

Scene* GameScene::createScene() {
	Scene* scene = Scene::create();
	GameScene* layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

Scene* GameScene::createScene(Stage stage) {
	Scene* scene = Scene::create();
	GameScene* layer = GameScene::create(stage);
	scene->addChild(layer);
	return scene;
}

GameScene* GameScene::create() {
	GameScene* layer = new (std::nothrow) GameScene();
	if (layer && layer->init()) {
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return nullptr;
}

GameScene* GameScene::create(Stage stage) {
	GameScene* layer = new (std::nothrow) GameScene();
	if (layer && layer->init(stage)) {
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return nullptr;
}

bool GameScene::init(Stage stage){
	stage_ = stage;
	return init();
}

bool GameScene::init() {
	if (Layer::init()) {

		winsize_ = Director::getInstance()->getWinSize();
		Sprite* bg = Sprite::create(GAME_SCENE_BG_FILE);
		bg->setPosition(winsize_ / 2);
		addChild(bg, GAME_SCENE_BACK_GROUND_ZORDER);

		Sprite* book = Sprite::create("book_01.png");
		book->setPosition(BOOK_POS);
		addChild(book, BOOK_ZORDER);

		Sprite* topWall = Sprite::create("top_wall.png");
		topWall->setPosition(TOP_WALL_POS);
		addChild(topWall, TOP_WALL_ZORDER);

		Sprite* base = Sprite::create("base.png");
		base->setPosition(winsize_ / 2);
		addChild(base, BASE_ZORDER);

		Sprite* magic_stand = Sprite::create("magic_stand_01.png");
		magic_stand->setPosition(MAGIC_STAND_POS);
		addChild(magic_stand, MAGIC_STAND_ZORDER);

		Sprite* magic_circle = Sprite::create("magic_circle.png");
		magic_circle->setPosition(MAGIC_CIRCLE_POS);
		addChild(magic_circle, MAGIC_CIRCLE_ZORDER);
		ScaleTo* magic_circle_scale_down = ScaleTo::create(1.0f,0.4f);
		ScaleTo* magic_circle_scale_up = ScaleTo::create(1.0f,1.0f);
		magic_circle->runAction(RepeatForever::create(Sequence::create(magic_circle_scale_down,magic_circle_scale_up,NULL)));

		initialize_ball_list();
		initialize_slots();
		initialize_balls();
		create_pending_ball();
		spawnBall();
		enableTouch();
		setKeypadEnabled(true);

//		schedule(schedule_selector(GameScene::update));

		return true;
	}
	return false;
}

void GameScene::initialize_ball_list() {
	available_ball_list_ = BallManager::getInstance()->get_available_ball_list_by_stage_index(1);
}

void GameScene::initialize_slots() {
	for (int x = 0; x < ROW_NUM; x++) {
		std::vector<Slot*> a_row;

		// Even row (starting index at 0) has 10 slots, odd row has 9 slots
		int slot_num;
		if (x%2 == 0){
			slot_num = SLOT_PER_ROW_NUM;
		} else {
			slot_num = SLOT_PER_ROW_NUM - 1;
		}

		for (int y = 0; y < slot_num; y++) {
			Slot* slot = new Slot();
			slot->row_index_ = x;
			slot->column_index_ = y;
			setPosForSlot(slot);
			a_row.push_back(slot);
		}
		slots_2d.push_back(a_row);
	}
}

void GameScene::initialize_balls(){
	BallsSetup ball_setup = StageManager::getInstance()->getBallsSetupByStage(stage_);
	int row_i = 0;
	int column_i = 0;
	BallsSetup::iterator row_itor;
	std::vector<std::string>::iterator itor;
	for (row_itor = ball_setup.begin(); row_itor != ball_setup.end(); row_itor++){
		for (itor = row_itor->begin(); itor != row_itor->end(); itor++){
			std::string ball_name = (std::string)(*itor);
			if (ball_name.compare(N0)){
				Ball* ball = Ball::create(ball_name);
				stucking_ball_list_.pushBack(ball);
				Slot* slot = (Slot*)(slots_2d.at(row_i)).at(column_i);
				ball->installIntoSlot(slot);
				addChild(ball,BALL_ZORDER);
			}
			column_i++;
		}
		column_i = 0;
		row_i ++;
	}
	log("stucking ball list size: %ld",stucking_ball_list_.size());
}

void GameScene::create_pending_ball(){
	std::string random_ball_name = generate_random_ball_name();
	pending_ball_ = Ball::create(random_ball_name);
	pending_ball_->setPosition(BALL_SPAWN_POS);
	addChild(pending_ball_,BALL_ZORDER);
}

Vec2 GameScene::posOfSlot(int index_row, int index_col){
	float pos_y = winsize_.height - PLAY_SCENE_TOP_BOUND - (index_row * EV3_ + E_);
	float pos_x;
	if ((index_row % 2) == 0){
		pos_x = PLAY_SCENE_SIDE_BOUND + index_col * E_* 2 + E_;
	} else {
		pos_x = PLAY_SCENE_SIDE_BOUND + (index_col+1) * E_* 2 ;
	}
	return Vec2(pos_x,pos_y);
}

void GameScene::setPosForSlot(Slot* slot){
	slot->pos_ = posOfSlot(slot->row_index_,slot->column_index_);
}

void GameScene::update(float dt) {
	if (flying_ball_) {

		// Detect ball touch other balls
		bool ball_hit_ball = false;
		for (Ball* ball : stucking_ball_list_) {
			if (DISTANCE_BETWEEN(flying_ball_->getPosition(),
					ball->getPosition()) <= (2 * E_)) {
				adjustBallHitBall(ball, flying_ball_);
				flying_ball_->doneShot();
				ball_hit_ball = true;
				break;
			}
		}

		if (!ball_hit_ball)

			// Detect ball touch top wall
			if (flying_ball_->getPosition().y + flying_ball_->getContentSize().height / 2
					> winsize_.height - PLAY_SCENE_TOP_BOUND) {
				adjustBallToTopSlot(flying_ball_);
				flying_ball_->doneShot();
			} else

			// Detect ball touch side walls
			if ((flying_ball_->getPosition().x
					- flying_ball_->getContentSize().width / 2)
					< PLAY_SCENE_SIDE_BOUND
					|| (flying_ball_->getPosition().x
							+ flying_ball_->getContentSize().width / 2)
							> (winsize_.width - PLAY_SCENE_SIDE_BOUND)) {
				if (!flying_ball_->isBouncing()) {
					flying_ball_->bounceVertical();
				}
			} else {
				flying_ball_->set_is_bouncing(false);
			}

	}
	Layer::update(dt);
}

void GameScene::enableTouch() {
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void GameScene::scanBallCollide() {
	schedule(schedule_selector(GameScene::update));
}

void GameScene::stopScanBallCollide() {
	unschedule(schedule_selector(GameScene::update));
}

bool GameScene::onTouchBegan(Touch *touch, Event *unused_event) {
//	if (ready_ball_) {
//		scanBallCollide();
//		Vec2 touchPos = touch->getLocation();
//		if (touchPos.y > ready_ball_->getPositionY()) {
//			ready_ball_->shot(touchPos);
//			flying_ball_ = ready_ball_;
//			ready_ball_ = nullptr;
//		}
//	}
	return true;
}

void GameScene::onTouchMoved(Touch *touch, Event *unused_event) {

}

void GameScene::onTouchEnded(Touch *touch, Event *unused_event) {
	if (ready_ball_) {
		scanBallCollide();
		Vec2 touchPos = touch->getLocation();
		if (touchPos.y > ready_ball_->getPositionY()) {
			ready_ball_->shot(touchPos);
			flying_ball_ = ready_ball_;
			ready_ball_ = nullptr;
		}
	}
}

void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode,
		Event* unused_event) {
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
		keyBackPressed();
	}
}

void GameScene::keyBackPressed() {
	Director::getInstance()->replaceScene(MainMenuScene::createScene());
}

std::string GameScene::generate_random_ball_name() {
	int ran = rand() % (available_ball_list_.size());
	return (std::string)(available_ball_list_.at(ran));
}

void GameScene::spawnBall() {
	ready_ball_ = pending_ball_;
	create_pending_ball();
	ready_ball_->setPosition(BALL_READY_POS);
	ready_ball_->setGameScene(this);
//	addChild(ready_ball_, BALL_ZORDER);
}

void GameScene::ballDoneShot(Ball* ball) {
	stopScanBallCollide();
	stucking_ball_list_.pushBack(ball);
	recursiveCheckSameBall(ball->getSlot(),ball->getSlot());
	log("Same ball num: %ld",same_ball_list_.size());
	if (same_ball_list_.size() >= 3){
		boomSameBalls();
	}
	same_ball_list_.clear();
	refreshTraversedBoolOfSlots();

	checkUntieToTop();
	boomUntieToTop();
	untie_ball_list_.clear();
	refreshTraversedBoolOfSlots();

	spawnBall();
	flying_ball_ = nullptr;

	if (stucking_ball_list_.size() == 0){
		showWinGame();
	}

}

void GameScene::checkUntieToTop(){
	std::vector<Slot*> top_row = slots_2d.at(0);
	for (Slot* slot : top_row){
		recursiveCheckHangToTop(slot);
	}
	std::vector<std::vector<Slot*>>::iterator row;
	std::vector<Slot*>::iterator slot_itor;
	for (row = slots_2d.begin(); row != slots_2d.end(); row++){
		for (slot_itor = row->begin(); slot_itor!= row->end(); slot_itor++){
			Slot* slot = (*slot_itor);
			if (slot->is_traversed_ == false && slot->ball_ != nullptr){
				untie_ball_list_.pushBack(slot->ball_);
			}
		}
	}
}

void GameScene::boomUntieToTop(){
	for (Ball* ball : untie_ball_list_){
		ball->getSlot()->ball_ = nullptr;
		stucking_ball_list_.eraseObject(ball);
		removeChild(ball);
	}
}

void GameScene::boomSameBalls(){
	for (Ball* ball : same_ball_list_){
//		ball->setVisible(false);
		ball->getSlot()->ball_ = nullptr;
		stucking_ball_list_.eraseObject(ball);
		removeChild(ball);
	}
}

void GameScene::refreshTraversedBoolOfSlots(){
//	for (auto& row : slots_2d){
//		for (auto& slot : row){
//			slot->is_traversed_ = false;
//		}
//	}

	std::vector<std::vector<Slot*>>::iterator row;
	std::vector<Slot*>::iterator slot_itor;
	for (row = slots_2d.begin(); row != slots_2d.end(); row++){
		for (slot_itor = row->begin(); slot_itor!= row->end(); slot_itor++){
			Slot* slot = (*slot_itor);
			slot->is_traversed_ = false;
		}
	}
}

void GameScene::recursiveCheckSameBall(Slot* origin_slot, Slot* traversed_slot){
	if (traversed_slot == nullptr)
		return;

	if (traversed_slot->is_traversed_ == true){
		return;
	}
	traversed_slot->is_traversed_ = true;

	if (traversed_slot->ball_ == nullptr){
		return;
	}

	if (isBallsSameColor(origin_slot->ball_,traversed_slot->ball_)){
		same_ball_list_.pushBack(traversed_slot->ball_);
	} else {
		return;
	}

	recursiveCheckSameBall(origin_slot,getAboveLeftSlot(traversed_slot));
	recursiveCheckSameBall(origin_slot,getAboveRightSlot(traversed_slot));
	recursiveCheckSameBall(origin_slot,getNextToLeftSlot(traversed_slot));
	recursiveCheckSameBall(origin_slot,getNextToRightSlot(traversed_slot));
	recursiveCheckSameBall(origin_slot,getBelowLeftSlot(traversed_slot));
	recursiveCheckSameBall(origin_slot,getBelowRightSlot(traversed_slot));
}

void GameScene::recursiveCheckHangToTop(Slot* slot){
	if (slot == nullptr){
		return;
	}

	if (slot->ball_ == nullptr){
		return;
	}

	if (slot->is_traversed_ == true){
		return;
	}
	slot->is_traversed_ = true;

	recursiveCheckHangToTop(getAboveLeftSlot(slot));
	recursiveCheckHangToTop(getAboveRightSlot(slot));
	recursiveCheckHangToTop(getNextToLeftSlot(slot));
	recursiveCheckHangToTop(getNextToRightSlot(slot));
	recursiveCheckHangToTop(getBelowLeftSlot(slot));
	recursiveCheckHangToTop(getBelowRightSlot(slot));
}

Slot* GameScene::getAboveLeftSlot(Slot* slot){
	int row_i = slot->row_index_;
	int col_i = slot->column_index_;
	if (row_i > 0){
		if (row_i % 2 == 1)
			return slots_2d[row_i - 1][col_i];
		else if (col_i > 0)
			return slots_2d[row_i - 1][col_i - 1];
		else
			return nullptr;
	} else {
		return nullptr;
	}
}

Slot* GameScene::getAboveRightSlot(Slot* slot){
	int row_i = slot->row_index_;
	int col_i = slot->column_index_;
	if (row_i > 0){
		if (row_i % 2 == 0){
			if (col_i < SLOT_PER_ROW_NUM - 1){
				return slots_2d[row_i - 1][col_i];
			} else {
				return nullptr;
			}
		} else {
			return slots_2d[row_i - 1][col_i + 1];
		}
	} else {
		return nullptr;
	}

}

Slot* GameScene::getNextToRightSlot(Slot* slot){
	int row_i = slot->row_index_;
	int col_i = slot->column_index_;
	if (row_i % 2 == 1){
		if (col_i < SLOT_PER_ROW_NUM - 2){
			return slots_2d[row_i][col_i + 1];
		} else {
			return nullptr;
		}
	} else {
		if (col_i < SLOT_PER_ROW_NUM - 1){
			return slots_2d[row_i][col_i + 1];
		}
		else {
			return nullptr;
		}
	}
}

Slot* GameScene::getNextToLeftSlot(Slot* slot){
	int row_i = slot->row_index_;
	int col_i = slot->column_index_;
//	if (row_i % 2 == 1){
		if (col_i > 0){
			return slots_2d[row_i][col_i - 1];
		} else {
			return nullptr;
		}
//	} else {
//		if (col_i < SLOT_PER_ROW_NUM - 1){
//			return slots_2d[row_i][col_i + 1];
//		}
//		else {
//			return nullptr;
//		}
//	}
}

Slot* GameScene::getBelowRightSlot(Slot* slot){
	int row_i = slot->row_index_;
	int col_i = slot->column_index_;
//	if (row_i > 0){
		if (row_i % 2 == 0){
			if (col_i < SLOT_PER_ROW_NUM - 1){
				return slots_2d[row_i + 1][col_i];
			} else {
				return nullptr;
			}
		} else {
			return slots_2d[row_i + 1][col_i + 1];
		}
//	} else {
//		return nullptr;
//	}

}

Slot* GameScene::getBelowLeftSlot(Slot* slot){
//	int row_i = slot->row_index_;
//	int col_i = slot->column_index_;
//	if (row_i > 0 && col_i > 0){
//	if (col_i > 0){
//		if (row_i % 2 == 1)
//			return slots_2d[row_i + 1][col_i];
//		else
//			return slots_2d[row_i + 1][col_i - 1];
//	} else {
//		return nullptr;
//	}

	int row_i = slot->row_index_;
	int col_i = slot->column_index_;
//	if (row_i > 0){
		if (row_i % 2 == 1)
			return slots_2d[row_i + 1][col_i];
		else if (col_i > 0)
			return slots_2d[row_i + 1][col_i - 1];
		else
			return nullptr;
//	} else {
//		return nullptr;
//	}
}

bool GameScene::isBallsSameColor(Ball* ball_1, Ball* ball_2){
	if (!ball_1->getName().compare(ball_2->getName())){
		return true;
	} else {
		return false;
	}
}

void GameScene::adjustBallToTopSlot(Ball* ball) {
	int slot_index = (int) ((ball->getPositionX() - PLAY_SCENE_SIDE_BOUND) / (E_ * 2)) + 1;
	Vec2 adjusted_pos = Vec2(E_ * 2 * slot_index + PLAY_SCENE_SIDE_BOUND - E_,
			winsize_.height - PLAY_SCENE_TOP_BOUND - E_);
	Slot* t_slot = slots_2d[0][slot_index-1];
	ball->installIntoSlot(t_slot);
}

float GameScene::angleWhenContactOfBalls(Ball* target_ball, Ball* coming_ball){
	Vec2 t_pos = target_ball->getPosition();
	Vec2 c_pos = coming_ball->getPosition();
	float tangent = (c_pos.x - t_pos.x)/(t_pos.y - c_pos.y);
	float t_degree = CC_RADIANS_TO_DEGREES(atan(tangent));
	if (t_pos.y < c_pos.y){
		if (c_pos.x < t_pos.x)
			t_degree -= 180;
		else
			t_degree += 180;
	}

	return t_degree;
}

void GameScene::adjustBallHitBall(Ball* target_ball, Ball* coming_ball) {
	Vec2 adjusted_pos;
	Slot* target_slot = target_ball->getSlot();
	Slot* coming_slot = nullptr;
	float contact_degree = angleWhenContactOfBalls(target_ball,coming_ball) ;

	// below - right
	if (contact_degree > 0 && contact_degree < 60){
		coming_slot = getBelowRightSlot(target_slot);
		if (coming_slot == nullptr){
			coming_slot = getBelowLeftSlot(target_slot);
		}
	} else
	// below - left
	if (contact_degree <= 0 && contact_degree > -60){
		coming_slot = getBelowLeftSlot(target_slot);
		if (coming_slot ==  nullptr){
			coming_slot = getBelowRightSlot(target_slot);
		}
	} else
	// next to right
	if (contact_degree > 60){
		coming_slot = getNextToRightSlot(target_slot);
	} else
	// next to left
	if (contact_degree < -60){
		coming_slot = getNextToLeftSlot(target_slot);
	}
	coming_ball->installIntoSlot(coming_slot);
}

void GameScene::showWinGame(){
	int star_num = 3;
	StageInfo* stage_info = StageManager::getInstance()->getStageInfoByStage(stage_);
	if (star_num > stage_info->getNo()){
		stage_info->setStarNum(star_num);
		stage_info->updateStageInfo();
		log("Update stage info");
	}
	Stage next_stage = stage_;
	next_stage.no_ ++;
	StageInfo* next_stage_info = StageManager::getInstance()->getStageInfoByStage(next_stage);
	if (!next_stage_info){
		next_stage_info = StageInfo::create(next_stage.planet_name_,next_stage.no_,0);
		StageManager::getInstance()->addNewStageInfoList(next_stage_info);
		log("new stage unlocked");
	}
	Director::getInstance()->replaceScene(ResultScene::createScene(true,200,star_num));
}

GameScene::GameScene() :
ready_ball_(NULL), flying_ball_(NULL), pending_ball_(NULL)
{
}

GameScene::~GameScene() {
}

