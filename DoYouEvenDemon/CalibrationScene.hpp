//
//  CalibrationScene.hpp
//  DoYouEvenDemon
//
//  Created by Amy Parent on 31/01/2016.
//  Copyright (c) 2016 PixelSpark. All rights reserved.
//
#ifndef CalibrationScene_hpp
#define CalibrationScene_hpp

#include <Meteor/Meteor.h>
using namespace Meteor;

class CalibrationScene : public Scene, public ControlsDelegate {
public:
    
    // MARK: Scene Cleanup
    
    virtual ~CalibrationScene();
    
    // MARK: Game management and logic
    
    void didMoveToView() override;
    
    void update(double delta) override;
    
    // MARK: Control Delegate
    
    void keyDown(Key aKey) override;
    
private:
    
    void reset();
    
    ARC<PolygonNode> _bar;
    
    ARC<PolygonNode> _indicator;
    
    double _beatTimer;
    
    bool   _acceptInput;
    
    bool   _process;
    
    double _delay;
    
};

#endif /* CalibrationScene_hpp */