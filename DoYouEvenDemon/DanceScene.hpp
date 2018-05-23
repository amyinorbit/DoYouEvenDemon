//
//  DanceScene.hpp
//  DoYouEvenDemon
//
//  Created by Amy Parent on 30/01/2016.
//  Copyright (c) 2016 PixelSpark. All rights reserved.
//
#ifndef DanceScene_hpp
#define DanceScene_hpp

#include <Meteor/Meteor.h>
#include <vector>
#include "BeatController.hpp"
#include "NoteController.hpp"
using namespace Meteor;

class DanceScene : public Scene, public ControlsDelegate {
public:
    
    DanceScene();
    
    // MARK: Scene Cleanup
    
    virtual ~DanceScene();
    
    // MARK: Game management and logic
    
    void didMoveToView() override;
    
    void willMoveFromView() override;
    
    void update(double delta) override;
    
    // MARK: Control Delegate
    
    void keyDown(Key aKey) override;
    
    
private:
    
    void onNextNotes();
    
    void onBeat();
    
    void onLoop();
    
    void onScore();
    
    void onFail();
    
    ARC<SpriteNode> _main;
    
    ARC<LabelNode> _scoreLabel;
    
    NoteController _controller;
    
    Int32 _score;
    
    Uint16 _combo;
    
    bool _gameover;
    
    enum Layers {
        LayerBackground,
        LayerBoss,
        LayerArrows,
        LayerFire,
        LayerLabels,
        LayerGui,
        LayerFollowers,
    };
    
};

#endif /* DanceScene_hpp */