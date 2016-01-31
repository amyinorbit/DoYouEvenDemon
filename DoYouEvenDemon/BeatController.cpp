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
const int kStartValidNotification   = kBeatControllerMask | 4;
const int kEndValidNotification     = kBeatControllerMask | 5;

double BeatController::_beatTime = 0;
double BeatController::_prog = 0;
double BeatController::_beatWindow = 0;
double BeatController::_delay = 0;
Uint8  BeatController::_beatProgression = 0;
bool   BeatController::_inWindow = false;

void callback() {
    Messenger::postMessage(kSongFinishedNotification);
}

void BeatController::setBPM(double BPM) {
    _beatTime = 60.0 / (BPM * precision);
    _beatWindow = _beatTime / 6.0;
}

double BeatController::timeToNextBeat() {
    return -_prog + (2*_beatTime);
}

void BeatController::setMusicFile(const std::string &file, int loops) {
    AudioEngine::playMusic(file, loops);
    _prog = -_delay;
    _beatProgression = 0;
    Mix_HookMusicFinished(callback);
}

void BeatController::stop() {
    Mix_HookMusicFinished(nullptr);
    AudioEngine::stopMusic(.5f);
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
        //std::cout<<":beat:";
        std::cout.flush();
    }
    _controlEnterBuffer();
    _controlExitBuffer();
}

bool BeatController::validateTiming() {
    return _inWindow;
}

void BeatController::setDelay(double delay) {
    _delay = delay;
}

void BeatController::_controlEnterBuffer() {
    if(_inWindow) return;
    if(_prog > -_beatWindow) {
        _inWindow = true;
        Messenger::postMessage(kStartValidNotification);
    }
}

void BeatController::_controlExitBuffer() {
    if(!_inWindow) return;
    if(_prog > _beatWindow-_beatTime && _prog < -_beatWindow ) {
        _inWindow = false;
        Messenger::postMessage(kEndValidNotification);
        //std::cout<<"exit"<<std::endl;
    }
}
