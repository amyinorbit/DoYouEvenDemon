//
//  CalibrationScene.cpp
//  DoYouEvenDemon
//
//  Created by Amy Parent on 31/01/2016.
//  Copyright (c) 2016 PixelSpark. All rights reserved.
//
#include "CalibrationScene.hpp"

CalibrationScene::~CalibrationScene() {
    // cleanup when the scene is deleted
}

void CalibrationScene::didMoveToView() {
    Controls::setDelegate(this);
    _indicator = alloc<PolygonNode>(Polygon({
        vec2(0, -10),
        vec2(10, 0),
        vec2(0, 10),
        vec2(-10, 0)
    }));
    _indicator->setX(-90);
    _indicator->setStrokeColor(Color(.8f, .3f, .0f));
    
    
    _indicator->runAction(Action::repeatForever(Action::sequence({
        Action::moveToX(90, 1.f),
        Action::runBlock([this](){ this->reset(); }),
        Action::moveToX(-90, 1.f),
        Action::runBlock([this](){ this->reset(); }),
    })), "backandforth");
    
    addChild(_indicator);
    
    _bar = alloc<PolygonNode>(Polygon({
        vec2(-100, -10),
        vec2(100, -10),
        vec2(100, 10),
        vec2(-100, 10)
    }));
    addChild(_bar);
    
    _acceptInput = true;
    _process = false;
    _beatTimer = 0;
    _delay = 0;
    // called when the scene is entering the view
}

void CalibrationScene::update(double delta) {
    // called before each frame is rendered
    _beatTimer += delta;
    
    if(_process)  {
        if(_beatTimer > .3) return;
        _acceptInput = false;
        _process = false;
        _delay = (.8f*_delay) + (.2f*_beatTimer);
        std::cout << "Delay: " << _delay << std::endl;
    }
}

void CalibrationScene::reset() {
    _beatTimer = 0;
    _acceptInput = true;
}

// MARK: ControlDelegate

void CalibrationScene::keyDown(Meteor::Key aKey) {
    // called when a key press occurs
    if(aKey == Key::SPACE) {
        if(!_acceptInput) return;
        _process = true;
    }
}