//
//  EndScene.cpp
//  DoYouEvenDemon
//
//  Created by Cesar Parent on 31/01/2016.
//  Copyright (c) 2016 PixelSpark. All rights reserved.
//
#include "EndScene.hpp"
#include "MainMenu.hpp"

EndScene::EndScene(const std::string& text) {
    
    addChild(alloc<SpriteNode>("assets/img/background.png"));
    
    auto title = alloc<LabelNode>("assets/kenpixel_mini.ttf");
    title->setVerticalAlignmentMode(LabelNode::VerticalAlignmentMode::Center);
    title->setFontSize(32);
    title->setText(text);
    addChild(title);
    
    auto space = alloc<LabelNode>("assets/kenpixel_mini.ttf");
    space->setVerticalAlignmentMode(LabelNode::VerticalAlignmentMode::Center);
    space->setFontSize(16);
    space->setText("press space to start");
    space->setY(size().height/2 - 16);
    addChild(space);
}

EndScene::~EndScene() {
    // cleanup when the scene is deleted
}

void EndScene::didMoveToView() {
    Controls::setDelegate(this);
    // called when the scene is entering the view
}

// MARK: ControlDelegate

void EndScene::keyDown(Meteor::Key aKey) {
    // called when a key press occurs
    if(aKey != Key::SPACE) return;
    Game::instance().presentScene(alloc<MainMenu>(), Transition::fadeWithDuration(1.f, Ease::linear));
    // TODO: switch back to main menu.
}