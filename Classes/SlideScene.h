#ifndef __SlideScene_SCENE_H__
#define __SlideScene_SCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "network/HttpClient.h"

class SlideScene : public cocos2d::Scene
{
public:
//    cocos2d::ui::ListView *listView;
//    int idx = 0;
//    int count = 0;
//    std::vector<int> iList;
//    std::vector<int> iDList;
//    std::vector<std::string> sName;
//    std::vector<std::string> vDescription;
//    
//    cocos2d::Sprite *loading1;
//    cocos2d::Sprite *loading2;
//    cocos2d::Sprite *bgLoading;
    
    static cocos2d::Scene* createScene(int index, int coursesId, int lessonId, std::string description, std::string sContent, std::string cDescription, std::string cName);

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(SlideScene);
};

#endif // __HELLOWORLD_SCENE_H__
