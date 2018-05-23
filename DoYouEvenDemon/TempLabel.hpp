//
//  TempLabel.hpp
//  DoYouEvenDemon
//
//  Created by Amy Parent on 31/01/2016.
//  Copyright (c) 2016 PixelSpark. All rights reserved.
//
#ifndef TempLabel_hpp
#define TempLabel_hpp

#include <Meteor/Meteor.h>
using namespace Meteor;

class TempLabel : public LabelNode {
public:
    
    // MARK: mark Node Initialisation
    
    TempLabel(const std::string& text, int fontsize = 16);
    
    virtual ~TempLabel();
    
};

#endif /* TempLabel_hpp */