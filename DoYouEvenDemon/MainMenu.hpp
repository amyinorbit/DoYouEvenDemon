//
//  MainMenu.hpp
//  DoYouEvenDemon
//
//  Created by Amy Parent on 31/01/2016.
//  Copyright (c) 2016 PixelSpark. All rights reserved.
//
#ifndef MainMenu_hpp
#define MainMenu_hpp

#include <Meteor/Meteor.h>
using namespace Meteor;

class MainMenu : public Scene, public ControlsDelegate {
public:
    
    // MARK: Scene Cleanup
    
    virtual ~MainMenu();
    
    // MARK: Game management and logic
    
    void didMoveToView() override;
    
    void update(double delta) override;
    
    // MARK: Control Delegate
    
    void keyDown(Key aKey) override;
    
private:
    
};

#endif /* MainMenu_hpp */