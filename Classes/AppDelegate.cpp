#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "scene/MainMenuScene.h"
#include "GameConstants.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);
    }

//    glview->setDesignResolutionSize(960, 1600, ResolutionPolicy::EXACT_FIT);
    glview->setDesignResolutionSize(WIDTH_RES, HEIGHT_RES, ResolutionPolicy::SHOW_ALL);

    // turn on display FPS
    director->setDisplayStats(true);

    std::vector<std::string> searchPaths;

    searchPaths.push_back(MAIN_MENU_FOLDER_PATH);
    searchPaths.push_back(UNIVERSE_FOLDER_PATH);
    searchPaths.push_back(GAME_SCENE_FOLDER_PATH);
    searchPaths.push_back(STAGE_CHOOSER_FOLDER_PATH);
    searchPaths.push_back(BALL_FOLDER_PATH);
    searchPaths.push_back(JSON_FILE_PATH);

    FileUtils::getInstance()->setSearchPaths(searchPaths);


    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
//    auto scene = HelloWorld::createScene();
    auto scene = MainMenuScene::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
