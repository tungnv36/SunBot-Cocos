#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "network/HttpClient.h"

USING_NS_CC;
USING_NS_CC_EXT;

class Courses : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Courses);
    
    void selectedItemEvent(Ref *sender, ui::ListView::EventType type);
    void getCourses();
    void onCompleteHttpRequest(network::HttpClient *sender, network::HttpResponse *response);
    void onRequestImgCompleted(network::HttpClient *sender, network::HttpResponse *response);
    void loadImage(std::string str);
    void hideLoading();
    bool replace(std::string& str, const std::string& from, const std::string& to);
    void replaceAll(std::string& str, const std::string& from, const std::string& to);
};

#endif // __HELLOWORLD_SCENE_H__
