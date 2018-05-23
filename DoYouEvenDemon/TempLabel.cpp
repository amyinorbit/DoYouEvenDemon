//
//  TempLabel.cpp
//  DoYouEvenDemon
//
//  Created by Amy Parent on 31/01/2016.
//  Copyright (c) 2016 PixelSpark. All rights reserved.
//

#include "TempLabel.hpp"

TempLabel::TempLabel(const std::string& text, int fontsize) :
LabelNode("assets/kenpixel_mini.ttf") {
    // initialise your game object here.
    setZPosition(100);
    setFontColor(Color::whiteColor);
    setFontSize(fontsize);
    setText(text);
    setVerticalAlignmentMode(VerticalAlignmentMode::Center);
    setHorizontalAlignmentMode(HorizontalAlignmentMode::Center);
    runAction(Action::fadeAlphaTo(0.f, 1.f), "fade");
    runAction(Action::sequence({
        Action::moveBy({0, -30}, 1.f, Ease::outSine),
        Action::removeFromParent()
    }), "bubble");
}

TempLabel::~TempLabel() {
    // cleanup when the node is deleted.
}