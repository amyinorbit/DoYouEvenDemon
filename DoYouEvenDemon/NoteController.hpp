//
//  NoteController.hpp
//  DoYouEvenDemon
//
//  Created by Cesar Parent on 30/01/2016.
//  Copyright © 2016 PixelSpark. All rights reserved.
//

#ifndef NoteController_hpp
#define NoteController_hpp

#include <stdio.h>
#include <Meteor/Meteor.h>
#include <unordered_map>
#include "defines.h"
#include "Arrow.hpp"

extern const int kAcceptingNoteNotification;
extern const int kComboNotification;
extern const int kValidBeatNotification;
extern const int kFailedBeatNotification;



struct NoteController final {
    
    NoteController();
    
    ~NoteController();
    
    bool validateKeys(Note note);
    
    void pushNote(ARC<Arrow> note);
    
private:
    
    void enterWindow();
    
    void beat();
    
    void exitWindow();
    
    ARC<Arrow> _current;
    
    ARC<Arrow> _next;
    
    ARC<Arrow> _after;
    
    bool _inWindow;
    
    bool _validBeat;
    
};

#endif /* NoteController_hpp */
