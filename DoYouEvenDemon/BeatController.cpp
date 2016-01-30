//
//  beatController.cpp
//  DoYouEvenDemon
//
//  Created by Cesar Parent on 30/01/2016.
//  Copyright © 2016 PixelSpark. All rights reserved.
//

#include "BeatController.hpp"
#include "Messenger.hpp"

const int kBeatControllerMask = 0x1 << 16;

const int kBeatNotification         = kBeatControllerMask | 0;
const int kOffBeatNotification      = kBeatControllerMask | 1;
const int kBeatCanceledNotification = kBeatControllerMask | 2;
const int kSongFinishedNotification = kBeatControllerMask | 3;

double BeatController::_beatTime = 0;
double BeatController::_prog = 0;
double BeatController::_beatWindow;
Uint8  BeatController::_beatProgression = 0;

void callback() {
    Messenger::postMessage(kSongFinishedNotification);
}

void BeatController::setBPM(double BPM) {
    _beatTime = 60.0 / (BPM * precision);
    _prog = 0;
    _beatProgression = 0;
}

void BeatController::setMusicFile(const std::string &file, int loops) {
    AudioEngine::playMusic(file, loops);
    Mix_HookMusicFinished(callback);
}

void BeatController::update(double delta) {
    _prog += delta;
    if (_prog >= 0) {
        _prog -= _beatTime;
        if(_beatProgression == 0) {
            Messenger::postMessage(kBeatNotification);
        }
        else {
            Messenger::postMessage(kOffBeatNotification);
        }
        _beatProgression += 1;
        _beatProgression %= precision;
    }
}

void BeatController::validateTiming() {
    
}
