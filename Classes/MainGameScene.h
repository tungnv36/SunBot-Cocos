#ifndef __MainGameScene_SCENE_H__
#define __MainGameScene_SCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "network/HttpClient.h"

class MainGameScene : public cocos2d::Scene
{
public:
    int numberOfColumn = 8;
    int numberOfRow = 8;
    int idx = 0;
    int count = 0;
    std::vector<int> vIndexOfCell;
    std::vector<int> vType;
    std::vector<std::string> vAction;
    std::vector<cocos2d::Point> vPoint;
    std::vector<cocos2d::Point> vPointBreak;
    
    cocos2d::Sprite *loading1;
    cocos2d::Sprite *loading2;
    cocos2d::Sprite *bgLoading;
    
    static cocos2d::Scene* createScene(int index, int coursesId, int lessonId, std::string description, std::string sContent, std::string cDescription, std::string cName);

    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    bool onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainGameScene);
private:
//    cocos2d::PhysicsWorld *world;
//    void setPhysicWorld(cocos2d::PhysicsWorld *m_world)
//    {
//        world = m_world;
//    }
    
    void getMap();
    void hideLoading();
    void showLoading();
    void onCompleteHttpRequest(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);
    void onRequestImgCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);
    void loadImage(std::string str);
    void runSunBot();
    void clearGame();
    int getTypeByIndexOfCell(int indexOfCell);
    void gameWin();
    void gameOver();
    void gameSetting();
    void nextBackGame();
};

#endif // __HELLOWORLD_SCENE_H__
