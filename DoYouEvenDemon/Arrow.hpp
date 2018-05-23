//
//  Arrow.hpp
//  DoYouEvenDemon
//
//  Created by Amy Parent on 31/01/2016.
//  Copyright (c) 2016 PixelSpark. All rights reserved.
//
#ifndef Arrow_hpp
#define Arrow_hpp

#include <Meteor/Meteor.h>
#include "defines.h"
using namespace Meteor;

enum class Note: Uint8 {
    Left = mask(1),
    Up = mask(2),
    Down = mask(3),
    Right = mask(4),
};

class Arrow : public SpriteNode {
public:
    
    static const ARC<Arrow> None;
    
    // MARK: mark Node Initialisation
    
    Arrow(Uint8 which);
    
    virtual ~Arrow();
    
    Note value() const {
        return _value;
    }
    
    void startMoving(double time, float where);
    
    void valid();
    
    void invalid();
    
private:
    
    bool _done;
    
    Note _value;
    
};

#endif /* Arrow_hpp */