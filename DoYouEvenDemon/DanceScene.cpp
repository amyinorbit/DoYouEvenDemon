//
//  DanceScene.cpp
//  DoYouEvenDemon
//
//  Created by Cesar Parent on 30/01/2016.
//  Copyright (c) 2016 PixelSpark. All rights reserved.
//
#include "DanceScene.hpp"
#include "BeatController.hpp"
#include "Messenger.hpp"

const char* levels[3] = {
    "assets/sound/l1.wav",
    "assets/sound/l2.wav",
    "assets/sound/l3.wav"
};

static int level = 0;

DanceScene::~DanceScene() {
    // cleanup when the scene is deleted
    Messenger::removeObserver(kBeatNotification, "dance");
    Messenger::removeObserver(kSongFinishedNotification, "dance");
    
}

void DanceScene::didMoveToView() {
    // called when the scene is entering the view
    Controls::setDelegate(this);
    setBackgroundColor({.2f, .2f, .2f});
    _comboCounter = 0;
    
    auto follower = alloc<SpriteNode>("assets/img/worshipers.png");
    follower->setClipRect({0, 0, 64, 64});
    //follower->setScale(2.f);
    addChild(follower);
    
    static bool doit = false;
    
    Messenger::addObserver(kBeatNotification, "dance", [this, follower](){
        doit = !doit;
        if(!doit) return;
        follower->runAction(Action::animate({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12},
                                            60.f/(70.f * 13)), "bow");
    });
    
    Messenger::addObserver(kSongFinishedNotification, "dance", [this](){
        level += 1;
        level = cap(level, 2);
        BeatController::setMusicFile(levels[level]);
    });
    
    BeatController::setBPM(140);
    BeatController::setMusicFile(levels[level]);
}

void DanceScene::update(double delta) {
    BeatController::update(delta);
    // called before each frame is rendered
}

// MARK: ControlDelegate

void DanceScene::keyDown(Meteor::Key aKey) {
    // called when a key press occurs
    if(aKey == Key::SPACE) {
        if(BeatController::validateTiming()) {
            AudioEngine::playSound("assets/sound/fx-success.wav");
            _comboCounter += 1;
        } else {
            AudioEngine::playSound("assets/sound/fx-fail.wav");
            _comboCounter = 0;
        }
        
        if(_comboCounter == 10) {
            AudioEngine::playSound("assets/sound/fx-combo.wav");
        }
        std::cout << "VALID BEAT: " << BeatController::validateTiming() << std::endl;
    }
}