//
//  EndScene.hpp
//  DoYouEvenDemon
//
//  Created by Cesar Parent on 31/01/2016.
//  Copyright (c) 2016 PixelSpark. All rights reserved.
//
#ifndef EndScene_hpp
#define EndScene_hpp

#include <Meteor/Meteor.h>
using namespace Meteor;

class EndScene : public Scene, public ControlsDelegate {
public:
    
    // MARK: Scene Cleanup
    
    EndScene(const std::string& text);
    
    virtual ~EndScene();
    
    // MARK: Game management and logic
    
    void didMoveToView() override;
    
    // MARK: Control Delegate
    
    void keyDown(Key aKey) override;
    
private:
    
};

#endif /* EndScene_hpp */