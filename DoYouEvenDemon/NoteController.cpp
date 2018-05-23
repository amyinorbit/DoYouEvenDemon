//
//  NoteController.cpp
//  DoYouEvenDemon
//
//  Created by Amy Parent on 30/01/2016.
//  Copyright © 2016 PixelSpark. All rights reserved.
//

#include "NoteController.hpp"
#include "BeatController.hpp"
#include "Messenger.hpp"

const int kAcceptingNoteNotification    = mask(15) | mask(1);
const int kComboNotification            = mask(15) | mask(2);
const int kValidBeatNotification        = mask(15) | mask(3);
const int kFailedBeatNotification       = mask(15) | mask(4);

NoteController::NoteController() : _inWindow(false) {
    // register observers
    Messenger::addObserver(kStartValidNotification,
                           "note",
                           std::bind(&NoteController::enterWindow, this));
    Messenger::addObserver(kEndValidNotification,
                           "note",
                           std::bind(&NoteController::exitWindow, this));
}

NoteController::~NoteController() {
    Messenger::removeObserver(kStartValidNotification, "note");
    Messenger::removeObserver(kEndValidNotification, "note");
}


void NoteController::pushNote(ARC<Arrow> note) {
    
    _after = note;
    
    //_after = note;
}

void NoteController::enterWindow() {
    _inWindow = true;
}

bool NoteController::validateKeys(Note note) {
    if(!_inWindow) return false;
    if(_current == Arrow::None) return false;
    _validBeat = (note == _current->value());
    if(_validBeat) {
        _current->valid();
    } else {
        _current->invalid();
    }
    return _validBeat;
}

void NoteController::exitWindow() {
    _inWindow = false;
    
    if(_current != Arrow::None && !_validBeat) {
        Messenger::postMessage(kFailedBeatNotification);
        _current->invalid();
    }
    else if(_current != Arrow::None && _validBeat) {
        Messenger::postMessage(kValidBeatNotification);
        _current->valid();
    }
    
    _current = _next;
    _next = _after;
    _after = Arrow::None;
    _validBeat = false;
    Messenger::postMessage(kAcceptingNoteNotification);
}