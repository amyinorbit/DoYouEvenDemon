//
//  MainMenu.cpp
//  DoYouEvenDemon
//
//  Created by Amy Parent on 31/01/2016.
//  Copyright (c) 2016 PixelSpark. All rights reserved.
//
#include "MainMenu.hpp"
#include "DanceScene.hpp"

MainMenu::~MainMenu() {
    // cleanup when the scene is deleted
}

void MainMenu::didMoveToView() {
    Controls::setDelegate(this);
    addChild(alloc<SpriteNode>("assets/img/background.png"));
    // called when the scene is entering the view
    addChild(alloc<SpriteNode>("assets/img/logo.png"));
    /*auto title = alloc<LabelNode>("assets/kenpixel_mini.ttf");
    title->setVerticalAlignmentMode(LabelNode::VerticalAlignmentMode::Center);
    title->setFontSize(32);
    title->setText("Do you even DEMON");
    addChild(title);*/
    
    auto space = alloc<LabelNode>("assets/kenpixel_mini.ttf");
    space->setVerticalAlignmentMode(LabelNode::VerticalAlignmentMode::Center);
    space->setFontSize(16);
    space->setText("press space to start");
    space->setY(size().height/2 - 20);
    addChild(space);
    
}

void MainMenu::update(double delta) {
    // called before each frame is rendered
}

// MARK: ControlDelegate

void MainMenu::keyDown(Meteor::Key aKey) {
    // called when a key press occurs
    if(aKey != Key::SPACE) return;
    Game::instance().presentScene(alloc<DanceScene>(), Transition::fadeWithDuration(1.f, Ease::linear));
}