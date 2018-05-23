//
//  SplashScreen.cpp
//  DoYouEvenDemon
//
//  Created by Amy Parent on 31/01/2016.
//  Copyright (c) 2016 PixelSpark. All rights reserved.
//
#include "SplashScreen.hpp"
#include "MainMenu.hpp"

SplashScreen::~SplashScreen() {
    // cleanup when the scene is deleted
}

void SplashScreen::didMoveToView() {
    // called when the scene is entering the view
    Controls::setDelegate(this);
    addChild(alloc<SpriteNode>("assets/img/pixelspark.png"));
    
    auto space = alloc<LabelNode>("assets/kenpixel_mini.ttf");
    space->setVerticalAlignmentMode(LabelNode::VerticalAlignmentMode::Center);
    space->setFontSize(16);
    space->setText("PixelSpark #GGJ16");
    space->setY(size().height/2 - 30);
    addChild(space);
    
    runAction(Action::sequence({
        Action::waitForDuration(2.f),
        Action::runBlock([this]{
            goToMain();
        }),
    }), "fadeIn");
}

// MARK: ControlDelegate

void SplashScreen::keyDown(Meteor::Key aKey) {
    // called when a key press occurs
    stopAllActions();
    goToMain();
}

void SplashScreen::goToMain() {
    Game::instance().presentScene(alloc<MainMenu>(), Transition::fadeWithDuration(1.f, Ease::linear));
}