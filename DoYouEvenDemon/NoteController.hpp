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
#include <deque>
#include "defines.h"

extern const int kAcceptingNoteNotification;

struct Note {
    static const Uint8 Left     = mask(1);
    static const Uint8 Right    = mask(2);
    static const Uint8 Up       = mask(3);
    static const Uint8 Down     = mask(4);
    
    Note(Uint8 keys = 0) {
        value = keys & all;
    }
    
    bool validateKeys(Uint8 keys) {
        return !(keys ^ value);
    }
    
    bool operator==(const Note& other) const {
        return (value == other.value);
    }
    
private:
    
    static const Uint8 all = Left | Right | Up | Down;
    Uint8 value;
    
};



struct NoteController final {
    
    NoteController();
    
    ~NoteController();
    
    bool validateKeys(Note note);
    
    void pushNote(Note note);
    
private:
    
    void enterWindow();
    
    void beat();
    
    void exitWindow();
    
    Note _current;
    
    Note _next;
    
    bool _inWindow;
    
};

#endif /* NoteController_hpp */
