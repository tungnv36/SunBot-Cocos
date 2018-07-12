#include "SlideScene.h"
#include "SimpleAudioEngine.h"
#include "json/document.h"
#include "json/rapidjson.h"
#include "LessonScene.h"

USING_NS_CC;

int bIndex;
int bCoursesId;
int bLessonId;
std::string bDescription;
std::string bsContent;
std::string bcDescription;
std::string bcName;

Scene* SlideScene::createScene(int index, int coursesId, int lessonId, std::string description, std::string sContent, std::string cDescription, std::string cName)
{
    bIndex = index;
    bCoursesId = coursesId;
    bLessonId = lessonId;
    bDescription = description;
    bsContent = sContent;
    bcDescription = cDescription;
    bcName = cName;
    return SlideScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool SlideScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto btBack = ui::Button::create("ic-stone-close.png");
    btBack->setScale(20 / btBack->getContentSize().width);
    btBack->setPosition(Vec2(origin.x + 15, origin.y + visibleSize.height - 15));
    btBack->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type) {
            case ui::Widget::TouchEventType::BEGAN:
                CCLOG("BEGAN");
                break;
            case ui::Widget::TouchEventType::ENDED:
                auto lesson = LessonScene::createScene(bIndex, bCoursesId, bLessonId, bDescription, bsContent, bcDescription, bcName);
                Director::getInstance()->replaceScene(lesson);
                break;
        }
    });
    this->addChild(btBack, 1000);
    
    experimental::ui::WebView *webView = experimental::ui::WebView::create();
    webView->loadHTMLString(bsContent);
    webView->setContentSize(Size(visibleSize.width - 60, visibleSize.height));
    webView->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    webView->setScalesPageToFit(true);
    this->addChild(webView);

    return true;
}

void SlideScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
