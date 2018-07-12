#ifndef __LessonListScene_SCENE_H__
#define __LessonListScene_SCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "network/HttpClient.h"

class LessonList : public cocos2d::Scene
{
public:
    cocos2d::ui::ListView *listView;
    int idx = 0;
    int count = 0;
//    static int coursesID;
    std::vector<int> iList;
    std::vector<int> iDList;
    std::vector<std::string> sName;
    std::vector<std::string> vDescription;
    std::vector<std::string> vContent;
    
    cocos2d::Sprite *loading1;
    cocos2d::Sprite *loading2;
    cocos2d::Sprite *bgLoading;
    
    static cocos2d::Scene* createScene(int Id, std::string courses, std::string description);

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(LessonList);
    
    void getLessonList();
    void hideLoading();
    void selectedItemEvent(Ref *sender, cocos2d::ui::ListView::EventType type);
    void onCompleteHttpRequest(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);
    void onRequestImgCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);
    void loadImage(std::string str);
};

#endif // __HELLOWORLD_SCENE_H__
