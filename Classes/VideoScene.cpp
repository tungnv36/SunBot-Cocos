#include "VideoScene.h"
#include "SimpleAudioEngine.h"
#include "json/document.h"
#include "json/rapidjson.h"

USING_NS_CC;

Scene* VideoScene::createScene()
{
    return VideoScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool VideoScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
//    experimental::ui::VideoPlayer *videoPlayer = experimental::ui::VideoPlayer::create();
//    videoPlayer->setURL("https://www.youtube.com/embed/XqZsoesa55w");
//    videoPlayer->setContentSize(Size(visibleSize.width, visibleSize.height));
//    videoPlayer->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
//    videoPlayer->play();
//    videoPlayer->setFullScreenEnabled(true);
//    this->addChild(videoPlayer);

    experimental::ui::WebView *webView = experimental::ui::WebView::create();
    webView->loadURL("https://www.youtube.com/embed/XqZsoesa55w");
    webView->setContentSize(Size(visibleSize.width, visibleSize.height));
    webView->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    webView->setScalesPageToFit(true);
    this->addChild(webView);
    
    auto btBack = ui::Button::create("ic-stone-close.png");
    btBack->setScale(20 / btBack->getContentSize().width);
    btBack->setPosition(Vec2(origin.x + 15, origin.y + visibleSize.height - 15));
    btBack->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type) {
            case ui::Widget::TouchEventType::BEGAN:
                CCLOG("BEGAN");
                break;
            case ui::Widget::TouchEventType::ENDED:
                CCLOG("ENDED");
            default:
                break;
        }
    });
    this->addChild(btBack);
    
    return true;
}

void VideoScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
