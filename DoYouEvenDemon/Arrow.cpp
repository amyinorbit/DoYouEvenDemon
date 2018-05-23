//
//  Arrow.cpp
//  DoYouEvenDemon
//
//  Created by Amy Parent on 31/01/2016.
//  Copyright (c) 2016 PixelSpark. All rights reserved.
//

#include "Arrow.hpp"

static const int kMovingArrow = 1;
static const int kValidArrow = 2;


Uint8 setbit(Uint8 aMask) {
    Uint8 bit = 0;
    while(!(aMask & 0x1)) {
        aMask = aMask >> 1;
        bit += 1;
    }
    return bit;
}

const ARC<Arrow> Arrow::None = ARC<Arrow>(nullptr);

Arrow::Arrow(Uint8 which) :
SpriteNode("assets/img/arrows.png") {
    
    setClipRect({setbit(which) * 32.f, kMovingArrow * 32.f, 32, 32});
    _done = false;
    _value = (Note)which;
    
}

Arrow::~Arrow() {
    // cleanup when the node is deleted.
}

void Arrow::startMoving(double time, float where) {
    runAction(Action::moveToY(where, time), "move");
}

void Arrow::valid() {
    if(_done) return;
    _done = true;
    AudioEngine::playSound("assets/sound/fx-success.wav");
    stopAction("move");
    auto clip = clipRect();
    clip.y = kValidArrow * 32.f;
    setClipRect(clip);
    runAction(Action::fadeAlphaTo(0, .5f), "fade");
    runAction(Action::scaleBy(5.f, 5.f, .5), "pop");
    runAction(Action::sequence({
        Action::waitForDuration(.6f),
        Action::removeFromParent()
    }), "remove");
}

void Arrow::invalid() {
    if(_done) return;
    _done = true;
    AudioEngine::playSound("assets/sound/fx-fail.wav");
    stopAction("move");
    runAction(Action::sequence({
        Action::moveToX(-1000, 1.f),
        Action::removeFromParent()
    }), "bye");
}
