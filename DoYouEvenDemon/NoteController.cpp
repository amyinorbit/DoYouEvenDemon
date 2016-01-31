//
//  NoteController.cpp
//  DoYouEvenDemon
//
//  Created by Cesar Parent on 30/01/2016.
//  Copyright © 2016 PixelSpark. All rights reserved.
//

#include "NoteController.hpp"
#include "BeatController.hpp"
#include "Messenger.hpp"

const int kAcceptingNoteNotification = mask(15) | 0x1;

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

void NoteController::pushNote(Note note) {
    _next = note;
}

void NoteController::enterWindow() {
    _inWindow = true;
}

bool NoteController::validateKeys(Note note) {
    return _inWindow && (note == _current);
}

void NoteController::exitWindow() {
    _inWindow = false;
    // Copy the next notes into the current ones.ß
    _current = _next;
    Messenger::postMessage(kAcceptingNoteNotification);
}