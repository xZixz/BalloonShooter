/*
 * GameScene.h
 *
 *  Created on: Sep 10, 2014
 *      Author: dudu
 */

#ifndef GAMESCENE_H_
#define GAMESCENE_H_

#include "cocos2d.h"
#include "../model/Ball.h"
#include "../model/GuideDots.h"
#include "../delegate/BallDelegate.h"
#include "../manager/StageManager.h"

USING_NS_CC;

class GameScene : public Layer , public BallDelegate {
public:

	enum GameState {
		NONE,
		PLAYING,
		LOST,
		WIN
	};

	static Scene* createScene();
	static Scene* createScene(Stage stage);
	static GameScene* create();
	static GameScene* create(Stage stage);
	virtual bool init();
	virtual bool init(Stage stage);
	virtual void enableTouch();
	virtual void initialize_slots();
		virtual Vec2 posOfSlot(int index_row, int index_col);
		virtual void setPosForSlot(Slot* slot);
	virtual void initialize_balls();
	virtual void build_available_ball_list();
	virtual void create_pending_ball();
	virtual void substitute_pending_ball();

	virtual void shootBall(Vec2 pos);
	virtual void scanBallCollide();
	virtual void stopScanBallCollide();
	virtual void adjustBallToTopSlot(Ball*);
	virtual void adjustBallHitBall(Ball* target_ball, Ball* coming_ball);
	virtual void recursiveCheckSameBall(Slot* origin_slot, Slot* traversed_slot);
	virtual bool isBallsSameColor(Ball* ball_1,Ball* ball_2);
	virtual void boomSameBalls();
	virtual void checkUntieToTop();
	virtual void boomUntieToTop();
	virtual void boomBalls();
	virtual void boomABall(Ball*);
	virtual void addARowToBoomList(int row_index);
	virtual void recursiveCheckHangToTop(Slot*);
	virtual void refreshTraversedBoolOfSlots();
	virtual float angleWhenContactOfBalls(Ball* target_ball, Ball* coming_ball);


	virtual void gameStart();
	virtual void gameStop();
	virtual void scheduleTimer();
	virtual void unscheduleTimer();
	virtual void startTimer(float dt);
	virtual void oneRowDown(float dt);
	virtual void wallDownOneRow();
	virtual void scheduleBallsFlowDown();
	virtual void unscheduleBallsFlowDown();
	virtual void ballsFlowDown(float dt);
	virtual void adjustPosOfSlotsOneRowDown();
	virtual void readjustPosOfBallsByPosOfSlots();

	virtual void redetermineCurrentMaxRow();
	virtual void checkLost();
	virtual bool isLoseConditionMet();
	virtual bool yBelowLimitLostConditionMet();
	virtual bool runOutOfBallLostConditionMet();
	virtual bool rowExceedingLoseConditionMet();

	virtual void updateScoreLabel();
	virtual void updateBallsLeftLabel();
	virtual void updateTimeLeftLabel();
	virtual void adjustGuidingArrow(Touch*);

	virtual void addBallToBoomList(Ball*);
	virtual void addBallToBoomList(Ball*, Slot*);
	virtual void addBallToBoomList(Slot*);

	void update(float dt);

	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchMoved(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);

	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* unused_event);
	virtual void keyBackPressed();
	virtual void removeSelf(Node* sender);

	void spawnBall();
	void swapBall();
	virtual bool isPendingBallTouch(Touch* touch);
	virtual bool checkBallAvailable(Ball* checked_ball);
	virtual void checkPendingBallAndRecreateIfUnavaiable();
	std::string generate_random_ball_name();
	Slot* getAboveRightSlot(Slot*);
	Slot* getAboveLeftSlot(Slot*);
	Slot* getNextToRightSlot(Slot*);
	Slot* getNextToLeftSlot(Slot*);
	Slot* getBelowRightSlot(Slot*);
	Slot* getBelowLeftSlot(Slot*);

	void showWinGame();
	void showLoseGame();

	void skill_btn_callback(Ref*);

	// ----------Delegate
	// Ball Delegate
	virtual void ballDoneShot(Ball*);

	GameScene();
	virtual ~GameScene();
protected:
	Size winsize_;
	Sprite* top_wall_;
	Label* score_label_;
	Label* balls_left_label_;
	Label* time_left_label_;
	Sprite* guiding_arrow_;
	GuideDots* guide_dots_;

	std::vector<std::string> available_ball_list_;
	Vector<Ball*> stucking_ball_list_;
	std::vector<std::vector<Slot*>> slots_2d;
	Vector<Ball*> same_ball_list_;
	Vector<Ball*> untie_ball_list_;
	Vector<Ball*> boom_ball_list_;

	Ball* pending_ball_;
	Ball* ready_ball_;
	Ball* flying_ball_;

	Stage stage_;
	StageSetup stage_setup_;
	GameState gameState;

	int row_down_times_;
	int current_max_row_num_;
	int score_;

	float scroll_down_velocity_;
	float current_lowest_y_;

	int current_ball_left_;
	float current_time_left_;

	bool is_key_ball_shot_;

};

#endif /* GAMESCENE_H_ */
