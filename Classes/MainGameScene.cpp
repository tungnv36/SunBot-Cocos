#include "MainGameScene.h"
#include "SimpleAudioEngine.h"
#include "json/document.h"
#include "json/rapidjson.h"
#include "LessonListScene.h"
#include "LessonScene.h"

USING_NS_CC;
USING_NS_CC_EXT;

int lesIndex;
int lesCoursesId;
int lesLessonId;
std::string lesDescription;
std::string lessContent;
std::string lescDescription;
std::string lescName;
int level = 1;

int startPoint = 1;
int endPoint = 2;
int objectPoint = 3;

std::string mDirection = "T";
Point *mFirstPoint;

Sprite *bgMainGame;
Sprite *bgGameBoard;
Sprite *gameBoard;
Sprite *spSunBot;

Scene* MainGameScene::createScene(int index, int coursesId, int lessonId, std::string description, std::string sContent, std::string cDescription, std::string cName)
{
    lesIndex = index;
    lesCoursesId = coursesId;
    lesLessonId = lessonId;
    lesDescription = description;
    lessContent = sContent;
    lescDescription = cDescription;
    lescName = cName;
    
    return MainGameScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MainGameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto btBack = ui::Button::create("new-delete.png");
    btBack->setScale(20 / btBack->getContentSize().width);
    btBack->setPosition(Vec2(origin.x + visibleSize.width - 15, origin.y + visibleSize.height - 40));
    btBack->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type) {
            case ui::Widget::TouchEventType::BEGAN:
                CCLOG("BEGAN");
                break;
            case ui::Widget::TouchEventType::ENDED:
                MainGameScene::clearGame();
                auto lesson = LessonScene::createScene(lesIndex, lesCoursesId, lesLessonId, lesDescription, lessContent, lescDescription, lescName);
                Director::getInstance()->replaceScene(lesson);
                break;
        }
    });
    this->addChild(btBack, 1);
    
    auto background = Sprite::create("new-bg-main-game.png");
    background->setContentSize(Size(visibleSize.width, visibleSize.height));
    background->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    this->addChild(background);
    
    bgMainGame = Sprite::create("new-bg-white-transparent.png");
    bgMainGame->setContentSize(Size(7 * visibleSize.width / 10, visibleSize.height));
    bgMainGame->setAnchorPoint(Vec2(0, 0));
    bgMainGame->setPosition(Vec2(origin.x, origin.y));
    this->addChild(bgMainGame);
    
    float paddingGameBoard = 20;
    bgGameBoard = Sprite::create("new-green-bg-2.png");
    bgGameBoard->setContentSize(Size(7 * visibleSize.width / 10 - paddingGameBoard, visibleSize.height - 2 * paddingGameBoard));
    bgGameBoard->setAnchorPoint(Vec2(0, 1));
    bgGameBoard->setPosition(Vec2(origin.x + paddingGameBoard / 2, origin.y + visibleSize.height - paddingGameBoard / 2));
    this->addChild(bgGameBoard);
    
    float wPannel = 3 * visibleSize.width / 10 - 10;
    float hPannel = visibleSize.height / 3;
    float sizeNBButton = wPannel / 5;
    
    auto lblLevel = Label::createWithTTF(StringUtils::format("%d", level), "fonts/arial.ttf", 12);
    lblLevel->setAnchorPoint(Vec2(0.5, 1));
    lblLevel->setPosition(Vec2(origin.x + bgMainGame->getContentSize().width + 5 + wPannel/2, origin.y + visibleSize.height - 10));
    lblLevel->setTextColor(Color4B::WHITE);
    this->addChild(lblLevel);
    
    auto bgPannel = Sprite::create("new-pannel-course.png");
    bgPannel->setContentSize(Size(wPannel, hPannel));
    bgPannel->setPosition(Vec2(origin.x + bgMainGame->getContentSize().width + 5 + wPannel/2, origin.y + visibleSize.height - 30 - hPannel/2));
    this->addChild(bgPannel);
    
    auto btBackLevel = ui::Button::create("new-back.png");
    
    btBackLevel->setScale(sizeNBButton / btBackLevel->getContentSize().width);
    btBackLevel->setAnchorPoint(Vec2(1, 0.5));
    btBackLevel->setPosition(Vec2(lblLevel->getPosition().x - lblLevel->getContentSize().width / 2 - 15, lblLevel->getPosition().y - lblLevel->getContentSize().height / 2));
    btBackLevel->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type) {
            case ui::Widget::TouchEventType::BEGAN:
                if(level > 1) {
                    level++;
                    MainGameScene::showLoading();
                    MainGameScene::getMap();
                }
                break;
            case ui::Widget::TouchEventType::ENDED:
                break;
        }
    });
    this->addChild(btBackLevel, 1);
    
    auto btNextLevel = ui::Button::create("new-next.png");
    
    btNextLevel->setScale(sizeNBButton / btNextLevel->getContentSize().width);
    btNextLevel->setAnchorPoint(Vec2(0, 0.5));
    btNextLevel->setPosition(Vec2(lblLevel->getPosition().x + lblLevel->getContentSize().width / 2 + 15, lblLevel->getPosition().y - lblLevel->getContentSize().height / 2));
    btNextLevel->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type) {
            case ui::Widget::TouchEventType::BEGAN:
                level++;
                MainGameScene::showLoading();
                MainGameScene::getMap();
                break;
            case ui::Widget::TouchEventType::ENDED:
                break;
        }
    });
    this->addChild(btNextLevel, 1);
    
    auto lblTitle = Label::createWithTTF("Nhiệm vụ", "fonts/arial.ttf", 10);
    lblTitle->setAnchorPoint(Vec2(0.5, 1));
    lblTitle->setPosition(Vec2(bgPannel->getContentSize().width/2, bgPannel->getContentSize().height - 5));
    lblTitle->setTextColor(Color4B::BLACK);
    bgPannel->addChild(lblTitle);
    
    std::string sContent = "Nhiệm vụ nhiệm vụ nhiệm vụ nhiệm vụ nhiệm vụ nhiệm vụ nhiệm vụ nhiệm vụ nhiệm vụ nhiệm vụ nhiệm vụ nhiệm vụ nhiệm vụ nhiệm vụ";
    std::istringstream iss(sContent);
    std::vector<std::string> results(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>());
    std::string str = "";
    std::string strOneLine = "";
    
    for (int i = 0; i < results.size(); i++) {
        if(strOneLine.length() < 30 && i < results.size() - 1) {
            strOneLine = strOneLine + " " + results[i].c_str();
        } else {
            if(i == results.size() - 1) {
                strOneLine = strOneLine + " " + results[i].c_str();
            }
            str = str + strOneLine + "\n";
            strOneLine = "";
        }
    }
    
    auto lblContent = Label::createWithTTF(str, "fonts/arial.ttf", 8);
    lblContent->setAnchorPoint(Vec2(0.5, 1));
    lblContent->setPosition(Vec2(bgPannel->getContentSize().width/2, lblTitle->getPosition().y - 15));
    lblContent->setTextColor(Color4B::BLACK);
    bgPannel->addChild(lblContent);
    
    float sizeButtonSmall = wPannel / 5;
    float sizeMoveButton = wPannel / 5;
    
    auto btEarse = ui::Button::create("new-earse.png");
    
    btEarse->setScale(sizeButtonSmall / btEarse->getContentSize().width);
    btEarse->setAnchorPoint(Vec2(0, 1));
    btEarse->setPosition(Vec2(bgPannel->getPosition().x - bgPannel->getContentSize().width / 2 + sizeButtonSmall / 2, bgPannel->getPosition().y - bgPannel->getContentSize().height / 2 - 10));
    btEarse->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type) {
            case ui::Widget::TouchEventType::BEGAN:
                CCLOG("BEGAN");
                break;
            case ui::Widget::TouchEventType::ENDED:
                break;
        }
    });
    this->addChild(btEarse, 1);
    
    auto btClear = ui::Button::create("new-delete.png");
    btClear->setScale(sizeButtonSmall / btClear->getContentSize().width);
    btClear->setAnchorPoint(Vec2(0.5, 1));
    btClear->setPosition(Vec2(bgPannel->getPosition().x, bgPannel->getPosition().y - bgPannel->getContentSize().height / 2 - 10));
    btClear->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type) {
            case ui::Widget::TouchEventType::BEGAN:
                CCLOG("BEGAN");
                break;
            case ui::Widget::TouchEventType::ENDED:
                MainGameScene::clearGame();
                break;
        }
    });
    this->addChild(btClear, 1);
    
    auto btPause = ui::Button::create("new-pause.png");
    btPause->setScale(sizeButtonSmall / btPause->getContentSize().width);
    btPause->setAnchorPoint(Vec2(1, 1));
    btPause->setPosition(Vec2(bgPannel->getPosition().x + bgPannel->getContentSize().width / 2 - sizeButtonSmall / 2, bgPannel->getPosition().y - bgPannel->getContentSize().height / 2 - 10));
    btPause->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type) {
            case ui::Widget::TouchEventType::BEGAN:
                CCLOG("BEGAN");
                break;
            case ui::Widget::TouchEventType::ENDED:
                break;
        }
    });
    this->addChild(btPause, 1);
    
    //add botton move
    auto btDown = ui::Button::create("new-down.png");
    btDown->setScale(sizeMoveButton / btDown->getContentSize().width);
    btDown->setPosition(Vec2(btClear->getPosition().x, origin.y + sizeMoveButton));
    btDown->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type) {
            case ui::Widget::TouchEventType::BEGAN:
                CCLOG("BEGAN");
                break;
            case ui::Widget::TouchEventType::ENDED:
                vAction.push_back("B");
                //Lấy vị trí trước
                auto oldPoint = mFirstPoint;
                if(vPoint.size() > 0) {
                    oldPoint = &vPoint.at(vPoint.size() - 1);
                }
                //Add point theo hướng
                float x = 0;
                float y = 0;
                if(mDirection == "T") {
                    x = oldPoint->x;
                    y = oldPoint->y - 1;
                } else if(mDirection == "B") {
                    x = oldPoint->x;
                    y = oldPoint->y + 1;
                } else if(mDirection == "L") {
                    x = oldPoint->x + 1;
                    y = oldPoint->y;
                } else {//R
                    x = oldPoint->x - 1;
                    y = oldPoint->y;
                }
                if(MainGameScene::getTypeByIndexOfCell(y * numberOfRow + x) == objectPoint || x < 0 || x > numberOfColumn - 1 || y < 0 || y > numberOfRow - 1) {
                    vPointBreak.push_back(*new Point(Vec2(x, y)));
                    x = oldPoint->x;
                    y = oldPoint->y;
                    vPoint.push_back(*new Point(Vec2(x, y)));
                } else {
                    vPointBreak.push_back(*new Point(Vec2(x, y)));
                    vPoint.push_back(*new Point(Vec2(x, y)));
                }
                break;
        }
    });
    this->addChild(btDown, 1);
    
    auto btPlay = ui::Button::create("new-play.png");
    btPlay->setScale(sizeButtonSmall / btPlay->getContentSize().width);
    btPlay->setPosition(Vec2(btClear->getPosition().x, btDown->getPosition().y + 3 + sizeMoveButton));
    btPlay->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type) {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                MainGameScene::runSunBot();
                break;
        }
    });
    this->addChild(btPlay, 1);
    
    auto btUp = ui::Button::create("new-up.png");
    btUp->setScale(sizeMoveButton / btUp->getContentSize().width);
    btUp->setPosition(Vec2(btClear->getPosition().x, btPlay->getPosition().y + 3 + sizeMoveButton));
    btUp->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type) {
            case ui::Widget::TouchEventType::BEGAN:
                CCLOG("BEGAN");
                break;
            case ui::Widget::TouchEventType::ENDED:
                vAction.push_back("T");
                //Lấy vị trí trước
                auto oldPoint = mFirstPoint;
                if(vPoint.size() > 0) {
                    oldPoint = &vPoint.at(vPoint.size() - 1);
                }
                //Add point theo hướng
                float x = 0;
                float y = 0;
                if(mDirection == "T") {
                    x = oldPoint->x;
                    y = oldPoint->y + 1;
                } else if(mDirection == "B") {
                    x = oldPoint->x;
                    y = oldPoint->y - 1;
                } else if(mDirection == "L") {
                    x = oldPoint->x - 1;
                    y = oldPoint->y;
                } else {//R
                    x = oldPoint->x + 1;
                    y = oldPoint->y;
                }
                if(MainGameScene::getTypeByIndexOfCell(y * numberOfRow + x) == objectPoint || x < 0 || x > numberOfColumn - 1 || y < 0 || y > numberOfRow - 1) {
                    vPointBreak.push_back(*new Point(Vec2(x, y)));
                    x = oldPoint->x;
                    y = oldPoint->y;
                    vPoint.push_back(*new Point(Vec2(x, y)));
                } else {
                    vPointBreak.push_back(*new Point(Vec2(x, y)));
                    vPoint.push_back(*new Point(Vec2(x, y)));
                }
                
                break;
        }
    });
    this->addChild(btUp, 1);
    
    auto btLeft = ui::Button::create("new-left.png");
    btLeft->setAnchorPoint(Vec2(0, 0.5));
    btLeft->setScale(sizeMoveButton / btLeft->getContentSize().width);
    btLeft->setPosition(Vec2(btEarse->getPosition().x + 5, btPlay->getPosition().y));
    btLeft->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type) {
            case ui::Widget::TouchEventType::BEGAN:
                CCLOG("BEGAN");
                break;
            case ui::Widget::TouchEventType::ENDED:
                vAction.push_back("L");
                //Lấy vị trí trước
                auto oldPoint = mFirstPoint;
                if(vPoint.size() > 0) {
                    oldPoint = &vPoint.at(vPoint.size() - 1);
                }
                vPoint.push_back(*oldPoint);
                vPointBreak.push_back(*oldPoint);
                //Xác định direction
                if(mDirection == "T") {
                    mDirection = "L";
                } else if(mDirection == "L") {
                    mDirection = "B";
                } else if(mDirection == "B") {
                    mDirection = "R";
                } else {
                    mDirection = "T";
                }
                break;
        }
    });
    this->addChild(btLeft, 1);
    
    auto btRight = ui::Button::create("new-right.png");
    btRight->setAnchorPoint(Vec2(1, 0.5));
    btRight->setScale(sizeMoveButton / btRight->getContentSize().width);
    btRight->setPosition(Vec2(btPause->getPosition().x - 5, btPlay->getPosition().y));
    btRight->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type) {
            case ui::Widget::TouchEventType::BEGAN:
                CCLOG("BEGAN");
                break;
            case ui::Widget::TouchEventType::ENDED:
                vAction.push_back("R");
                //Lấy vị trí trước
                auto oldPoint = mFirstPoint;
                if(vPoint.size() > 0) {
                    oldPoint = &vPoint.at(vPoint.size() - 1);
                }
                vPoint.push_back(*oldPoint);
                vPointBreak.push_back(*oldPoint);
                //Xác định direction
                if(mDirection == "T") {
                    mDirection = "R";
                } else if(mDirection == "L") {
                    mDirection = "T";
                } else if(mDirection == "B") {
                    mDirection = "L";
                } else {
                    mDirection = "B";
                }
                break;
        }
    });
    this->addChild(btRight, 1);
    
    //Add game board
    float paddingGB = 10;
//    float wGameBoard = bgGameBoard->getContentSize().width - paddingGB;
//    float hGameBoard = bgGameBoard->getContentSize().height - paddingGB;
    gameBoard = Sprite::create("new-game-board.png");//new-game-board.png
    gameBoard->setContentSize(Size(bgGameBoard->getContentSize().width - paddingGB, bgGameBoard->getContentSize().height - paddingGB));
//    gameBoard->setAnchorPoint(Vec2(0, 0));
    gameBoard->setPosition(Vec2(bgGameBoard->getContentSize().width / 2, bgGameBoard->getContentSize().height / 2));
    bgGameBoard->addChild(gameBoard);
    
    MainGameScene::showLoading();
    
    MainGameScene::getMap();
    
    return true;
}

int MainGameScene::getTypeByIndexOfCell(int indexOfCell) {
    for(int i = 0; i < vIndexOfCell.size(); i++) {
        if(indexOfCell == vIndexOfCell.at(i)) {
            return vType.at(i);
        }
    }
    return 0;
}

void MainGameScene::clearGame() {
    float wSquare = gameBoard->getContentSize().width / numberOfColumn;
    float hSquare = (gameBoard->getContentSize().height) / numberOfColumn;
    spSunBot->setPosition(Vec2(mFirstPoint->x * wSquare + wSquare/2, mFirstPoint->y * hSquare + hSquare/2));
    auto actionRotate = RotateTo::create(0.1, 0);
    spSunBot->runAction(actionRotate);
    mDirection = "T";
    vAction.clear();
    vPoint.clear();
    vPointBreak.clear();
}

void MainGameScene::runSunBot() {
    Vector<FiniteTimeAction*> animFrames;
    float wSquare = gameBoard->getContentSize().width / numberOfColumn;
    float hSquare = (gameBoard->getContentSize().height) / numberOfColumn;
    for (int i = 0; i < vAction.size(); i++) {
        if(vAction.at(i) == "T") {
            float x = vPoint.at(i).x;
            float y = vPoint.at(i).y;
            float x2 = vPointBreak.at(i).x;
            float y2 = vPointBreak.at(i).y;
            if(x == x2 && y == y2) {
                auto actionMove = MoveTo::create(1, Vec2(x * wSquare + wSquare/2, y * hSquare + hSquare/2));
                animFrames.pushBack(actionMove);
            } else {
                auto actionMove1 = MoveTo::create(0.1, Vec2(x2 * wSquare + wSquare/2, y2 * hSquare + hSquare/2));
                auto actionMove2 = MoveTo::create(0.1, Vec2(x * wSquare + wSquare/2, y * hSquare + hSquare/2));
                animFrames.pushBack(actionMove1);
                animFrames.pushBack(actionMove2);
            }
        }
        if(vAction.at(i) == "B") {
            float x = vPoint.at(i).x;
            float y = vPoint.at(i).y;
            float x2 = vPointBreak.at(i).x;
            float y2 = vPointBreak.at(i).y;
            if(x == x2 && y == y2) {
                auto actionMove = MoveTo::create(1, Vec2(x * wSquare + wSquare/2, y * hSquare + hSquare/2));
                animFrames.pushBack(actionMove);
            } else {
                auto actionMove1 = MoveTo::create(0.1, Vec2(x2 * wSquare + wSquare/2, y2 * hSquare + hSquare/2));
                auto actionMove2 = MoveTo::create(0.1, Vec2(x * wSquare + wSquare/2, y * hSquare + hSquare/2));
                animFrames.pushBack(actionMove1);
                animFrames.pushBack(actionMove2);
            }
        }
        if(vAction.at(i) == "L") {
            auto actionRotate = RotateBy::create(1, -90);
            animFrames.pushBack(actionRotate);
        }
        if(vAction.at(i) == "R") {
            auto actionRotate = RotateBy::create(1, 90);
            animFrames.pushBack(actionRotate);
        }
    }
    auto callback = CallFunc::create( [this]() {
        float x = vPoint.at(vPoint.size() - 1).x;
        float y = vPoint.at(vPoint.size() - 1).y;
        if(MainGameScene::getTypeByIndexOfCell(y * numberOfRow + x) == endPoint) {
            MainGameScene::gameWin();
        } else {
            MainGameScene::gameOver();
        }
    });
    animFrames.pushBack(callback);
    auto actionSequence = Sequence::create(animFrames);
    spSunBot->runAction(actionSequence);
}

void MainGameScene::gameWin() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto gameWinSprite = Sprite::create("new-pannel-course.png");
    gameWinSprite->setContentSize(Size(visibleSize.width / 2.5, visibleSize.height / 2));
    gameWinSprite->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    
    this->addChild(gameWinSprite, 1000);
}

void MainGameScene::gameOver() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //background
    auto bgGameOver = Sprite::create("bg-transparent.png");
    bgGameOver->setContentSize(Size(visibleSize.width, visibleSize.height));
    bgGameOver->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    this->addChild(bgGameOver, 1000);
    //pannel
    auto gamePannelSprite = Sprite::create("new-pannel-lesson-list.png");
    gamePannelSprite->setContentSize(Size(visibleSize.width / 2.5, visibleSize.height / 2));
    gamePannelSprite->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y - visibleSize.height / 2));
    auto actionMove = MoveTo::create(0.2, Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    gamePannelSprite->runAction(actionMove);
    bgGameOver->addChild(gamePannelSprite);
    //text
    auto lblContent = Label::createWithTTF("Thua mất rồi", "fonts/arial.ttf", 14);
    lblContent->setPosition(Vec2(gamePannelSprite->getContentSize().width/2, gamePannelSprite->getContentSize().height/2));
    lblContent->setTextColor(Color4B::BLACK);
    gamePannelSprite->addChild(lblContent);
    auto lblContent2 = Label::createWithTTF("Cùng thử lại nhé!", "fonts/arial.ttf", 14);
    lblContent2->setPosition(Vec2(gamePannelSprite->getContentSize().width/2, lblContent->getPosition().y - lblContent->getContentSize().height));
    lblContent2->setTextColor(Color4B::BLACK);
    gamePannelSprite->addChild(lblContent2);
    //Button
    auto btRePlay = ui::Button::create("new-menu-button-2.png");
    btRePlay->setScale((gamePannelSprite->getContentSize().width/2) / btRePlay->getContentSize().width);
    btRePlay->setPosition(Vec2(gamePannelSprite->getContentSize().width / 2, 0));
    btRePlay->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type) {
            case ui::Widget::TouchEventType::BEGAN:
                CCLOG("BEGAN");
                break;
            case ui::Widget::TouchEventType::ENDED:
                bgGameOver->removeFromParent();
                gamePannelSprite->removeFromParent();
                MainGameScene::clearGame();
                break;
        }
    });
    gamePannelSprite->addChild(btRePlay);
    
    auto lblTextButton = Label::createWithTTF("Chơi lại", "fonts/arial.ttf", 5);
    lblTextButton->setPosition(Vec2(btRePlay->getContentSize().width/2, btRePlay->getContentSize().height/2));
    lblTextButton->setTextColor(Color4B::WHITE);
    btRePlay->addChild(lblTextButton);
}

void MainGameScene::getMap() {
    auto request = new network::HttpRequest();
    request->setUrl("http://150.95.105.77:8080/api/courses/getMap/" + std::to_string(lesLessonId) + "/" + std::to_string(level));
    request->setRequestType(network::HttpRequest::Type::GET);
    request->setResponseCallback(CC_CALLBACK_2(MainGameScene::onCompleteHttpRequest, this));
    network::HttpClient::getInstance()->send(request);
    request->release();
}

void MainGameScene::onCompleteHttpRequest(network::HttpClient *sender, network::HttpResponse *response) {
    std::vector<char> *buffer = response->getResponseData();
    log("DATA %s", buffer->data());
    std::string str = buffer->data();
    rapidjson::Document document;
    document.Parse<0>(str.c_str());
    
    if (document.HasParseError()) {
        CCLOG("Error!");
        MainGameScene::getMap();
    } else {
        if(document.IsObject()) {
            rapidjson::Value &arr = document["impediments"];
            count = arr.Size();
            if(count == 0) {
                MainGameScene::hideLoading();
            }
            for (rapidjson::SizeType i = 0; i < arr.Size(); i++) {
                if(arr[i]["type"].GetInt() == 1) {
                    int x = arr[i]["indexOfCell"].GetInt() % numberOfColumn;
                    int y = arr[i]["indexOfCell"].GetInt() / numberOfRow;
                    mFirstPoint = new Point(Vec2(x, y));
                }
                if(arr[i]["indexOfCell"].GetInt() != -1) {
                    vIndexOfCell.push_back(arr[i]["indexOfCell"].GetInt());
                } else {
                    vIndexOfCell.push_back(0);
                }
                vType.push_back(arr[i]["type"].GetInt());
                if(arr[i]["imageUrl"].GetStringLength() > 1) {
                    MainGameScene::loadImage(arr[i]["imageUrl"].GetString());
                } else {
                    idx++;
                    if(idx >= count) {
                        MainGameScene::hideLoading();
                        idx = 0;
                    }
                }
            }
        }
    }
}

void MainGameScene::loadImage(std::string str)
{
    auto request = new network::HttpRequest();
    request->setUrl(str);
    request->setRequestType(network::HttpRequest::Type::GET);
    request->setResponseCallback(CC_CALLBACK_2(MainGameScene::onRequestImgCompleted, this));
    network::HttpClient::getInstance()->send(request);
    request->release();
}

void MainGameScene::onRequestImgCompleted(network::HttpClient *sender, network::HttpResponse *response) {
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    float wSquare = gameBoard->getContentSize().width / numberOfColumn;
    float hSquare = (gameBoard->getContentSize().height) / numberOfColumn;// (bgGameBoard->getContentSize().height - 10) / numberOfColumn;//gameBoard->getContentSize().height
    if (!response)
    {
        return;
    }
    
    if (!response->isSucceed())
    {
        idx++;
        if(idx >= count) {
            MainGameScene::hideLoading();
            idx = 0;
        }
        return;
    }
    
    int indexOfCell = vIndexOfCell.at(idx);// - 1;
    int x = indexOfCell % numberOfColumn;
    int y = indexOfCell / numberOfRow;
    log("X: %d, Y: %d", x, y);

    if(vType.at(idx) == 4) {
        auto bgNone = Sprite::create("new-bg-none.png");
        bgNone->setContentSize(Size(wSquare, hSquare));
        bgNone->setPosition(Vec2(x * wSquare + wSquare/2, y * hSquare + hSquare/2));
        gameBoard->addChild(bgNone, 100);
    } else if(vType.at(idx) == 1) {
        std::vector<char> *buffer = response->getResponseData();
        Image * image = new  Image ();
        image-> initWithImageData ( reinterpret_cast<const unsigned char*>(&(buffer->front())), buffer->size());
        Texture2D * texture = new  Texture2D ();
        texture-> initWithImage (image);
        spSunBot = Sprite :: createWithTexture (texture);
        spSunBot->setContentSize(Size(wSquare>hSquare?hSquare:wSquare, wSquare>hSquare?hSquare:wSquare));
        spSunBot->setPosition(Vec2(x * wSquare + wSquare/2, y * hSquare + hSquare/2));
        gameBoard->addChild(spSunBot, 200);
    } else {
        std::vector<char> *buffer = response->getResponseData();
        Image * image = new  Image ();
        image-> initWithImageData ( reinterpret_cast<const unsigned char*>(&(buffer->front())), buffer->size());
        Texture2D * texture = new  Texture2D ();
        texture-> initWithImage (image);
        Sprite * sprite = Sprite :: createWithTexture (texture);
        sprite->setContentSize(Size(wSquare, hSquare));
        sprite->setPosition(Vec2(x * wSquare + wSquare/2, y * hSquare + hSquare/2));// + wSquare/2  + hSquare/2
        gameBoard->addChild(sprite, 100);
    }
    
    idx++;
    if(idx >= count) {
        MainGameScene::hideLoading();
        idx = 0;
    }
}

void MainGameScene::showLoading() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
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
    
    this->addChild(bgLoading, 10);
    this->addChild(loading2, 11);
    this->addChild(loading1, 11);
}

void MainGameScene::hideLoading() {
    loading2->removeFromParent();
    loading1->removeFromParent();
    bgLoading->removeFromParent();
}

std::vector<std::string> split(std::string strToSplit, char delimeter)
{
    std::stringstream ss(strToSplit);
    std::string item;
    std::vector<std::string> splittedStrings;
    while (std::getline(ss, item, delimeter))
    {
        splittedStrings.push_back(item);
    }
    return splittedStrings;
}

void MainGameScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
