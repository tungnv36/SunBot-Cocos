#include "CoursesScene.h"
#include "SimpleAudioEngine.h"
#include "json/document.h"
#include "json/rapidjson.h"
#include "VideoScene.h"
#include "LessonListScene.h"
#include <string>

ui::ListView *listView;
int idx = 0;
int count = 0;
std::vector<int> iList;
std::vector<int> iDList;
std::vector<std::string> sName;
std::vector<std::string> sDes;

Sprite *loading1;
Sprite *loading2;
Sprite *bgLoading;

Scene* Courses::createScene()
{
    return Courses::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Courses::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto bg = Sprite::create("new-bg-sunbot.png");
    bg->setContentSize(visibleSize);
    bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    this->addChild(bg);
    
//    auto bottomPannel = Sprite::create("pannel-bottom.png");
//    bottomPannel->setContentSize(Size(visibleSize.width, bottomPannel->getContentSize().height * visibleSize.width / bottomPannel->getContentSize().width));
//    bottomPannel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + bottomPannel->getContentSize().height / 2));
//    this->addChild(bottomPannel);
    
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
    
    auto lblTitle = Label::createWithTTF("Sunbot xin chào!", "fonts/Pacifico.ttf", 13);
    lblTitle->setAnchorPoint(Vec2(0, 0));
    lblTitle->setPosition(Vec2(20, pannelDes->getContentSize().height / 2 - 5));
    lblTitle->setTextColor(Color4B::BLACK);
    pannelDes->addChild(lblTitle);
    
    auto lblSubTitle = Label::createWithTTF("Chúng ta cùng bắt đầu thử thách nhé!", "fonts/arial.ttf", 7);
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
    
    listView = ui::ListView::create();
    listView->setDirection(ui::ScrollView::Direction::HORIZONTAL);
    listView->setClippingEnabled(false);
    listView->setAnchorPoint(Vec2(0, 0));
    listView->setContentSize(Size(visibleSize.width - 60, visibleSize.height - visibleSize.height / 3));
    listView->setPosition(Vec2(origin.x + 30, origin.y + visibleSize.height / 3));
    
    listView->setItemsMargin(20);
    listView->setBottomPadding(20);
    
//    float scale = visibleSize.width / (3.5 * listView->getContentSize().width);
//    listView->setScale(2, 1);
    
    listView->addEventListener(CC_CALLBACK_2(Courses::selectedItemEvent, this));
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
    
    Courses::getCourses();
    
    return true;
}

void Courses::selectedItemEvent(Ref *sender, ui::ListView::EventType type) {
    ui::ListView *listview = static_cast<ui::ListView *>(sender);
    switch (type) {
        case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_START:
            break;
        case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_END:
            log("SELECTED %ld", listview->getCurSelectedIndex());
            auto lessonList = LessonList::createScene(iDList[listview->getCurSelectedIndex()], "Khoá " + std::to_string(iList[listview->getCurSelectedIndex()]), sDes[listview->getCurSelectedIndex()]);
            Director::getInstance()->replaceScene(lessonList);
            break;
    }
}

void Courses::getCourses() {
    auto request = new network::HttpRequest();
    request->setUrl("http://150.95.105.77:8080/api/courses/getcourses");
    request->setRequestType(network::HttpRequest::Type::GET);
    request->setResponseCallback(CC_CALLBACK_2(Courses::onCompleteHttpRequest, this));
    network::HttpClient::getInstance()->send(request);
    request->release();
}

void Courses::onCompleteHttpRequest(network::HttpClient *sender, network::HttpResponse *response) {
    std::vector<char> *buffer = response->getResponseData();
    log("%s", buffer->data());
    std::string str = buffer->data();
    rapidjson::Document document;
    document.Parse<0>(str.c_str());
    
    if (document.HasParseError()) {
        CCLOG("Error!");
        Courses::getCourses();
    } else {
        if(document.IsArray()) {
            rapidjson::Value &arr = document;
            count = arr.Size();
            if(count == 0) {
                Courses::hideLoading();
            }
            for (rapidjson::SizeType i = 0; i < arr.Size(); i++) {
                iList.push_back(i + 1);
                iDList.push_back(arr[i]["id"].GetInt());
                sName.push_back(arr[i]["name"].GetString());
                sDes.push_back(arr[i]["description"].GetString());
                
                std::string url = arr[i]["background"].GetString();
                std::replace(url.begin(), url.end(), '\\', '/');
                
                Courses::loadImage(url);
            }
        }
    }
}

bool replace(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

void replaceAll(std::string& str, const std::string& from, const std::string& to) {
    if(from.empty())
        return;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}

void Courses::hideLoading() {
    loading2->removeFromParent();
    loading1->removeFromParent();
    bgLoading->removeFromParent();
    idx = 0;
}

void Courses::loadImage(std::string str)
{
    auto request = new network::HttpRequest();
    request->setUrl(str);
    request->setRequestType(network::HttpRequest::Type::GET);
    request->setResponseCallback(CC_CALLBACK_2(Courses::onRequestImgCompleted, this));
    network::HttpClient::getInstance()->send(request);
    request->release();
}

void Courses::onRequestImgCompleted(network::HttpClient *sender, network::HttpResponse *response) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    if (!response)
    {
        return;
    }

    if (!response->isSucceed())
    {
        ui::Button *bgItem = ui::Button::create("new-pannel-course.png");
        
//        float scale = visibleSize.width / (3.5 * bgItem->getContentSize().width);
//        bgItem->setScale(scale);
        
        auto lblTitle = Label::createWithTTF(StringUtils::format("%s %u", "Khoá ", iList.at(idx)), "fonts/Pacifico.ttf", 10);
        lblTitle->setPosition(Vec2(bgItem->getContentSize().width / 2, bgItem->getContentSize().height / 2 + 32));
        lblTitle->setTextColor(Color4B(53.0, 53.0, 53.0, 255.0));
        bgItem->addChild(lblTitle);
        
        auto lblSubTitle = Label::createWithTTF(sName.at(idx), "fonts/arial.ttf", 8);
        lblSubTitle->setPosition(Vec2(bgItem->getContentSize().width / 2, bgItem->getContentSize().height / 4 - 5));
        lblSubTitle->setTextColor(Color4B(53.0, 53.0, 53.0, 255.0));
        bgItem->addChild(lblSubTitle);
        
        listView->pushBackCustomItem(bgItem);
        idx++;
        if(idx >= count) {
            Courses::hideLoading();
        }
        return;
    }

    ui::Button *bgItem = ui::Button::create("new-pannel-course.png");
    
//    float scale = visibleSize.width / (3.5 * bgItem->getContentSize().width);
//    bgItem->setScale(scale);

    auto lblTitle = Label::createWithTTF(StringUtils::format("%s %u", "Khoá ", iList.at(idx)), "fonts/Pacifico.ttf", 10);
    lblTitle->setPosition(Vec2(bgItem->getContentSize().width / 2, bgItem->getContentSize().height / 2 + 32));
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
        Courses::hideLoading();
    }
}

void Courses::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
