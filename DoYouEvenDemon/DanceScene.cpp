//
//  DanceScene.cpp
//  DoYouEvenDemon
//
//  Created by Amy Parent on 30/01/2016.
//  Copyright (c) 2016 PixelSpark. All rights reserved.
//
#include "DanceScene.hpp"
#include "BeatController.hpp"
#include "Messenger.hpp"
#include "Arrow.hpp"
#include "TempLabel.hpp"
#include "MainMenu.hpp"
#include "EndScene.hpp"
#include <ctime>

const char* levels[3] = {
    "assets/sound/l1.wav",
    "assets/sound/l2.wav",
    "assets/sound/l3.wav"
};

static int level = 2;


static vec2 POS(int which) {
    return vec2((which * 60) - 90,
                (which>0 && which<3) ? 60 : 40);
}

DanceScene::DanceScene() {
    
    _combo = 0;
    _score = 0;
    _gameover = false;
    
    setZSort(true);
    
    auto bg = alloc<SpriteNode>("assets/img/background.png");
    bg->setZPosition(LayerBackground);
    addChild(bg);
    
    // Add the observers
    Messenger::addObserver(kBeatNotification,
                           "dance",
                           std::bind(&DanceScene::onBeat, this));
    Messenger::addObserver(kSongFinishedNotification,
                           "dance",
                           std::bind(&DanceScene::onLoop, this));
    Messenger::addObserver(kAcceptingNoteNotification,
                           "dance",
                           std::bind(&DanceScene::onNextNotes, this));
    Messenger::addObserver(kValidBeatNotification,
                           "dance",
                           std::bind(&DanceScene::onScore, this));
    Messenger::addObserver(kFailedBeatNotification,
                           "dance",
                           std::bind(&DanceScene::onFail, this));
    
    _main = alloc<SpriteNode>("assets/img/demon.png");
    _main->setClipRect({0, 0, 64, 64});
    _main->setY(10);
    _main->setZPosition(LayerBoss);
    _main->runAction(Action::animate({0, 1}, 60.f/140.f), "anim");
    addChild(_main);
    
    float x = (size().width/2) - 50;
    float y = (size().height/2) - 50;
    for(int i = 0; i < 2; ++i) {
        auto f = alloc<SpriteNode>("assets/img/worshipers.png");
        f->setName("follower");
        f->setClipRect({0, 0, 64, 64});
        f->setZPosition(LayerFollowers);
        f->setX(i == 0 ? -x : x);
        f->setY(y);
        f->setXScale(i == 0 ? 1 : -1);
        f->runAction(Action::animate({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12},
                                     60.f/(70.f * 13)), "bow");
        addChild(f);
    }
    
    
    for(int i = 0; i < 4; ++i) {
        auto pos = POS(i);
        // lay out target arrows
        auto node = alloc<SpriteNode>("assets/img/arrows.png");
        node->setClipRect({i * 32.f, 0, 32.f, 32.f});
        node->setX(pos.x);
        node->setY(-50);
        node->setZPosition(LayerGui);
        addChild(node);
        
        auto campfire = alloc<SpriteNode>("assets/img/fire.png");
        campfire->setClipRect({0, 0, 48, 48});
        campfire->runAction(Action::repeatForever(Action::animate({0, 1, 2, 3}, .1)), "flicker");
        campfire->setPosition(pos);
        campfire->setZPosition(LayerFire);
        addChild(campfire);
    }
    
    _scoreLabel = alloc<LabelNode>("assets/kenpixel_mini.ttf");
    _scoreLabel->setText("0");
    _scoreLabel->setFontSize(24);
    _scoreLabel->setZPosition(LayerLabels);
    _scoreLabel->setY(-size().height/2 + 10);
    addChild(_scoreLabel);
    
}

DanceScene::~DanceScene() {
    // cleanup when the scene is deleted
    Messenger::removeObserver(kBeatNotification, "dance");
    Messenger::removeObserver(kSongFinishedNotification, "dance");
    Messenger::removeObserver(kAcceptingNoteNotification, "dance");
    Messenger::removeObserver(kValidBeatNotification, "dance");
    Messenger::removeObserver(kFailedBeatNotification, "dance");
    
}

void DanceScene::didMoveToView() {
    // called when the scene is entering the view
    Controls::setDelegate(this);
    BeatController::setBPM(140);
    BeatController::setMusicFile(levels[level]);
}

void DanceScene::willMoveFromView() {
    
    Messenger::removeObserver(kBeatNotification, "dance");
    Messenger::removeObserver(kSongFinishedNotification, "dance");
    Messenger::removeObserver(kAcceptingNoteNotification, "dance");
    Messenger::removeObserver(kValidBeatNotification, "dance");
    Messenger::removeObserver(kFailedBeatNotification, "dance");
}

void DanceScene::update(double delta) {
    BeatController::update(delta);
    if(_gameover) return;
    if(_score >= 1500) {
        _gameover = true;
        BeatController::stop();
        Game::instance().presentScene(alloc<EndScene>("YOU WIN!"),
                                      Transition::fadeWithDuration(1.f, Ease::linear));
    } else if(_score < -50) {
        _gameover = true;
        BeatController::stop();
        Game::instance().presentScene(alloc<EndScene>("YOU FAIL!"),
                                      Transition::fadeWithDuration(1.f, Ease::linear));
    }
}

// MARK: ControlDelegate

void DanceScene::keyDown(Meteor::Key aKey) {
    // called when a key press occurs
    
    switch (aKey) {
        case Key::LEFT:
            _controller.validateKeys(Note::Left);
            break;
            
        case Key::RIGHT:
            _controller.validateKeys(Note::Right);
            break;
            
        case Key::UP:
            _controller.validateKeys(Note::Up);
            break;
            
        case Key::DOWN:
            _controller.validateKeys(Note::Down);
            break;
            
        case Key::PRINTSCREEN:
            Game::instance().takeScreenshot([](bool success, const std::string& str){
                if(!success) return;
                std::cout << str << std::endl;
            }, FileManager::applicationSupportDirectoryURL()+std::to_string(time(nullptr))+".png");
            break;
            
        case Key::ESCAPE:
            if(_gameover) return;
            _gameover = true;
            BeatController::stop();
            Game::instance().presentScene(alloc<MainMenu>(),
                                          Transition::fadeWithDuration(1.f, Ease::linear));
            break;
            
        default:
            break;
    }
}

// MARK: Listeners

void DanceScene::onNextNotes() {
    int which = 1 + rand() % 4;
    auto arrow = alloc<Arrow>(mask(which));
    arrow->setPosition(POS(which-1));
    arrow->startMoving(BeatController::timeToNextBeat(), -50);
    arrow->setZPosition(LayerArrows);
    addChild(arrow);
    _controller.pushNote(arrow);
    //addChild(arrow);
}

void DanceScene::onBeat() {
    static bool doit = false;
    doit = !doit;
    if(!doit) return;
    enumerateChildNodesWithName("follower", [](ARC<SpriteNode> f, bool& stop){
        f->runAction(Action::animate({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12},
                                     60.f/(70.f * 13)), "bow");
    });
    _main->runAction(Action::animate({0, 1}, 60.f/140.f), "anim");
}

void DanceScene::onLoop() {
    if(_gameover) return;
    level += 1;
    level = cap(level, 2);
    BeatController::setMusicFile(levels[level]);
}

void DanceScene::onScore() {
    int scored = 10 + _combo;
    _score += scored;
    _combo += 1;
    _scoreLabel->setText(std::to_string(_score));
    
    if(_combo >= 20) {
        _combo = 0;
        _score += 100;
        auto l = alloc<TempLabel>("COMBO!", 32);
        l->setZPosition(LayerLabels);
        addChild(l);
        AudioEngine::playSound("assets/sound/fx-combo.wav");
    } else {
        auto l = alloc<TempLabel>(std::string("+")+std::to_string(scored));
        l->setZPosition(LayerLabels);
        addChild(l);
    }
    
}

void DanceScene::onFail() {
    _combo = 0;
    _score -= 5;
    _scoreLabel->setText(std::to_string(_score));
}