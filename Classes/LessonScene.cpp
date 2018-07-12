#include "LessonScene.h"
#include "SimpleAudioEngine.h"
#include "json/document.h"
#include "json/rapidjson.h"
#include "LessonListScene.h"
#include "SlideScene.h"
#include "MainGameScene.h"

USING_NS_CC;
USING_NS_CC_EXT;

int cId = 0;
int lId = 0;
int indexLesson = 0;
std::string sDesCript = "";
std::string sCont = "";
std::string cDes = "";
std::string cN = "";

Scene* LessonScene::createScene(int index, int coursesId, int lessonId, std::string description, std::string sContent, std::string cDescription, std::string cName)
{
    cId = coursesId;
    lId = lessonId;
    indexLesson = index;
    sDesCript = description;
    sCont = sContent;
    cDes = cDescription;
    cN = cName;
    return LessonScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool LessonScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto background = Sprite::create("new-bg-sunbot-3.png");
    background->setContentSize(Size(visibleSize.width, visibleSize.height));
    background->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    this->addChild(background);
    
    auto pannel = Sprite::create("new-pannel-lesson.png");
    pannel->setAnchorPoint(Vec2(0.5, 0));
    pannel->setContentSize(Size(2.8 * visibleSize.width / 4, 4 * visibleSize.height / 5));
    pannel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 14));
    this->addChild(pannel);
    
    auto titlePannel = Sprite::create("new-title-pannel.png");
    titlePannel->setAnchorPoint(Vec2(0.5, 0));
    titlePannel->setContentSize(Size(visibleSize.width / 4, visibleSize.height / 8));
    titlePannel->setPosition(Vec2(origin.x + visibleSize.width / 2, pannel->getPosition().y + pannel->getContentSize().height - 10));
    this->addChild(titlePannel);
    
    auto sunbot = Sprite::create("sunbot-right.png");
    sunbot->setContentSize(Size(sunbot->getContentSize().width * visibleSize.height / (3 * sunbot->getContentSize().height), visibleSize.height / 3));
    sunbot->setAnchorPoint(Vec2(0, 0));
    sunbot->setPosition(Vec2(origin.x + 5, origin.y + visibleSize.height / 8));
    this->addChild(sunbot);
    
    auto column = Sprite::create("new-column.png");
    column->setAnchorPoint(Vec2(0.5, 0));
    column->setContentSize(Size(column->getContentSize().width * (visibleSize.height / (2 * column->getContentSize().height)), visibleSize.height / 2));
    column->setPosition(Vec2(origin.x + visibleSize.width - sunbot->getContentSize().width / 1.8, origin.y + visibleSize.height / 10));
    this->addChild(column);
    
    float buttonWidth = visibleSize.width / 7;
    
    auto btBack = ui::Button::create("new-menu-button-1.png");
    btBack->setScale(buttonWidth / btBack->getContentSize().width);
    btBack->setPosition(Vec2(column->getPosition().x, column->getPosition().y + column->getContentSize().height / 4));
    btBack->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type) {
            case ui::Widget::TouchEventType::BEGAN:
                CCLOG("BEGAN");
                break;
            case ui::Widget::TouchEventType::ENDED:
                auto lessonList = LessonList::createScene(cId, cN, cDes);
                Director::getInstance()->replaceScene(lessonList);
                break;
        }
    });
    this->addChild(btBack);
    
    auto lblBack = Label::createWithTTF("Back", "fonts/Comic Kings.ttf", 6);
    lblBack->setPosition(Vec2(btBack->getContentSize().width / 2, btBack->getContentSize().height / 2));
    lblBack->setTextColor(Color4B::WHITE);
    btBack->addChild(lblBack);

    auto btPlay = ui::Button::create("new-menu-button-2.png");
    btPlay->setScale(buttonWidth / btPlay->getContentSize().width);
    btPlay->setPosition(Vec2(column->getPosition().x, column->getPosition().y + column->getContentSize().height / 2));
    btPlay->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type) {
            case ui::Widget::TouchEventType::BEGAN:
                CCLOG("BEGAN");
                break;
            case ui::Widget::TouchEventType::ENDED:
                auto mainGame = MainGameScene::createScene(indexLesson, cId, lId, sDesCript, sCont, cDes, cN);
                Director::getInstance()->replaceScene(mainGame);
                break;
        }
    });
    this->addChild(btPlay);
    
    auto lblPlay = Label::createWithTTF("Play", "fonts/Comic Kings.ttf", 6);
    lblPlay->setPosition(Vec2(btPlay->getContentSize().width / 2, btPlay->getContentSize().height / 2));
    lblPlay->setTextColor(Color4B::WHITE);
    btPlay->addChild(lblPlay);

    auto btSlide = ui::Button::create("new-menu-button-1.png");
    btSlide->setScale(buttonWidth / btSlide->getContentSize().width);
    btSlide->setPosition(Vec2(column->getPosition().x, column->getPosition().y + 3 * column->getContentSize().height / 4));
    btSlide->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type) {
            case ui::Widget::TouchEventType::BEGAN:
                CCLOG("BEGAN");
                break;
            case ui::Widget::TouchEventType::ENDED:
                auto slide = SlideScene::createScene(cId, lId, indexLesson, sDesCript, sCont, cDes, cN);
                Director::getInstance()->replaceScene(slide);
                break;
        }
    });
    this->addChild(btSlide);
    
    auto lblSlide = Label::createWithTTF("Slide", "fonts/Comic Kings.ttf", 6);
    lblSlide->setPosition(Vec2(btSlide->getContentSize().width / 2, btSlide->getContentSize().height / 2));
    lblSlide->setTextColor(Color4B::WHITE);
    btSlide->addChild(lblSlide);
    
    auto lblTitle = Label::createWithTTF("Bài " + std::to_string(indexLesson), "fonts/Pacifico.ttf", 15);
    lblTitle->setPosition(Vec2(titlePannel->getContentSize().width / 2, titlePannel->getContentSize().height / 2));
    lblTitle->setTextColor(Color4B::WHITE);
    titlePannel->addChild(lblTitle);
    
    std::istringstream iss(cDes);
    std::vector<std::string> results(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>());
    std::string str = "";
    std::string strOneLine = "";
    for (int i = 0; i < results.size(); i++) {
        if(strOneLine.length() < 70 && i < results.size() - 1) {
            strOneLine = strOneLine + " " + results[i].c_str();
        } else {
            if(i == results.size() - 1) {
                strOneLine = strOneLine + " " + results[i].c_str();
            }
            str = str + strOneLine + "\n";
            strOneLine = "";
        }
    }
    
    auto lblContent = Label::createWithTTF(str, "fonts/arial.ttf", 11);
    lblContent->setAnchorPoint(Vec2(0.5, 1));
    lblContent->setPosition(Vec2(pannel->getContentSize().width / 2, pannel->getContentSize().height - 20));
    lblContent->setTextColor(Color4B::BLACK);
    pannel->addChild(lblContent);
    
    return true;
}

void LessonScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
