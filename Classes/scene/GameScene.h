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
#include "../delegate/BallDelegate.h"
#include "../manager/StageManager.h"

USING_NS_CC;

class GameScene : public Layer , public BallDelegate {
public:

	static Scene* createScene();
	static Scene* createScene(Stage stage);
	static GameScene* create();
	static GameScene* create(Stage stage);
	virtual bool init();
	virtual bool init(Stage stage);
	virtual void enableTouch();
	virtual void initialize_ball_list();
	virtual void initialize_slots();
		virtual Vec2 posOfSlot(int index_row, int index_col);
		virtual void setPosForSlot(Slot* slot);
	virtual void initialize_balls();
	virtual void create_pending_ball();

	virtual void scanBallCollide();
	virtual void stopScanBallCollide();
	virtual void adjustBallToTopSlot(Ball*);
	virtual void adjustBallHitBall(Ball* target_ball, Ball* coming_ball);
	virtual void recursiveCheckSameBall(Slot* origin_slot, Slot* traversed_slot);
	virtual bool isBallsSameColor(Ball* ball_1,Ball* ball_2);
	virtual void boomSameBalls();
	virtual void checkUntieToTop();
	virtual void boomUntieToTop();
	virtual void recursiveCheckHangToTop(Slot*);
	virtual void refreshTraversedBoolOfSlots();
	virtual float angleWhenContactOfBalls(Ball* target_ball, Ball* coming_ball);

	void update(float dt);

	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchMoved(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);

	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* unused_event);
	virtual void keyBackPressed();

	void spawnBall();
	std::string generate_random_ball_name();
	Slot* getAboveRightSlot(Slot*);
	Slot* getAboveLeftSlot(Slot*);
	Slot* getNextToRightSlot(Slot*);
	Slot* getNextToLeftSlot(Slot*);
	Slot* getBelowRightSlot(Slot*);
	Slot* getBelowLeftSlot(Slot*);

	void showWinGame();

	// ----------Delegate
	// Ball Delegate
	void ballDoneShot(Ball*);

	GameScene();
	virtual ~GameScene();
protected:
	Size winsize_;
	std::vector<std::string> available_ball_list_;
	Vector<Ball*> stucking_ball_list_;
	std::vector<std::vector<Slot*>> slots_2d;
	Vector<Ball*> same_ball_list_;
	Vector<Ball*> untie_ball_list_;

	Ball* pending_ball_;
	Ball* ready_ball_;
	Ball* flying_ball_;

	Stage stage_;
};

#endif /* GAMESCENE_H_ */
