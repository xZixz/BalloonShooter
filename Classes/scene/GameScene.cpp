/*
 * GameScene.cpp
 *
 *  Created on: Sep 10, 2014
 *      Author: dudu
 */

#include "GameScene.h"
#include "../manager/BallManager.h"
//#include "../model/FireBall.h"
#include "../scene/MainMenuScene.h"
#include "../scene/ResultScene.h"
#include "../GameConstants.h"
#include "../GameMacros.h"

#define GAME_SCENE_BG_FILE "game_scene_bg.jpg"
#define PILLARS_IMAGE_FILE "pillars.png"
#define DINO_IMAGE_FILE "dino.png"

#define LEAF_BTN_IMAGE_FILE "leaf_skill_btn.png"
#define ARROW_BTN_IMAGE_FILE "arrow_skill_btn.png"
#define FLOWER_BTN_IMAGE_FILE "flower_skill_btn.png"
#define BOOM_BTN_IMAGE_FILE "boom_skill_btn.png"

#define GAME_SCENE_BACK_GROUND_ZORDER 1
#define PILLARS_ZORDER 2
#define DINO_ZORDER 3
#define MENU_ZORDER 8

#define BOOK_ZORDER 7
#define MAGIC_CIRCLE_ZORDER 9
#define BALL_ZORDER 20
#define TOP_WALL_ZORDER 5
#define BASE_ZORDER 4
#define MAGIC_STAND_ZORDER 7
#define SCORE_FRAME_ZORDER 7
#define BALLS_LEFT_FRAME_ZORDER 7
#define TIME_LEFT_FRAME_ZORDER 7
#define DEAD_LINE_ZORDER 7

#define LEAF_SKILL_BTN_TAG 1
#define ARROW_SKILL_BTN_TAG 2
#define FLOWER_SKILL_BTN_TAG 3
#define BOOM_SKILL_BTN_TAG 4

#define BOOK_POS Vec2(480,234)
#define TOP_WALL_POS Vec2(480,1543)
#define MAGIC_STAND_POS Vec2(814,165)
#define BALL_SPAWN_POS Vec2(813,251)
#define MAGIC_CIRCLE_POS Vec2(483,247)
#define SCORE_FRAME_POS Vec2(654,1556)
#define BALLS_LEFT_FRAME_POS Vec2(190,1547)
#define TIME_LEFT_FRAME_POS Vec2(420,1543)
#define DEAD_LINE_POS Vec2(480,383)
#define SCORE_LABEL_POS Vec2(86,30)
#define BALLS_LEFT_LABEL_POS Vec2(104,35)
#define TIME_LEFT_LABEL_POS Vec2(143,38)

#define PILLARS_POS Vec2(768,1097)
#define DINO_POS Vec2(804,371)
#define BALL_READY_POS Vec2(800,394)
#define LEAF_BTN_POS Vec2(429,84)
#define ARROW_BTN_POS Vec2(657,84)
#define FLOWER_BTN_POS Vec2(885,84)
#define BOOM_BTN_POS Vec2(1113,84)

#define PLAY_SCENE_SIDE_BOUND 50
#define PLAY_SCENE_TOP_BOUND 115

#define SLOT_PER_ROW_NUM 10
#define ROW_NUM 20
#define ROW_NUM_PLAYABLE 14
#define Y_END_LIMIT 405

#define E_ 72.5f
#define EV3_ 125.57f

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
		stage_setup_ = StageManager::getInstance()->getStageSetupByStage(stage_);
		current_ball_left_ = stage_setup_.ball_limit;
		current_time_left_ = stage_setup_.time_limit;

		// Background
		Sprite* bg = Sprite::create(GAME_SCENE_BG_FILE);
		bg->setPosition(winsize_ / 2);
		addChild(bg, GAME_SCENE_BACK_GROUND_ZORDER);

		Sprite* pillars = Sprite::create(PILLARS_IMAGE_FILE);
		pillars->setPosition(PILLARS_POS);
		addChild(pillars,PILLARS_ZORDER);

		Sprite* dino = Sprite::create(DINO_IMAGE_FILE);
		dino->setPosition(DINO_POS);
		addChild(dino,DINO_ZORDER);

		// Buttons
		Menu* menu = Menu::create();
		menu->setPosition(Vec2::ZERO);
		addChild(menu,MENU_ZORDER);

		MenuItemImage* leaf_skill_btn = MenuItemImage::create(LEAF_BTN_IMAGE_FILE,LEAF_BTN_IMAGE_FILE, CC_CALLBACK_1(GameScene::skill_btn_callback,this));
		MenuItemImage* arrow_skill_btn = MenuItemImage::create(ARROW_BTN_IMAGE_FILE,ARROW_BTN_IMAGE_FILE, CC_CALLBACK_1(GameScene::skill_btn_callback,this));
		MenuItemImage* flower_skill_btn = MenuItemImage::create(FLOWER_BTN_IMAGE_FILE,FLOWER_BTN_IMAGE_FILE, CC_CALLBACK_1(GameScene::skill_btn_callback,this));
		MenuItemImage* boom_skill_btn = MenuItemImage::create(BOOM_BTN_IMAGE_FILE,BOOM_BTN_IMAGE_FILE, CC_CALLBACK_1(GameScene::skill_btn_callback,this));
		leaf_skill_btn->setTag(LEAF_SKILL_BTN_TAG);
		arrow_skill_btn->setTag(ARROW_SKILL_BTN_TAG);
		flower_skill_btn->setTag(FLOWER_SKILL_BTN_TAG);
		boom_skill_btn->setTag(BOOM_SKILL_BTN_TAG);
		leaf_skill_btn->setPosition(LEAF_BTN_POS);
		arrow_skill_btn->setPosition(ARROW_BTN_POS);
		flower_skill_btn->setPosition(FLOWER_BTN_POS);
		boom_skill_btn->setPosition(BOOM_BTN_POS);

		menu->addChild(leaf_skill_btn);
		menu->addChild(arrow_skill_btn);
		menu->addChild(flower_skill_btn);
		menu->addChild(boom_skill_btn);

		/*
		 *  Old version
		 */
		/*
		Sprite* book = Sprite::create("book_01.png");
		book->setPosition(BOOK_POS);
		addChild(book, BOOK_ZORDER);

		top_wall_ = Sprite::create("top_wall.png");
		top_wall_->setPosition(TOP_WALL_POS);
		addChild(top_wall_, TOP_WALL_ZORDER);


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
		magic_circle->runAction(RepeatForever::create(Sequence::create(magic_circle_scale_down,magic_circle_scale_up,(char*)NULL)));

		Sprite* score_frame = Sprite::create("score_base_gamescne.png");
		score_frame->setPosition(SCORE_FRAME_POS);
		addChild(score_frame,SCORE_FRAME_ZORDER);

		score_label_ = Label::create("0","Arial",40);
		score_label_->setPosition(SCORE_LABEL_POS);
		score_frame->addChild(score_label_);

		Sprite* balls_left_frame = Sprite::create("stage_num_base_gamescne.png");
		balls_left_frame->setPosition(BALLS_LEFT_FRAME_POS);
		addChild(balls_left_frame,BALLS_LEFT_FRAME_ZORDER);

		balls_left_label_ = Label::create(std::to_string(current_ball_left_),"Arial",40);
		balls_left_label_->setPosition(BALLS_LEFT_LABEL_POS);
		balls_left_frame->addChild(balls_left_label_);

		Sprite* time_left_frame = Sprite::create("coin_base_gamescne.png");
		time_left_frame->setPosition(TIME_LEFT_FRAME_POS);
		addChild(time_left_frame,TIME_LEFT_FRAME_ZORDER);

		time_left_label_ = Label::create(std::to_string((int)current_time_left_),"Arial",40);
		time_left_label_->setPosition(TIME_LEFT_LABEL_POS);
		time_left_frame->addChild(time_left_label_);

		Sprite* dead_line = Sprite::create("dead_line.png");
		dead_line->setPosition(DEAD_LINE_POS);
		addChild(dead_line,DEAD_LINE_ZORDER);
		*/

		guiding_arrow_ = Sprite::create("arrow.png");
		guiding_arrow_->setAnchorPoint(Vec2(0.5f,0.0f));
		guiding_arrow_->setPosition(BALL_READY_POS);
		addChild(guiding_arrow_,BALL_ZORDER-1);

		guide_dots_ = GuideDots::createWithFileName("guide_dot.png");
		guide_dots_->setPosition(BALL_READY_POS);
		guide_dots_->setSideBound(winsize_.width/2 - PLAY_SCENE_SIDE_BOUND - E_);
		addChild(guide_dots_,BALL_ZORDER + 1);

		initialize_slots();
		initialize_balls();
		build_available_ball_list();
		create_pending_ball();
		spawnBall();
		enableTouch();
		setKeypadEnabled(true);

//		schedule(schedule_selector(GameScene::oneRowDown),5.0f);
		gameStart();

		return true;
	}
	return false;
}

void GameScene::build_available_ball_list(){
	available_ball_list_.clear();
	bool found;
	for (Ball* ball : stucking_ball_list_){
		found = false;
		for (std::string ball_name : available_ball_list_){
			if (!ball_name.compare(ball->getName())){
				found = true;
				break;
			};
		}
		if (found){
			continue;
		}
		available_ball_list_.push_back(ball->getName());
	}

	// Remove unshotable balls
	std::vector<std::string> unshotable_ball_list = BallManager::getInstance()->getUnshotableBallList();
	for (std::string unshotable_ball_name : unshotable_ball_list){
		available_ball_list_.erase(std::remove(available_ball_list_.begin(),available_ball_list_.end(),unshotable_ball_name),available_ball_list_.end());
	}
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
			setPosForSlot(slot); // set position for each slot
			a_row.push_back(slot);
		}
		slots_2d.push_back(a_row);
	}
}

void GameScene::initialize_balls(){
	BallsSetup ball_setup = StageManager::getInstance()->getBallsSetupByStageJSON(stage_);
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
				current_lowest_y_ = ball->getPositionY() - E_;
			}
			column_i++;
		}
		column_i = 0;
		current_max_row_num_ = row_i;
		row_i ++;
	}
}

void GameScene::create_pending_ball(){
	std::string random_ball_name = generate_random_ball_name();
	pending_ball_ = Ball::create(random_ball_name);
//	pending_ball_ = FireBall::create();
//	pending_ball_->addSpecialType(Ball::SpecialType::SPECIAL_3);
	pending_ball_->setPosition(BALL_SPAWN_POS);
	pending_ball_->setGameScene(this);
	addChild(pending_ball_,BALL_ZORDER);
}

void GameScene::substitute_pending_ball(){
	removeChild(pending_ball_);
	create_pending_ball();
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

				ball_hit_ball = true;
				if (!ball->getName().compare(KEY_BALL_NAME)){ // check if key ball was hit
					is_key_ball_shot_ = true;
				}

				// if it's a fire-ball, not adjust its position
				if (flying_ball_->containSpecialType(Ball::SpecialType::SPECIAL_4)){
					// TODO
//					FireBall* fire_ball = (FireBall*)flying_ball_;
//					if (flying_ball_->getSpecialType() == Ball::SpecialType::SPECIAL_4){ // ball special 4
						boomABall(ball);
						flying_ball_->destroyABall();
//					}
//					else if (flying_ball_->getSpecialType() == Ball::SpecialType::SPECIAL_2_4){ // ball special 2 4
//						boomABall(ball);
//						fire_ball->destroyABall();
//						Slot* next_to_right_slot = getNextToRightSlot(ball->getSlot());
//						if (next_to_right_slot && next_to_right_slot->ball_){
//							boomABall(next_to_right_slot->ball_);
//							fire_ball->destroyABall();
//						}
//						Slot* next_to_left_slot = getNextToLeftSlot(ball->getSlot());
//						if (next_to_left_slot && next_to_left_slot->ball_){
//							fire_ball->destroyABall();
//							boomABall(next_to_left_slot->ball_);
//						}
//					}
				} else {
					adjustBallHitBall(ball, flying_ball_);
					flying_ball_->doneShot();
				}
				break;
			}
		}

		if (!ball_hit_ball){

			// Detect ball touch top wall
			if (flying_ball_->getPosition().y + flying_ball_->getContentSize().height / 2
//					> (top_wall_->getPosition().y - top_wall_->getContentSize().height/2)) {
					> (winsize_.height - PLAY_SCENE_TOP_BOUND)) {
				// if it's a fire-ball, not adjust its position
				if (flying_ball_->getSpecialType() & Ball::SpecialType::SPECIAL_4){

				} else {
					adjustBallToTopSlot(flying_ball_);
				}
				flying_ball_->doneShot();
			}

			// Detect ball touch side walls
			else if ((flying_ball_->getPosition().x - flying_ball_->getContentSize().width / 2) < PLAY_SCENE_SIDE_BOUND
					|| (flying_ball_->getPosition().x + flying_ball_->getContentSize().width / 2) > (winsize_.width - PLAY_SCENE_SIDE_BOUND)) {
				if (!flying_ball_->isBouncing()) {
					flying_ball_->bounceVertical();
				}
			} else {
				flying_ball_->set_is_bouncing(false);
			}
		}

	}

	// Scroll balls down


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


void GameScene::scheduleBallsFlowDown(){
	schedule(schedule_selector(GameScene::ballsFlowDown));
}

void GameScene::unscheduleBallsFlowDown(){
	unschedule(schedule_selector(GameScene::ballsFlowDown));
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
	if (gameState == GameState::PLAYING){
		if (isPendingBallTouch(touch)){
			swapBall();
			return false;
		} else {
			adjustGuidingArrow(touch);
			guide_dots_->setDeg(touch);
		}
		return true;
	}
	return false;
}

void GameScene::onTouchMoved(Touch *touch, Event *unused_event) {
	adjustGuidingArrow(touch);
	guide_dots_->setDeg(touch);
}

void GameScene::onTouchEnded(Touch *touch, Event *unused_event) {
	if (ready_ball_) {
		scanBallCollide();
		Vec2 touchPos = touch->getLocation();
		if (touchPos.y > ready_ball_->getPositionY()) {
			shootBall(touchPos);
		}
	}
}

void GameScene::adjustGuidingArrow(Touch* touch){
	Vec2 touchPos = touch->getLocation();
	float delta_y = touchPos.y - BALL_READY_POS.y;
	float delta_x = touchPos.x - BALL_READY_POS.x;
	if (delta_y == 0 ){
		guiding_arrow_->setRotation(0);
	} else {
		float tangent = delta_y/delta_x;
		float degree = CC_RADIANS_TO_DEGREES(atan(tangent));
		if (delta_x < 0) degree += 180;
		guiding_arrow_->setRotation(90 - degree);
	}
}

void GameScene::shootBall(Vec2 pos){
	ready_ball_->shot(pos);
	flying_ball_ = ready_ball_;
	ready_ball_ = nullptr;
	current_ball_left_ --;
	updateBallsLeftLabel();
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
	if (available_ball_list_.size() > 0){
		int ran = rand() % (available_ball_list_.size());
		return (std::string)(available_ball_list_.at(ran));
	} else {
		// No available ball left, only unshotable ball left
		return pending_ball_->getName();
	}
}

bool GameScene::checkBallAvailable(Ball* checked_ball){
	for (Ball* ball : stucking_ball_list_){
		if (!checked_ball->getName().compare(ball->getName())){
			return true;
		}
	}
	return false;
}

void GameScene::checkPendingBallAndRecreateIfUnavaiable(){
	if (!checkBallAvailable(pending_ball_)){
		substitute_pending_ball();
	}
}

void GameScene::spawnBall() {
	ready_ball_ = pending_ball_;
	create_pending_ball();
	ready_ball_->setPosition(BALL_READY_POS);
//	ready_ball_->addSpecialType(Ball::SpecialType::SPECIAL_1_3);
//	ready_ball_->setGameScene(this);
//	addChild(ready_ball_, BALL_ZORDER);
}

void GameScene::swapBall(){
	if (pending_ball_){
		Vec2 mediator_pos = ready_ball_->getPosition();
		ready_ball_->setPosition(pending_ball_->getPosition());
		pending_ball_->setPosition(mediator_pos);
		Ball* mediator_ball = ready_ball_;
		ready_ball_ = pending_ball_;
		pending_ball_ = mediator_ball;
		mediator_ball = nullptr;
		delete mediator_ball;
	}
}

bool GameScene::isPendingBallTouch(Touch* touch){
	Vec2 touch_pos = touch->getLocation();
	if (pending_ball_->getBoundingBox().containsPoint(touch_pos)) return true;
	return false;
}

void GameScene::ballDoneShot(Ball* ball) {
	stopScanBallCollide();
	if (!ball->containSpecialType(Ball::SpecialType::SPECIAL_4)){
		stucking_ball_list_.pushBack(ball);
	}

	if (is_key_ball_shot_){ // key ball was shot
		for (Ball* ball : stucking_ball_list_){
			boom_ball_list_.pushBack(ball);
		}

	} else {

		if (ball->getSpecialType() == Ball::SpecialType::SPECIAL_0) { // normal ball
			recursiveCheckSameBall(ball->getSlot(),ball->getSlot());
			refreshTraversedBoolOfSlots();
			if (same_ball_list_.size() >= 3){
				for (Ball* ball : same_ball_list_){
					ball->getSlot()->is_traversed_ = true;
					boom_ball_list_.pushBack(ball);
				}
			}
			same_ball_list_.clear();
		} else if (ball->getSpecialType() == Ball::SpecialType::SPECIAL_1) { // ball special_1
			// TODO
			Slot* special_slot = ball->getSlot();
			addBallToBoomList(ball, special_slot);
			int rec_height = 4;
			int rec_width = 2;
			for (int i = 1; i <= rec_height; i += 2){

				Slot* slot_above_left = getAboveLeftSlot(special_slot);
				Slot* slot_above_right = getAboveRightSlot(special_slot);
				Slot* slot_middle = nullptr;
				if (slot_above_left) {
					slot_middle = getAboveRightSlot(slot_above_left);
				} else if (slot_above_right){
					slot_middle = getAboveLeftSlot(slot_above_right);
				} else {
					break;
				}

				addBallToBoomList(slot_above_left);
				addBallToBoomList(slot_above_right);
				addBallToBoomList(slot_middle);

				if (slot_middle){
					special_slot = slot_middle;
				} else {
					break;
				}

			}

		} else if (ball->getSpecialType() == Ball::SpecialType::SPECIAL_2) { // ball special_2
			// TODO
			Slot* special_slot = ball->getSlot();
			addBallToBoomList(special_slot);

			Slot* slot_above_left = getAboveLeftSlot(special_slot);
			addBallToBoomList(slot_above_left);

			Slot* slot_above_right = getAboveRightSlot(special_slot);
			addBallToBoomList(slot_above_right);

			Slot* slot_next_to_left = getNextToLeftSlot(special_slot);
			addBallToBoomList(slot_next_to_left);

			Slot* slot_next_to_right = getNextToRightSlot(special_slot);
			addBallToBoomList(slot_next_to_right);

			Slot* slot_below_left = getBelowLeftSlot(special_slot);
			addBallToBoomList(slot_below_left);

			Slot* slot_below_right = getBelowRightSlot(special_slot);
			addBallToBoomList(slot_below_right);

		} else if (ball->getSpecialType() == Ball::SpecialType::SPECIAL_3) { // ball special_3
			// TODO
			Slot* special_slot = ball->getSlot();
			addBallToBoomList(ball, special_slot);
			int above_row_index = special_slot->row_index_ - 1;
			if (above_row_index >= 0){
				addARowToBoomList(above_row_index);
			}
		} else if (ball->getSpecialType() == Ball::SpecialType::SPECIAL_4) { // ball special_4
			// TODO
			ball->explode();
		} else if (ball->getSpecialType() == Ball::SpecialType::SPECIAL_1_2){ // ball special 1 + 2
			// TODO
			Slot* special_slot = ball->getSlot();
			int loop_num = 3;
			Slot* tmp_slot = special_slot;
			for (int i = 0; i < loop_num; i++ ){
				if (tmp_slot == nullptr)
					break;
				addBallToBoomList(tmp_slot);

				Slot* slot_next_to_left = getNextToLeftSlot(tmp_slot);
				addBallToBoomList(slot_next_to_left);

				Slot* slot_next_to_right = getNextToRightSlot(tmp_slot);
				addBallToBoomList(slot_next_to_right);

				Slot* slot_above_left = getAboveLeftSlot(tmp_slot);
				addBallToBoomList(slot_above_left);

				Slot* slot_above_right = getAboveRightSlot(tmp_slot);
				addBallToBoomList(slot_above_right);

				if (tmp_slot->row_index_ > 1){
					tmp_slot = slots_2d[tmp_slot->row_index_ - 2][tmp_slot->column_index_];
				} else {
					break;
				}
			}
		} else if(ball->getSpecialType() == Ball::SpecialType::SPECIAL_1_3){ // ball special 1 + 3
			// TODO
			Slot* special_slot = ball->getSlot();
			addBallToBoomList(ball, special_slot);
			int above_slot_index = special_slot->row_index_ - 1;
			if (above_slot_index >= 0){
				addARowToBoomList(above_slot_index);
				int lvl2_above_slot_index = above_slot_index - 1;
				if (lvl2_above_slot_index >= 0){
					addARowToBoomList(lvl2_above_slot_index);
					Slot* tmp_slot = slots_2d[lvl2_above_slot_index][special_slot->column_index_];

					Slot* slot_above_left = getAboveLeftSlot(tmp_slot);
					addBallToBoomList(slot_above_left);

					Slot* slot_above_right = getAboveRightSlot(tmp_slot);
					addBallToBoomList(slot_above_right);

					if (lvl2_above_slot_index > 1){
						Slot* tmp_slot_a = slots_2d[lvl2_above_slot_index - 2][special_slot->column_index_];
						addBallToBoomList(tmp_slot_a);
						Slot* slot_next_to_left_a = getNextToLeftSlot(tmp_slot_a);
						addBallToBoomList(slot_next_to_left_a);
						Slot* slot_next_to_right_a = getNextToRightSlot(tmp_slot_a);
						addBallToBoomList(slot_next_to_right_a);
					}

				}
			}

		} else if (ball->getSpecialType() == Ball::SpecialType::SPECIAL_2_3){ // ball special 2 + 3
			Slot* special_slot = ball->getSlot();
			int above_slot_index = special_slot->row_index_ - 1;
			int below_slot_index = special_slot->row_index_ + 1;
			if (above_slot_index >= 0){
				addARowToBoomList(above_slot_index);
			}
			addARowToBoomList(special_slot->row_index_);
			addARowToBoomList(below_slot_index);
		} else { // not any of above
			ball->explode();
		}

		checkUntieToTop();
		for (Ball* ball : untie_ball_list_){
			boom_ball_list_.pushBack(ball);
		}
	}

	boomBalls();

	untie_ball_list_.clear();
	refreshTraversedBoolOfSlots();

	if (stucking_ball_list_.size() == 0){
		showWinGame();
		return;
	}

	redetermineCurrentMaxRow();
	checkLost();

	build_available_ball_list();
	checkPendingBallAndRecreateIfUnavaiable();
	spawnBall();
	flying_ball_ = nullptr;

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
		ball->explode();
	}
}

void GameScene::boomSameBalls(){
	for (Ball* ball : same_ball_list_){
		ball->getSlot()->ball_ = nullptr;
		stucking_ball_list_.eraseObject(ball);
		ball->explode();
	}
}

void GameScene::boomABall(Ball* ball){
	ball->getSlot()->ball_ = nullptr;
	stucking_ball_list_.eraseObject(ball);
	ball->explode();
}

void GameScene::boomBalls(){
	int score = 0;
	int increment = 10;
	for (Ball* ball : boom_ball_list_){
		score += increment;
		score_ += score;
//		ball->getSlot()->ball_ = nullptr;
//		stucking_ball_list_.eraseObject(ball);

		std::string score_string = std::to_string(score);
		Label* label = Label::create(score_string,"Arial",20);
		label->setPosition(ball->getPosition());
		EaseIn* scale_out = EaseIn::create(ScaleTo::create(0.5f,2.0f),2.0f);
		FadeOut* fade_out = FadeOut::create(0.5f);
		label->runAction(Sequence::create(scale_out,fade_out,CallFunc::create(CC_CALLBACK_0(GameScene::removeSelf,this,label)),nullptr));
		addChild(label,BALL_ZORDER + 1);

		boomABall(ball);
//		ball->explode();
	}
	updateScoreLabel();
	boom_ball_list_.clear();
}

void GameScene::addARowToBoomList(int row_index){
	int col_num = SLOT_PER_ROW_NUM;
	if (row_index %2 == 1){
		col_num = SLOT_PER_ROW_NUM - 1;
	}
	for (int j = 0; j < col_num; j++){
		Slot* boom_slot = slots_2d[row_index][j];
		addBallToBoomList(boom_slot);
	}
}

void GameScene::updateScoreLabel(){
//	score_label_->setString(std::to_string(score_));
}

void GameScene::updateBallsLeftLabel(){
//	balls_left_label_->setString(std::to_string(current_ball_left_));
}

void GameScene::updateTimeLeftLabel(){
//	time_left_label_->setString(std::to_string((int)current_time_left_));
}

void GameScene::removeSelf(Node* sender){
	sender->removeFromParent();
}

void GameScene::refreshTraversedBoolOfSlots(){
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
		if (col_i > 0){
			return slots_2d[row_i][col_i - 1];
		} else {
			return nullptr;
		}
}

Slot* GameScene::getBelowRightSlot(Slot* slot){
	int row_i = slot->row_index_;
	int col_i = slot->column_index_;
		if (row_i % 2 == 0){
			if (col_i < SLOT_PER_ROW_NUM - 1){
				return slots_2d[row_i + 1][col_i];
			} else {
				return nullptr;
			}
		} else {
			return slots_2d[row_i + 1][col_i + 1];
		}

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
		if (coming_slot == nullptr || coming_slot->hasBall()){
			coming_slot = getBelowLeftSlot(target_slot);
		}
	} else
	// below - left
	if (contact_degree <= 0 && contact_degree > -60){
		coming_slot = getBelowLeftSlot(target_slot);
		if (coming_slot ==  nullptr || coming_slot->hasBall()){
			coming_slot = getBelowRightSlot(target_slot);
		}
	} else
	// next to right
	if (contact_degree > 60){
		coming_slot = getNextToRightSlot(target_slot);
		if (coming_slot->hasBall()){
			coming_slot = getBelowRightSlot(target_slot);
		}
	} else
	// next to left
	if (contact_degree < -60){
		coming_slot = getNextToLeftSlot(target_slot);
		if (coming_slot->hasBall()){
			coming_slot = getBelowLeftSlot(target_slot);
		}
	}
	coming_ball->installIntoSlot(coming_slot);
}

void GameScene::gameStart(){
	gameState = GameState::PLAYING;
//	scheduleBallsFlowDown();
	scheduleTimer();
}

void GameScene::gameStop(){
	unscheduleBallsFlowDown();
	unscheduleTimer();
}

void GameScene::scheduleTimer(){
	schedule(schedule_selector(GameScene::startTimer));
}

void GameScene::unscheduleTimer(){
	unschedule(schedule_selector(GameScene::startTimer));
}

void GameScene::startTimer(float dt){
	current_time_left_ -= dt;
	updateTimeLeftLabel();
	if (current_time_left_ <= 0){
		showLoseGame();
	}
}

void GameScene::oneRowDown(float dt){
	row_down_times_ ++;
	wallDownOneRow();
	adjustPosOfSlotsOneRowDown();
	readjustPosOfBallsByPosOfSlots();
	checkLost();
}

void GameScene::wallDownOneRow(){
	Vec2 top_wall_new_pos = top_wall_->getPosition() - Vec2(0,EV3_);
	top_wall_->setPosition(top_wall_new_pos);
}

void GameScene::ballsFlowDown(float dt){
	float flow_distance = scroll_down_velocity_ * dt;
	Vec2 top_wall_new_pos = top_wall_->getPosition() - Vec2(0,flow_distance);
	top_wall_->setPosition(top_wall_new_pos);

	// adjust position of slots
	for (std::vector<Slot*> row : slots_2d){
			for (Slot* slot : row){
				slot->pos_ = slot->pos_ - Vec2(0,flow_distance);
			}
		}

	readjustPosOfBallsByPosOfSlots();
	current_lowest_y_ -= flow_distance;
	checkLost();
}

void GameScene::adjustPosOfSlotsOneRowDown(){
	for (std::vector<Slot*> row : slots_2d){
		for (Slot* slot : row){
			slot->pos_ = slot->pos_ - Vec2(0,EV3_);
		}
	}
}

void GameScene::readjustPosOfBallsByPosOfSlots(){
	for (Ball* ball : stucking_ball_list_){
		ball->setPosition(ball->getSlot()->pos_);
	}
}

void GameScene::redetermineCurrentMaxRow(){
	current_max_row_num_ = 0;
	for (Ball* ball : stucking_ball_list_){
		int row_index_of_ball = ball->getSlot()->row_index_;
		if (current_max_row_num_ < row_index_of_ball){
			current_max_row_num_ = row_index_of_ball;
			current_lowest_y_ = ball->getPosition().y - E_;
		}
	}
//	std::vector<Slot*> last_row = (std::vector<Slot*>)slots_2d.at(current_max_row_num_);
//	for (Slot* slot : last_row){
//		if (slot->hasBall()){
//			current_lowest_y_ = slot->pos_.y - E_;
//			break;
//		}
//	}
}

void GameScene::checkLost(){
	if (isLoseConditionMet()){
		showLoseGame();
	}
}

bool GameScene::isLoseConditionMet(){
	if (yBelowLimitLostConditionMet()) return true;
	if (runOutOfBallLostConditionMet()) return true;
	return false;
}

bool GameScene::yBelowLimitLostConditionMet(){
//	std::vector<Slot*> last_row = (std::vector<Slot*>)slots_2d.at(current_max_row_num_);
//	for (Slot* slot : last_row){
//		if (slot->hasBall()){
//			 = slot->pos_.y - E_;
//			break;
//		}
//	}
	if (current_lowest_y_ <= Y_END_LIMIT){
		return true;
	}
	return false;
}

bool GameScene::runOutOfBallLostConditionMet(){
	if (current_ball_left_ <= 0){
		return true;
	}
	return false;
}

bool GameScene::rowExceedingLoseConditionMet(){
	redetermineCurrentMaxRow();
	if ((current_max_row_num_ + row_down_times_) > ROW_NUM_PLAYABLE) return true;
	return false;
}

void GameScene::addBallToBoomList(Ball* ball){
	if (ball){
		addBallToBoomList(ball, ball->getSlot());
	}
}

void GameScene::addBallToBoomList(Ball* ball, Slot* slot){
	if (slot && ball){
		boom_ball_list_.pushBack(ball);
		slot->is_traversed_ = true;
	}
}

void GameScene::addBallToBoomList(Slot* slot){
	if (slot){
		addBallToBoomList(slot->ball_,slot);
	}
}

void GameScene::showWinGame(){
	gameState = GameState::WIN;
	int star_num = 0;
//	unscheduleBallsFlowDown();
	gameStop();

	if (score_ >= stage_setup_.star_3){
		star_num = 3;
	} else if (score_ >= stage_setup_.star_2){
		star_num = 2;
	} else {
		star_num = 1;
	}

	StageInfo* stage_info = StageManager::getInstance()->getStageInfoByStage(stage_);
	if (star_num > stage_info->getNo()){
		stage_info->setStarNum(star_num);
		stage_info->updateStageInfo();
	}
	Stage next_stage = stage_;
	next_stage.no_ ++;
	if (next_stage.no_ > TOTAL_STAGE_PER_PLANET){
		next_stage.no_ = 1;
		next_stage.planet_name_ = StageManager::getInstance()->getNextPlanetName(stage_.planet_name_);
	}

	StageInfo* next_stage_info = StageManager::getInstance()->getStageInfoByStage(next_stage);
	if (!next_stage_info){
		next_stage_info = StageInfo::create(next_stage.planet_name_,next_stage.no_,0);
		StageManager::getInstance()->addNewStageInfoList(next_stage_info);
	}

	setTouchEnabled(false);
	runAction(Sequence::create(DelayTime::create(1.0f),CallFunc::create([this,star_num](){
		Director::getInstance()->replaceScene(ResultScene::createScene(true,score_,star_num,stage_));
	}),nullptr));

}

void GameScene::showLoseGame(){
	gameState = GameState::LOST;
//	unscheduleBallsFlowDown();
	gameStop();
	runAction(Sequence::create(DelayTime::create(1.0f),CallFunc::create([this](){
		Director::getInstance()->replaceScene(ResultScene::createScene(false,score_,0,stage_));
	}),nullptr));
}

void GameScene::skill_btn_callback(Ref* sender){
	MenuItem* btn = (MenuItem*)sender;
	int tag = btn->getTag();
	switch (tag){
		case LEAF_SKILL_BTN_TAG:
			ready_ball_->addSpecialType(Ball::SpecialType::SPECIAL_1);
			break;
		case ARROW_SKILL_BTN_TAG:
			ready_ball_->addSpecialType(Ball::SpecialType::SPECIAL_2);
			break;
		case FLOWER_SKILL_BTN_TAG:
			ready_ball_->addSpecialType(Ball::SpecialType::SPECIAL_3);
			break;
		case BOOM_SKILL_BTN_TAG:
			ready_ball_->addSpecialType(Ball::SpecialType::SPECIAL_4);
			break;
		default:
			break;
	}
}

GameScene::GameScene() :
ready_ball_(NULL), flying_ball_(NULL), pending_ball_(NULL), top_wall_(NULL),
row_down_times_(0), current_max_row_num_(0), score_(0), score_label_(NULL),
guiding_arrow_(NULL), scroll_down_velocity_(20), current_lowest_y_(1600),
current_ball_left_(0), current_time_left_(0), balls_left_label_(NULL), time_left_label_(NULL),
gameState(GameState::NONE), is_key_ball_shot_(false), guide_dots_(NULL)
{
}

GameScene::~GameScene() {
}

