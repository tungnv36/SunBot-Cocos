#include "LessonListScene.h"
#include "SimpleAudioEngine.h"
#include "json/document.h"
#include "json/rapidjson.h"
#include "CoursesScene.h"
#include "VideoScene.h"
#include "LessonScene.h"
#include <string>

USING_NS_CC;
USING_NS_CC_EXT;

int coursesID = 0;
std::string sCourses = "";
std::string sDescription = "";

Scene* LessonList::createScene(int Id, std::string courses, std::string description)
{
    coursesID = Id;
    sCourses = courses;
    sDescription = description;
    return LessonList::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool LessonList::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto background = Sprite::create("new-bg-sunbot-2.png");
    background->setContentSize(Size(visibleSize.width, visibleSize.height));
    background->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    this->addChild(background);
    
    auto btBack = ui::Button::create("new-delete.png");
    btBack->setScale(20 / btBack->getContentSize().width);
    btBack->setPosition(Vec2(origin.x + 15, origin.y + visibleSize.height - 15));
    btBack->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type) {
            case ui::Widget::TouchEventType::BEGAN:
                CCLOG("BEGAN");
                break;
            case ui::Widget::TouchEventType::ENDED:
                auto coursesScene = Courses::createScene();
                Director::getInstance()->replaceScene(coursesScene);
                break;
        }
    });
    this->addChild(btBack);
    
    auto sunbot = Sprite::create("sunbot-right.png");
    float wSunbot = sunbot->getContentSize().width * 1.5 * visibleSize.height / (5 * sunbot->getContentSize().height);
    sunbot->setContentSize(Size(wSunbot, 1.5 * visibleSize.height / 5));
    sunbot->setAnchorPoint(Vec2(0, 0));
    sunbot->setPosition(Vec2(origin.x + 2, origin.y + visibleSize.height / 8));
    this->addChild(sunbot);
    
    auto pannelDes = Sprite::create("new-pannel-description.png");
    pannelDes->setContentSize(Size(visibleSize.width / 2.2, visibleSize.height / 7));
    pannelDes->setAnchorPoint(Vec2(0, 0.5));
    pannelDes->setPosition(Vec2(sunbot->getPosition().x + sunbot->getContentSize().width, sunbot->getPosition().y + sunbot->getContentSize().height / 2));
    this->addChild(pannelDes);
    
    auto lblTitle = Label::createWithTTF(sCourses, "fonts/Pacifico.ttf", 13);
    lblTitle->setAnchorPoint(Vec2(0, 0));
    lblTitle->setPosition(Vec2(20, pannelDes->getContentSize().height / 2 - 5));
    lblTitle->setTextColor(Color4B::BLACK);
    pannelDes->addChild(lblTitle);
    
    std::istringstream iss(sDescription);
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
    
    auto lblSubTitle = Label::createWithTTF(str, "fonts/arial.ttf", 7);
    lblSubTitle->setAnchorPoint(Vec2(0, 1));
    lblSubTitle->setPosition(Vec2(20, pannelDes->getContentSize().height / 2 - 5));
    lblSubTitle->setTextColor(Color4B::BLACK);
    pannelDes->addChild(lblSubTitle);
    
    float sizeButton = visibleSize.height / 10;
    
    auto btAbout = ui::Button::create("new-about.png");
    //    btAbout->setContentSize(Size(bottomPannel->getContentSize().height / 3, bottomPannel->getContentSize().height / 3));
    btAbout->setScale(sizeButton / btAbout->getContentSize().width);
    btAbout->setPosition(Vec2(origin.x + visibleSize.width - 10 - sizeButton / 2, origin.y + 10 + sizeButton / 2));
    btAbout->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
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
    this->addChild(btAbout);
    
    auto btMovie = ui::Button::create("new-movie.png");
    //    btMovie->setContentSize(Size(bottomPannel->getContentSize().height / 3, bottomPannel->getContentSize().height / 3));
    btMovie->setScale(sizeButton / btMovie->getContentSize().width);
    btMovie->setPosition(Vec2(origin.x + visibleSize.width - 20 - sizeButton / 2 - sizeButton, origin.y + 10 + sizeButton / 2));
    btMovie->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
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
    this->addChild(btMovie);
    
    auto btPlay = ui::Button::create("new-play.png");
    //    btPlay->setContentSize(Size(bottomPannel->getContentSize().height / 3, bottomPannel->getContentSize().height / 3));
    btPlay->setScale(sizeButton / btPlay->getContentSize().width);
    btPlay->setPosition(Vec2(origin.x + visibleSize.width - 30 - sizeButton / 2 - sizeButton - sizeButton, origin.y + 10 + sizeButton / 2));
    btPlay->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type) {
            case ui::Widget::TouchEventType::ENDED:
                auto videoScene = VideoScene::createScene();
                Director::getInstance()->replaceScene(videoScene);
                break;
        }
    });
    this->addChild(btPlay);
    
    listView = cocos2d::ui::ListView::create();
    listView->setDirection(ui::ScrollView::Direction::HORIZONTAL);
    listView->setClippingEnabled(false);
    listView->setAnchorPoint(Vec2(0, 0));
    listView->setContentSize(Size(visibleSize.width - 60, visibleSize.height - visibleSize.height / 3));
    listView->setPosition(Vec2(origin.x + 30, origin.y + visibleSize.height / 3));

    listView->setItemsMargin(20);
    listView->setBottomPadding(20);

    listView->addEventListener(CC_CALLBACK_2(LessonList::selectedItemEvent, this));
    this->addChild(listView);
    
    bgLoading = Sprite::create("bg-white.jpg");
    bgLoading->setContentSize(Size(visibleSize.width, visibleSize.height));
    bgLoading->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

    loading2 = Sprite::create("loading2.png");
    loading2->setContentSize(Size(visibleSize.height/3, visibleSize.height/3));
    loading2->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

    auto loadingRotate = RotateBy::create(0.1, 20);
    auto rotateReeat = RepeatForever::create(loadingRotate);
    loading2->runAction(rotateReeat);

    loading1 = Sprite::create("loading1.png");
    loading1->setContentSize(Size(visibleSize.height/3, visibleSize.height/3));
    loading1->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

    this->addChild(bgLoading);
    this->addChild(loading2);
    this->addChild(loading1);
    
    LessonList::getLessonList();
    
    return true;
}

void LessonList::selectedItemEvent(Ref *sender, ui::ListView::EventType type) {
    ui::ListView *listview = static_cast<ui::ListView *>(sender);
    switch (type) {
        case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_START:
            break;
        case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_END:
            log("SELECTED %ld", listview->getCurSelectedIndex());
            auto lesson = LessonScene::createScene(iList[listview->getCurSelectedIndex()], coursesID, iDList[listview->getCurSelectedIndex()], vDescription[listview->getCurSelectedIndex()], vContent[listview->getCurSelectedIndex()], sDescription, "Khoá " + std::to_string(iList[listview->getCurSelectedIndex()]));
            Director::getInstance()->replaceScene(lesson);
            break;
    }
}

void LessonList::getLessonList() {
    auto request = new network::HttpRequest();
    request->setUrl("http://150.95.105.77:8080/api/courses/getLesson/" + std::to_string(coursesID));
    request->setRequestType(network::HttpRequest::Type::GET);
    request->setResponseCallback(CC_CALLBACK_2(LessonList::onCompleteHttpRequest, this));
    network::HttpClient::getInstance()->send(request);
    request->release();
}

void LessonList::onCompleteHttpRequest(network::HttpClient *sender, network::HttpResponse *response) {
    std::vector<char> *buffer = response->getResponseData();
    log("%s", buffer->data());
    std::string str = buffer->data();
    rapidjson::Document document;
    document.Parse<0>(str.c_str());
    
    if (document.HasParseError()) {
        CCLOG("Error!");
        LessonList::getLessonList();
    } else {
        if(document.IsArray()) {
            rapidjson::Value &arr = document;
            count = arr.Size();
            if(count == 0) {
                loading2->removeFromParent();
                loading1->removeFromParent();
                bgLoading->removeFromParent();
            }
            for (rapidjson::SizeType i = 0; i < arr.Size(); i++) {
                log("IDIDID: %d", arr[i]["id"].GetInt());
                iList.push_back(i + 1);
                iDList.push_back(arr[i]["id"].GetInt());
                sName.push_back(arr[i]["name"].GetString());
                vDescription.push_back(arr[i]["description"].GetString());
                vContent.push_back(arr[i]["content"].GetString());
                
                std::string url = arr[i]["background"].GetString();
                std::replace(url.begin(), url.end(), '\\', '/');
                
                LessonList::loadImage(url);
            }
        }
    }
}

void LessonList::hideLoading() {
    loading2->removeFromParent();
    loading1->removeFromParent();
    bgLoading->removeFromParent();
    idx = 0;
}

void LessonList::loadImage(std::string str)
{
    auto request = new network::HttpRequest();
    request->setUrl(str);
    request->setRequestType(network::HttpRequest::Type::GET);
    request->setResponseCallback(CC_CALLBACK_2(LessonList::onRequestImgCompleted, this));
    network::HttpClient::getInstance()->send(request);
    request->release();
}

void LessonList::onRequestImgCompleted(network::HttpClient *sender, network::HttpResponse *response) {
    if (!response)
    {
        return;
    }
    
    if (!response->isSucceed())
    {
        ui::Button *bgItem = ui::Button::create("new-pannel-lesson-list.png");
        
        auto lblTitle = Label::createWithTTF(StringUtils::format("%s %u", "Bài ", iList.at(idx)), "fonts/Pacifico.ttf", 10);
        lblTitle->setPosition(Vec2(bgItem->getContentSize().width / 2, bgItem->getContentSize().height / 2 + 34));
        lblTitle->setTextColor(Color4B(53.0, 53.0, 53.0, 255.0));
        bgItem->addChild(lblTitle);
        
        auto lblSubTitle = Label::createWithTTF(sName.at(idx), "fonts/arial.ttf", 8);
        lblSubTitle->setPosition(Vec2(bgItem->getContentSize().width / 2, bgItem->getContentSize().height / 4 - 5));
        lblSubTitle->setTextColor(Color4B(53.0, 53.0, 53.0, 255.0));
        bgItem->addChild(lblSubTitle);
        
        listView->pushBackCustomItem(bgItem);
        idx++;
        if(idx >= count) {
            LessonList::hideLoading();
        }
        return;
    }
    
    ui::Button *bgItem = ui::Button::create("new-pannel-lesson-list.png");
    
    auto lblTitle = Label::createWithTTF(StringUtils::format("%s %u", "Bài ", iList.at(idx)), "fonts/Pacifico.ttf", 10);
    lblTitle->setPosition(Vec2(bgItem->getContentSize().width / 2, bgItem->getContentSize().height / 2 + 34));
    lblTitle->setTextColor(Color4B(53.0, 53.0, 53.0, 255.0));
    bgItem->addChild(lblTitle);
    
    std::vector<char> *buffer = response->getResponseData();
    Image * image = new  Image ();
    image-> initWithImageData ( reinterpret_cast<const unsigned char*>(&(buffer->front())), buffer->size());
    Texture2D * texture = new  Texture2D ();
    texture-> initWithImage (image);
    Sprite * sprite = Sprite :: createWithTexture (texture);
    sprite->setPosition(Vec2(bgItem->getContentSize().width/2, bgItem->getContentSize().height / 2));
    sprite->setContentSize(Size(bgItem->getContentSize().width/3.5, bgItem->getContentSize().width/3.5));
    bgItem->addChild(sprite);
    
    std::istringstream iss(sName.at(idx));
    std::vector<std::string> results(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>());
    std::string str = "";
    std::string strOneLine = "";
    for (int i = 0; i < results.size(); i++) {
        if(strOneLine.length() < 20 && i < results.size() - 1) {
            strOneLine = strOneLine + " " + results[i].c_str();
        } else {
            if(i == results.size() - 1) {
                strOneLine = strOneLine + " " + results[i].c_str();
            }
            str = str + strOneLine + "\n";
            strOneLine = "";
        }
    }
    
    auto lblSubTitle = Label::createWithTTF(str, "fonts/arial.ttf", 8);
    lblSubTitle->setAnchorPoint(Vec2(0.5, 1));
    lblSubTitle->setPosition(Vec2(bgItem->getContentSize().width / 2, bgItem->getContentSize().height / 4 + 2));
    lblSubTitle->setTextColor(Color4B(53.0, 53.0, 53.0, 255.0));
    bgItem->addChild(lblSubTitle);
    
    listView->pushBackCustomItem(bgItem);
    idx++;
    if(idx >= count) {
        LessonList::hideLoading();
    }
}

void LessonList::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
    #endif
}
