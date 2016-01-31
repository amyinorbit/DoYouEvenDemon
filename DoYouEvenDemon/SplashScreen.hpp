//
//  SplashScreen.hpp
//  DoYouEvenDemon
//
//  Created by Cesar Parent on 31/01/2016.
//  Copyright (c) 2016 PixelSpark. All rights reserved.
//
#ifndef SplashScreen_hpp
#define SplashScreen_hpp

#include <Meteor/Meteor.h>
using namespace Meteor;

class SplashScreen : public Scene, public ControlsDelegate {
public:
    
    // MARK: Scene Cleanup
    
    virtual ~SplashScreen();
    
    // MARK: Game management and logic
    
    void didMoveToView() override;
    
    // MARK: Control Delegate
    
    void keyDown(Key aKey) override;
    
private:
    
    void goToMain();
};

#endif /* SplashScreen_hpp */